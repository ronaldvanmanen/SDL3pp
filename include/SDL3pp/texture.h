// SDL3++
//
// Copyright (C) 2025 Ronald van Manen <rvanmanen@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

namespace sdl3
{
    class renderer;
}

#include <cstdint>
#include <utility>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>

#include <SDL3/SDL_render.h>

#include "error.h"
#include "pixel_format_traits.h"
#include "pixel_format.h"
#include "properties.h"
#include "renderer.h"
#include "size.h"
#include "surface.h"
#include "texture_access.h"

namespace sdl3
{
    class texture_base
    {
    protected:
        texture_base(renderer & owner, pixel_format format, texture_access access, length<int32_t> width, length<int32_t> height);
        
        texture_base(renderer & owner, property_group & properties);

        texture_base(renderer & owner, property_group && properties);

        texture_base(texture_base const& other) = delete;

        ~texture_base();

        texture_base& operator=(texture_base const& other) = delete;

    public:
        property_group properties() const;

        SDL_Texture* native_handle();

    protected:
        SDL_Texture* _native_handle;
    };

    template<typename TPixelFormat>
    class texture : public texture_base
    {
    public:
        texture(renderer & owner, texture_access access, length<std::int32_t> width, length<std::int32_t> height);

        texture(renderer & owner, texture_access access, size_2d<std::int32_t> const& size);

        texture(texture<TPixelFormat> const& other) = delete;

        texture(texture<TPixelFormat>&& other);

        texture<TPixelFormat>& operator=(texture<TPixelFormat> const& other) = delete;

        void update(surface<TPixelFormat> const& pixels);

        template<typename CallbackFunction>
        void with_lock(CallbackFunction callback);
    };

    namespace
    {
        property_group make_texture_properties(pixel_format format, color_space color_space, texture_access access, length<std::int32_t> width, length<std::int32_t> height)
        {
            property_group properties;
            properties.set(SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, static_cast<SDL_PixelFormat>(format));
            properties.set(SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, static_cast<SDL_Colorspace>(color_space));
            properties.set(SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, static_cast<SDL_TextureAccess>(access));
            properties.set(SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, quantity_cast<std::int32_t>(width));
            properties.set(SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, quantity_cast<std::int32_t>(height));
            return properties;
        }
    }

    template<typename TPixelFormat>
    texture<TPixelFormat>::texture(renderer & owner, texture_access access, length<std::int32_t> width, length<std::int32_t> height)
    : texture_base(owner, make_texture_properties(TPixelFormat::format, TPixelFormat::color_space, access, width, height))
    { }

    template<typename TPixelFormat>
    texture<TPixelFormat>::texture(renderer & owner, texture_access access, size_2d<std::int32_t> const& size)
    : texture_base(owner, make_texture_properties(TPixelFormat::format, TPixelFormat::color_space, access, size.width, size.height))
    { }

    template<typename TPixelFormat>
    texture<TPixelFormat>::texture(texture<TPixelFormat>&& other)
    : _native_handle(std::exchange(other._native_handle, nullptr))
    { }

    template<typename TPixelFormat>
    void
    texture<TPixelFormat>::update(surface<TPixelFormat> const& pixels)
    {
        throw_last_error(
            SDL_UpdateTexture(
                _native_handle,
                nullptr,
                pixels.pixels(),
                pixels.pitch() * sizeof(TPixelFormat)
            )
        );
    }

    template<typename TPixelFormat> template <typename CallbackFunction>
    void
    texture<TPixelFormat>::with_lock(CallbackFunction callback)
    {
        void* pixels;
        std::int32_t pitch;
        throw_last_error(
            SDL_LockTexture(_native_handle, nullptr, &pixels, &pitch)
        );

        surface<TPixelFormat> surface(
            _native_handle->w * px,
            _native_handle->h * px,
            static_cast<TPixelFormat*>(pixels),
            pitch / sizeof(TPixelFormat)
        );

        callback(surface);

        SDL_UnlockTexture(_native_handle);
    }
}

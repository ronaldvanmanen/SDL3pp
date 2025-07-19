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
#include "pixels.h"
#include "properties.h"
#include "renderer.h"
#include "size.h"
#include "surface.h"

namespace sdl3
{
    enum class texture_access : std::int32_t
    {
        static_access = SDL_TEXTUREACCESS_STATIC,
        streaming_access = SDL_TEXTUREACCESS_STREAMING,
        target_access = SDL_TEXTUREACCESS_TARGET
    };

    class texture_base
    {
    protected:
        texture_base(renderer & owner, pixel_format format, texture_access access, length<int32_t> width, length<int32_t> height);
        
        texture_base(renderer & owner, property_group & properties);

        texture_base(renderer & owner, property_group && properties);

        texture_base(texture_base const& other) = delete;

        ~texture_base();

        texture_base & operator=(texture_base const& other) = delete;

    public:
        property_group properties() const;

        SDL_Texture* native_handle();

    protected:
        SDL_Texture* _native_handle;
    };

    template<pixel_format P, color_space C, texture_access A>
    class texture : public texture_base
    {
    public:
        static const pixel_format format = P;

        static const color_space color_space = C;

        static const texture_access access = A;

        using pixel_type = typename pixel_color<P, C>::type;

    public:
        texture(renderer & owner, length<std::int32_t> width, length<std::int32_t> height);

        texture(renderer & owner, size_2d<std::int32_t> const& size);

        texture(texture<P, C, A> const& other) = delete;

        texture(texture<P, C, A> && other);

        texture<P, C, A> & operator=(texture<P, C, A> const& other) = delete;

        void update(surface<P, C> const& pixels);

        template<typename CallbackFunction>
        void with_lock(CallbackFunction callback);
    };

    namespace details
    {
        inline
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

    template<pixel_format P, color_space C, texture_access A>
    texture<P, C, A>::texture(renderer & owner, length<std::int32_t> width, length<std::int32_t> height)
    : texture_base(owner, details::make_texture_properties(format, color_space, access, width, height))
    { }

    template<pixel_format P, color_space C, texture_access A>
    texture<P, C, A>::texture(renderer & owner, size_2d<std::int32_t> const& size)
    : texture_base(owner, details::make_texture_properties(format, color_space, access, size.width, size.height))
    { }

    template<pixel_format P, color_space C, texture_access A>
    texture<P, C, A>::texture(texture<P, C, A> && other)
    : _native_handle(std::exchange(other._native_handle, nullptr))
    { }

    template<pixel_format P, color_space C, texture_access A>
    void
    texture<P, C, A>::update(surface<P, C> const& pixels)
    {
        throw_last_error(
            SDL_UpdateTexture(
                _native_handle,
                nullptr,
                pixels.pixels(),
                pixels.pitch()
            )
        );
    }

    template<pixel_format P, color_space C, texture_access A>
    template<typename CallbackFunction>
    void
    texture<P, C, A>::with_lock(CallbackFunction callback)
    {
        using pixel_type = surface<format>::type;

        void* pixels;
        std::int32_t pitch;
        throw_last_error(
            SDL_LockTexture(_native_handle, nullptr, &pixels, &pitch)
        );

        surface<format> surface(
            _native_handle->w * px,
            _native_handle->h * px,
            static_cast<pixel_type*>(pixels),
            pitch
        );

        callback(surface);

        SDL_UnlockTexture(_native_handle);
    }
}

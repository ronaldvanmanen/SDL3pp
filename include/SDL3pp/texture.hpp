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

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>

#include <SDL3/SDL_render.h>

#include "blend_mode.hpp"
#include "color.hpp"
#include "error.hpp"
#include "pixels.hpp"
#include "properties.hpp"
#include "size.hpp"
#include "window.hpp"

namespace sdl3
{
    enum class texture_access : std::int32_t
    {
        static_access = SDL_TEXTUREACCESS_STATIC,
        streaming_access = SDL_TEXTUREACCESS_STREAMING,
        target_access = SDL_TEXTUREACCESS_TARGET
    };

    template <pixel_format P, texture_access A, color_space C = default_color_space<P>()>
        requires(is_compatible_color_space<P, C>())
    class texture
    {
    public:
        static const pixel_format format = P;

        static const color_space color_space = C;

        static const texture_access access = A;

        using pixel_type = typename pixel_color<P, C>::type;

    public:
        texture(renderer & owner, length<std::int32_t> width, length<std::int32_t> height)
        : _native_handle(nullptr)
        {
            property_group properties;
            properties.set(SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, static_cast<SDL_PixelFormat>(format));
            properties.set(SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, static_cast<SDL_Colorspace>(color_space));
            properties.set(SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, static_cast<SDL_TextureAccess>(access));
            properties.set(SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, quantity_cast<std::int32_t>(width));
            properties.set(SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, quantity_cast<std::int32_t>(height));
            _native_handle = check_pointer(
                SDL_CreateTextureWithProperties(owner.native_handle(), properties.native_handle())
            );
        }

        texture(renderer & owner, size_2d<std::int32_t> const & size)
        : _native_handle(nullptr)
        {
            property_group properties;
            properties.set(SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, static_cast<SDL_PixelFormat>(format));
            properties.set(SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, static_cast<SDL_Colorspace>(color_space));
            properties.set(SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, static_cast<SDL_TextureAccess>(access));
            properties.set(SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, quantity_cast<std::int32_t>(size.width));
            properties.set(SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, quantity_cast<std::int32_t>(size.height));
            _native_handle = check_pointer(
                SDL_CreateTextureWithProperties(owner.native_handle(), properties.native_handle())
            );
        }

    private:
        texture(renderer & owner, property_group & properties)
        : _native_handle(
              check_pointer(SDL_CreateTextureWithProperties(owner.native_handle(), properties.native_handle()))
          )
        { }

    public:
        texture(texture<P, A, C> && other)
        : _native_handle(std::exchange(other._native_handle, nullptr))
        { }

        texture<P, A, C> & operator=(texture<P, A, C> const & other) = delete;

        ~texture()
        {
            if (_native_handle != nullptr)
            {
                SDL_DestroyTexture(_native_handle);
            }
        }

        void update(surface<P, C> const & pixels)
        {
            check_result(SDL_UpdateTexture(_native_handle, nullptr, pixels.pixels(), pixels.pitch()));
        }

        template <typename CallbackFunction>
        void with_lock(CallbackFunction callback)
        {
            using pixel_type = surface<P, C>::type;

            void * pixels;
            std::int32_t pitch;
            check_result(SDL_LockTexture(_native_handle, nullptr, &pixels, &pitch));

            surface<P, C>
                surface(_native_handle->w * px, _native_handle->h * px, static_cast<pixel_type *>(pixels), pitch);

            callback(surface);

            SDL_UnlockTexture(_native_handle);
        }

        property_group properties() const
        {
            return property_group(SDL_GetTextureProperties(_native_handle));
        }

        SDL_Texture * native_handle()
        {
            return _native_handle;
        }

    private:
        SDL_Texture * _native_handle;
    };

    template <pixel_format P, color_space C = default_color_space<P>()>
    using static_texture = texture<P, texture_access::static_access, C>;

    template <pixel_format P, color_space C = default_color_space<P>()>
    using streaming_texture = texture<P, texture_access::streaming_access, C>;

    template <pixel_format P, color_space C = default_color_space<P>()>
    using target_texture = texture<P, texture_access::target_access, C>;
}  // namespace sdl3

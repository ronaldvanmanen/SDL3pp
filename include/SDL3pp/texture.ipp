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

#include "renderer.hpp"
#include "texture.hpp"

namespace sdl3
{
    namespace details
    {
        inline SDL_Texture *
        create_texture(
            renderer & owner,
            pixel_format format,
            texture_access access,
            length<std::int32_t> width,
            length<std::int32_t> height
        )
        {
            SDL_Texture * native_handle = SDL_CreateTexture(
                owner.native_handle(),
                static_cast<SDL_PixelFormat>(format),
                static_cast<SDL_TextureAccess>(access),
                quantity_cast<std::int32_t>(width),
                quantity_cast<std::int32_t>(height)
            );
            throw_last_error(native_handle != nullptr);
            return native_handle;
        }

        inline SDL_Texture *
        create_texture(renderer & owner, property_group & properties)
        {
            SDL_Texture * native_handle = SDL_CreateTextureWithProperties(
                owner.native_handle(),
                properties.native_handle()
            );
            throw_last_error(native_handle != nullptr);
            return native_handle;
        }

        inline SDL_Texture *
        create_texture(renderer & owner, property_group && properties)
        {
            SDL_Texture * native_handle = SDL_CreateTextureWithProperties(
                owner.native_handle(),
                properties.native_handle()
            );
            throw_last_error(native_handle != nullptr);
            return native_handle;
        }
    }  // namespace details

    inline texture_base::texture_base(
        renderer & owner,
        pixel_format format,
        texture_access access,
        length<std::int32_t> width,
        length<std::int32_t> height
    )
    : _native_handle(details::create_texture(owner, format, access, width, height))
    { }

    inline texture_base::texture_base(renderer & owner, property_group & properties)
    : _native_handle(details::create_texture(owner, properties))
    { }

    inline texture_base::texture_base(renderer & owner, property_group && properties)
    : _native_handle(details::create_texture(owner, properties))
    { }

    inline texture_base::texture_base(texture_base && other)
    : _native_handle(std::exchange(other._native_handle, nullptr))
    { }

    inline texture_base::~texture_base()
    {
        if (_native_handle != nullptr)
        {
            SDL_DestroyTexture(_native_handle);
        }
    }

    inline property_group
    texture_base::properties() const
    {
        return property_group(SDL_GetTextureProperties(_native_handle));
    }

    inline SDL_Texture *
    texture_base::native_handle()
    {
        return _native_handle;
    }

    namespace details
    {
        inline property_group
        make_texture_properties(
            pixel_format format,
            color_space color_space,
            texture_access access,
            length<std::int32_t> width,
            length<std::int32_t> height
        )
        {
            property_group properties;
            properties.set(SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, static_cast<SDL_PixelFormat>(format));
            properties.set(SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, static_cast<SDL_Colorspace>(color_space));
            properties.set(SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, static_cast<SDL_TextureAccess>(access));
            properties.set(SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, quantity_cast<std::int32_t>(width));
            properties.set(SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, quantity_cast<std::int32_t>(height));
            return properties;
        }
    }  // namespace details

    template <pixel_format P, texture_access A, color_space C>
        requires(is_compatible_color_space<P, C>())
    texture<P, A, C>::texture(renderer & owner, length<std::int32_t> width, length<std::int32_t> height)
    : texture_base(owner, details::make_texture_properties(format, color_space, access, width, height))
    { }

    template <pixel_format P, texture_access A, color_space C>
        requires(is_compatible_color_space<P, C>())
    texture<P, A, C>::texture(renderer & owner, size_2d<std::int32_t> const & size)
    : texture_base(owner, details::make_texture_properties(format, color_space, access, size.width, size.height))
    { }

    template <pixel_format P, texture_access A, color_space C>
        requires(is_compatible_color_space<P, C>())
    texture<P, A, C>::texture(texture<P, A, C> && other)
    : texture_base(other)
    { }

    template <pixel_format P, texture_access A, color_space C>
        requires(is_compatible_color_space<P, C>())
    void
    texture<P, A, C>::update(surface<P, C> const & pixels)
    {
        throw_last_error(SDL_UpdateTexture(_native_handle, nullptr, pixels.pixels(), pixels.pitch()));
    }

    template <pixel_format P, texture_access A, color_space C>
        requires(is_compatible_color_space<P, C>())
    template <typename CallbackFunction>
    void
    texture<P, A, C>::with_lock(CallbackFunction callback)
    {
        using pixel_type = surface<P, C>::type;

        void * pixels;
        std::int32_t pitch;
        throw_last_error(SDL_LockTexture(_native_handle, nullptr, &pixels, &pitch));

        surface<P, C> surface(_native_handle->w * px, _native_handle->h * px, static_cast<pixel_type *>(pixels), pitch);

        callback(surface);

        SDL_UnlockTexture(_native_handle);
    }
}  // namespace sdl3

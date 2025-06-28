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

#include "SDL3pp/texture.h"

#include <cassert>

namespace sdl3
{
    SDL_Texture* create_texture(
        sdl3::renderer & owner,
        sdl3::pixel_format format,
        sdl3::texture_access access,
        sdl3::length<std::int32_t> width,
        sdl3::length<std::int32_t> height
    )
    {
        SDL_Texture* native_handle = SDL_CreateTexture(
            owner.native_handle(),
            static_cast<SDL_PixelFormat>(format),
            static_cast<SDL_TextureAccess>(access),
            quantity_cast<std::int32_t>(width),
            quantity_cast<std::int32_t>(height)
        );
        throw_last_error(native_handle != nullptr);
        return native_handle;
    }

    SDL_Texture* create_texture(sdl3::renderer & owner, sdl3::property_group & properties)
    {
        SDL_Texture* native_handle = SDL_CreateTextureWithProperties(
            owner.native_handle(),
            properties.native_handle()
        );
        throw_last_error(native_handle != nullptr);
        return native_handle;
    }
}

sdl3::texture_base::texture_base(
    sdl3::renderer & owner,
    sdl3::pixel_format format,
    sdl3::texture_access access,
    sdl3::length<std::int32_t> width,
    sdl3::length<std::int32_t> height
)
: _native_handle(sdl3::create_texture(owner, format, access, width, height))
{ }

sdl3::texture_base::texture_base(sdl3::renderer & owner, sdl3::property_group & properties)
: _native_handle(sdl3::create_texture(owner, properties))
{ }

sdl3::texture_base::~texture_base()
{
    if (_native_handle != nullptr)
    {
        SDL_DestroyTexture(_native_handle);
    }
}

sdl3::property_group
sdl3::texture_base::properties() const
{
    return sdl3::property_group(SDL_GetTextureProperties(_native_handle));
}

SDL_Texture*
sdl3::texture_base::native_handle()
{
    return _native_handle;
}

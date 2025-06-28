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

#include "SDL3pp/error.h"
#include "SDL3pp/renderer.h"
#include "SDL3pp/texture.h"

namespace sdl3
{
    SDL_Renderer* create_renderer(sdl3::window & owner)
    {
        SDL_Renderer* native_handle = SDL_CreateRenderer(
            owner.native_handle(), nullptr
        );
        throw_last_error(native_handle != nullptr);
        return native_handle;
    }

    SDL_Renderer* create_renderer(sdl3::window & owner, std::string const& name)
    {
        SDL_Renderer* native_handle = SDL_CreateRenderer(
            owner.native_handle(), name.c_str()
        );
        throw_last_error(native_handle != nullptr);
        return native_handle;
    }
}

sdl3::renderer::renderer(sdl3::window & owner)
: _native_handle(sdl3::create_renderer(owner))
{ }

sdl3::renderer::renderer(sdl3::window & owner, std::string const& name)
: _native_handle(sdl3::create_renderer(owner, name))
{ }


sdl3::renderer::renderer(renderer&& other)
: _native_handle(std::exchange(other._native_handle, nullptr))
{}

sdl3::renderer::~renderer()
{
    if (_native_handle != nullptr)
    {
        SDL_DestroyRenderer(_native_handle);
    }
}

std::string
sdl3::renderer::name() const
{
    char const *retval = SDL_GetRendererName(_native_handle);
    sdl3::throw_last_error(retval != nullptr);
    return std::string(retval);
}

sdl3::property_group
sdl3::renderer::properties() const
{
    return sdl3::property_group(SDL_GetRendererProperties(_native_handle));
}

sdl3::size_2d<std::int32_t>
sdl3::renderer::output_size() const
{
    int width, height;
    sdl3::throw_last_error(
        SDL_GetCurrentRenderOutputSize(_native_handle, &width, &height)
    );
    return sdl3::size_2d<std::int32_t>(width * px, height * px);
}

sdl3::color
sdl3::renderer::draw_color() const
{
    std::uint8_t r, g, b, a;
    throw_last_error(
        SDL_GetRenderDrawColor(_native_handle, &r, &g, &b, &a)
    );
    return sdl3::color(r, g, b, a);
}

void
sdl3::renderer::draw_color(sdl3::color const& draw_color)
{
    throw_last_error(
        SDL_SetRenderDrawColor(
            _native_handle, draw_color.r, draw_color.g, draw_color.b, draw_color.a
        )
    );
}

sdl3::blend_mode
sdl3::renderer::draw_blend_mode() const
{
    SDL_BlendMode mode;
    throw_last_error(
        SDL_GetRenderDrawBlendMode(_native_handle, &mode)
    );
    return static_cast<sdl3::blend_mode>(mode);
}

void
sdl3::renderer::draw_blend_mode(sdl3::blend_mode mode)
{
    throw_last_error(
        SDL_SetRenderDrawBlendMode(_native_handle, static_cast<SDL_BlendMode>(mode))
    );
}

void
sdl3::renderer::clear()
{
    sdl3::throw_last_error(
        SDL_RenderClear(_native_handle)
    );
}

void
sdl3::renderer::present()
{
    SDL_RenderPresent(_native_handle);
}

void
sdl3::renderer::copy(sdl3::texture_base const& texture)
{
    sdl3::throw_last_error(
        SDL_RenderTexture(
            _native_handle,
            const_cast<sdl3::texture_base&>(texture).native_handle(),
            nullptr,
            nullptr)
    );
}

SDL_Renderer* sdl3::renderer::native_handle()
{
    return _native_handle;
}

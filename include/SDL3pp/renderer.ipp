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

#include "renderer.hpp"
#include "texture.hpp"

namespace sdl3
{
    inline renderer::renderer(window & owner)
    : _native_handle(check_pointer(SDL_CreateRenderer(owner.native_handle(), nullptr)))
    { }

    inline renderer::renderer(window & owner, std::string const & name)
    : _native_handle(check_pointer(SDL_CreateRenderer(owner.native_handle(), name.c_str())))
    { }

    inline renderer::renderer(renderer && other)
    : _native_handle(std::exchange(other._native_handle, nullptr))
    { }

    inline renderer::~renderer()
    {
        if (_native_handle != nullptr)
        {
            SDL_DestroyRenderer(_native_handle);
        }
    }

    inline std::string
    renderer::name() const
    {
        char const * retval = SDL_GetRendererName(_native_handle);
        check_result(retval != nullptr);
        return std::string(retval);
    }

    inline property_group
    renderer::properties() const
    {
        return property_group(SDL_GetRendererProperties(_native_handle));
    }

    inline size_2d<std::int32_t>
    renderer::output_size() const
    {
        int width, height;
        check_result(SDL_GetCurrentRenderOutputSize(_native_handle, &width, &height));
        return size_2d<std::int32_t>(width * px, height * px);
    }

    inline color
    renderer::draw_color() const
    {
        std::uint8_t r, g, b, a;
        check_result(SDL_GetRenderDrawColor(_native_handle, &r, &g, &b, &a));
        return color(r8(r), g8(g), b8(b), a8(a));
    }

    inline void
    renderer::draw_color(color const & draw_color)
    {
        check_result(SDL_SetRenderDrawColor(_native_handle, draw_color.r, draw_color.g, draw_color.b, draw_color.a));
    }

    inline blend_mode
    renderer::draw_blend_mode() const
    {
        SDL_BlendMode mode;
        check_result(SDL_GetRenderDrawBlendMode(_native_handle, &mode));
        return static_cast<blend_mode>(mode);
    }

    inline void
    renderer::draw_blend_mode(blend_mode mode)
    {
        check_result(SDL_SetRenderDrawBlendMode(_native_handle, static_cast<SDL_BlendMode>(mode)));
    }

    inline void
    renderer::clear()
    {
        check_result(SDL_RenderClear(_native_handle));
    }

    inline void
    renderer::present()
    {
        SDL_RenderPresent(_native_handle);
    }

    inline void
    renderer::copy(texture_base & texture)
    {
        check_result(SDL_RenderTexture(_native_handle, texture.native_handle(), nullptr, nullptr));
    }

    inline SDL_Renderer *
    renderer::native_handle()
    {
        return _native_handle;
    }
}  // namespace sdl3

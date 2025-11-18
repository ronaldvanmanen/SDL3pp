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

#include <cstdint>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>

#include <SDL3/SDL_surface.h>

#include "error.hpp"
#include "pixels.hpp"
#include "size.hpp"
#include "units.hpp"

namespace sdl3
{
    template <pixel_format P, color_space C = default_color_space<P>()>
        requires(is_compatible_color_space<P, C>())
    class surface
    {
    public:
        static const pixel_format format = P;

        using pixel_type = typename pixel_color<P, C>::type;

    public:
        surface(length<std::int32_t> const & width, length<std::int32_t> const & height)
        : _native_handle(check_pointer(SDL_CreateSurface(
              boost::units::quantity_cast<std::int32_t>(width),
              boost::units::quantity_cast<std::int32_t>(height),
              static_cast<SDL_PixelFormat>(format)
          )))
        , _free_handle(true)
        { }

        surface(size_2d<std::int32_t> const & size)
        : _native_handle(check_pointer(SDL_CreateSurface(
              boost::units::quantity_cast<std::int32_t>(size.width),
              boost::units::quantity_cast<std::int32_t>(size.height),
              static_cast<SDL_PixelFormat>(format)
          )))
        , _free_handle(true)
        { }

        surface(
            length<std::int32_t> const & width,
            length<std::int32_t> const & height,
            pixel_type * pixels,
            std::int32_t pitch
        )
        : _native_handle(check_pointer(SDL_CreateSurfaceFrom(
              boost::units::quantity_cast<std::int32_t>(width),
              boost::units::quantity_cast<std::int32_t>(height),
              static_cast<SDL_PixelFormat>(format),
              pixels,
              pitch
          )))
        , _free_handle(true)
        { }

        surface(SDL_Surface * native_handle, bool free_handle)
        : _native_handle(native_handle)
        , _free_handle(free_handle)
        {
            check_result(_native_handle != nullptr);
        }

        surface(surface<P, C> const & other) = delete;

        surface(surface<P, C> && other)
        : _native_handle(std::exchange(other._native_handle, nullptr))
        , _free_handle(std::exchange(other._free_handle, false))
        { }

        ~surface()
        {
            if (_free_handle && _native_handle != nullptr)
            {
                SDL_DestroySurface(_native_handle);
            }
        }

        surface<P, C> & operator=(surface<P, C> const & other) = delete;

        length<std::int32_t> width() const
        {
            return _native_handle->w * px;
        }

        length<std::int32_t> height() const
        {
            return _native_handle->h * px;
        }

        void color_space(sdl3::color_space const & value)
        {
            SDL_SetSurfaceColorspace(_native_handle, static_cast<SDL_Colorspace>(value));
        }

        sdl3::color_space color_space() const
        {
            return static_cast<sdl3::color_space>(SDL_GetSurfaceColorspace(_native_handle));
        }

        template <pixel_format P2, sdl3::color_space C2 = default_color_space<P>()>
        void blit(surface<P2, C2> & source)
        {
            auto source_handle = source.native_handle();
            auto source_rect = SDL_Rect{0, 0, source_handle->w, source_handle->h};
            auto target_handle = this->native_handle();
            auto target_rect = SDL_Rect{0, 0, target_handle->w, target_handle->h};
            check_result(SDL_BlitSurface(source_handle, &source_rect, target_handle, &target_rect));
        }

        std::int32_t pitch() const
        {
            return _native_handle->pitch;
        }

        pixel_type const * pixels() const
        {
            return reinterpret_cast<pixel_type const *>(_native_handle->pixels);
        }

        pixel_type & operator()(offset<int32_t> x, offset<int32_t> y)
        {
            auto * pixels = reinterpret_cast<pixel_type *>(_native_handle->pixels);
            auto const pitch = _native_handle->pitch / sizeof(pixel_type);
            auto const sx = boost::units::quantity_cast<std::size_t>(x);
            auto const sy = boost::units::quantity_cast<std::size_t>(y);
            return pixels[sy * pitch + sx];
        }

        pixel_type const & operator()(offset<int32_t> x, offset<int32_t> y) const
        {
            auto const * pixels = reinterpret_cast<pixel_type const *>(_native_handle->pixels);
            auto const pitch = _native_handle->pitch / sizeof(pixel_type);
            auto const sx = boost::units::quantity_cast<std::size_t>(x);
            auto const sy = boost::units::quantity_cast<std::size_t>(y);
            return pixels[sy * pitch + sx];
        }

        template <typename CallbackFunction>
        void with_lock(CallbackFunction callback)
        {
            const bool must_lock = SDL_MUSTLOCK(_native_handle);

            if (must_lock)
            {
                check_result(SDL_LockSurface(_native_handle));
            }

            callback(*this);

            if (must_lock)
            {
                SDL_UnlockSurface(_native_handle);
            }
        }

        SDL_Surface * native_handle()
        {
            return _native_handle;
        }

    private:
        SDL_Surface * _native_handle;

        bool _free_handle;
    };

}  // namespace sdl3

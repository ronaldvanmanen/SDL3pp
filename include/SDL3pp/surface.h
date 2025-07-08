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

#include "color_space.h"
#include "error.h"
#include "length.h"
#include "pixel_format.h"
#include "pixel_format_traits.h"
#include "size.h"
#include "window.h"

namespace sdl3
{
    class surface_base
    {
    protected:
        surface_base(length<std::int32_t> const& width, length<std::int32_t> const& height, pixel_format format);

        surface_base(size_2d<std::int32_t> const& size, pixel_format format);

        surface_base(length<std::int32_t> const& width, length<std::int32_t> const& height, pixel_format format, void* pixels, std::int32_t pitch);

        surface_base(surface_base const& other);

        surface_base(SDL_Surface * native_handle, bool free_handle);

    public:
        ~surface_base();

        surface_base& operator=(surface_base const& other) = delete;

        void color_space(sdl3::color_space const& value);

        sdl3::color_space color_space() const;

        length<std::int32_t> width() const;

        length<std::int32_t> height() const;

        SDL_Surface* native_handle();

    protected:
        SDL_Surface* _native_handle;

        bool _free_handle;
    };

    surface_base get_surface(window & owner);

    void blit(surface_base & source, surface_base & target);

    template<typename TPixelFormat>
    class surface : public surface_base
    {
    public:
        surface(length<std::int32_t> const& width, length<std::int32_t> const& height);

        surface(size_2d<std::int32_t> const& size);

        surface(length<std::int32_t> const& width, length<std::int32_t> const& height, TPixelFormat* pixels, std::int32_t pitch);

        surface(window & owner);

        surface(surface<TPixelFormat> const& other);

        surface<TPixelFormat>& operator=(surface<TPixelFormat> const& other) = delete;

        std::int32_t pitch() const;

        TPixelFormat const* pixels() const;

        TPixelFormat& operator()(offset<int32_t> x, offset<int32_t> y);

        TPixelFormat const& operator()(offset<int32_t> x, offset<int32_t> y) const;

        template<typename CallbackFunction>
        void with_lock(CallbackFunction callback);
    };

    template<typename TPixelFormat>
    surface<TPixelFormat>::surface(length<std::int32_t> const& width, length<std::int32_t> const& height)
    : surface_base(width, height, pixel_format_traits<TPixelFormat>::format)
    {
        color_space(TPixelFormat::color_space);
    }

    template<typename TPixelFormat>
    surface<TPixelFormat>::surface(size_2d<std::int32_t> const& size)
    : surface_base(size, pixel_format_traits<TPixelFormat>::format)
    {
        color_space(TPixelFormat::color_space);
    }

    template<typename TPixelFormat>
    surface<TPixelFormat>::surface(length<std::int32_t> const& width, length<std::int32_t> const& height, TPixelFormat* pixels, std::int32_t pitch)
    : surface_base(width, height, pixel_format_traits<TPixelFormat>::format, pixels, pitch * sizeof(TPixelFormat))
    {
        color_space(TPixelFormat::color_space);
    }

    template<typename TPixelFormat>
    surface<TPixelFormat>::surface(window & owner)
    : surface_base(owner)
    {
        color_space(TPixelFormat::color_space);
    }

    template<typename TPixelFormat>
    surface<TPixelFormat>::surface(surface<TPixelFormat> const& other)
    : surface_base(other)
    {
        color_space(TPixelFormat::color_space);
    }

    template<typename TPixelFormat>
    std::int32_t
    surface<TPixelFormat>::pitch() const
    {
        return _native_handle->pitch / sizeof(TPixelFormat);
    }

    template<typename TPixelFormat>
    TPixelFormat const*
    surface<TPixelFormat>::pixels() const
    {
        return reinterpret_cast<TPixelFormat const*>(_native_handle->pixels);
    }

    template<typename TPixelFormat>
    TPixelFormat&
    surface<TPixelFormat>::operator()(offset<std::int32_t> x, offset<std::int32_t> y)
    {
        TPixelFormat * pixels = reinterpret_cast<TPixelFormat*>(_native_handle->pixels);
        auto const pitch = _native_handle->pitch / sizeof(TPixelFormat);
        auto const sx = boost::units::quantity_cast<std::size_t>(x);
        auto const sy = boost::units::quantity_cast<std::size_t>(y);
        return pixels[sy * pitch + sx];
    }

    template<typename TPixelFormat>
    TPixelFormat const&
    surface<TPixelFormat>::operator()(offset<std::int32_t> x, offset<std::int32_t> y) const
    {
        TPixelFormat const* pixels = reinterpret_cast<TPixelFormat const*>(_native_handle->pixels);
        auto const pitch = _native_handle->pitch / sizeof(TPixelFormat);
        auto const sx = boost::units::quantity_cast<std::size_t>(x);
        auto const sy = boost::units::quantity_cast<std::size_t>(y);
        return pixels[sy * pitch + sx];
    }

    template<typename TPixelFormat> template <typename CallbackFunction>
    void
    surface<TPixelFormat>::with_lock(CallbackFunction callback)
    {
        const bool must_lock = SDL_MUSTLOCK(_native_handle);

        if (must_lock)
        {
            throw_last_error(
                SDL_LockSurface(_native_handle)
            );
        }

        callback(*this);

        if (must_lock)
        {
            SDL_UnlockSurface(_native_handle);
        }
    }
}

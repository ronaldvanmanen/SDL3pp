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
    class surface_base
    {
    public:
        surface_base(length<std::int32_t> const & width, length<std::int32_t> const & height, pixel_format format);

        surface_base(size_2d<std::int32_t> const & size, pixel_format format);

        surface_base(
            length<std::int32_t> const & width,
            length<std::int32_t> const & height,
            pixel_format format,
            void * pixels,
            std::int32_t pitch
        );

        surface_base(surface_base const & other);

        surface_base(SDL_Surface * native_handle, bool free_handle);

        ~surface_base();

        surface_base & operator=(surface_base const & other) = delete;

        void color_space(sdl3::color_space const & value);

        sdl3::color_space color_space() const;

        length<std::int32_t> width() const;

        length<std::int32_t> height() const;

        SDL_Surface * native_handle();

        void blit(surface_base & source);

    protected:
        SDL_Surface * _native_handle;

        bool _free_handle;
    };

    inline surface_base::surface_base(
        length<std::int32_t> const & width,
        length<std::int32_t> const & height,
        pixel_format format
    )
    : _native_handle(check_pointer(SDL_CreateSurface(
          boost::units::quantity_cast<std::int32_t>(width),
          boost::units::quantity_cast<std::int32_t>(height),
          static_cast<SDL_PixelFormat>(format)
      )))
    , _free_handle(true)
    { }

    inline surface_base::surface_base(size_2d<std::int32_t> const & size, pixel_format format)
    : _native_handle(check_pointer(SDL_CreateSurface(
          boost::units::quantity_cast<std::int32_t>(size.width),
          boost::units::quantity_cast<std::int32_t>(size.height),
          static_cast<SDL_PixelFormat>(format)
      )))
    , _free_handle(true)
    { }

    inline surface_base::surface_base(
        length<std::int32_t> const & width,
        length<std::int32_t> const & height,
        pixel_format format,
        void * pixels,
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

    inline surface_base::surface_base(SDL_Surface * native_handle, bool free_handle)
    : _native_handle(native_handle)
    , _free_handle(free_handle)
    {
        check_result(_native_handle != nullptr);
    }

    inline surface_base::surface_base(surface_base const & other)
    : _native_handle(SDL_CreateSurface(other._native_handle->w, other._native_handle->h, other._native_handle->format))
    , _free_handle(true)
    {
        check_result(SDL_BlitSurface(other._native_handle, nullptr, _native_handle, nullptr));
    }

    inline surface_base::~surface_base()
    {
        if (_free_handle && _native_handle != nullptr)
        {
            SDL_DestroySurface(_native_handle);
        }
    }

    inline length<std::int32_t>
    surface_base::width() const
    {
        return _native_handle->w * px;
    }

    inline length<std::int32_t>
    surface_base::height() const
    {
        return _native_handle->h * px;
    }

    inline void
    surface_base::color_space(sdl3::color_space const & value)
    {
        SDL_SetSurfaceColorspace(_native_handle, static_cast<SDL_Colorspace>(value));
    }

    inline color_space
    surface_base::color_space() const
    {
        return static_cast<sdl3::color_space>(SDL_GetSurfaceColorspace(_native_handle));
    }

    inline SDL_Surface *
    surface_base::native_handle()
    {
        return _native_handle;
    }

    inline void
    surface_base::blit(surface_base & source)
    {
        auto source_handle = source.native_handle();
        auto source_rect = SDL_Rect{0, 0, source_handle->w, source_handle->h};
        auto target_handle = this->native_handle();
        auto target_rect = SDL_Rect{0, 0, target_handle->w, target_handle->h};
        check_result(SDL_BlitSurface(source_handle, &source_rect, target_handle, &target_rect));
    }

    template <pixel_format P, color_space C = default_color_space<P>()>
        requires(is_compatible_color_space<P, C>())
    class surface : public surface_base
    {
    public:
        static const pixel_format format = P;

        using pixel_type = typename pixel_color<P, C>::type;

    public:
        surface(length<std::int32_t> const & width, length<std::int32_t> const & height);

        surface(size_2d<std::int32_t> const & size);

        surface(
            length<std::int32_t> const & width,
            length<std::int32_t> const & height,
            pixel_type * pixels,
            std::int32_t pitch
        );

        surface(surface<P, C> const & other);

        surface<P, C> & operator=(surface<P, C> const & other) = delete;

        std::int32_t pitch() const;

        pixel_type const * pixels() const;

        pixel_type & operator()(offset<int32_t> x, offset<int32_t> y);

        pixel_type const & operator()(offset<int32_t> x, offset<int32_t> y) const;

        template <typename CallbackFunction>
        void with_lock(CallbackFunction callback);
    };

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    surface<P, C>::surface(length<std::int32_t> const & width, length<std::int32_t> const & height)
    : surface_base(width, height, format)
    { }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    surface<P, C>::surface(size_2d<std::int32_t> const & size)
    : surface_base(size, format)
    { }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    surface<P, C>::surface(
        length<std::int32_t> const & width,
        length<std::int32_t> const & height,
        pixel_type * pixels,
        std::int32_t pitch
    )
    : surface_base(width, height, format, pixels, pitch)
    { }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    surface<P, C>::surface(surface<P, C> const & other)
    : surface_base(other)
    { }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    std::int32_t
    surface<P, C>::pitch() const
    {
        return _native_handle->pitch;
    }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    typename surface<P, C>::pixel_type const *
    surface<P, C>::pixels() const
    {
        return reinterpret_cast<pixel_type const *>(_native_handle->pixels);
    }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    typename surface<P, C>::pixel_type &
    surface<P, C>::operator()(offset<std::int32_t> x, offset<std::int32_t> y)
    {
        auto * pixels = reinterpret_cast<pixel_type *>(_native_handle->pixels);
        auto const pitch = _native_handle->pitch / sizeof(pixel_type);
        auto const sx = boost::units::quantity_cast<std::size_t>(x);
        auto const sy = boost::units::quantity_cast<std::size_t>(y);
        return pixels[sy * pitch + sx];
    }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    typename surface<P, C>::pixel_type const &
    surface<P, C>::operator()(offset<std::int32_t> x, offset<std::int32_t> y) const
    {
        auto const * pixels = reinterpret_cast<pixel_type const *>(_native_handle->pixels);
        auto const pitch = _native_handle->pitch / sizeof(pixel_type);
        auto const sx = boost::units::quantity_cast<std::size_t>(x);
        auto const sy = boost::units::quantity_cast<std::size_t>(y);
        return pixels[sy * pitch + sx];
    }

    template <pixel_format P, color_space C>
        requires(is_compatible_color_space<P, C>())
    template <typename CallbackFunction>
    void
    surface<P, C>::with_lock(CallbackFunction callback)
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
}  // namespace sdl3

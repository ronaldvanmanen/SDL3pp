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

#include <boost/operators.hpp>

#include "base_color.hpp"
#include "pixels.hpp"

namespace sdl3
{
    template<pixel_format P>
    requires (is_packed<P>() && !has_alpha<P>())
    struct rgb_packed_color_traits { };

#define RGB_PACKED_COLOR_TRAITS(PIXEL_FORMAT, PACKED_SIZE, R_BITS, G_BITS, B_BITS) \
    template<> \
    struct rgb_packed_color_traits<pixel_format::PIXEL_FORMAT> \
    { \
        using packed_type = std::uint##PACKED_SIZE##_t; \
        using r_type = r##R_BITS; \
        using g_type = g##G_BITS; \
        using b_type = b##B_BITS; \
        static const size_t r_bits = R_BITS; \
    }; \
    /**/

    RGB_PACKED_COLOR_TRAITS(rgb332,     8,   3, 3, 2)
    RGB_PACKED_COLOR_TRAITS(xrgb4444,   16,  4, 4, 4)
    RGB_PACKED_COLOR_TRAITS(xbgr4444,   16,  4, 4, 4)
    RGB_PACKED_COLOR_TRAITS(xrgb8888,   32,  8, 8, 8)
    RGB_PACKED_COLOR_TRAITS(rgbx8888,   32,  8, 8, 8)
    RGB_PACKED_COLOR_TRAITS(xbgr8888,   32,  8, 8, 8)
    RGB_PACKED_COLOR_TRAITS(bgrx8888,   32,  8, 8, 8)
    RGB_PACKED_COLOR_TRAITS(rgb565,     16,  5, 6, 5)
    RGB_PACKED_COLOR_TRAITS(bgr565,     16,  5, 6, 5)
#undef RGB_PACKED_COLOR_TRAITS

    template<pixel_format P, color_space C = default_color_space<P>()>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    class alignas(alignof(typename rgb_packed_color_traits<P>::packed_type)) rgb_packed_color
    : boost::equality_comparable<rgb_packed_color<P, C>
    , boost::additive<rgb_packed_color<P, C>
    , boost::multiplicative<rgb_packed_color<P, C>
    > > >
    {
    private:
        inline static SDL_PixelFormatDetails const* format_details = SDL_GetPixelFormatDetails(static_cast<SDL_PixelFormat>(P));

    public:
        static constexpr pixel_format format = P;

        static constexpr color_space color_space = C;

        static const rgb_packed_color black;

        static const rgb_packed_color white;

        using packed_type = typename rgb_packed_color_traits<P>::packed_type;

        using r_type = typename rgb_packed_color_traits<P>::r_type;

        using g_type = typename rgb_packed_color_traits<P>::g_type;

        using b_type = typename rgb_packed_color_traits<P>::b_type;
        
    public:
        rgb_packed_color();

        rgb_packed_color(r_type r, g_type g, b_type b);

        rgb_packed_color(rgb_packed_color<P, C> const& other);

        rgb_packed_color<P, C> & operator=(rgb_packed_color<P, C> const& other);

        rgb_packed_color<P, C> & operator*=(rgb_packed_color<P, C> const& other);

        rgb_packed_color<P, C> & operator/=(rgb_packed_color<P, C> const& other);

        rgb_packed_color<P, C> & operator+=(rgb_packed_color<P, C> const& other);

        rgb_packed_color<P, C> & operator-=(rgb_packed_color<P, C> const& other);

        bool operator==(rgb_packed_color const& other) const;

        r_type r() const;

        g_type g() const;

        b_type b() const;

    private:
        static packed_type pack(r_type r, g_type g, b_type b);

    private:
        packed_type _value;
    };

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    struct pixel_color<P, C>
    {
        using type = rgb_packed_color<P, C>;
    };

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    const rgb_packed_color<P, C> rgb_packed_color<P, C>::black(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min()
    );

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    const rgb_packed_color<P, C> rgb_packed_color<P, C>::white(
        base_color_limits<r_type>::max(),
        base_color_limits<g_type>::max(),
        base_color_limits<b_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C>::rgb_packed_color()
    : rgb_packed_color(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min()
    )
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C>::rgb_packed_color(r_type r, g_type g, b_type b)
    : _value(pack(r, g, b))
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C>::rgb_packed_color(rgb_packed_color<P, C> const& other)
    : _value(other._value)
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C> &
    rgb_packed_color<P, C>::operator=(rgb_packed_color<P, C> const& other)
    {
        if (this != &other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    bool
    rgb_packed_color<P, C>::operator==(rgb_packed_color<P, C> const& other) const
    {
        return _value == other._value;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C> &
    rgb_packed_color<P, C>::operator*=(rgb_packed_color<P, C> const& other)
    {
        _value = pack(
            r() * other.r(),
            g() * other.g(),
            b() * other.b()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C> &
    rgb_packed_color<P, C>::operator/=(rgb_packed_color<P, C> const& other)
    {
        _value = pack(
            r() / other.r(),
            g() / other.g(),
            b() / other.b()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C> &
    rgb_packed_color<P, C>::operator+=(rgb_packed_color<P, C> const& other)
    {
        _value = pack(
            r() + other.r(),
            g() + other.g(),
            b() + other.b()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_packed_color<P, C> &
    rgb_packed_color<P, C>::operator-=(rgb_packed_color<P, C> const& other)
    {
        _value = pack(
            r() - other.r(),
            g() - other.g(),
            b() - other.b()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_packed_color<P, C>::r_type
    rgb_packed_color<P, C>::r() const
    {
        return r_type((_value & format_details->Rmask) >> format_details->Rshift);
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_packed_color<P, C>::g_type
    rgb_packed_color<P, C>::g() const
    {
        return g_type((_value & format_details->Gmask) >> format_details->Gshift);
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_packed_color<P, C>::b_type
    rgb_packed_color<P, C>::b() const
    {
        return b_type((_value & format_details->Bmask) >> format_details->Bshift);
    }
    
    template<pixel_format P, color_space C>
    requires (is_packed<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_packed_color<P, C>::packed_type
    rgb_packed_color<P, C>::pack(r_type r, g_type g, b_type b)
    {
        return ((static_cast<packed_type>(r) << static_cast<packed_type>(format_details->Rshift)) & static_cast<packed_type>(format_details->Rmask))
             | ((static_cast<packed_type>(g) << static_cast<packed_type>(format_details->Gshift)) & static_cast<packed_type>(format_details->Gmask))
             | ((static_cast<packed_type>(b) << static_cast<packed_type>(format_details->Bshift)) & static_cast<packed_type>(format_details->Bmask));
    }

    template<class CharT, class Traits, pixel_format P, color_space C>
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> & stream, rgb_packed_color<P, C> const& value)
    {
        return stream << value.a << ',' << value.r << ',' << value.g << ',' << value.b;
    }

    using s_rgb332 = rgb_packed_color<pixel_format::rgb332, color_space::srgb>;
    using s_xrgb4444 = rgb_packed_color<pixel_format::xrgb4444, color_space::srgb>;
    using s_xbgr4444 = rgb_packed_color<pixel_format::xbgr4444, color_space::srgb>;
    using s_xrgb8888 = rgb_packed_color<pixel_format::xrgb8888, color_space::srgb>;
    using s_rgbx8888 = rgb_packed_color<pixel_format::rgbx8888, color_space::srgb>;
    using s_xbgr8888 = rgb_packed_color<pixel_format::xbgr8888, color_space::srgb>;
    using s_bgrx8888 = rgb_packed_color<pixel_format::bgrx8888, color_space::srgb>;
    using s_rgb565 = rgb_packed_color<pixel_format::rgb565, color_space::srgb>;
    using s_bgr565 = rgb_packed_color<pixel_format::bgr565, color_space::srgb>;

    template<pixel_format P>
    requires (is_packed<P>() && has_alpha<P>())
    struct rgba_packed_color_traits { };
    
#define RGBA_PACKED_COLOR_TRAITS(PIXEL_FORMAT, PACKED_SIZE, R_BITS, G_BITS, B_BITS, A_BITS) \
    template<> \
    struct rgba_packed_color_traits<pixel_format::PIXEL_FORMAT> \
    { \
        using packed_type = std::uint##PACKED_SIZE##_t; \
        using r_type = r##R_BITS; \
        using g_type = g##G_BITS; \
        using b_type = b##B_BITS; \
        using a_type = a##A_BITS; \
    };

    RGBA_PACKED_COLOR_TRAITS(argb4444,      16, 4,  4,  4,  4)
    RGBA_PACKED_COLOR_TRAITS(rgba4444,      16, 4,  4,  4,  4)
    RGBA_PACKED_COLOR_TRAITS(abgr4444,      16, 4,  4,  4,  4)
    RGBA_PACKED_COLOR_TRAITS(bgra4444,      16, 4,  4,  4,  4)
    RGBA_PACKED_COLOR_TRAITS(argb8888,      32, 8,  8,  8,  8)
    RGBA_PACKED_COLOR_TRAITS(rgba8888,      32, 8,  8,  8,  8)
    RGBA_PACKED_COLOR_TRAITS(abgr8888,      32, 8,  8,  8,  8)
    RGBA_PACKED_COLOR_TRAITS(bgra8888,      32, 8,  8,  8,  8)
    RGBA_PACKED_COLOR_TRAITS(argb1555,      16, 5,  5,  5,  1)
    RGBA_PACKED_COLOR_TRAITS(rgba5551,      16, 5,  5,  5,  1)
    RGBA_PACKED_COLOR_TRAITS(abgr1555,      16, 5,  5,  5,  1)
    RGBA_PACKED_COLOR_TRAITS(bgra5551,      16, 5,  5,  5,  1)
    RGBA_PACKED_COLOR_TRAITS(argb2101010,   32, 10, 10, 10, 2)
    RGBA_PACKED_COLOR_TRAITS(abgr2101010,   32, 10, 10, 10, 2)
#undef RGBA_PACKED_COLOR_TRAITS

    template<pixel_format P, color_space C = default_color_space<P>()>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    class alignas(alignof(typename rgba_packed_color_traits<P>::packed_type)) rgba_packed_color
    : boost::equality_comparable<rgba_packed_color<P, C>
    , boost::additive<rgba_packed_color<P, C>
    , boost::multiplicative<rgba_packed_color<P, C>
    > > >
    {
    private:
        inline static SDL_PixelFormatDetails const* format_details = SDL_GetPixelFormatDetails(static_cast<SDL_PixelFormat>(P));

    public:
        static constexpr pixel_format format = P;

        static constexpr color_space color_space = C;

        static const rgba_packed_color black;

        static const rgba_packed_color white;

        using packed_type = typename rgba_packed_color_traits<P>::packed_type;

        using r_type = typename rgba_packed_color_traits<P>::r_type;

        using g_type = typename rgba_packed_color_traits<P>::g_type;

        using b_type = typename rgba_packed_color_traits<P>::b_type;

        using a_type = typename rgba_packed_color_traits<P>::a_type;
        
    public:
        rgba_packed_color();

        rgba_packed_color(r_type r, g_type g, b_type b, a_type a);

        rgba_packed_color(rgba_packed_color<P, C> const& other);

        rgba_packed_color<P, C> & operator=(rgba_packed_color<P, C> const& other);

        rgba_packed_color<P, C> & operator*=(rgba_packed_color<P, C> const& other);

        rgba_packed_color<P, C> & operator/=(rgba_packed_color<P, C> const& other);

        rgba_packed_color<P, C> & operator+=(rgba_packed_color<P, C> const& other);

        rgba_packed_color<P, C> & operator-=(rgba_packed_color<P, C> const& other);

        bool operator==(rgba_packed_color const& other) const;

        r_type r() const;

        g_type g() const;

        b_type b() const;

        a_type a() const;

    private:
        static packed_type pack(r_type r, g_type g, b_type b, a_type a);

    private:
        packed_type _value;
    };

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    struct pixel_color<P, C>
    {
        using type = rgba_packed_color<P, C>;
    };

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    const rgba_packed_color<P, C> rgba_packed_color<P, C>::black(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min(),
        base_color_limits<a_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    const rgba_packed_color<P, C> rgba_packed_color<P, C>::white(
        base_color_limits<r_type>::max(),
        base_color_limits<g_type>::max(),
        base_color_limits<b_type>::max(),
        base_color_limits<a_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C>::rgba_packed_color()
    : rgba_packed_color(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min(),
        base_color_limits<a_type>::min()
    )
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C>::rgba_packed_color(r_type r, g_type g, b_type b, a_type a)
    : _value(pack(r, g, b, a))
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C>::rgba_packed_color(rgba_packed_color<P, C> const& other)
    : _value(other._value)
    { }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C> &
    rgba_packed_color<P, C>::operator=(rgba_packed_color<P, C> const& other)
    {
        if (this != &other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    bool
    rgba_packed_color<P, C>::operator==(rgba_packed_color<P, C> const& other) const
    {
        return _value == other._value;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C> &
    rgba_packed_color<P, C>::operator*=(rgba_packed_color<P, C> const& other)
    {
        _value = pack(
            r() * other.r(),
            g() * other.g(),
            b() * other.b(),
            a() * other.a()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C> &
    rgba_packed_color<P, C>::operator/=(rgba_packed_color<P, C> const& other)
    {
        _value = pack(
            r() / other.r(),
            g() / other.g(),
            b() / other.b(),
            a() / other.a()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C> &
    rgba_packed_color<P, C>::operator+=(rgba_packed_color<P, C> const& other)
    {
        _value = pack(
            r() + other.r(),
            g() + other.g(),
            b() + other.b(),
            a() + other.a()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_packed_color<P, C> &
    rgba_packed_color<P, C>::operator-=(rgba_packed_color<P, C> const& other)
    {
        _value = pack(
            r() - other.r(),
            g() - other.g(),
            b() - other.b(),
            a() - other.a()
        );
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_packed_color<P, C>::r_type
    rgba_packed_color<P, C>::r() const
    {
        return r_type((_value & format_details->Rmask) >> format_details->Rshift);
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_packed_color<P, C>::g_type
    rgba_packed_color<P, C>::g() const
    {
        return g_type((_value & format_details->Gmask) >> format_details->Gshift);
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_packed_color<P, C>::b_type
    rgba_packed_color<P, C>::b() const
    {
        return b_type((_value & format_details->Bmask) >> format_details->Bshift);
    }

    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_packed_color<P, C>::a_type
    rgba_packed_color<P, C>::a() const
    {
        return a_type((_value & format_details->Amask) >> format_details->Ashift);
    }
    
    template<pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_packed_color<P, C>::packed_type
    rgba_packed_color<P, C>::pack(r_type r, g_type g, b_type b, a_type a)
    {
        return ((static_cast<packed_type>(r) << static_cast<packed_type>(format_details->Rshift)) & static_cast<packed_type>(format_details->Rmask))
             | ((static_cast<packed_type>(g) << static_cast<packed_type>(format_details->Gshift)) & static_cast<packed_type>(format_details->Gmask))
             | ((static_cast<packed_type>(b) << static_cast<packed_type>(format_details->Bshift)) & static_cast<packed_type>(format_details->Bmask))
             | ((static_cast<packed_type>(a) << static_cast<packed_type>(format_details->Ashift)) & static_cast<packed_type>(format_details->Amask));
    }

    template<class CharT, class Traits, pixel_format P, color_space C>
    requires (is_packed<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> & stream, rgba_packed_color<P, C> const& value)
    {
        return stream << value.a() << ',' << value.r() << ',' << value.g() << ',' << value.b();
    }

    using s_argb4444 = rgba_packed_color<pixel_format::argb4444, color_space::srgb>;
    using s_rgba4444 = rgba_packed_color<pixel_format::rgba4444, color_space::srgb>;
    using s_abgr4444 = rgba_packed_color<pixel_format::abgr4444, color_space::srgb>;
    using s_bgra4444 = rgba_packed_color<pixel_format::bgra4444, color_space::srgb>;
    using s_argb8888 = rgba_packed_color<pixel_format::argb8888, color_space::srgb>;
    using s_rgba8888 = rgba_packed_color<pixel_format::rgba8888, color_space::srgb>;
    using s_abgr8888 = rgba_packed_color<pixel_format::abgr8888, color_space::srgb>;
    using s_bgra8888 = rgba_packed_color<pixel_format::bgra8888, color_space::srgb>;
    using s_argb1555 = rgba_packed_color<pixel_format::argb1555, color_space::srgb>;
    using s_rgba5551 = rgba_packed_color<pixel_format::rgba5551, color_space::srgb>;
    using s_abgr1555 = rgba_packed_color<pixel_format::abgr1555, color_space::srgb>;
    using s_bgra5551 = rgba_packed_color<pixel_format::bgra5551, color_space::srgb>;
    using s_argb2101010 = rgba_packed_color<pixel_format::argb2101010, color_space::srgb>;
    using s_abgr2101010 = rgba_packed_color<pixel_format::abgr2101010, color_space::srgb>;
}

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

#include <algorithm>

#include <boost/operators.hpp>

#include "color.h"
#include "pixels.h"

namespace sdl3
{
    template<pixel_format P>
    requires (is_array<P>() && !has_alpha<P>())
    struct rgb_array_color_traits
    { };

#define RGB_ARRAY_COLOR_TRAITS(PIXEL_FORMAT, SCALAR_TYPE, R_INDEX, G_INDEX, B_INDEX) \
    template<> \
    struct rgb_array_color_traits<pixel_format::PIXEL_FORMAT> \
    { \
        using scalar_type = SCALAR_TYPE; \
        using r_type = red<scalar_type>; \
        using b_type = blue<scalar_type>; \
        using g_type = green<scalar_type>; \
        static const size_t r_index = R_INDEX; \
        static const size_t g_index = G_INDEX; \
        static const size_t b_index = B_INDEX; \
        static const size_t size = 3; \
    };

    RGB_ARRAY_COLOR_TRAITS(rgb24, std::uint8_t, 0, 1, 2)
    RGB_ARRAY_COLOR_TRAITS(bgr24, std::uint8_t, 2, 1, 0)
    RGB_ARRAY_COLOR_TRAITS(rgb48, std::uint16_t, 0, 1, 2)
    RGB_ARRAY_COLOR_TRAITS(bgr48, std::uint16_t, 2, 1, 0)
    RGB_ARRAY_COLOR_TRAITS(rgb96f, float, 0, 1, 2)
    RGB_ARRAY_COLOR_TRAITS(bgr96f, float, 2, 1, 0)
#undef RGB_ARRAY_COLOR_TRAITS

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    class alignas(alignof(typename rgb_array_color_traits<P>::scalar_type)) rgb_array_color
    : boost::equality_comparable<rgb_array_color<P, C>
    , boost::additive<rgb_array_color<P, C>
    , boost::multiplicative<rgb_array_color<P, C>
    , boost::multiplicative<rgb_array_color<P, C>, typename rgb_array_color_traits<P>::scalar_type
    > > > >
    {
    public:
        static const pixel_format format = P;

        static const color_space color_space = C;

        using scalar_type = typename rgb_array_color_traits<P>::scalar_type;

        using r_type = typename rgb_array_color_traits<P>::r_type;

        using b_type = typename rgb_array_color_traits<P>::b_type;

        using g_type = typename rgb_array_color_traits<P>::g_type;

        static const size_t size = rgb_array_color_traits<P>::size;

        static const size_t r_index = rgb_array_color_traits<P>::r_index;

        static const size_t g_index = rgb_array_color_traits<P>::g_index;

        static const size_t b_index = rgb_array_color_traits<P>::b_index;

        static const rgb_array_color<P, C> black;

        static const rgb_array_color<P, C> white;

    public:
        rgb_array_color();

        rgb_array_color(r_type r, g_type g, b_type b);

        rgb_array_color(rgb_array_color<P, C> const& other);

        rgb_array_color<P, C> & operator=(rgb_array_color<P, C> const& other);

        rgb_array_color<P, C> & operator*=(rgb_array_color<P, C> const& other);

        rgb_array_color<P, C> & operator/=(rgb_array_color<P, C> const& other);

        rgb_array_color<P, C> & operator+=(rgb_array_color<P, C> const& other);

        rgb_array_color<P, C> & operator-=(rgb_array_color<P, C> const& other);
        
        rgb_array_color<P, C> & operator*=(scalar_type scalar);

        rgb_array_color<P, C> & operator/=(scalar_type scalar);

        bool operator==(rgb_array_color<P, C> const& other) const;

        r_type r() const;

        g_type g() const;

        b_type b() const;

    private:
        scalar_type _components[size];
    };

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    struct pixel_color<P, C>
    {
        using type = rgb_array_color<P, C>;
    };

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> const rgb_array_color<P, C>::black(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min()
    );

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> const rgb_array_color<P, C>::white(
        base_color_limits<r_type>::max(),
        base_color_limits<g_type>::max(),
        base_color_limits<b_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C>::rgb_array_color()
    {
        _components[r_index] = base_color_limits<r_type>::min();
        _components[g_index] = base_color_limits<g_type>::min();
        _components[b_index] = base_color_limits<b_type>::min();
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C>::rgb_array_color(r_type r, g_type g, b_type b)
    {
        _components[r_index] = r;
        _components[g_index] = g;
        _components[b_index] = b;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C>::rgb_array_color(rgb_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] = other._components[i];
        }
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator=(rgb_array_color<P, C> const& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < size; ++i)
            {
                _components[i] = other._components[i];
            }
        }
        return *this;
    }
            
    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator*=(rgb_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] *= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator/=(rgb_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] /= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator+=(rgb_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] += other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator-=(rgb_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] -= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator*=(scalar_type scalar)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] *= scalar;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    rgb_array_color<P, C> &
    rgb_array_color<P, C>::operator/=(scalar_type scalar)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] /= scalar;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    bool
    rgb_array_color<P, C>::operator==(rgb_array_color<P, C> const& other) const
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (_components[i] != other._components[i])
            {
                return false;
            }
        }
        return true;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_array_color<P, C>::r_type
    rgb_array_color<P, C>::r() const
    {
        return _components[r_index];
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_array_color<P, C>::g_type
    rgb_array_color<P, C>::g() const
    {
        return _components[g_index];
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && !has_alpha<P>() && is_rgb_color_space<C>())
    typename rgb_array_color<P, C>::b_type
    rgb_array_color<P, C>::b() const
    {
        return _components[b_index];
    }

    using s_rgb24 = rgb_array_color<pixel_format::rgb24, color_space::srgb>;
    using s_bgr24 = rgb_array_color<pixel_format::bgr24, color_space::srgb>;
    using s_rgb48 = rgb_array_color<pixel_format::rgb48, color_space::srgb>;
    using s_bgr48 = rgb_array_color<pixel_format::bgr48, color_space::srgb>;
    using s_rgb96f = rgb_array_color<pixel_format::rgb96f, color_space::srgb>;
    using s_bgr96f = rgb_array_color<pixel_format::bgr96f, color_space::srgb>;

    template<pixel_format P>
    requires (is_array<P>() && has_alpha<P>())
    struct rgba_array_color_traits { };

#define RGBA_ARRAY_COLOR_TRAITS(PIXEL_FORMAT, SCALAR_TYPE, R_INDEX, G_INDEX, B_INDEX, A_INDEX) \
    template<> \
    struct rgba_array_color_traits<pixel_format::PIXEL_FORMAT> \
    { \
        using scalar_type = SCALAR_TYPE; \
        using r_type = red<scalar_type>; \
        using b_type = blue<scalar_type>; \
        using g_type = green<scalar_type>; \
        using a_type = alpha<scalar_type>; \
        static const size_t r_index = R_INDEX; \
        static const size_t g_index = G_INDEX; \
        static const size_t b_index = B_INDEX; \
        static const size_t a_index = A_INDEX; \
        static const size_t size = 4; \
    };

    RGBA_ARRAY_COLOR_TRAITS(rgba128f, float, 0, 1, 2, 3)
    RGBA_ARRAY_COLOR_TRAITS(bgra128f, float, 3, 2, 1, 0)
#undef RGBA_ARRAY_COLOR_TRAITS

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    class alignas(alignof(typename rgba_array_color_traits<P>::scalar_type)) rgba_array_color
    : boost::equality_comparable<rgba_array_color<P, C>
    , boost::additive<rgba_array_color<P, C>
    , boost::multiplicative<rgba_array_color<P, C>
    , boost::multiplicative<rgba_array_color<P, C>, typename rgba_array_color_traits<P>::scalar_type
    > > > >
    {
    public:
        static const pixel_format format = P;

        static const color_space color_space = C;

        using scalar_type = typename rgba_array_color_traits<P>::scalar_type;

        using r_type = typename rgba_array_color_traits<P>::r_type;

        using b_type = typename rgba_array_color_traits<P>::b_type;

        using g_type = typename rgba_array_color_traits<P>::g_type;

        using a_type = typename rgba_array_color_traits<P>::a_type;

        static const size_t size = rgba_array_color_traits<P>::size;

        static const size_t r_index = rgba_array_color_traits<P>::r_index;

        static const size_t g_index = rgba_array_color_traits<P>::g_index;

        static const size_t b_index = rgba_array_color_traits<P>::b_index;

        static const size_t a_index = rgba_array_color_traits<P>::a_index;

        static const rgba_array_color<P, C> black;

        static const rgba_array_color<P, C> white;

    public:
        rgba_array_color();

        rgba_array_color(r_type r, g_type g, b_type b, a_type a);

        rgba_array_color(rgba_array_color<P, C> const& other);

        rgba_array_color<P, C> & operator=(rgba_array_color<P, C> const& other);

        rgba_array_color<P, C> & operator*=(rgba_array_color<P, C> const& other);

        rgba_array_color<P, C> & operator/=(rgba_array_color<P, C> const& other);

        rgba_array_color<P, C> & operator+=(rgba_array_color<P, C> const& other);

        rgba_array_color<P, C> & operator-=(rgba_array_color<P, C> const& other);
        
        rgba_array_color<P, C> & operator*=(scalar_type scalar);

        rgba_array_color<P, C> & operator/=(scalar_type scalar);

        bool operator==(rgba_array_color<P, C> const& other) const;

        r_type r() const;

        g_type g() const;

        b_type b() const;

        a_type a() const;

    private:
        scalar_type _components[size];
    };

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    struct pixel_color<P, C>
    {
        using type = rgba_array_color<P, C>;
    };

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> const rgba_array_color<P, C>::black(
        base_color_limits<r_type>::min(),
        base_color_limits<g_type>::min(),
        base_color_limits<b_type>::min(),
        base_color_limits<a_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> const rgba_array_color<P, C>::white(
        base_color_limits<r_type>::max(),
        base_color_limits<g_type>::max(),
        base_color_limits<b_type>::max(),
        base_color_limits<b_type>::max()
    );

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C>::rgba_array_color()
    {
        _components[r_index] = base_color_limits<r_type>::min();
        _components[g_index] = base_color_limits<g_type>::min();
        _components[b_index] = base_color_limits<b_type>::min();
        _components[a_index] = base_color_limits<a_type>::min();
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C>::rgba_array_color(r_type r, g_type g, b_type b, a_type a)
    {
        _components[r_index] = r;
        _components[g_index] = g;
        _components[b_index] = b;
        _components[a_index] = a;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C>::rgba_array_color(rgba_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] = other._components[i];
        }
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator=(rgba_array_color<P, C> const& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < size; ++i)
            {
                _components[i] = other._components[i];
            }
        }
        return *this;
    }
            
    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator*=(rgba_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] *= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator/=(rgba_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] /= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator+=(rgba_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] += other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator-=(rgba_array_color<P, C> const& other)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] -= other._components[i];
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator*=(scalar_type scalar)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] *= scalar;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    rgba_array_color<P, C> &
    rgba_array_color<P, C>::operator/=(scalar_type scalar)
    {
        for (size_t i = 0; i < size; ++i)
        {
            _components[i] /= scalar;
        }
        return *this;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    bool
    rgba_array_color<P, C>::operator==(rgba_array_color<P, C> const& other) const
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (_components[i] != other._components[i])
            {
                return false;
            }
        }
        return true;
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_array_color<P, C>::r_type
    rgba_array_color<P, C>::r() const
    {
        return _components[r_index];
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_array_color<P, C>::g_type
    rgba_array_color<P, C>::g() const
    {
        return _components[g_index];
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_array_color<P, C>::b_type
    rgba_array_color<P, C>::b() const
    {
        return _components[b_index];
    }

    template<pixel_format P, color_space C>
    requires (is_array<P>() && has_alpha<P>() && is_rgb_color_space<C>())
    typename rgba_array_color<P, C>::a_type
    rgba_array_color<P, C>::a() const
    {
        return _components[a_index];
    }

    using s_rgba64 = rgba_array_color<pixel_format::rgba64, color_space::srgb>;
    using s_argb64 = rgba_array_color<pixel_format::argb64, color_space::srgb>;
    using s_bgra64 = rgba_array_color<pixel_format::bgra64, color_space::srgb>;
    using s_abgr64 = rgba_array_color<pixel_format::abgr64, color_space::srgb>;
    using s_rgba128f = rgba_array_color<pixel_format::rgba128f, color_space::srgb>;
    using s_bgra128f = rgba_array_color<pixel_format::bgra128f, color_space::srgb>;
}

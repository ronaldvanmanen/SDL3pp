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

#include <random>
#include <type_traits>

#include "SDL3pp/array_color.hpp"
#include "SDL3pp/base_color.hpp"
#include "SDL3pp/numerics.hpp"
#include "SDL3pp/packed_color.hpp"

namespace sdl3::unit_test::tools
{
    template<class T>
    struct promote
    {
        using type = T;
    };

    template<>
    struct promote<std::uint8_t>
    {
        using type = unsigned short;
    };

    template<class ClampedInt>
    requires (is_clamped_integral_v<ClampedInt>)
    class uniform_clamped_int_distribution
    {
    public:
        using result_type = ClampedInt;

    private:
        using int_type = promote<
            typename base_type<result_type>::type
        >::type;

    public:
        uniform_clamped_int_distribution()
        : _distribution(
            static_cast<int_type>(std::numeric_limits<result_type>::min()),
            static_cast<int_type>(std::numeric_limits<result_type>::max())
        )
        { }

        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(_distribution(engine));
        }

    private:
        std::uniform_int_distribution<int_type> _distribution;
    };

    template<class ClampedReal>
    requires (is_clamped_floating_point_v<ClampedReal>)
    class uniform_clamped_real_distribution
    {
    public:
        using result_type = ClampedReal;

    private:
        using real_type = base_type<result_type>::type;

    public:
        uniform_clamped_real_distribution()
        : _distribution(
            static_cast<real_type>(std::numeric_limits<result_type>::min()),
            static_cast<real_type>(std::numeric_limits<result_type>::max())
        )
        { }

        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(_distribution(engine));
        }

    private:
        std::uniform_real_distribution<real_type> _distribution;
    };

    template<typename Color>
    class uniform_color_distribution
    { };

    template<typename T, typename Tag>
    requires (is_clamped_integral_v<T>)
    class uniform_color_distribution<base_color<T, Tag> >
    {
    public:
        using result_type = base_color<T, Tag>;

    public:
        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(_distribution(engine));
        }

    private:
        uniform_clamped_int_distribution<T> _distribution;
    };

    template<typename T, typename Tag>
    requires (is_clamped_floating_point_v<T>)
    class uniform_color_distribution<base_color<T, Tag> >
    {
    public:
        using result_type = base_color<T, Tag>;

    public:
        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(_distribution(engine));
        }

    private:
        uniform_clamped_real_distribution<T> _distribution;
    };

    template<pixel_format P, color_space C>
    class uniform_color_distribution<rgb_packed_color<P, C>>
    {
    public:
        using result_type = rgb_packed_color<P, C>;

    private:
        using r_type = result_type::r_type;
        using g_type = result_type::g_type;
        using b_type = result_type::b_type;

    public:
        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(
                _r_distribution(engine),
                _g_distribution(engine),
                _b_distribution(engine)
            );
        }

    private:
        uniform_color_distribution<r_type> _r_distribution;
        uniform_color_distribution<g_type> _g_distribution;
        uniform_color_distribution<b_type> _b_distribution;
    };

    template<pixel_format P, color_space C>
    class uniform_color_distribution<rgba_packed_color<P, C>>
    {
    public:
        using result_type = rgba_packed_color<P, C>;

    private:
        using r_type = result_type::r_type;
        using g_type = result_type::g_type;
        using b_type = result_type::b_type;
        using a_type = result_type::a_type;

    public:
        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(
                _r_distribution(engine),
                _g_distribution(engine),
                _b_distribution(engine),
                _a_distribution(engine)
            );
        }

    private:
        uniform_color_distribution<r_type> _r_distribution;
        uniform_color_distribution<g_type> _g_distribution;
        uniform_color_distribution<b_type> _b_distribution;
        uniform_color_distribution<a_type> _a_distribution;
    };

    template<pixel_format P, color_space C>
    class uniform_color_distribution<rgb_array_color<P, C> >
    {
    public:
        using result_type = rgb_array_color<P, C>;

    private:
        using r_type = result_type::r_type;
        using g_type = result_type::g_type;
        using b_type = result_type::b_type;

    public:
        template <class Engine>
        result_type operator()(Engine & engine) /*const*/
        {
            return result_type(
                _r_distribution(engine),
                _g_distribution(engine),
                _b_distribution(engine)
            );
        }

    private:
        uniform_color_distribution<r_type> _r_distribution;
        uniform_color_distribution<g_type> _g_distribution;
        uniform_color_distribution<b_type> _b_distribution;
    };

}

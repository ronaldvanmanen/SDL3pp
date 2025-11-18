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
#include <iostream>

#include <SDL3/SDL_pixels.h>

#include "error.hpp"
#include "numerics.hpp"

namespace sdl3
{
    enum class pixel_type : std::uint32_t
    {
        unknown = SDL_PIXELTYPE_UNKNOWN,
        index1 = SDL_PIXELTYPE_INDEX1,
        index2 = SDL_PIXELTYPE_INDEX2,
        index4 = SDL_PIXELTYPE_INDEX4,
        index8 = SDL_PIXELTYPE_INDEX8,
        packed8 = SDL_PIXELTYPE_PACKED8,
        packed16 = SDL_PIXELTYPE_PACKED16,
        packed32 = SDL_PIXELTYPE_PACKED32,
        array_u8 = SDL_PIXELTYPE_ARRAYU8,
        array_u16 = SDL_PIXELTYPE_ARRAYU16,
        array_u32 = SDL_PIXELTYPE_ARRAYU32,
        array_f16 = SDL_PIXELTYPE_ARRAYF16,
        array_f32 = SDL_PIXELTYPE_ARRAYF32
    };

    enum class bitmap_order
    {
        none = SDL_BITMAPORDER_NONE,
        b4321 = SDL_BITMAPORDER_4321,
        b1234 = SDL_BITMAPORDER_1234
    };

    enum class packed_order
    {
        none = SDL_PACKEDORDER_NONE,
        xrgb = SDL_PACKEDORDER_XRGB,
        rgbx = SDL_PACKEDORDER_RGBX,
        argb = SDL_PACKEDORDER_ARGB,
        rgba = SDL_PACKEDORDER_RGBA,
        xbgr = SDL_PACKEDORDER_XBGR,
        bgrx = SDL_PACKEDORDER_BGRX,
        abgr = SDL_PACKEDORDER_ABGR,
        bgra = SDL_PACKEDORDER_BGRA
    };

    enum class array_order
    {
        none = SDL_ARRAYORDER_NONE,
        rgb = SDL_ARRAYORDER_RGB,
        rgba = SDL_ARRAYORDER_RGBA,
        argb = SDL_ARRAYORDER_ARGB,
        bgr = SDL_ARRAYORDER_BGR,
        bgra = SDL_ARRAYORDER_BGRA,
        abgr = SDL_ARRAYORDER_ABGR
    };

    enum class packed_layout
    {
        none = SDL_PACKEDLAYOUT_NONE,
        p332 = SDL_PACKEDLAYOUT_332,
        p4444 = SDL_PACKEDLAYOUT_4444,
        p1555 = SDL_PACKEDLAYOUT_1555,
        p5551 = SDL_PACKEDLAYOUT_5551,
        p565 = SDL_PACKEDLAYOUT_565,
        p8888 = SDL_PACKEDLAYOUT_8888,
        p2101010 = SDL_PACKEDLAYOUT_2101010,
        p1010102 = SDL_PACKEDLAYOUT_1010102
    };

    enum class pixel_format : std::uint32_t
    {
        unknown = SDL_PIXELFORMAT_UNKNOWN,
        index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
        index1msb = SDL_PIXELFORMAT_INDEX1MSB,
        index2lsb = SDL_PIXELFORMAT_INDEX2LSB,
        index2msb = SDL_PIXELFORMAT_INDEX2MSB,
        index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
        index4msb = SDL_PIXELFORMAT_INDEX4MSB,
        index8 = SDL_PIXELFORMAT_INDEX8,
        rgb332 = SDL_PIXELFORMAT_RGB332,
        xrgb4444 = SDL_PIXELFORMAT_XRGB4444,
        xbgr4444 = SDL_PIXELFORMAT_XBGR4444,
        xrgb1555 = SDL_PIXELFORMAT_XRGB1555,
        xbgr1555 = SDL_PIXELFORMAT_XBGR1555,
        argb4444 = SDL_PIXELFORMAT_ARGB4444,
        rgba4444 = SDL_PIXELFORMAT_RGBA4444,
        abgr4444 = SDL_PIXELFORMAT_ABGR4444,
        bgra4444 = SDL_PIXELFORMAT_BGRA4444,
        argb1555 = SDL_PIXELFORMAT_ARGB1555,
        rgba5551 = SDL_PIXELFORMAT_RGBA5551,
        abgr1555 = SDL_PIXELFORMAT_ABGR1555,
        bgra5551 = SDL_PIXELFORMAT_BGRA5551,
        rgb565 = SDL_PIXELFORMAT_RGB565,
        bgr565 = SDL_PIXELFORMAT_BGR565,
        rgb24 = SDL_PIXELFORMAT_RGB24,
        bgr24 = SDL_PIXELFORMAT_BGR24,
        xrgb8888 = SDL_PIXELFORMAT_XRGB8888,
        rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
        xbgr8888 = SDL_PIXELFORMAT_XBGR8888,
        bgrx8888 = SDL_PIXELFORMAT_BGRX8888,
        argb8888 = SDL_PIXELFORMAT_ARGB8888,
        rgba8888 = SDL_PIXELFORMAT_RGBA8888,
        abgr8888 = SDL_PIXELFORMAT_ABGR8888,
        bgra8888 = SDL_PIXELFORMAT_BGRA8888,
        xrgb2101010 = SDL_PIXELFORMAT_XRGB2101010,
        xbgr2101010 = SDL_PIXELFORMAT_XBGR2101010,
        argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
        abgr2101010 = SDL_PIXELFORMAT_ABGR2101010,
        rgb48 = SDL_PIXELFORMAT_RGB48,
        bgr48 = SDL_PIXELFORMAT_BGR48,
        rgba64 = SDL_PIXELFORMAT_RGBA64,
        argb64 = SDL_PIXELFORMAT_ARGB64,
        bgra64 = SDL_PIXELFORMAT_BGRA64,
        abgr64 = SDL_PIXELFORMAT_ABGR64,
        rgb48f = SDL_PIXELFORMAT_RGB48_FLOAT,
        bgr48f = SDL_PIXELFORMAT_BGR48_FLOAT,
        rgba64f = SDL_PIXELFORMAT_RGBA64_FLOAT,
        argb64f = SDL_PIXELFORMAT_ARGB64_FLOAT,
        bgra64f = SDL_PIXELFORMAT_BGRA64_FLOAT,
        abgr64f = SDL_PIXELFORMAT_ABGR64_FLOAT,
        rgb96f = SDL_PIXELFORMAT_RGB96_FLOAT,
        bgr96f = SDL_PIXELFORMAT_BGR96_FLOAT,
        rgba128f = SDL_PIXELFORMAT_RGBA128_FLOAT,
        argb128f = SDL_PIXELFORMAT_ARGB128_FLOAT,
        bgra128f = SDL_PIXELFORMAT_BGRA128_FLOAT,
        abgr128f = SDL_PIXELFORMAT_ABGR128_FLOAT,

        yv12 = SDL_PIXELFORMAT_YV12,
        iyuv = SDL_PIXELFORMAT_IYUV,
        yuy2 = SDL_PIXELFORMAT_YUY2,
        uyvy = SDL_PIXELFORMAT_UYVY,
        yvyu = SDL_PIXELFORMAT_YVYU,
        nv12 = SDL_PIXELFORMAT_NV12,
        nv21 = SDL_PIXELFORMAT_NV21,
        p010 = SDL_PIXELFORMAT_P010,
        external_oes = SDL_PIXELFORMAT_EXTERNAL_OES,

        mjpg = SDL_PIXELFORMAT_MJPG
    };

    template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT>>
    std::basic_string<CharT, Traits, Allocator> name(pixel_format const & value)
    {
        switch (value)
        {
            case pixel_format::unknown:     return "unknown";
            case pixel_format::index1lsb:   return "index1lsb";
            case pixel_format::index1msb:   return "index1msb";
            case pixel_format::index2lsb:   return "index2lsb";
            case pixel_format::index2msb:   return "index2msb";
            case pixel_format::index4lsb:   return "index4lsb";
            case pixel_format::index4msb:   return "index4msb";
            case pixel_format::index8:      return "index8";
            case pixel_format::rgb332:      return "rgb332";
            case pixel_format::xrgb4444:    return "xrgb4444";
            case pixel_format::xbgr4444:    return "xbgr4444";
            case pixel_format::xrgb1555:    return "xrgb1555";
            case pixel_format::xbgr1555:    return "xbgr1555";
            case pixel_format::argb4444:    return "argb4444";
            case pixel_format::rgba4444:    return "rgba4444";
            case pixel_format::abgr4444:    return "abgr4444";
            case pixel_format::bgra4444:    return "bgra4444";
            case pixel_format::argb1555:    return "argb1555";
            case pixel_format::rgba5551:    return "rgba5551";
            case pixel_format::abgr1555:    return "abgr1555";
            case pixel_format::bgra5551:    return "bgra5551";
            case pixel_format::rgb565:      return "rgb565";
            case pixel_format::bgr565:      return "bgr565";
            case pixel_format::rgb24:       return "rgb24";
            case pixel_format::bgr24:       return "bgr24";
            case pixel_format::xrgb8888:    return "xrgb8888";
            case pixel_format::rgbx8888:    return "rgbx8888";
            case pixel_format::xbgr8888:    return "xbgr8888";
            case pixel_format::bgrx8888:    return "bgrx8888";
            case pixel_format::argb8888:    return "argb8888";
            case pixel_format::rgba8888:    return "rgba8888";
            case pixel_format::abgr8888:    return "abgr8888";
            case pixel_format::bgra8888:    return "bgra8888";
            case pixel_format::xrgb2101010: return "xrgb2101010";
            case pixel_format::xbgr2101010: return "xbgr2101010";
            case pixel_format::argb2101010: return "argb2101010";
            case pixel_format::abgr2101010: return "abgr2101010";
            case pixel_format::rgb48:       return "rgb48";
            case pixel_format::bgr48:       return "bgr48";
            case pixel_format::rgba64:      return "rgba64";
            case pixel_format::argb64:      return "argb64";
            case pixel_format::bgra64:      return "bgra64";
            case pixel_format::abgr64:      return "abgr64";
            case pixel_format::rgb48f:      return "rgb48f";
            case pixel_format::bgr48f:      return "bgr48f";
            case pixel_format::rgba64f:     return "rgba64f";
            case pixel_format::argb64f:     return "argb64f";
            case pixel_format::bgra64f:     return "bgra64f";
            case pixel_format::abgr64f:     return "abgr64f";
            case pixel_format::rgb96f:      return "rgb96f";
            case pixel_format::bgr96f:      return "bgr96f";
            case pixel_format::rgba128f:    return "rgba128f";
            case pixel_format::argb128f:    return "argb128f";
            case pixel_format::bgra128f:    return "bgra128f";
            case pixel_format::abgr128f:    return "abgr128f";

            case pixel_format::yv12:         return "yv12";
            case pixel_format::iyuv:         return "iyuv";
            case pixel_format::yuy2:         return "yuy2";
            case pixel_format::uyvy:         return "uyvy";
            case pixel_format::yvyu:         return "yvyu";
            case pixel_format::nv12:         return "nv12";
            case pixel_format::nv21:         return "nv21";
            case pixel_format::p010:         return "p010";
            case pixel_format::external_oes: return "external_oes";

            case pixel_format::mjpg: return "mjpg";

            default: return "unknown";
        }
    }

    template <class CharT, class Traits>
    std::basic_ostream<CharT, Traits> & operator<<(
        std::basic_ostream<CharT, Traits> & stream,
        pixel_format const & value
    )
    {
        return stream << name<CharT, Traits>(value);
    }

    enum class color_type
    {
        unknown = SDL_COLOR_TYPE_UNKNOWN,
        rgb = SDL_COLOR_TYPE_RGB,
        ycbcr = SDL_COLOR_TYPE_YCBCR
    };

    enum class color_space : std::uint32_t
    {
        unknown = SDL_COLORSPACE_UNKNOWN,
        srgb = SDL_COLORSPACE_SRGB,
        srgb_linear = SDL_COLORSPACE_SRGB_LINEAR,
        hdr10 = SDL_COLORSPACE_HDR10,
        jpeg = SDL_COLORSPACE_JPEG,
        bt601_limited = SDL_COLORSPACE_BT601_LIMITED,
        bt601_full = SDL_COLORSPACE_BT601_FULL,
        bt709_limited = SDL_COLORSPACE_BT709_LIMITED,
        bt709_full = SDL_COLORSPACE_BT709_FULL,
        bt2020_limited = SDL_COLORSPACE_BT2020_LIMITED,
        bt2020_full = SDL_COLORSPACE_BT2020_FULL
    };

    template <class CharT, class Traits>
    std::basic_ostream<CharT, Traits> & operator<<(
        std::basic_ostream<CharT, Traits> & stream,
        color_space const & value
    )
    {
        switch (value)
        {
            case color_space::unknown:        stream << "unknown";
            case color_space::srgb:           stream << "srgb";
            case color_space::srgb_linear:    stream << "srgb_linear";
            case color_space::hdr10:          stream << "hdr10";
            case color_space::jpeg:           stream << "jpeg";
            case color_space::bt601_limited:  stream << "bt601_limited";
            case color_space::bt601_full:     stream << "bt601_full";
            case color_space::bt709_limited:  stream << "bt709_limited";
            case color_space::bt709_full:     stream << "bt709_full";
            case color_space::bt2020_limited: stream << "bt2020_limited";
            case color_space::bt2020_full:    stream << "bt2020_full";
        }
        return stream;
    }

    class pixel_format_details
    {
    public:
        pixel_format_details(pixel_format format)
        : _native_handle(check_pointer(SDL_GetPixelFormatDetails(static_cast<SDL_PixelFormat>(format))))
        { }

        pixel_format_details(SDL_PixelFormatDetails const * native_handle)
        : _native_handle(native_handle)
        { }

        pixel_format_details(pixel_format_details const & other)
        : _native_handle(other._native_handle)
        { }

        pixel_format_details(pixel_format_details && other)
        : _native_handle(other._native_handle)
        { }

        [[nodiscard]]
        std::uint8_t bits_per_pixel() const
        {
            return _native_handle->bits_per_pixel;
        }

        [[nodiscard]]
        std::uint8_t bytes_per_pixel() const
        {
            return _native_handle->bytes_per_pixel;
        }

        [[nodiscard]]
        std::uint32_t r_mask() const
        {
            return _native_handle->Rmask;
        }

        [[nodiscard]]
        std::uint32_t g_mask() const
        {
            return _native_handle->Gmask;
        }

        [[nodiscard]]
        std::uint32_t b_mask() const
        {
            return _native_handle->Bmask;
        }

        [[nodiscard]]
        std::uint32_t a_mask() const
        {
            return _native_handle->Amask;
        }

        [[nodiscard]]
        std::uint8_t g_bits() const
        {
            return _native_handle->Gbits;
        }

        [[nodiscard]]
        std::uint8_t r_bits() const
        {
            return _native_handle->Rbits;
        }

        [[nodiscard]]
        std::uint8_t b_bits() const
        {
            return _native_handle->Bbits;
        }

        [[nodiscard]]
        std::uint8_t a_bits() const
        {
            return _native_handle->Abits;
        }

        [[nodiscard]]
        std::uint8_t r_shift() const
        {
            return _native_handle->Rshift;
        }

        [[nodiscard]]
        std::uint8_t g_shift() const
        {
            return _native_handle->Gshift;
        }

        [[nodiscard]]
        std::uint8_t b_shift() const
        {
            return _native_handle->Bshift;
        }

        [[nodiscard]]
        std::uint8_t a_shift() const
        {
            return _native_handle->Ashift;
        }

        [[nodiscard]]
        SDL_PixelFormatDetails const * native_handle()
        {
            return _native_handle;
        }

    private:
        SDL_PixelFormatDetails const * _native_handle;
    };

    using pixel_bit_depth = tagged_numeric<std::size_t, struct pixel_bit_depth_tag>;

    using pixel_byte_depth = tagged_numeric<std::size_t, struct pixel_byte_depth_tag>;

    template <pixel_format P>
    [[nodiscard]]
    static constexpr pixel_type get_pixel_type() noexcept
    {
        return static_cast<pixel_type>(SDL_PIXELTYPE(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr pixel_bit_depth bits_per_pixel() noexcept
    {
        return static_cast<pixel_bit_depth>(SDL_BITSPERPIXEL(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr pixel_byte_depth bytes_per_pixel() noexcept
    {
        return static_cast<pixel_byte_depth>(SDL_BYTESPERPIXEL(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_indexed() noexcept
    {
        return SDL_ISPIXELFORMAT_INDEXED(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_packed() noexcept
    {
        return SDL_ISPIXELFORMAT_PACKED(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_array() noexcept
    {
        return SDL_ISPIXELFORMAT_ARRAY(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_10bit() noexcept
    {
        return SDL_ISPIXELFORMAT_10BIT(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_float() noexcept
    {
        return SDL_ISPIXELFORMAT_FLOAT(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool has_alpha() noexcept
    {
        return SDL_ISPIXELFORMAT_ALPHA(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bool is_four_cc() noexcept
    {
        return SDL_ISPIXELFORMAT_FOURCC(static_cast<SDL_PixelFormat>(P));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr bitmap_order pixel_order() noexcept
        requires(is_indexed<P>())
    {
        return static_cast<bitmap_order>(SDL_PIXELORDER(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr packed_order pixel_order() noexcept
        requires(is_packed<P>())
    {
        return static_cast<packed_order>(SDL_PIXELORDER(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr array_order pixel_order() noexcept
        requires(is_array<P>())
    {
        return static_cast<array_order>(SDL_PIXELORDER(static_cast<SDL_PixelFormat>(P)));
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr packed_layout pixel_layout() noexcept
        requires(is_packed<P>())
    {
        return static_cast<packed_layout>(SDL_PIXELLAYOUT(static_cast<SDL_PixelFormat>(P)));
    }

    template <color_space C>
    [[nodiscard]]
    static constexpr color_type color_space_type() noexcept
    {
        return static_cast<color_type>(SDL_COLORSPACETYPE(static_cast<SDL_Colorspace>(C)));
    }

    template <color_space C>
    [[nodiscard]]
    static constexpr bool is_rgb_color_space() noexcept
    {
        return color_type::rgb == color_space_type<C>();
    }

    template <pixel_format P, color_space C>
    [[nodiscard]]
    static constexpr bool is_compatible_color_space() noexcept
    {
        return (is_array<P>() || is_indexed<P>() || is_packed<P>()) && is_rgb_color_space<C>();
    }

    template <pixel_format P>
    [[nodiscard]]
    static constexpr color_space default_color_space() noexcept
    {
        if (is_four_cc<P>())
        {
            switch (P)
            {
                case pixel_format::mjpg: return color_space::srgb;
                case pixel_format::p010: return color_space::hdr10;
                default:                 return color_space::jpeg;
            }
        }
        if (is_float<P>())
        {
            return color_space::srgb_linear;
        }
        if (is_10bit<P>())
        {
            return color_space::hdr10;
        }
        return color_space::srgb;
    }

    template <pixel_format P, color_space C>
    struct pixel_color
    { };
}  // namespace sdl3

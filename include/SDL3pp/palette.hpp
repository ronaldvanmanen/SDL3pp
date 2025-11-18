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
#include <optional>
#include <vector>

#include <boost/operators.hpp>

#include <SDL3/SDL_pixels.h>

#include "color.hpp"
#include "pixels.hpp"
#include "surface.hpp"

namespace sdl3
{
    class palette
    {
    public:
        class indexed_color
        // clang-format off
        : boost::equality_comparable<indexed_color
        , boost::equality_comparable<indexed_color, color
        > >
        // clang-format on
        {
        public:
            indexed_color(palette * owner, std::size_t index)
            : _owner(owner)
            , _index(index)
            { }

            indexed_color(indexed_color const & other)
            : _owner(other._owner)
            , _index(other._index)
            { }

            indexed_color(indexed_color && other)
            : _owner(std::exchange(other._owner, nullptr))
            , _index(std::exchange(other._index, -1))
            { }

            indexed_color & operator=(color const & value)
            {
                check_result(SDL_SetPaletteColors(
                    _owner->_native_handle,
                    reinterpret_cast<SDL_Color const *>(&value),
                    static_cast<int>(_index),
                    static_cast<int>(1)
                ));

                return *this;
            }

            [[nodiscard]]
            bool operator==(palette::indexed_color const & other)
            {
                return _owner == other._owner && _index == other._index;
            }

            [[nodiscard]]
            bool operator==(color const & other)
            {
                return get() == other;
            }

            [[nodiscard]]
            color const & get() const
            {
                return reinterpret_cast<color const &>(_owner->_native_handle->colors[_index]);
            }

            [[nodiscard]]
            operator color const &() const
            {
                return get();
            }

        private:
            palette * _owner;

            std::size_t _index;
        };

        class const_indexed_color
        // clang-format off
        : boost::equality_comparable<const_indexed_color
        , boost::equality_comparable<const_indexed_color, color
        > >
        // clang-format on
        {
        public:
            const_indexed_color(palette const * owner, std::size_t index)
            : _owner(owner)
            , _index(index)
            { }

            const_indexed_color(const_indexed_color const & other)
            : _owner(other._owner)
            , _index(other._index)
            { }

            [[nodiscard]]
            bool operator==(palette::const_indexed_color const & other)
            {
                return _owner == other._owner && _index == other._index;
            }

            [[nodiscard]]
            bool operator==(color const & other)
            {
                return get() == other;
            }

            [[nodiscard]]
            color const & get() const
            {
                return reinterpret_cast<color const &>(_owner->_native_handle->colors[_index]);
            }

            [[nodiscard]]
            operator color const &() const
            {
                return get();
            }

        private:
            palette const * _owner;

            std::size_t _index;
        };

    public:
        palette(std::size_t size)
        : _native_handle(check_pointer(SDL_CreatePalette(static_cast<int>(size))))
        , _free_handle(true)
        { }

        palette(std::initializer_list<color> colors)
        : _native_handle(check_pointer(SDL_CreatePalette(static_cast<int>(colors.size()))))
        , _free_handle(true)
        {
            check_result(SDL_SetPaletteColors(
                _native_handle,
                reinterpret_cast<SDL_Color const *>(colors.begin()),
                static_cast<int>(0),
                static_cast<int>(colors.size())
            ));
        }

        palette(std::vector<color> const & colors)
        : _native_handle(check_pointer(SDL_CreatePalette(static_cast<int>(colors.size()))))
        , _free_handle(true)
        {
            check_result(SDL_SetPaletteColors(
                _native_handle,
                reinterpret_cast<SDL_Color const *>(&colors[0]),
                static_cast<int>(0),
                static_cast<int>(colors.size())
            ));
        }

        palette(palette const & other)
        : _native_handle(check_pointer(SDL_CreatePalette(static_cast<int>(other.size()))))
        , _free_handle(true)
        {
            check_result(
                SDL_SetPaletteColors(_native_handle, other._native_handle->colors, 0, other._native_handle->ncolors)
            );
        }

        palette(palette && other)
        : _native_handle(std::exchange(other._native_handle, nullptr))
        , _free_handle(std::exchange(other._free_handle, false))
        { }

        palette(SDL_Palette * native_handle, bool free_handle)
        : _native_handle(native_handle)
        , _free_handle(free_handle)
        { }

        ~palette()
        {
            if (_free_handle && _native_handle != nullptr)
            {
                SDL_DestroyPalette(_native_handle);
            }
        }

        palette & operator=(std::initializer_list<color> colors)
        {
            check_result(SDL_SetPaletteColors(
                _native_handle,
                reinterpret_cast<SDL_Color const *>(colors.begin()),
                static_cast<int>(0),
                static_cast<int>(colors.size())
            ));
            return *this;
        }

        palette & operator=(std::vector<color> const & colors)
        {
            check_result(SDL_SetPaletteColors(
                _native_handle,
                reinterpret_cast<SDL_Color const *>(&colors[0]),
                static_cast<int>(0),
                static_cast<int>(colors.size())
            ));
            return *this;
        }

        [[nodiscard]]
        indexed_color operator[](std::size_t index)
        {
            if (index >= size())
            {
                throw std::out_of_range("index must be less than size()");
            }
            return indexed_color(this, index);
        }

        [[nodiscard]]
        const_indexed_color operator[](std::size_t index) const
        {
            if (index >= size())
            {
                throw std::out_of_range("index must be less than size()");
            }
            return const_indexed_color(this, index);
        }

        [[nodiscard]]
        std::size_t size() const
        {
            return _native_handle->ncolors;
        }

        [[nodiscard]]
        SDL_Palette * native_handle()
        {
            return _native_handle;
        }

    private:
        SDL_Palette * _native_handle;

        bool _free_handle;
    };

    template <pixel_format P, color_space C = default_color_space<P>()>
    [[nodiscard]]
    palette create_palette(surface<P, C> & owner)
        requires(is_indexed<P>())
    {
        auto result = SDL_CreateSurfacePalette(owner.native_handle());
        check_result(result != nullptr);
        return palette(result, false);
    }

    template <pixel_format P, color_space C = default_color_space<P>()>
    [[nodiscard]]
    std::optional<palette> get_palette(surface<P, C> & owner)
        requires(is_indexed<P>())
    {
        auto native_handle = SDL_GetSurfacePalette(owner.native_handle());
        if (native_handle == nullptr)
        {
            return std::nullopt;
        }
        return palette(native_handle, false);
    }

    inline std::ostream & operator<<(std::ostream & stream, palette::indexed_color const & value)
    {
        return stream << value.get();
    }
}  // namespace sdl3

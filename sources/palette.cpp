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

#include <utility>

#include "SDL3pp/error.h"
#include "SDL3pp/palette.h"

namespace sdl3
{
    void set_palette_colors(SDL_Palette * palette, SDL_Color const* colors, int first_color, int num_colors)
    {
        throw_last_error(
            SDL_SetPaletteColors(palette, colors, first_color, num_colors)
        );
    }

    void set_palette_colors(SDL_Palette * palette, color const* colors, std::size_t first_color, std::size_t num_colors)
    {
        set_palette_colors(
            palette,
            reinterpret_cast<SDL_Color const*>(colors),
            static_cast<int>(first_color),
            static_cast<int>(num_colors)
        );
    }
}

sdl3::palette::palette(std::size_t size)
: _native_handle(SDL_CreatePalette(static_cast<int>(size)))
, _free_handle(true)
{ }

sdl3::palette::palette(sdl3::surface_base & owner)
: _native_handle(SDL_CreateSurfacePalette(owner.native_handle()))
, _free_handle(false)
{ }

sdl3::palette::palette(std::initializer_list<color> colors)
: _native_handle(SDL_CreatePalette(static_cast<int>(colors.size())))
, _free_handle(true)
{
    set_palette_colors(_native_handle, colors.begin(), 0, colors.size());
}

sdl3::palette::palette(std::vector<color> const& colors)
: _native_handle(SDL_CreatePalette(static_cast<int>(colors.size())))
, _free_handle(true)
{
    set_palette_colors(_native_handle, &colors[0], 0, colors.size());
}

sdl3::palette::palette(sdl3::palette const& other)
: _native_handle(SDL_CreatePalette(static_cast<int>(other.size())))
, _free_handle(true)
{
    set_palette_colors(_native_handle, other._native_handle->colors, 0, other._native_handle->ncolors);
}

sdl3::palette::palette(sdl3::palette && other)
: _native_handle(std::exchange(other._native_handle, nullptr))
, _free_handle(std::exchange(other._free_handle, false))
{ }

sdl3::palette::palette(SDL_Palette *native_handle, bool free_handle)
: _native_handle(native_handle)
, _free_handle(free_handle)
{ }

sdl3::palette::~palette()
{
    if (_free_handle && _native_handle != nullptr)
    {
        SDL_DestroyPalette(_native_handle);
    }
} 

sdl3::palette&
sdl3::palette::operator=(std::initializer_list<sdl3::color> colors)
{
    set_palette_colors(_native_handle, colors.begin(), 0, colors.size());

    return *this;
}

sdl3::palette&
sdl3::palette::operator=(std::vector<sdl3::color> const& colors)
{
    set_palette_colors(_native_handle, &colors[0], 0, colors.size());

    return *this;
}

sdl3::palette::indexed_color
sdl3::palette::operator[](std::size_t index)
{
    if (index >= size())
    {
        throw std::out_of_range("index must be less than size()");
    }
    return sdl3::palette::indexed_color(this, index);
}

sdl3::palette::const_indexed_color
sdl3::palette::operator[](std::size_t index) const
{
    if (index >= size())
    {
        throw std::out_of_range("index must be less than size()");
    }
    return sdl3::palette::const_indexed_color(this, index);
}

std::size_t
sdl3::palette::size() const
{
    return _native_handle->ncolors;
}

SDL_Palette*
sdl3::palette::native_handle()
{
    return _native_handle;
}

sdl3::palette::indexed_color::indexed_color(sdl3::palette * owner, std::size_t index)
: _owner(owner)
, _index(index)
{ }

sdl3::palette::indexed_color::indexed_color(sdl3::palette::indexed_color const& other)
: _owner(other._owner)
, _index(other._index)
{ }

sdl3::palette::indexed_color::indexed_color(sdl3::palette::indexed_color && other)
: _owner(std::exchange(other._owner, nullptr))
, _index(std::exchange(other._index, -1))
{ }

sdl3::palette::indexed_color&
sdl3::palette::indexed_color::operator=(sdl3::color const& value)
{
    sdl3::set_palette_colors(_owner->_native_handle, &value, _index, 1);

    return *this;
}

sdl3::color const&
sdl3::palette::indexed_color::get() const
{
    return reinterpret_cast<sdl3::color const&>(_owner->_native_handle->colors[_index]);
}

sdl3::palette::indexed_color::operator sdl3::color const&() const
{
    return get();
}

sdl3::palette::const_indexed_color::const_indexed_color(sdl3::palette const * owner, std::size_t index)
: _owner(owner)
, _index(index)
{ }

sdl3::palette::const_indexed_color::const_indexed_color(sdl3::palette::const_indexed_color const& other)
: _owner(other._owner)
, _index(other._index)
{ }

sdl3::color const&
sdl3::palette::const_indexed_color::get() const
{
    return reinterpret_cast<sdl3::color const&>(_owner->_native_handle->colors[_index]);
}

sdl3::palette::const_indexed_color::operator sdl3::color const&() const
{
    return get();
}

bool
sdl3::operator==(sdl3::palette::indexed_color const& left, sdl3::palette::indexed_color const& right)
{
    return left.get() == right.get();
}

bool
sdl3::operator!=(sdl3::palette::indexed_color const& left, sdl3::palette::indexed_color const& right)
{
    return !(left == right);
}

bool
sdl3::operator==(sdl3::palette::indexed_color const& left, sdl3::color const& right)
{
    return left.get() == right;
}

bool
sdl3::operator!=(sdl3::palette::indexed_color const& left, sdl3::color const& right)
{
    return !(left == right);
}

bool
sdl3::operator==(sdl3::color const& left, sdl3::palette::indexed_color const& right)
{
    return left == right.get();
}

bool
sdl3::operator!=(sdl3::color const& left, sdl3::palette::indexed_color const& right)
{
    return !(left == right);
}

std::ostream&
sdl3::operator<<(std::ostream& stream, sdl3::palette::indexed_color const& value)
{
    return stream << value.get();
}

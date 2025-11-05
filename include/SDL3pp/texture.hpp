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

namespace sdl3
{
    class renderer;
}

#include <cstdint>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>

#include <SDL3/SDL_render.h>

#include "blend_mode.hpp"
#include "color.hpp"
#include "error.hpp"
#include "pixels.hpp"
#include "properties.hpp"
#include "size.hpp"
#include "window.hpp"

namespace sdl3
{
    enum class texture_access : std::int32_t
    {
        static_access = SDL_TEXTUREACCESS_STATIC,
        streaming_access = SDL_TEXTUREACCESS_STREAMING,
        target_access = SDL_TEXTUREACCESS_TARGET
    };

    class texture_base
    {
    protected:
        texture_base(renderer & owner, pixel_format format, texture_access access, length<int32_t> width, length<int32_t> height);
        
        texture_base(renderer & owner, property_group & properties);

        texture_base(renderer & owner, property_group && properties);

        texture_base(texture_base const& other) = delete;

        texture_base(texture_base && other);

        ~texture_base();

        texture_base & operator=(texture_base const& other) = delete;

    public:
        property_group properties() const;

        SDL_Texture* native_handle();

    protected:
        SDL_Texture* _native_handle;
    };
    
    template<pixel_format P, texture_access A, color_space C = default_color_space<P>()>
    requires (is_compatible_color_space<P, C>())
    class texture : public texture_base
    {
    public:
        static const pixel_format format = P;

        static const color_space color_space = C;

        static const texture_access access = A;

        using pixel_type = typename pixel_color<P, C>::type;

    public:
        texture(renderer & owner, length<std::int32_t> width, length<std::int32_t> height);

        texture(renderer & owner, size_2d<std::int32_t> const& size);

        texture(texture<P, A, C> const& other) = delete;

        texture(texture<P, A, C> && other);

        texture<P, A, C> & operator=(texture<P, A, C> const& other) = delete;

        void update(surface<P, C> const& pixels);

        template<typename CallbackFunction>
        void with_lock(CallbackFunction callback);
    };

    template<pixel_format P, color_space C = default_color_space<P>()>
    using static_texture = texture<P, texture_access::static_access, C>;

    template<pixel_format P, color_space C = default_color_space<P>()>
    using streaming_texture = texture<P, texture_access::streaming_access, C>;

    template<pixel_format P, color_space C = default_color_space<P>()>
    using target_texture = texture<P, texture_access::target_access, C>;
}

#include "texture.ipp"

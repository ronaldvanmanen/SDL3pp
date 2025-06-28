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

#include <SDL3/SDL_properties.h>

#include "error.h"

namespace sdl3
{
    class property_group
    {
    public:
        property_group()
        : _native_handle(SDL_CreateProperties())
        { }

        property_group(SDL_PropertiesID properties_id)
        : _native_handle(properties_id)
        { }

        ~property_group()
        {
            SDL_DestroyProperties(_native_handle);
        }

        template<typename T>
        void set(const char* name, T* value)
        {
            throw_last_error(
                SDL_SetPointerProperty(
                    _native_handle,
                    name,
                    static_cast<void*>(value)
                )
            );
        }

        void set(const char* name, const char* value)
        {
            throw_last_error(
                SDL_SetStringProperty(
                    _native_handle,
                    name,
                    value
                )
            );
        }

        template<typename T>
        void set(const char* name, T value)
        {
            throw_last_error(
                SDL_SetNumberProperty(
                    _native_handle,
                    name,
                    static_cast<std::int64_t>(value)
                )
            );
        }

        void set(const char* name, float value)
        {
            throw_last_error(
                SDL_SetFloatProperty(
                    _native_handle,
                    name,
                    value
                )
            );
        }

        void set(const char* name, bool value)
        {
            throw_last_error(
                SDL_SetBooleanProperty(
                    _native_handle,
                    name,
                    value
                )
            );
        }

        template<typename T>
        T* get(const char* name, T* default_value) const
        {
            return static_cast<T*>(
                SDL_GetPointerProperty(
                    _native_handle,
                    name,
                    static_cast<void*>(default_value)
                )
            );
        }

        const char* get(const char* name, const char* default_value) const
        {
            return SDL_GetStringProperty(
                _native_handle,
                name,
                default_value
            );
        }

        template<typename T>
        T get(const char* name, T default_value) const
        {
            return static_cast<T>(
                SDL_GetNumberProperty(
                    _native_handle,
                    name,
                    static_cast<std::int64_t>(default_value)
                )
            );
        }

        float get(const char* name, float default_value) const
        {
            return SDL_GetFloatProperty(
                _native_handle,
                name,
                default_value
            );
        }

        bool get(const char* name, bool default_value) const
        {
            return SDL_GetBooleanProperty(
                _native_handle,
                name,
                default_value
            );
        }

        bool has(const char* name) const
        {
            return SDL_HasProperty(_native_handle, name);
        }

        void clear(const char* name)
        {
            SDL_ClearProperty(_native_handle, name);
        }
        
        SDL_PropertiesID native_handle()
        {
            return _native_handle;
        }

    private:
        SDL_PropertiesID _native_handle;
    };
}

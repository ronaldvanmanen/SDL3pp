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

#include <SDL3/SDL_events.h>

namespace sdl3
{
    enum class event_type : std::uint32_t
    {
        quit = SDL_EVENT_QUIT,
        app_terminating = SDL_EVENT_TERMINATING,
        app_low_memory = SDL_EVENT_LOW_MEMORY,
        app_will_enter_background = SDL_EVENT_WILL_ENTER_BACKGROUND,
        app_did_enter_background = SDL_EVENT_DID_ENTER_BACKGROUND,
        app_will_enter_foreground = SDL_EVENT_WILL_ENTER_FOREGROUND,
        app_did_enter_foreground = SDL_EVENT_DID_ENTER_FOREGROUND,
        locale_changed = SDL_EVENT_LOCALE_CHANGED,
        // display_event = SDL_DISPLAYEVENT,
        // window_event = SDL_WINDOWEVENT,
        // sys_wm_event = SDL_SYSWMEVENT,
        key_down = SDL_EVENT_KEY_DOWN,
        key_up = SDL_EVENT_KEY_UP,
        text_editing = SDL_EVENT_TEXT_EDITING,
        text_input = SDL_EVENT_TEXT_INPUT,
        keymap_changed = SDL_EVENT_KEYMAP_CHANGED,
        // text_editing_ext = SDL_EVENT_TEXT_EDITING_EXT,
        mouse_motion = SDL_EVENT_MOUSE_MOTION,
        mouse_button_down = SDL_EVENT_MOUSE_BUTTON_DOWN,
        mouse_button_up = SDL_EVENT_MOUSE_BUTTON_UP,
        mouse_wheel = SDL_EVENT_MOUSE_WHEEL,
        joystick_axis_motion = SDL_EVENT_JOYSTICK_AXIS_MOTION,
        joystick_ball_motion = SDL_EVENT_JOYSTICK_BALL_MOTION,
        joystick_hat_motion = SDL_EVENT_JOYSTICK_HAT_MOTION,
        joystick_button_down = SDL_EVENT_JOYSTICK_BUTTON_DOWN,
        joystick_button_up = SDL_EVENT_JOYSTICK_BUTTON_UP,
        joystick_device_added = SDL_EVENT_JOYSTICK_ADDED,
        joystick_device_removed = SDL_EVENT_JOYSTICK_REMOVED,
        joystick_battery_updated = SDL_EVENT_JOYSTICK_BATTERY_UPDATED,
        controller_axis_motion = SDL_EVENT_GAMEPAD_AXIS_MOTION,
        controller_button_down = SDL_EVENT_GAMEPAD_BUTTON_DOWN,
        controller_button_up = SDL_EVENT_GAMEPAD_BUTTON_UP,
        controller_device_added = SDL_EVENT_GAMEPAD_ADDED,
        controller_device_removed = SDL_EVENT_GAMEPAD_REMOVED,
        controller_device_remapped = SDL_EVENT_GAMEPAD_REMAPPED,
        controller_touchpad_down = SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN,
        controller_touchpad_motion = SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION,
        controller_touchpad_up = SDL_EVENT_GAMEPAD_TOUCHPAD_UP,
        controller_sensor_update = SDL_EVENT_GAMEPAD_SENSOR_UPDATE,
        finger_down = SDL_EVENT_FINGER_DOWN,
        finger_up = SDL_EVENT_FINGER_UP,
        finger_motion = SDL_EVENT_FINGER_MOTION,
        // dollar_gesture = SDL_DOLLARGESTURE,
        // dollar_record = SDL_DOLLARRECORD,
        // multigesture = SDL_MULTIGESTURE,
        clipboard_update = SDL_EVENT_CLIPBOARD_UPDATE,
        drop_file = SDL_EVENT_DROP_FILE,
        drop_text = SDL_EVENT_DROP_TEXT,
        drop_begin = SDL_EVENT_DROP_BEGIN,
        drop_complete = SDL_EVENT_DROP_COMPLETE,
        audio_device_added = SDL_EVENT_AUDIO_DEVICE_ADDED,
        audio_device_removed = SDL_EVENT_AUDIO_DEVICE_REMOVED,
        sensor_update = SDL_EVENT_SENSOR_UPDATE,
        render_targets_reset = SDL_EVENT_RENDER_TARGETS_RESET,
        render_device_reset = SDL_EVENT_RENDER_DEVICE_RESET,
        poll_sentinel = SDL_EVENT_POLL_SENTINEL,
        user_event = SDL_EVENT_USER,
    };
}

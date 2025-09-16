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
#include <cassert>
#include <cstdint>
#include <random>
#include <vector>

#include <boost/units/cmath.hpp>

#include "SDL3pp/color.hpp"
#include "SDL3pp/events.hpp"
#include "SDL3pp/indexed_color.hpp"
#include "SDL3pp/packed_color.hpp"
#include "SDL3pp/palette.hpp"
#include "SDL3pp/pixels.hpp"
#include "SDL3pp/renderer.hpp"
#include "SDL3pp/size.hpp"
#include "SDL3pp/surface.hpp"
#include "SDL3pp/window.hpp"

#include "shared/math.hpp"
#include "shared/stopwatch.hpp"

using sdl3::px;
using sdl3::operator""_r8;
using sdl3::operator""_g8;
using sdl3::operator""_b8;
using sdl3::operator""_a8;

void
diamond_step(
    sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb> & map,
    std::default_random_engine & random_number_engine,
    sdl3::offset<std::int32_t> center_x,
    sdl3::offset<std::int32_t> center_y,
    sdl3::length<std::int32_t> distance,
    int randomness
)
{
    auto random_number_distribution = std::uniform_int_distribution<int>(-randomness, randomness);
    auto sum = 0;
    auto count = 0;
    auto top = center_y - distance;
    if (top >= 0*px && top < map.height())
    {
        auto left = center_x - distance;
        if (left >= 0*px && left < map.width())
        {
            sum += map(left, top);
            ++count;
        }

        auto right = center_x + distance;
        if (right >= 0*px && right < map.width())
        {
            sum += map(right, top);
            ++count;
        }
    }

    auto bottom = center_y + distance;
    if (bottom >= 0*px && bottom < map.height())
    {
        auto left = center_x - distance;
        if (left >= 0*px && left < map.width())
        {
            sum += map(left, bottom);
            ++count;
        }

        auto right = center_x + distance;
        if (right >= 0*px && right < map.width())
        {
            sum += map(right, bottom);
            ++count;
        }
    }

    int average = sum / count;
    int random = random_number_distribution(random_number_engine);
    int value = std::clamp(average + random, 0, 255);

    map(center_x, center_y) = static_cast<sdl3::index8>(value);
}

void
square_step(
    sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb> & map,
    std::default_random_engine & random_number_engine,
    sdl3::offset<std::int32_t> center_x,
    sdl3::offset<std::int32_t> center_y,
    sdl3::length<std::int32_t> distance,
    int randomness
)
{
    auto random_number_distribution = std::uniform_int_distribution<int>(-randomness, randomness);
    auto sum = 0;
    auto count = 0;
    auto top = center_y - distance;
    if (top >= 0*px && top < map.height())
    {
        sum += map(center_x, top);
        ++count;
    }

    auto left = center_x - distance;
    if (left >= 0*px && left < map.width())
    {
        sum += map(left, center_y);
        ++count;
    }

    auto bottom = center_y + distance;
    if (bottom >= 0*px && bottom < map.height())
    {
        sum += map(center_x, bottom);
        ++count;
    }

    auto right = center_x + distance;
    if (right >= 0*px && right < map.width())
    {
        sum += map(right, center_y);
        ++count;
    }

    int average = sum / count;
    int random = random_number_distribution(random_number_engine);
    int value = std::clamp(average + random, 0, 255);

    map(center_x, center_y) = static_cast<sdl3::index8>(value);
}

sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb>
generate_diamond_square_image(
    std::default_random_engine & random_number_engine,
    sdl3::length<std::int32_t> square_size
)
{
    auto actual_size = sdl3::size_2d<std::int32_t>(1*px + sdl3::next_power_of_two(square_size));
    auto actual_surface = sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb>(actual_size);
    actual_surface.with_lock([&random_number_engine](sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb> & image)
    {
        const auto image_width = image.width();
        const auto image_height = image.height();
        const auto initial_randomness = 256;
        
        auto random_number_distribution = std::uniform_int_distribution<int>(0, initial_randomness - 1);

        image(0*px,                 0*px)                   = sdl3::index8(random_number_distribution(random_number_engine));
        image(image_width - 1*px,   0*px)                   = sdl3::index8(random_number_distribution(random_number_engine));
        image(0*px,                 image_height - 1*px)    = sdl3::index8(random_number_distribution(random_number_engine));
        image(image_width - 1*px,   image_height - 1*px)    = sdl3::index8(random_number_distribution(random_number_engine));

        auto randomness = initial_randomness / 2;

        for (auto step_size = image_height - 1*px; step_size > 1*px; step_size /= 2)
        {
            auto half_step_size = step_size / 2;

            for (auto y = half_step_size; y < image_height; y += step_size)
            {
                for (auto x = half_step_size; x < image_width; x += step_size)
                {
                    diamond_step(image, random_number_engine, x, y, half_step_size, randomness);
                }
            }

            for (auto y = 0*px; y < image_height; y += half_step_size)
            {
                for (auto x = boost::units::fmod(y, step_size) == 0*px ? half_step_size : 0*px; x < image_width; x += step_size)
                {
                    square_step(image, random_number_engine, x, y, half_step_size, randomness);
                }
            }

            randomness /= 2;
        }
    });

    return actual_surface;
}

sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb>
generate_diamond_square_image(
    std::default_random_engine &random_number_engine,
    sdl3::length<std::int32_t> width,
    sdl3::length<std::int32_t> height
)
{
    return generate_diamond_square_image(random_number_engine, std::max(width, height));
}

sdl3::surface<sdl3::pixel_format::index8, sdl3::color_space::srgb>
generate_diamond_square_image(std::default_random_engine &random_number_engine, sdl3::size_2d<std::int32_t> size)
{
    return generate_diamond_square_image(random_number_engine, size.width, size.height);
}

void rotate_left(std::vector<sdl3::color> & palette)
{
    rotate(palette.begin(), palette.begin() + 1, palette.end());
}

void rotate_right(std::vector<sdl3::color> & palette)
{
    rotate(palette.begin(), palette.end() - 1, palette.end());
}

int main()
{
    auto window = sdl3::window("Plasma Fractal", 640*px, 480*px);
    auto event_queue = sdl3::event_queue();

    auto random_number_engine = std::default_random_engine(0);
    auto plasma_surface = generate_diamond_square_image(random_number_engine, window.size());
    auto plasma_palette = create_palette(plasma_surface);
    auto plasma_colors = std::vector<sdl3::color>(256);

    for (sdl3::safe_uint8_t i = 0; i < 32; ++i)
    {
        sdl3::safe_uint8_t lo = i * 255 / 31;
        sdl3::safe_uint8_t hi = 255 - lo;
        plasma_colors[i]        = sdl3::color(sdl3::r8(lo), sdl3::g8(0),  sdl3::b8(0),  sdl3::a8(255));
        plasma_colors[i + 32]   = sdl3::color(sdl3::r8(hi), sdl3::g8(0),  sdl3::b8(0),  sdl3::a8(255));
        plasma_colors[i + 64]   = sdl3::color(sdl3::r8(0),  sdl3::g8(lo), sdl3::b8(0),  sdl3::a8(255));
        plasma_colors[i + 96]   = sdl3::color(sdl3::r8(0),  sdl3::g8(hi), sdl3::b8(0),  sdl3::a8(255));
        plasma_colors[i + 128]  = sdl3::color(sdl3::r8(0),  sdl3::g8(0),  sdl3::b8(lo), sdl3::a8(255));
        plasma_colors[i + 160]  = sdl3::color(sdl3::r8(0),  sdl3::g8(0),  sdl3::b8(hi), sdl3::a8(255));
        plasma_colors[i + 192]  = sdl3::color(sdl3::r8(lo), sdl3::g8(0),  sdl3::b8(lo), sdl3::a8(255));
        plasma_colors[i + 224]  = sdl3::color(sdl3::r8(hi), sdl3::g8(0),  sdl3::b8(hi), sdl3::a8(255));
    }

    plasma_palette = plasma_colors;

    auto stopwatch = sdl3::stopwatch::start_now();
    auto reverse_rotation = false;
    auto running = true;
    while (running)
    {
        sdl3::event polled_event;
        if (event_queue.poll(polled_event))
        {
            polled_event.handle(sdl3::event_handler
            {
                [&running](sdl3::quit_event &&)
                {
                    running = false;
                },

                [&reverse_rotation](sdl3::key_up_event && key_event)
                {
                    auto const scan_code = key_event.scan_code();
                    if (scan_code == sdl3::scan_code::r)
                    {
                        reverse_rotation = !reverse_rotation;
                    }
                },

                [](auto &&) { }
            });
        }
        else
        {
            auto window_surface = window.surface();
            window_surface.blit(plasma_surface);
            window.update_surface();

            static const auto refresh_rate = sdl3::fractional_seconds(1.0 / 60.0);
            const auto elapsed = elapsed_seconds(stopwatch);
            if (elapsed < refresh_rate)
            {
                continue;
            }

            stopwatch.reset();

            if (reverse_rotation)
            {
                rotate_right(plasma_colors);
            }
            else
            {
                rotate_left(plasma_colors);
            }

            plasma_palette = plasma_colors;
        }
    }

    return 0;
}

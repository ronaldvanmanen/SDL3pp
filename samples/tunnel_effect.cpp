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

#include <chrono>
#include <cmath>
#include <cstdint>
#include <numbers>

#include <boost/units/cmath.hpp>

#include "SDL3pp/color.h"
#include "SDL3pp/event_queue.h"
#include "SDL3pp/event.h"
#include "SDL3pp/packed_color.h"
#include "SDL3pp/renderer.h"
#include "SDL3pp/surface.h"
#include "SDL3pp/texture.h"
#include "SDL3pp/window.h"

#include "shared/math.h"
#include "shared/stopwatch.h"

using sdl3::px;
using sdl3::second;

struct displacement
{
    displacement()
    : displacement(0, 0)
    {}

    displacement(sdl3::length<std::int32_t> x, sdl3::length<std::int32_t> y)
    : x(x), y(y)
    { }

    sdl3::length<std::int32_t> x;

    sdl3::length<std::int32_t> y;
};

class displacement_table
{
public:
    displacement_table(sdl3::size_2d<std::int32_t> size);

    displacement_table(sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height);

    ~displacement_table();

public:
    sdl3::length<std::int32_t> width() const;

    sdl3::length<std::int32_t> height() const;

    displacement& operator()(sdl3::offset<int32_t> x, sdl3::offset<int32_t> y);

    displacement const& operator()(sdl3::offset<int32_t> x, sdl3::offset<int32_t> y) const;

private:
    displacement* _pixels;

    sdl3::length<std::int32_t> _width;

    sdl3::length<std::int32_t> _height;
};

displacement_table::displacement_table(sdl3::size_2d<std::int32_t> size)
: displacement_table(size.width, size.height)
{ }

displacement_table::displacement_table(sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height)
: _pixels(new displacement[boost::units::quantity_cast<std::size_t>(height) * boost::units::quantity_cast<std::size_t>(width)])
, _width(width)
, _height(height)
{ }

displacement_table::~displacement_table()
{
    delete[] _pixels;
}

sdl3::length<std::int32_t>
displacement_table::width() const
{
    return _width;
}

sdl3::length<std::int32_t>
displacement_table::height() const
{
    return _height;
}

displacement&
displacement_table::operator()(sdl3::offset<std::int32_t> x, sdl3::offset<std::int32_t> y)
{
    return _pixels[
        boost::units::quantity_cast<std::size_t>(y * _height / px + x)
    ];
}

displacement const&
displacement_table::operator()(sdl3::offset<std::int32_t> x, sdl3::offset<std::int32_t> y) const
{
    return _pixels[
        boost::units::quantity_cast<std::size_t>(y * _height / px + x)
    ];
}

sdl3::length<double>
calc_distance(sdl3::length<double> width, sdl3::length<double> height, sdl3::offset<double> x, sdl3::offset<double> y)
{
    // distance = int(ratio * texHeight / sqrt((x - w / 2.0) * (x - w / 2.0) + (y - h / 2.0) * (y - h / 2.0))) % texHeight;
    const double ratio = 32;
    return sdl3::length<double>::from_value(
        fmod(
            ratio * height / boost::units::sqrt(
                boost::units::pow<2>(x - width / 2.0) +
                boost::units::pow<2>(y - height / 2.0)
            ),
            boost::units::quantity_cast<double>(height)
        )
    );
}

sdl3::length<double>
calc_angle(sdl3::length<double> width, sdl3::length<double> height, sdl3::offset<double> x, sdl3::offset<double> y)
{
    // angle = (unsigned int)(0.5 * texWidth * atan2(y - h / 2.0, x - w / 2.0) / 3.1416);
    return sdl3::length<double>::from_value(
        boost::units::quantity_cast<double>(
            0.5 * width * boost::units::atan2(y - height / 2.0, x - width / 2.0) / std::numbers::pi
        )
    );
}

displacement_table
generate_displacement_image(sdl3::length<std::int32_t> square_size)
{
    auto const actual_size = next_power_of_two(square_size);

    displacement_table displacement_image(actual_size, actual_size);

    for (sdl3::offset<std::int32_t> y = 0*px; y < actual_size; y += 1*px)
    {
        for (sdl3::offset<std::int32_t> x = 0*px; x < actual_size; x += 1*px)
        {
            auto displace_x = sdl3::length<std::int32_t>(calc_distance(actual_size, actual_size, x, y));
            auto displace_y = sdl3::length<std::int32_t>(calc_angle(actual_size, actual_size, x, y));
            displacement_image(x, y) = displacement(displace_x, displace_y);
        }
    }

    return displacement_image;
}

displacement_table
generate_displacement_image(sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height)
{
    return generate_displacement_image(
        std::max(width, height)
    );
}

displacement_table
generate_displacement_table(sdl3::size_2d<std::int32_t> size)
{
    return generate_displacement_image(size.width, size.height);
}

sdl3::surface<sdl3::sargb8888>
generate_xor_image(sdl3::length<std::int32_t> square_size)
{
    sdl3::length<std::int32_t> actual_size = next_power_of_two(square_size);

    sdl3::surface<sdl3::sargb8888> xor_image(actual_size, actual_size);

    for (sdl3::offset<int32_t> y = 0; y < actual_size; y += 1*px)
    {
        for (sdl3::offset<int32_t> x = 0; x < actual_size; x += 1*px)
        {
            xor_image(x, y) = sdl3::sargb8888(
                sdl3::a8(0xFF),
                sdl3::r8(0x00),
                sdl3::g8(0x00),
                sdl3::b8((x * 256 / actual_size) ^ (y * 256 / actual_size))
            );
        }
    }

    return xor_image;
}

sdl3::surface<sdl3::sargb8888>
generate_xor_image(sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height)
{
    return generate_xor_image(std::max(width, height));
}

sdl3::surface<sdl3::sargb8888>
generate_xor_image(sdl3::size_2d<std::int32_t> const& size)
{
    return generate_xor_image(size.width, size.height);
}

sdl3::length<std::int32_t>
power_of_two_mod(sdl3::length<std::int32_t> x, sdl3::length<std::int32_t> y)
{
    const auto x_value = boost::units::quantity_cast<int32_t>(x);
    const auto y_value = boost::units::quantity_cast<int32_t>(y);
    return sdl3::length<std::int32_t>::from_value(x_value & (y_value - 1));
}

int main()
{
    auto window = sdl3::window("Tunnel Effect", 800*px, 600*px, sdl3::window_flags::resizable);
    auto renderer = sdl3::renderer(window);
    auto texture = sdl3::texture<sdl3::sargb8888>(renderer, sdl3::texture_access::streaming_access, renderer.output_size());

    auto event_queue = sdl3::event_queue();

    auto source_image = generate_xor_image(renderer.output_size());
    auto displacement_table = generate_displacement_table(renderer.output_size());
    auto target_image = sdl3::surface<sdl3::sargb8888>(renderer.output_size());
    
    auto stopwatch = sdl3::stopwatch::start_now();
    auto running = true;
    while (running)
    {
        sdl3::event poll_event;
        if (event_queue.poll(poll_event))
        {
            switch (poll_event.type())
            {
                case sdl3::event_type::quit:
                    running = false;
                    break;
            }
        }
        else
        {
            const auto target_width = target_image.width();
            const auto target_height = target_image.height();
            const auto source_width = source_image.width();
            const auto source_height = source_image.height();

            const auto time = elapsed_time(stopwatch);
            const auto speed_x = sdl3::length<double>(source_width) / second;
            const auto speed_y = sdl3::length<double>(source_height) * 0.25 / second;
            const auto shift_x = sdl3::length<std::int32_t>(speed_x * time);
            const auto shift_y = sdl3::length<std::int32_t>(speed_y * time);
            const auto offset_x = (source_width - target_width) / 2;
            const auto offset_y = (source_height - target_height) / 2;

            for (auto target_y = 0*px; target_y < target_height; target_y += 1*px)
            {
                for (auto target_x = 0*px; target_x < target_width; target_x += 1*px)
                {
                    const auto displacement = displacement_table(target_x + offset_x, target_y + offset_y);
                    const auto source_x = power_of_two_mod(displacement.x + shift_x, source_width);
                    const auto source_y = power_of_two_mod(displacement.y + shift_y, source_height);
                    target_image(target_x, target_y) = source_image(source_x, source_y);
                }
            }

            texture.update(target_image);
            renderer.draw_blend_mode(sdl3::blend_mode::none);
            renderer.draw_color(sdl3::color::black);
            renderer.clear();
            renderer.copy(texture);
            renderer.present();
        }
    }

    return 0;
}

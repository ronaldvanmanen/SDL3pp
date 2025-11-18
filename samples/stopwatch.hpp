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
#include <cstdint>

#include "SDL3pp/units.hpp"

namespace sdl3
{
    class stopwatch
    {
    public:
        using clock = std::chrono::steady_clock;
        using time_point = clock::time_point;
        using duration = clock::duration;

    public:
        static stopwatch start_now();

        stopwatch();

        void start();

        void stop();

        void reset();

        duration elapsed();

    private:
        time_point _start_time;

        duration _elapsed_time;

        bool _running;
    };

    using fractional_seconds = std::chrono::duration<double>;

    inline stopwatch stopwatch::start_now()
    {
        stopwatch instance;
        instance.start();
        return instance;
    }

    inline stopwatch::stopwatch()
    : _start_time(time_point::min())
    , _elapsed_time(duration::zero())
    , _running(false)
    { }

    inline void stopwatch::start()
    {
        if (_running)
            return;
        _start_time = clock::now();
        _running = true;
    }

    inline void stopwatch::stop()
    {
        if (!_running)
            return;

        auto end_time = clock::now();
        auto lap_time = end_time - _start_time;
        _elapsed_time += lap_time;
        _running = false;
    }

    inline void stopwatch::reset()
    {
        _start_time = clock::now();
        _elapsed_time = duration::zero();
    }

    inline stopwatch::duration stopwatch::elapsed()
    {
        auto elapsed_time = _elapsed_time;
        if (_running)
        {
            auto now = clock::now();
            auto lap_time = now - _start_time;
            elapsed_time += lap_time;
        }
        return elapsed_time;
    }

    inline fractional_seconds elapsed_seconds(stopwatch & instance)
    {
        return std::chrono::duration_cast<fractional_seconds>(instance.elapsed());
    }

    inline time<double> elapsed_time(stopwatch & instance)
    {
        return sdl3::time<double>(sdl3::elapsed_seconds(instance).count() * sdl3::seconds);
    }
}  // namespace sdl3

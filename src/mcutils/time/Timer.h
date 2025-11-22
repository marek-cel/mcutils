/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MCUTILS_TIME_TIMER_H_
#define MCUTILS_TIME_TIMER_H_

#include <chrono>
#include <thread>

namespace mc {

/**
 * \brief Timer class.
 */
class Timer
{
public:

    /**
     * \brief Start the timer.
     * \param interval timer interval expressed in seconds.
     */
    void Start(double interval)
    {
        _interval = std::chrono::nanoseconds(static_cast<int>(interval * 1.0e9));
        _last_time = std::chrono::steady_clock::now();
    }

    /**
     * \brief Wait for the timeout.
     * \return elapsed time since the last timeout expressed in seconds.
     */
    double WaitForTimeout()
    {
        std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
        std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - _last_time);
        if (elapsed < _interval)
        {
            std::chrono::nanoseconds duration = _interval - elapsed;
            std::this_thread::sleep_for(duration);
        }

        now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - _last_time);

        _last_time = now;

        return static_cast<double>(elapsed.count()) * 1.0e-9;
    }

private:

    std::chrono::nanoseconds _interval;
    std::chrono::time_point<std::chrono::steady_clock> _last_time;
};

} // namespace mc

#endif // MCUTILS_TIME_TIMER_H_

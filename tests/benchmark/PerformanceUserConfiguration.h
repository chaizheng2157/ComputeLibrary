/*
 * Copyright (c) 2017 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ARM_COMPUTE_TEST_PERFORMANCE_PERFORMANCE_USER_CONFIGURATION_H__
#define __ARM_COMPUTE_TEST_PERFORMANCE_PERFORMANCE_USER_CONFIGURATION_H__

#include "UserConfiguration.h"

namespace arm_compute
{
namespace test
{
class ProgramOptions;

namespace performance
{
/** Specialisation of @ref UserConfiguration to provide performance specific
 * configuration options.
 */
struct PerformanceUserConfiguration : public UserConfiguration
{
    PerformanceUserConfiguration() = default;

    /** Initialise the configuration according to the program options.
     *
     * @param[in] options Parsed command line options.
     */
    PerformanceUserConfiguration(const ProgramOptions &options);

    Option<unsigned int> runs{};
};
} // namespace performance

extern performance::PerformanceUserConfiguration user_config;
} // namespace test
} // namespace arm_compute
#endif

/**
 * @file    Stats_c.h
 * @author  Phil Lockett <phillockett65@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Interface for the Safe Implementation.
 * 
 * Safe provides a multi-thread protected counter.
 */

#if !defined(_SAFE_C_H__20260619_1253__INCLUDED_)
#define _SAFE_C_H__20260619_1253__INCLUDED_

#include <mutex>


/**
 * @section Safe Implementation.
 */

template<typename T=int>
class Safe
{
private:
    mutable std::mutex mtx;
    T value;

public:
    T get(void) const { std::lock_guard<std::mutex> lock(mtx); return value; }
    void set(T v) { std::lock_guard<std::mutex> lock(mtx); value = v; }
    void inc(T v=1) { std::lock_guard<std::mutex> lock(mtx); value += v; }

};

#endif // !defined(_SAFE_C_H__20260619_1253__INCLUDED_)

/**
 * @file    test2.cpp
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
 * Dummy module to test Statistics Implementation. Called from test.cpp.
 */

#include "Stats_c.h"


/**
 * Dummy remote function to test Statistics Implementation.
 *
 * @param  count - Statistics count.
 * @return error value or 0 if no errors.
 */
void remoteFunction(int count)
{
//- Do some work. Example that increments the counter with a known value.
    Stats_c<>::incCounter("remote", 20);

//- Do some more work. Example that increments the counter one step at a time.
    for (int i = 0; i < count; ++i)
    {
        Stats_c<>::incCounter("remote");
    }
}


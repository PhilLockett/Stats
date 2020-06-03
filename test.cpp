/**
 * @file    test.cpp
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
 * Unit test code for the Statistics Implementation.
 *
 * Build using:
 *    g++ -c -o Stats_c.o Stats_c.cpp
 *    g++ -c -o test.o test.cpp
 *    g++ -c -o test2.o test2.cpp
 *    g++ -o test test.o test2.o Stats_c.o 
 *
 * Test using:
 *    ./test
 *
 */

#include <iostream>

#include "Stats_c.h"

static Stats_c * statsInst = Stats_c::getInstance();

extern void remoteFunction(int count);

/**
 * Dummy local function to test Statistics Implementation.
 *
 * @param  count - Statistics count.
 * @return error value or 0 if no errors.
 */
void localFunction(const int count)
{
//- Do some work. Example that increments the counter with a known value.
    statsInst->incCounter("Local", 10);

//- Do some more work. Example that increments the counter one at a time.
    for (int i = 0; i < count; ++i)
    {
        statsInst->incCounter("Local");
    }
}

/**
 * Test system entry point.
 *
 * @param  argc - command line argument count.
 * @param  argv - command line argument vector.
 * @return error value or 0 if no errors.
 */
int main(int argc, char *argv[])
{
//- Initialise.
    statsInst->incCounter("main");

//- Status check. 
    std::cout << "Current Statistics:" << std::endl;
    std::cout << *statsInst << std::endl;

//- Do some work.
    localFunction(6);
    remoteFunction(2);   // Call test module with same initial log level.

//- Status check. 
    std::cout << "Current Statistics:" << std::endl;
    std::cout << *statsInst << std::endl;

//- Reset counters and do some more work.
    statsInst->clearAllCounters();
    localFunction(4);
    remoteFunction(7);   // Call test module with verbose log level.

//- Status check. 
    std::cout << "Current Statistics:" << std::endl;
    std::cout << *statsInst << std::endl;

//- One more time without the reset.
    statsInst->setCounter("main", 2);
    localFunction(1);
    remoteFunction(1);   // Call test module with same initial log level.

//- Status check. 
    std::cout << "Current Statistics:" << std::endl;
    std::cout << *statsInst << std::endl;

    return 0;
}


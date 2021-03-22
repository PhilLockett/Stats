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

//- Do some more work. Example that increments the counter one step at a time.
    for (int i = 0; i < count; ++i)
    {
        statsInst->incCounter("Local");
    }
}

int test0(void)
{
    std::cout << "\tTest clearing counters with global reference.\n";
    int err = 0;

    statsInst->clearAllCounters();

    if (statsInst->getCounter("local") != 0)
        err++;

    return err;
}
int test1(void)
{
    std::cout << "\tTest initialisation with global reference.\n";
    int err = 0;

    statsInst->incCounter("local");

    if (statsInst->getCounter("local") != 1)
        err++;

    return err;
}
int test2(void)
{
    std::cout << "\tTest second incrementation with global reference.\n";
    int err = 0;

    statsInst->incCounter("local");

    if (statsInst->getCounter("local") != 2)
        err++;

    return err;
}
int test3(void)
{
    std::cout << "\tTest incrementation by 2 with global reference.\n";
    int err = 0;

    statsInst->incCounter("local", 2);

    if (statsInst->getCounter("local") != 4)
        err++;

    return err;
}
int test4(void)
{
    std::cout << "\tTest multiple increments with global reference.\n";
    int err = 0;

    for (int i = 0; i < 10; ++i)
        statsInst->incCounter("local");

    if (statsInst->getCounter("local") != 14)
        err++;

    return err;
}
int test5(void)
{
    std::cout << "\tTest multiple increments by 5 with global reference.\n";
    int err = 0;

    for (int i = 0; i < 4; ++i)
        statsInst->incCounter("local", 5);

    if (statsInst->getCounter("local") != 34)
        err++;

    return err;
}
int test6(void)
{
    std::cout << "\tTest multiple increments by remote function.\n";
    int err = 0;

    remoteFunction(2);

    if (statsInst->getCounter("local") != 34)
        err++;

    if (statsInst->getCounter("remote") != 22)
        err++;

    return err;
}
int display(void)
{
    std::cout << "Display Current Statistics:\n"  << *statsInst << '\n';
    int err = 0;

    return err;
}
int test7(void)
{
    std::cout << "\tTest clearing counters with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    localStatsInst->clearAllCounters();

    if (localStatsInst->getCounter("local") != 0)
        err++;

    return err;
}
int test8(void)
{
    std::cout << "\tTest initialisation with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    localStatsInst->incCounter("local");

    if (localStatsInst->getCounter("local") != 1)
        err++;

    return err;
}
int test9(void)
{
    std::cout << "\tTest second incrementation with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    localStatsInst->incCounter("local");

    if (localStatsInst->getCounter("local") != 2)
        err++;

    return err;
}
int test10(void)
{
    std::cout << "\tTest incrementation by 2 with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    localStatsInst->incCounter("local", 2);

    if (localStatsInst->getCounter("local") != 4)
        err++;

    return err;
}
int test11(void)
{
    std::cout << "\tTest multiple increments with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 6; ++i)
        localStatsInst->incCounter("local");

    if (localStatsInst->getCounter("local") != 10)
        err++;

    return err;
}
int test12(void)
{
    std::cout << "\tTest multiple increments by 5 with local reference.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 3; ++i)
        localStatsInst->incCounter("local", 5);

    if (localStatsInst->getCounter("local") != 25)
        err++;

    return err;
}
int test13(void)
{
    std::cout << "\tTest multiple increments by remote function.\n";
    int err = 0;

    static Stats_c * localStatsInst = Stats_c::getInstance();
    remoteFunction(7);

    if (localStatsInst->getCounter("local") != 25)
        err++;

    if (localStatsInst->getCounter("remote") != 27)
        err++;

    return err;
}
int test14(void)
{
    std::cout << "\tTest set existing counter to a specific value.\n";
    int err = 0;

    statsInst->setCounter("local", 20);

    if (statsInst->getCounter("local") != 20)
        err++;

    if (statsInst->getCounter("remote") != 27)
        err++;

    return err;
}
int test15(void)
{
    std::cout << "\tTest set new counter to a specific value.\n";
    int err = 0;

    statsInst->setCounter("test", 10);

    if (statsInst->getCounter("test") != 10)
        err++;

    if (statsInst->getCounter("local") != 20)
        err++;

    if (statsInst->getCounter("remote") != 27)
        err++;

    return err;
}


int runTests(void)
{
    std::cout << "Executing all tests.\n";
    int err = 0;

    err += test0();
    err += test1();
    err += test2();
    err += test3();
    err += test4();
    err += test5();
    err += test6();
    err += display();
    err += test7();
    err += test8();
    err += test9();
    err += test10();
    err += test11();
    err += test12();
    err += test13();
    err += display();
    err += test14();
    err += test15();
    err += display();

    if (err)
        std::cerr << err << " ERROR(S) encountered!.\n";
    else
        std::cout << "All tests passed.\n";

    return err;
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
    return runTests();
}


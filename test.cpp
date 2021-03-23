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
#include <sstream>

#include "Stats_c.h"


extern void remoteFunction(int count);

int test0(void)
{
    std::cout << "\tTest clearing counters with direct access.\n";
    int err = 0;

    Stats_c::clearAllCounters();

    if (Stats_c::getCounter("local") != 0)
        err++;

    return err;
}
int test1(void)
{
    std::cout << "\tTest initialisation with direct access.\n";
    int err = 0;

    Stats_c::incCounter("local");

    if (Stats_c::getCounter("local") != 1)
        err++;

    return err;
}
int test2(void)
{
    std::cout << "\tTest second incrementation with direct access.\n";
    int err = 0;

    Stats_c::incCounter("local");

    if (Stats_c::getCounter("local") != 2)
        err++;

    return err;
}
int test3(void)
{
    std::cout << "\tTest incrementation by 2 with direct access.\n";
    int err = 0;

    Stats_c::incCounter("local", 2);

    if (Stats_c::getCounter("local") != 4)
        err++;

    return err;
}
int test4(void)
{
    std::cout << "\tTest multiple increments with direct access.\n";
    int err = 0;

    for (int i = 0; i < 10; ++i)
        Stats_c::incCounter("local");

    if (Stats_c::getCounter("local") != 14)
        err++;

    return err;
}
int test5(void)
{
    std::cout << "\tTest multiple increments by 5 with direct access.\n";
    int err = 0;

    for (int i = 0; i < 4; ++i)
        Stats_c::incCounter("local", 5);

    if (Stats_c::getCounter("local") != 34)
        err++;

    return err;
}
int test6(void)
{
    std::cout << "\tTest multiple increments by remote function.\n";
    int err = 0;

    remoteFunction(2);

    if (Stats_c::getCounter("local") != 34)
        err++;

    if (Stats_c::getCounter("remote") != 22)
        err++;

    return err;
}
int test7(void)
{
    std::cout << "\tTest clearing counters with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.clearAllCounters();

    if (localStatsInst.getCounter("local") != 0)
        err++;

    return err;
}
int test8(void)
{
    std::cout << "\tTest initialisation with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local");

    if (localStatsInst.getCounter("local") != 1)
        err++;

    return err;
}
int test9(void)
{
    std::cout << "\tTest second incrementation with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local");

    if (localStatsInst.getCounter("local") != 2)
        err++;

    return err;
}
int test10(void)
{
    std::cout << "\tTest incrementation by 2 with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local", 2);

    if (localStatsInst.getCounter("local") != 4)
        err++;

    return err;
}
int test11(void)
{
    std::cout << "\tTest multiple increments with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 6; ++i)
        localStatsInst.incCounter("local");

    if (localStatsInst.getCounter("local") != 10)
        err++;

    return err;
}
int test12(void)
{
    std::cout << "\tTest multiple increments by 5 with local reference.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 3; ++i)
        localStatsInst.incCounter("local", 5);

    if (localStatsInst.getCounter("local") != 25)
        err++;

    return err;
}
int test13(void)
{
    std::cout << "\tTest multiple increments by remote function.\n";
    int err = 0;

    static Stats_c & localStatsInst = Stats_c::getInstance();
    remoteFunction(7);

    if (localStatsInst.getCounter("local") != 25)
        err++;

    if (localStatsInst.getCounter("remote") != 27)
        err++;

    return err;
}
int test14(void)
{
    std::cout << "\tTest set existing counter to a specific value.\n";
    int err = 0;

    Stats_c::setCounter("local", 20);

    if (Stats_c::getCounter("local") != 20)
        err++;

    if (Stats_c::getCounter("remote") != 27)
        err++;

    return err;
}
int test15(void)
{
    std::cout << "\tTest set new counter to a specific value.\n";
    int err = 0;

    Stats_c::setCounter("test", 10);

    if (Stats_c::getCounter("test") != 10)
        err++;

    if (Stats_c::getCounter("local") != 20)
        err++;

    if (Stats_c::getCounter("remote") != 27)
        err++;

    return err;
}
std::string getCounterName(int a)
{
    std::stringstream ss;
    ss << "counter" << a;

    return ss.str();
}
int test16(void)
{
    std::cout << "\tTest larger number of counters.\n";
    int err = 0;
    const int COUNTERS = 200000;
    const int INCREMENTS = 4;

    Stats_c::clearAllCounters();

    for (int j = 0; j < INCREMENTS; ++j)
    {
		std::cout << "\t\tIncrementing.\n";
        for (int i = 0; i < COUNTERS; ++i)
        {
            Stats_c::incCounter(getCounterName(i));
        }
    }

    std::cout << "\t\tChecking.\n";
    for (int i = 0; i < COUNTERS; ++i)
    {
        if (Stats_c::getCounter(getCounterName(i)) != INCREMENTS)
            err++;
    }

    return err;
}

void display(void)
{
    std::cout << "Display Current Statistics:\n"  << Stats_c::getInstance() << '\n';
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
    display();
    err += test7();
    err += test8();
    err += test9();
    err += test10();
    err += test11();
    err += test12();
    err += test13();
    display();
    err += test14();
    err += test15();
    display();
    err += test16();

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


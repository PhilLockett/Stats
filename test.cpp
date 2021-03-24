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

#define UNIT_TEST(func, desc) \
int func(void) {\
    std::cout << '\t' << #func << "() - " << desc << '\n'; \
    int err = 0;

#define END_TEST return err; }

#define REQUIRE(cond) if(!(cond)) {\
        err++; \
        std::cerr << "Requirement (" << #cond << ") failed\n"; \
}

UNIT_TEST(test0, "Test clearing counters with direct access.")
    Stats_c::clearAllCounters();

    REQUIRE(Stats_c::getCounter("local") == 0)
END_TEST

UNIT_TEST(test1, "Test initialisation with direct access.")
    Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 1)
END_TEST

UNIT_TEST(test2, "Test second incrementation with direct access.")
    Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 2)
END_TEST

UNIT_TEST(test3, "Test incrementation by 2 with direct access.")
    Stats_c::incCounter("local", 2);

    REQUIRE(Stats_c::getCounter("local") == 4)
END_TEST

UNIT_TEST(test4, "Test multiple increments with direct access.")
    for (int i = 0; i < 10; ++i)
        Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 14)
END_TEST

UNIT_TEST(test5, "Test multiple increments by 5 with direct access.")
    for (int i = 0; i < 4; ++i)
        Stats_c::incCounter("local", 5);

    REQUIRE(Stats_c::getCounter("local") == 34)
END_TEST

UNIT_TEST(test6, "Test multiple increments by remote function.")
    remoteFunction(2);

    REQUIRE(Stats_c::getCounter("local") == 34)
    REQUIRE(Stats_c::getCounter("remote") == 22)
END_TEST

UNIT_TEST(test7, "Test clearing counters with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.clearAllCounters();

    REQUIRE(localStatsInst.getCounter("local") == 0)
END_TEST

UNIT_TEST(test8, "Test initialisation with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local");

    REQUIRE(localStatsInst.getCounter("local") == 1)
END_TEST

UNIT_TEST(test9, "Test second incrementation with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local");

    REQUIRE(localStatsInst.getCounter("local") == 2)
END_TEST

UNIT_TEST(test10, "Test incrementation by 2 with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    localStatsInst.incCounter("local", 2);

    REQUIRE(localStatsInst.getCounter("local") == 4)
END_TEST

UNIT_TEST(test11, "Test multiple increments with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 6; ++i)
        localStatsInst.incCounter("local");

    REQUIRE(localStatsInst.getCounter("local") == 10)
END_TEST

UNIT_TEST(test12, "Test multiple increments by 5 with local reference.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    for (int i = 0; i < 3; ++i)
        localStatsInst.incCounter("local", 5);

    REQUIRE(localStatsInst.getCounter("local") == 25)
END_TEST

UNIT_TEST(test13, "Test multiple increments by remote function.")
    static Stats_c & localStatsInst = Stats_c::getInstance();
    remoteFunction(7);

    REQUIRE(localStatsInst.getCounter("local") == 25)
    REQUIRE(localStatsInst.getCounter("remote") == 27)
END_TEST

UNIT_TEST(test14, "Test set existing counter to a specific value.")
    Stats_c::setCounter("local", 20);

    REQUIRE(Stats_c::getCounter("local") == 20)
    REQUIRE(Stats_c::getCounter("remote") == 27)
END_TEST

UNIT_TEST(test15, "Test set new counter to a specific value.")
    Stats_c::setCounter("test", 10);

    REQUIRE(Stats_c::getCounter("test") == 10)
    REQUIRE(Stats_c::getCounter("local") == 20)
    REQUIRE(Stats_c::getCounter("remote") == 27)
END_TEST

std::string getCounterName(int a)
{
    std::stringstream ss;
    ss << "counter" << a;

    return ss.str();
}
UNIT_TEST(test16, "Test large number of counters.")
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
        REQUIRE(Stats_c::getCounter(getCounterName(i)) == INCREMENTS)
    }
END_TEST


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


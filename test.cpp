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
 *    g++ -std=c++20 -c -o test.o test.cpp
 *    g++ -std=c++20 -c -o test2.o test2.cpp
 *    g++ -std=c++20 -c -o Stats_c.o Stats_c.cpp
 *    g++ -std=c++20 -c -o unittest.o unittest.cpp
 *    g++ -std=c++20 -o test test.o test2.o Stats_c.o unittest.o
 *
 * Test using:
 *    ./test
 *
 */

#include <iostream>
#include <sstream>
#include <vector>

#include "Stats_c.h"

#include "unittest.h"


extern void remoteFunction(int count);


/**
 * @section test statistics using direct calls to the static singleton.
 *
 * All of these are interdependent.
 */
UNIT_TEST(test0, "Test clearing counters with direct access.")
    Stats_c::clearAllCounters();

    REQUIRE(Stats_c::getCounter("local") == 0)

NEXT_CASE(test1, "Test initialisation with direct access.")
    Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 1)

NEXT_CASE(test2, "Test second incrementation with direct access.")
    Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 2)

NEXT_CASE(test3, "Test incrementation by 2 with direct access.")
    Stats_c::incCounter("local", 2);

    REQUIRE(Stats_c::getCounter("local") == 4)

NEXT_CASE(test4, "Test multiple increments with direct access.")
    for (int i = 0; i < 10; ++i)
        Stats_c::incCounter("local");

    REQUIRE(Stats_c::getCounter("local") == 14)

NEXT_CASE(test5, "Test multiple increments by 5 with direct access.")
    for (int i = 0; i < 4; ++i)
        Stats_c::incCounter("local", 5);

    REQUIRE(Stats_c::getCounter("local") == 34)

NEXT_CASE(test6, "Test multiple increments by remote function.")
    remoteFunction(2);

    REQUIRE(Stats_c::getCounter("local") == 34)
    REQUIRE(Stats_c::getCounter("remote") == 22)
END_TEST


/**
 * @section test statistics using a local reference to the static singleton.
 *
 * All of these are interdependent. Most of these test using the local 
 * reference but tests at the end use direct calls to the static singleton
 * to show either way is possible.
 */
UNIT_TEST(test7, "Test clearing counters with local reference.")
    auto & stats = Stats_c::getInstance(); // Could be a reference global to the file.
    stats.clearAllCounters();

    REQUIRE(stats.getCounter("local") == 0)

NEXT_CASE(test8, "Test initialisation with local reference.")
    stats.incCounter("local");

    REQUIRE(stats.getCounter("local") == 1)

NEXT_CASE(test9, "Test second incrementation with local reference.")
    stats.incCounter("local");

    REQUIRE(stats.getCounter("local") == 2)

NEXT_CASE(test10, "Test incrementation by 2 with local reference.")
    stats.incCounter("local", 2);

    REQUIRE(stats.getCounter("local") == 4)

NEXT_CASE(test11, "Test multiple increments with local reference.")
    for (int i = 0; i < 6; ++i)
        stats.incCounter("local");

    REQUIRE(stats.getCounter("local") == 10)

NEXT_CASE(test12, "Test multiple increments by 5 with local reference.")
    for (int i = 0; i < 3; ++i)
        stats.incCounter("local", 5);

    REQUIRE(stats.getCounter("local") == 25)

NEXT_CASE(test13, "Test multiple increments by remote function.")
    remoteFunction(7);

    REQUIRE(stats.getCounter("local") == 25)
    REQUIRE(stats.getCounter("remote") == 27)

NEXT_CASE(test14, "Test set existing counter to a specific value.")
    Stats_c::setCounter("local", 20);

    REQUIRE(Stats_c::getCounter("local") == 20)
    REQUIRE(Stats_c::getCounter("remote") == 27)

NEXT_CASE(test15, "Test set new counter to a specific value.")
    Stats_c::setCounter("test", 10);

    REQUIRE(Stats_c::getCounter("test") == 10)
    REQUIRE(Stats_c::getCounter("local") == 20)
    REQUIRE(Stats_c::getCounter("remote") == 27)
END_TEST


/**
 * @section test a large number of counters being used.
 */
std::string getCounterName(int a)
{
    std::stringstream ss;
    ss << "counter" << a;

    return ss.str();
}
UNIT_TEST(test16, "Test large number of counters.")
    const int COUNTERS = 250000;
    const int INCREMENTS = 4;

    Stats_c::clearAllCounters();

    for (int j = 0; j < INCREMENTS; ++j)
    {
        if (IS_VERBOSE)
            std::cout << "\tIncrementing.\n";
        for (int i = 0; i < COUNTERS; ++i)
        {
            Stats_c::incCounter(getCounterName(i));
        }
    }

    if (IS_VERBOSE)
        std::cout << "\tChecking.\n";
    for (int i = 0; i < COUNTERS; ++i)
    {
        REQUIRE(Stats_c::getCounter(getCounterName(i)) == INCREMENTS)
    }
END_TEST


/**
 * @section test a large number of counters being used by different threads.
 */
static std::mutex displayMutex;

void worker(const int count)
{
    if (IS_VERBOSE)
    {
        std::lock_guard<std::mutex> lock(displayMutex);
        std::cout << "\tthread " << std::this_thread::get_id() << " working\n";
    }
    for (int i = 0; i < count; ++i)
    {
        Stats_c::incCounter(getCounterName(i));
    }
    if (IS_VERBOSE)
    {
        std::lock_guard<std::mutex> lock(displayMutex);
        std::cout << "\tthread " << std::this_thread::get_id() << " finished\n";
    }
}

void startWorkers(const int threads, const int count)
{
    std::vector<std::future<void>> futures;
    futures.reserve(threads);
    for (int i = 0; i < threads; ++i)
    {
        futures.push_back(std::async(std::launch::async, worker, count));
    }
}

UNIT_TEST(test17, "Test large number of counters used by different threads.")
    const int COUNTERS = 25000;
    const int THREADS = 10;

    Stats_c::clearAllCounters();

    startWorkers(THREADS, COUNTERS);

    if (IS_VERBOSE)
        std::cout << "\tChecking.\n";
    for (int i = 0; i < COUNTERS; ++i)
    {
        REQUIRE(Stats_c::getCounter(getCounterName(i)) == THREADS)
    }
END_TEST


void display(void)
{
    if (IS_VERBOSE)
        std::cout << "Display Current Statistics:\n"  << Stats_c::getInstance() << '\n';
}

int runTests(void)
{
    std::cout << "Executing all tests.\n";
//    VERBOSE_OFF

    RUN_TEST(test0)
//    display();

    RUN_TEST(test7)
//    display();

    RUN_TEST(test16)
    RUN_TEST(test17)

    const int err = FINISHED;
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


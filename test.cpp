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
 *    g++ -std=c++20 -c -o unittest.o unittest.cpp
 *    g++ -std=c++20 -o test test.o test2.o unittest.o
 *
 * Test using:
 *    ./test
 *
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

#include "Stats_c.h"

#include "unittest.h"


extern void remoteFunction(int count);


/**
 * @section test statistics using direct calls to the static singleton.
 *
 * All of these are interdependent.
 */
UNIT_TEST(test0, "Test clearing counters with direct access.")
    Stats_c<>::clearAllCounters();

    REQUIRE(Stats_c<>::getCounter("local") == 0)

NEXT_CASE(test1, "Test initialisation with direct access.")
    Stats_c<>::incCounter("local");

    REQUIRE(Stats_c<>::getCounter("local") == 1)

NEXT_CASE(test2, "Test second incrementation with direct access.")
    Stats_c<>::incCounter("local");

    REQUIRE(Stats_c<>::getCounter("local") == 2)

NEXT_CASE(test3, "Test incrementation by 2 with direct access.")
    Stats_c<>::incCounter("local", 2);

    REQUIRE(Stats_c<>::getCounter("local") == 4)

NEXT_CASE(test4, "Test multiple increments with direct access.")
    for (int i = 0; i < 10; ++i)
        Stats_c<>::incCounter("local");

    REQUIRE(Stats_c<>::getCounter("local") == 14)

NEXT_CASE(test5, "Test multiple increments by 5 with direct access.")
    for (int i = 0; i < 4; ++i)
        Stats_c<>::incCounter("local", 5);

    REQUIRE(Stats_c<>::getCounter("local") == 34)

NEXT_CASE(test6, "Test multiple increments by remote function.")
    remoteFunction(2);

    REQUIRE(Stats_c<>::getCounter("local") == 34)
    REQUIRE(Stats_c<>::getCounter("remote") == 22)

END_TEST


/**
 * @section test statistics using a local reference to the static singleton.
 *
 * All of these are interdependent. Most of these test using the local 
 * reference but tests at the end use direct calls to the static singleton
 * to show either way is possible.
 */
UNIT_TEST(test7, "Test clearing counters with local reference.")
    // Could be a reference global used by the entire source file.
    auto & stats = Stats_c<>::getInstance();
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
    Stats_c<>::setCounter("local", 20);

    REQUIRE(Stats_c<>::getCounter("local") == 20)
    REQUIRE(Stats_c<>::getCounter("remote") == 27)

NEXT_CASE(test15, "Test set new counter to a specific value.")
    Stats_c<>::setCounter("test", 10);

    REQUIRE(Stats_c<>::getCounter("test") == 10)
    REQUIRE(Stats_c<>::getCounter("local") == 20)
    REQUIRE(Stats_c<>::getCounter("remote") == 27)

END_TEST


/**
 * @section test a large number of counters incremented by various amounts.
 */
static std::string genCounterName(int a)
{
    return "counter" + std::to_string(a);
}
UNIT_TEST(test16, "Test large number of counters incremented by various amounts.")
    const int COUNTERS = 250000;
    const int INCREMENTS = 4;

    Stats_c<>::clearAllCounters();

    int total = 0;
    for (int j = 1; j <= INCREMENTS; ++j)
    {
        if (IS_VERBOSE)
            std::cout << "\tIncrementing by " << j << ".\n";
        for (int i = 0; i < COUNTERS; ++i)
        {
            Stats_c<>::incCounter(genCounterName(i), j);
        }
        total += j;
    }

    if (IS_VERBOSE)
        std::cout << "\tChecking.\n";
    REQUIRE(Stats_c<>::size() == COUNTERS)

    PROFILE_OFF
    for (auto & [counter, count] : Stats_c<>::getInstance())
    {
        REQUIRE(count == total)
        REQUIRE(Stats_c<>::getCounter(counter) == total)
    }
    PROFILE_ON

END_TEST


/**
 * @section test a large number of counters being used by different threads.
 */
static void worker(const int count)
{
static std::mutex displayMutex;

    std::stringstream id;
    id << "Thread " << std::this_thread::get_id();
    if (IS_VERBOSE)
    {
        std::lock_guard<std::mutex> lock(displayMutex);
        std::cout << "\t" << id.str() << " working\n";
    }
    for (int i = 0; i < count; ++i)
    {
        Stats_c<>::incCounter(genCounterName(i));
    }
    if (IS_VERBOSE)
    {
        std::lock_guard<std::mutex> lock(displayMutex);
        std::cout << "\t" << id.str() << " finished\n";
    }
}

static void startWorkers(const int threads, const int count)
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

    Stats_c<>::clearAllCounters();

    startWorkers(THREADS, COUNTERS);

    if (IS_VERBOSE)
        std::cout << "\tChecking.\n";
    REQUIRE(Stats_c<>::size() == COUNTERS)

    PROFILE_OFF
    for (auto & [counter, count] : Stats_c<>::getInstance())
    {
        REQUIRE(count == THREADS)
        REQUIRE(Stats_c<>::getCounter(counter) == THREADS)
    }
    PROFILE_ON

END_TEST


/**
 * @section test counters using different precision are independent.
 */
UNIT_TEST(test18, "Test two sets of counters using different precision.")

    // Use a local reference for convenience.
    auto & stats = Stats_c<>::getInstance();
    stats.clearAllCounters();

    auto & counters = Stats_c<size_t>::getInstance();
    counters.clearAllCounters();

    stats.incCounter("local");
    stats.incCounter("local");
    stats.incCounter("stats");

    counters.incCounter("local");
    counters.incCounter("counters", 3);

    REQUIRE(stats.getCounter("local") == 2)
    REQUIRE(stats.getCounter("stats") == 1)
    REQUIRE(stats.getCounter("counters") == 0)

    REQUIRE(counters.getCounter("local") == 1)
    REQUIRE(counters.getCounter("stats") == 0)
    REQUIRE(counters.getCounter("counters") == 3)

END_TEST


/**
 * @section test iterator functionality.
 */
UNIT_TEST(test19, "Test iterating over all statistics.")

    // Use a local reference for convenience.
    auto & stats = Stats_c<>::getInstance();
    stats.clearAllCounters();

    // Set up dumy data.
    std::map<std::string, int> data{
        { "Sean Connery", 6 },
        { "George Lazenby", 1 },
        { "Roger Moore", 7 },
        { "Timothy Dalton", 2 },
        { "Pierce Brosnan", 4 },
        { "Daniel Craig", 5 }
    };
    for (auto & [letter, frequency] : data)
    {
        stats.incCounter(letter, frequency);
    }

    REQUIRE(data.size() == Stats_c<>::size())

    // Check basic functionality of Iterator.
    Stats_c<>::Iterator it = Stats_c<>::begin();
    ++it;
    REQUIRE(it->second == data[it->first])

    // Iterate over all statistics and compare to data.
    int items{};
    for (auto & [counter, count] : Stats_c<>::getInstance())
    {
        REQUIRE(count == data[counter])
        ++items;
    }
    REQUIRE(items == data.size())

END_TEST


/**
 * @section run the tests.
 */
template<typename T=int>
static void display(void)
{
    if (IS_VERBOSE)
        std::cout << "Display Current Statistics:\n"  << Stats_c<T>::getInstance() << '\n';
}

static int runTests(void)
{
    std::cout << "Executing all tests.\n";
//    VERBOSE_OFF

    RUN_TEST(test0)
    // display<>();

    RUN_TEST(test7)
    // display<>();

    RUN_TEST(test16)
    RUN_TEST(test17)
    RUN_TEST(test18)
    // display<>();
    // display<size_t>();

    RUN_TEST(test19)

    const int err{FINISHED};
    OUTPUT_SUMMARY;

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


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
 * Interface for the Statistics Implementation.
 */

#if !defined(_STATS_C_H__20190903_1340__INCLUDED_)
#define _STATS_C_H__20190903_1340__INCLUDED_

#include <unordered_map>
#include <string>
#include <future>


/**
 * @section Statistics Singleton.
 *
 * Implementation of the Statistics Singleton.
 */

template <typename T=int>
class Stats_c
{
public:
//- Delete the copy constructor and assignement operator.
    Stats_c(const Stats_c &) = delete;
    void operator=(const Stats_c &) = delete;

    friend std::ostream & operator<<(std::ostream &os, const Stats_c &A) { A._display(os); return os; }

    static Stats_c<T> & getInstance() { static Stats_c<T> instance; return instance; }

    static void clearAllCounters(void) { getInstance()._clearAllCounters(); }

    static T getCounter(const std::string & key) { return getInstance()._getCounter(key); }
    static void setCounter(const std::string & key, T value=0) { getInstance()._setCounter(key, value); }
    static void incCounter(const std::string & key, T step=1) { getInstance()._incCounter(key, step); }

private:
//- Hide the default constructor and destructor.
    Stats_c(void) {}
    virtual ~Stats_c(void) {}

    void _display(std::ostream &os) const;

    void _clearAllCounters(void) { std::lock_guard<std::mutex> lock(countsMutex); counts.clear(); }

    T _getCounter(const std::string & key) const;
    void _setCounter(const std::string & key, T value);
    void _incCounter(const std::string & key, T step);

    mutable std::mutex countsMutex;
    std::unordered_map<std::string, T> counts;

};

/**
 * Get the current value of a counter.
 *
 * @param  key - string representing the key of the counter.
 * @return the current value of the counter for the given key.
 */
template<typename T>
T Stats_c<T>::_getCounter(const std::string & key) const
{
    std::lock_guard<std::mutex> lock(countsMutex);
    auto it = counts.find(key);
    if (it == counts.end())
    {
        return 0;
    }

    return it->second;
}


/**
 * Set a new value for a counter.
 *
 * @param  key - string representing the key of the counter.
 * @param  value - new value to set the counter to (default = 0).
 */
template<typename T>
void Stats_c<T>::_setCounter(const std::string & key, T value)
{
    std::lock_guard<std::mutex> lock(countsMutex);
    auto it = counts.find(key);
    if (it == counts.end())
    {
        counts[key] = value;
    }
    else
    {
        it->second = value;
    }
}


/**
 * Increment a counter.
 *
 * @param  key - string representing the key of the counter.
 * @param  step - amount to increment the counter by (default = 1).
 */
template<typename T>
void Stats_c<T>::_incCounter(const std::string & key, T step)
{
    std::lock_guard<std::mutex> lock(countsMutex);
    auto it = counts.find(key);
    if (it == counts.end())
    {
        counts[key] = step;
    }
    else
    {
        it->second += step;
    }
}


/**
 * Send the current name-value pairs to the output stream.
 *
 * @param  os - Output stream.
 */
template<typename T>
void Stats_c<T>::_display(std::ostream &os) const
{
    std::lock_guard<std::mutex> lock(countsMutex);
    for (auto& x: counts)
    {
        os << "\t" << x.first << "\t" << x.second << "\n";
    }
}


#endif // !defined(_STATS_C_H__20190903_1340__INCLUDED_)


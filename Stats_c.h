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


/**
 * @section Statistics Singleton.
 *
 * Implementation of the Statistics Singleton.
 */

class Stats_c
{
private:
//- Hide the default constructor and destructor.
    Stats_c(void) {}
    virtual ~Stats_c(void) {}

    void _display(std::ostream &os) const;

    void _clearAllCounters(void) { counts.clear(); }

    int _getCounter(const std::string & key) const;
    void _setCounter(const std::string & key, int value);
    void _incCounter(const std::string & key, int step);

    std::unordered_map<std::string, int> counts;

public:
//- Delete the copy constructor and assignement operator.
    Stats_c(const Stats_c &) = delete;
    void operator=(const Stats_c &) = delete;

    friend std::ostream & operator<<(std::ostream &os, const Stats_c &A) { A._display(os); return os; }

    static Stats_c & getInstance() { static Stats_c instance; return instance; }

    static void clearAllCounters(void) { getInstance()._clearAllCounters(); }

    static int getCounter(const std::string & key) { return getInstance()._getCounter(key); }
    static void setCounter(const std::string & key, int value=0) { getInstance()._setCounter(key, value); }
    static void incCounter(const std::string & key, int step=1) { getInstance()._incCounter(key, step); }

};

#endif // !defined(_STATS_C_H__20190903_1340__INCLUDED_)


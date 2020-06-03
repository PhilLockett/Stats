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

#include <map>
#include <string>

using namespace std;


/**
 * @section Statistics Singleton.
 *
 * Implementation of the Statistics Singleton.
 */

class Stats_c
{
private:
//- Hide the default constructor, destructor, copy constructor and assignement operator.
    Stats_c(void) {}
    virtual ~Stats_c(void) {}
    Stats_c(Stats_c const&);
    void operator=(Stats_c const&);

    void display(std::ostream &os) const;

    static Stats_c* instance;
    map<string, int> counts;

public:
    friend std::ostream & operator<<(std::ostream &os, const Stats_c &A) { A.display(os); return os; }

    static Stats_c* getInstance();
    void clearAllCounters(void) { counts.clear(); }

    int getCounter(string key) const;
    void setCounter(string key, int value=0);
    void incCounter(string key, int step=1);

};

#endif // !defined(_STATS_C_H__20190903_1340__INCLUDED_)


/**
 * @file    Stats_c.cpp
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
 * Statistics Implementation.
 */

#include <iostream>

#include "Stats_c.h"


/**
 * Get the current value of a counter.
 *
 * @param  key - string representing the key of the counter.
 * @return the current value of the counter for the given key.
 */
int Stats_c::getCounter(std::string key) const
{
    std::map<std::string, int>::const_iterator it = counts.find(key);
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
void Stats_c::setCounter(std::string key, int value)
{
    std::map<std::string, int>::iterator it = counts.find(key);
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
void Stats_c::incCounter(std::string key, int step)
{
    std::map<std::string, int>::iterator it = counts.find(key);
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
void Stats_c::display(std::ostream &os) const
{
    for (auto& x: counts)
    {
        os << "\t" << x.first.c_str() << "\t" << x.second << "\n";
    }
}


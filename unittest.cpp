/**
 * @file    unittest.cpp
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

#include "unittest.h"

std::string UnitTest_c::function = "UNDEFINED";
std::string UnitTest_c::description = "UNDEFINED";
std::string UnitTest_c::condition = "UNDEFINED";
bool UnitTest_c::verbose = true;
int UnitTest_c::errors = 0;



/**
 * Send the current name-value pairs to the output stream.
 *
 * @param  os - Output stream.
 */
void UnitTest_c::_display(std::ostream &os) const
{
     os << "\tFunction:\t" << function << "()\n";
     os << "\tDescription:\t" << description << "()\n";
     os << "\tVerbose:\t" << verbose << '\n';
}

void UnitTest_c::_progress(const std::string & func, const std::string & desc)
{
    UnitTest_c::setFunction(func);
    UnitTest_c::setDescription(desc);

    if (verbose)
        std::cout << '\t' << function << "() - " << description << '\n';
}

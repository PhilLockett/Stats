/**
 * @file    unittest.h
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
 * Simple unit test "framework".
 */

#if !defined(_UNITTEST_H__20210324_0940__INCLUDED_)
#define _UNITTEST_H__20210324_0940__INCLUDED_

#include <string>

/**
 * @section unit test macro definitions.
 *
 * Implementation of the unit test macros.
 */

#define VERBOSE_ON UnitTest_c::getInstance().setVerbose(true);
#define VERBOSE_OFF UnitTest_c::getInstance().setVerbose(false);

#define UNIT_TEST(func, desc) void func(void) {\
    UnitTest_c::getInstance().progress(#func, desc);

#define END_TEST }

#define REQUIRE(cond) if (!(cond)) UnitTest_c::getInstance().failure(#cond);

#define RUN_TEST(func)    func();

#define ERROR_COUNT UnitTest_c::getInstance().getErrorCount()

/**
 * @section unit test context data.
 *
 * Implementation of the unit test context Singleton.
 */

class UnitTest_c
{
private:
//- Hide the default constructor and destructor.
    UnitTest_c(void) {}
    virtual ~UnitTest_c(void) {}

    void display(std::ostream &os) const;

    static std::string function;
    static std::string description;
    static std::string condition;
    static bool verbose;
    static int errors;


public:
//- Delete the copy constructor and assignement operator.
    UnitTest_c(const UnitTest_c &) = delete;
    void operator=(const UnitTest_c &) = delete;

    friend std::ostream & operator<<(std::ostream &os, const UnitTest_c &A) { A.display(os); return os; }

    static UnitTest_c & getInstance() { static UnitTest_c instance; return instance; }

    static void setVerbose(bool state = true) { verbose = state; }
    static void progress(const std::string & func, const std::string & desc);
    static void failure(const std::string & cond);
    static int getErrorCount(void) { return errors; }

};

#endif // !defined(_UNITTEST_H__20210324_0940__INCLUDED_)

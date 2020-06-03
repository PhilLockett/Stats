# Stats_c - A simple implementation of a statistics counter as a singleton.

## Introduction

This is a simple statistics counter implemented as a singleton. The counts are 
of type int, but can easily be customised, or even converted to a template. 
The keys are simply C++ string types. If the key is not found, it is added to 
the list, otherwise it is updated. The keys a system wide, so if the same key 
is used through out the system, the same counter is updated.

The code is wholly contained in the files 'Stats_c.cpp' and 'Stats_c.h'. All 
other files are to support the unit test code. The code is liberally
 commented. The test code exercises the whole API and illustrates the usage.


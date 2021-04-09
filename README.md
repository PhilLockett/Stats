# Stats_c

A simple statistics counter implemented as a singleton.

## Overview

A statistics counter is useful in a real time environment for mapping 
behaviour as well as counting items. It should allow any counter to be added 
or updated from anywhere in the system.

This is a simple statistics counter implemented as a singleton. The counts are 
of type int, but can easily be customised, or even converted to a template. 
The keys are simply C++ string types for convenience, but speed is 
compromised. If the key is not found, it is added to the list, otherwise it 
is updated. The keys a system wide, so if the same key is used through out the 
system, the same counter is updated.

The stats counter code is wholly contained in the files 'Stats_c.cpp' and 
'Stats_c.h'. All other files are to support the unit test code. The code is 
liberally commented. The test code exercises the whole API and illustrates 
the usage.

## Cloning and Running

The test code is dependent on UnitTest. To compile and run the Stats code you
first need to clone the unit test code, then copy unittest.cpp and unittest.h 
into the Stats directory before executing make.

    git clone https://github.com/PhilLockett/UnitTest.git

To clone, build and run the Stats code, including the test code, execute the 
following unix/linux commands:

    git clone https://github.com/PhilLockett/Stats.git
    cd Stats/
    cp ../UnitTest/unittest.cpp .
    cp ../UnitTest/unittest.h .
    make
    ./test

## Points of interest

This code has the following points of interest:

  * The statistics counter code (Stats_c) is implemented as a singleton.
  * Keys are implemented as strings for convenience.
  * Any counter can be updated from anywhere in the system.

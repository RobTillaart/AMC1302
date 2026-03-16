//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// PURPOSE: unit tests for the AMC1302 library
//     URL: https://github.com/RobTillaart/AMC1302
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "AMC1302.h"


unittest_setup()
{
  fprintf(stderr, "AMC1302_LIB_VERSION: %s\n", (char *) AMC1302_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, AMC1302_OK);
}


unittest(test_constructor)
{
  AMC1302 amc(14, 15);
}


unittest_main()


//  -- END OF FILE --


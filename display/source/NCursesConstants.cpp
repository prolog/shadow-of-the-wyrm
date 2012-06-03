#include "NCursesConstants.hpp"

NCursesConstants::NCursesConstants()
{
}

NCursesConstants::~NCursesConstants()
{
}

// The map always (always!) starts on row 2.  The message buffer
// always (always!) gets line 0 and 1.
const int NCursesConstants::MAP_START_ROW = 2;
const int NCursesConstants::MAP_START_COL = 0;

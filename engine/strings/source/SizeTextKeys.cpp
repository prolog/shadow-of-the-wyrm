#include "SizeTextKeys.hpp"

using namespace std;


SizeTextKeys::SizeTextKeys()
{
}

SizeTextKeys::~SizeTextKeys()
{
}

string SizeTextKeys::get_size_sid_from_creature_size(const CreatureSize size)
{
  string size_sid;
  
  switch(size)
  {
    case CREATURE_SIZE_TINY:
      size_sid = SIZE_TINY;
      break;
    case CREATURE_SIZE_SMALL:
      size_sid = SIZE_SMALL;
      break;
    case CREATURE_SIZE_MEDIUM:
      size_sid = SIZE_MEDIUM;
      break;
    case CREATURE_SIZE_LARGE:
      size_sid = SIZE_LARGE;
      break;
    case CREATURE_SIZE_HUGE:
      size_sid = SIZE_HUGE;
      break;
    case CREATURE_SIZE_BEHEMOTH: 
      size_sid = SIZE_BEHEMOTH;
      break;
    default:
      break;
  }
  
  return size_sid;
}

const string SizeTextKeys::SIZE = "SIZE";
const string SizeTextKeys::SIZE_TINY = "SIZE_TINY";
const string SizeTextKeys::SIZE_SMALL = "SIZE_SMALL";
const string SizeTextKeys::SIZE_MEDIUM = "SIZE_MEDIUM";
const string SizeTextKeys::SIZE_LARGE = "SIZE_LARGE";
const string SizeTextKeys::SIZE_HUGE = "SIZE_HUGE";
const string SizeTextKeys::SIZE_BEHEMOTH = "SIZE_BEHEMOTH";

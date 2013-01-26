#include "MapTypeQueries.hpp"

// General overworld queries
bool OverworldMapTypeQuery::should_update_depth() const
{
  return false;
}

// General underworld queries
bool UnderworldMapTypeQuery::should_update_depth() const
{
  return true;
}


#include "MapTypeQueries.hpp"

// General overworld queries
bool DepthlessMapTypeQuery::should_update_depth() const
{
  return false;
}

// General underworld, air, cosmos queries
bool DepthMapTypeQuery::should_update_depth() const
{
  return true;
}

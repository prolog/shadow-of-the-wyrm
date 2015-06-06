#include <sstream>
#include "CreatureGenerationOptionsStringBuilder.hpp"

using namespace std;

string CreatureGenerationOptionsStringBuilder::build(const CreatureGenerationOptions& cgo)
{
  ostringstream creature_generation_options;
  creature_generation_options << "id=" << cgo.get_id();

  map<string, bool> hostility_map = cgo.get_hostility_map();

  for (const auto& host_pair : hostility_map)
  {
    creature_generation_options << ";" << "hostility=" << host_pair.first << ":" << host_pair.second;
  }

  return creature_generation_options.str();
}



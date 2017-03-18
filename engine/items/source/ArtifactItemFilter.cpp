#include "ArtifactItemFilter.hpp"

using namespace std;

bool ArtifactItemFilter::passes_filter(ItemPtr item) const
{
  return (item && item->get_artifact());
}


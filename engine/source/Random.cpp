#include <ctime>
#include "Random.hpp"

PoissonDistribution::PoissonDistribution(const int mean)
: pdist(mean), poisson_generator(mt, pdist)
{
  poisson_generator.engine().seed(static_cast<uint32_t>(std::time(0)));
}

int PoissonDistribution::next()
{
  return poisson_generator();
}


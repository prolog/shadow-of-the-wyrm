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

NormalDistribution::NormalDistribution(const int mean, const int standard_deviation)
: ndist(mean, standard_deviation), normal_generator(mt, ndist)
{
  normal_generator.engine().seed(static_cast<uint32_t>(std::time(0)));
}

double NormalDistribution::next()
{
  return normal_generator();
}

int NormalDistribution::next_int()
{
  return static_cast<int>(normal_generator());
}

int NormalDistribution::next_int_as_pct()
{
  int val = next_int();

  if (val > 100)
  {
    val = 100;
  }
  else if (val < 0)
  {
    val = 0;
  }

  return val;
}

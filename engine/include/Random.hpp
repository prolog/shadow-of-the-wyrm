#pragma once
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/variate_generator.hpp>

// Provides a number of classes that encapsulate non-uniform probability
// distributions (Normal, Poisson, etc).
class PoissonDistribution
{
  public:
    PoissonDistribution(const int mean);

    int next();

  private:
    boost::mt19937 mt;
    boost::poisson_distribution<int> pdist;
    boost::variate_generator<boost::mt19937, boost::poisson_distribution<int>> poisson_generator;
};


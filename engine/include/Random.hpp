#pragma once
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
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

class NormalDistribution
{
  public:
    NormalDistribution(const int mean, const int standard_deviation);

    double next();
    int next_int();
    int next_int_as_pct();

  private:
    boost::mt19937 mt;
    boost::normal_distribution<> ndist;
    boost::variate_generator<boost::mt19937, boost::normal_distribution<>> normal_generator;
};
#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Feature.hpp"
#include "Trap.hpp"

using FeatureSerializationMap =  std::map<ClassIdentifier, FeaturePtr>;

class FeatureFactory
{
  public:
    static FeaturePtr create_feature(const ClassIdentifier ci);
    static LockPtr create_lock();
    static TrapPtr create_trap();

  protected:
    FeatureFactory();
    ~FeatureFactory();

    static void initialize_feature_map();

    static FeatureSerializationMap feature_map;
};


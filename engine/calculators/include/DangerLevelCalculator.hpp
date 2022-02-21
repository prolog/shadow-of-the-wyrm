#pragma once
#include <map>
#include <memory>
#include <string>
#include "common.hpp"
#include "Map.hpp"

// Danger level calculator.  Different types of map (world, overworld,
// underworld) have different methods of danger calculation, so this class
// provides a common interface that abstracts away the details.
class DangerLevelCalculator
{
  public:
    // Calculate the new danger level, given the old.
    virtual int calculate(MapPtr old_map, MapPtr new_map = nullptr) const = 0;
    virtual ~DangerLevelCalculator() {};

    void set_property(const std::string& new_property, const std::string& new_value);
    std::string get_property(const std::string& property) const;
    void set_properties(const std::map<std::string, std::string>& new_properties);
    std::map<std::string, std::string> get_properties() const;

  protected:
    std::map<std::string, std::string> properties;
};

using DangerLevelCalculatorPtr = std::unique_ptr<DangerLevelCalculator>;


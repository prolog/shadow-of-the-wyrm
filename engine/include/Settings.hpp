#pragma once
#include <boost/property_tree/ptree.hpp>

class Settings
{
  public:
    static Settings& instance()
    {
      static Settings settings;
      return settings;
    }

  protected:
    Settings();

    boost::property_tree::ptree p_tree;
};


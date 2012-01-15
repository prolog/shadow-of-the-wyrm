#pragma once
#include <string>
#include "common.hpp"
class Weight
{
  public:
    Weight();
    ~Weight();

    void set_weight(const uint ounces);
    void set_weight(const uint pounds, const uint ounces);
    uint get_weight() const;

    
    std::string str() const;

  protected:
    uint ounces;
};

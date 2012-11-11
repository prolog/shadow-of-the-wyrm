#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class Weight : public ISerializable
{
  public:
    Weight();
    ~Weight();
    bool operator==(const Weight& weight);

    void set_weight(const uint ounces);
    void set_weight(const uint pounds, const uint ounces);
    uint get_weight() const;
    double get_weight_in_lbs() const;
    
    static uint get_weight_in_oz_given_lbs(const uint pounds);
    
    std::string str() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    uint ounces;

  private:
    ClassIdentifier internal_class_identifier() const;
};

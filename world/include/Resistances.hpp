#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include "DamageTypes.hpp"

inline DamageType operator--(DamageType &dt, int)
{
  return dt = DamageType(dt-1);
}

inline DamageType operator++(DamageType &dt, int)
{
  return dt = DamageType(dt+1);
}

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

#define DEFAULT_RESISTANCE_VALUE 1.0;
class Resistance
{
  public:
    Resistance();
    virtual ~Resistance() {};
    Resistance(const DamageType type, const std::string& name_sid, const double value);

    void set_type(const DamageType new_type);
    DamageType get_type() const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;

    void set_value(const double new_value);
    double get_value() const;

    std::string str() const;

  protected:
    DamageType type;
    std::string name_sid;
    double value;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & type & name_sid & value;
    }
};

// Individual resistance types
class SlashResistance : public Resistance
{
  public:
    SlashResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class PierceResistance : public Resistance
{
  public:
    PierceResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class PoundResistance : public Resistance
{
  public:
    PoundResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class HeatResistance : public Resistance
{
  public:
    HeatResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class ColdResistance : public Resistance
{
  public:
    ColdResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class AcidResistance : public Resistance
{
  public:
    AcidResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class PoisonResistance : public Resistance
{
  public:
    PoisonResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class HolyResistance : public Resistance
{
  public:
    HolyResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class ShadowResistance : public Resistance
{
  public:
    ShadowResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class ArcaneResistance : public Resistance
{
  public:
    ArcaneResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class MentalResistance : public Resistance
{
  public:
    MentalResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class SonicResistance : public Resistance
{
  public:
    SonicResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class RadiantResistance : public Resistance
{
  public:
    RadiantResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

class LightningResistance : public Resistance
{
  public:
    LightningResistance();
  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<Resistance>(*this);
    }
};

typedef std::map<DamageType, boost::shared_ptr<Resistance> > ResistancesMap;

// Resistance container class
class Resistances
{
  public:
    Resistances();

    void set_resistance_value(const DamageType type, double value);
    double get_resistance_value(const DamageType type) const;

    std::string str() const;
    
  protected:
    void default_resistances();

    ResistancesMap resistances;

  
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & resistances;
    }
};

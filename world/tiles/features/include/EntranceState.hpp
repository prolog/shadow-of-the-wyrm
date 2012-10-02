#pragma once
#include "common.hpp"
#include "EntranceTypes.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class EntranceState
{
  public:
    EntranceState();
    EntranceState(const EntranceStateType new_state);
    
    void set_state(const EntranceStateType new_state);
    EntranceStateType get_state() const;
    
    uchar get_symbol() const;
    
  protected:
    EntranceStateType state;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & state;
    }
};

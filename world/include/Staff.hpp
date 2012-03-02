#pragma once
#include "Item.hpp"

class Staff : public Item
{
  public:
    Staff();
    ~Staff();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Staff> StaffPtr;

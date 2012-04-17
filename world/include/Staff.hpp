#pragma once
#include "Item.hpp"

class Staff : public Item
{
  public:
    Staff();
    ~Staff();
    
    Item* clone();
};

typedef boost::shared_ptr<Staff> StaffPtr;

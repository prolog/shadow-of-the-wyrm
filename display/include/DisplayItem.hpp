#pragma once
#include <map>
#include <string>

// A DisplayItem contains the relevant details of an item for the Display
// to use in its inventory and equipment management routines.
class DisplayItem
{
  public:
    DisplayItem();
    ~DisplayItem();

    void set_description(const std::string& new_description);
    std::string get_description();
    
    // Additional status-related items go here.
    
  protected:
    std::string description;
};

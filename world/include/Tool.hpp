#pragma once
#include "Item.hpp"

class Tool : public Item
{
  public:
    Tool();
    ~Tool();

    bool operator==(const Tool& rhs) const;
    
    void set_lock_id(const std::string& new_lock_id);
    std::string get_lock_id() const;

    Item* clone();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    std::string lock_id;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Tool> ToolPtr;


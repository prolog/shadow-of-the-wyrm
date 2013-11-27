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

    Item* clone() override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string lock_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Tool> ToolPtr;


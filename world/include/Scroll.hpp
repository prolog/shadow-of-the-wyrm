#pragma once
#include "Readable.hpp"

class Scroll : public Readable
{
  public:
    Scroll();
    ~Scroll();
    
    bool destroy_on_read() const override;
    
    Item* clone() override;

  protected:
    virtual void do_enchant_item(const int points) override;
    virtual void increase_value(const int points) override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using ScrollPtr = std::shared_ptr<Scroll>;

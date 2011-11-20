#pragma once
#include <string>

class MenuComponent
{
  public:
    MenuComponent() {};
    MenuComponent(const std::string& new_text);

    virtual void set_text(const std::string& new_text);
    virtual std::string get_text() const;

  protected:
    std::string text;
};

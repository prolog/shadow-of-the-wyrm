#pragma once
#include <boost/shared_ptr.hpp>
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

typedef boost::shared_ptr<MenuComponent> MenuComponentPtr;

#pragma once

// A class that can be used to control space after a component (i.e.
// empty lines before next component), space before a component within
// the current (left padding), etc.
class ComponentAlignment
{
  public:
    ComponentAlignment();
    ComponentAlignment(const bool o, const int v);

    void set_override_default(const bool new_override_default);
    bool get_override_default() const;

    void set_value(const int new_value);
    int get_value() const;

  protected:
    bool override_default;
    int value;
};


#pragma once
#include <string>

class DropParameters
{
  public:
    DropParameters();
    DropParameters(const std::string& new_item_base_id, const int new_percent_chance, const int min, const int max);

    std::string get_item_base_id() const;
    int get_percent_chance() const;
    int get_min() const;
    int get_max() const;

  protected:
    std::string item_base_id;
    int percent_chance;
    int min;
    int max;
};

#pragma once
#include <set>

// Wrapper for NCurses menu/item data, mostly to allow easy deletion
// during program flow.

class NCursesMenuWrapper
{
  public:
    NCursesMenuWrapper();
    NCursesMenuWrapper(const int n_items);
    
    void set_num_items(const int new_num_items);
    int get_num_items() const;

    bool has_options() const;
    void clear_options();
    void add_option(const char option);
    bool is_option_in_set(const char option) const;

  protected:
    int num_items;
    std::set<char> options;
};

#pragma once
#include <ncurses/ncurses.h>
#include <ncurses/menu.h>

// Wrapper for NCurses menu/item data, mostly to allow easy deletion
// during program flow.

class NCursesMenuWrapper
{
  public:
    NCursesMenuWrapper();
    NCursesMenuWrapper(MENU* new_menu, ITEM** new_items, const int n_items);
    
    void set_menu(MENU* new_menu);
    MENU* get_menu() const;

    void set_items(ITEM** new_items);
    ITEM** get_items() const;

    void set_num_items(const int new_num_items);
    int get_num_items() const;
    
    void release_pointer_structures(); // Frees its associated pointers

  protected:
    MENU* menu;
    ITEM** items;
    int num_items;
};

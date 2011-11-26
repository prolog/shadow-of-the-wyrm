#include "NCursesMenuWrapper.hpp"

NCursesMenuWrapper::NCursesMenuWrapper()
{
  menu = NULL;
  items = NULL;
  num_items = 0;
}

NCursesMenuWrapper::NCursesMenuWrapper(MENU* new_menu, ITEM** new_items, const int new_num_items) : menu(new_menu), items(new_items), num_items(new_num_items)
{
}

void NCursesMenuWrapper::set_menu(MENU* new_menu)
{
  menu = new_menu;
}

MENU* NCursesMenuWrapper::get_menu() const
{
  return menu;
}

void NCursesMenuWrapper::set_items(ITEM** new_items)
{
  items = new_items;
}

ITEM** NCursesMenuWrapper::get_items() const
{
  return items;
}

void NCursesMenuWrapper::set_num_items(const int new_num_items)
{
  num_items = new_num_items;
}

int NCursesMenuWrapper::get_num_items() const
{
  return num_items;
}

void NCursesMenuWrapper::release_pointer_structures()
{
  for (int i = 0; i < num_items; i++)
  {
    ITEM* item = items[i];
    
    if (item)
    {
      free_item(item);
    }
  }

  if (menu)
  {
    free_menu(menu);
  }

  num_items = 0;
}

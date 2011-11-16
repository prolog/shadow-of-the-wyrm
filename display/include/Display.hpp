/*!
 *********************************************************************

 	General definition of an abstract Display so that multiple displays
	can be specified (curses-based, graphical tiles, etc).

 *********************************************************************/
#pragma once
#include <string>
#include "Map.hpp"
#include "Prompt.hpp"

class Menu;

class Display
{
	public:
	  virtual bool create() = 0;
	  virtual void tear_down() = 0;

	  virtual void draw(const Map& current_map) = 0;

	  // Return result is the response to whatever prompt is displayed
	  virtual std::string display_menu(const Menu& current_menu) = 0;

	  virtual void clear_menu() = 0;

  protected:
//????    virtual std::string display_prompt(PromptPtr prompt) = 0;

};

typedef boost::shared_ptr<Display> DisplayPtr;

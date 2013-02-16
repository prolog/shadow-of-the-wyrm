/*!
 *********************************************************************

 	General definition of an abstract Display so that multiple displays
	can be specified (curses-based, graphical tiles, etc).

 *********************************************************************/
#pragma once
#include <string>
#include "DisplayItem.hpp"
#include "DisplayMap.hpp"
#include "DisplayStatistics.hpp"
#include "ISerializable.hpp"
#include "Prompt.hpp"

class Menu;

class MapDisplayArea
{
  public:
    MapDisplayArea();
    MapDisplayArea(const uint height, const uint width);

    void set_height(const uint height);
    uint get_height() const;

    void set_width(const uint width);
    uint get_width() const;

  protected:
    uint height;
    uint width;
};

class Display : public ISerializable
{
	public:
    virtual ~Display() {};
    
	  virtual bool create() = 0;
	  virtual void tear_down() = 0;

    // Get the screen's current width
    virtual unsigned int get_width() const = 0;
    virtual void clear_messages() = 0;
    
    // Clears the message buffer, map, and info display.
    virtual void clear_display() = 0;

    // Add a message to display to the user
    virtual void add_message(const std::string& message, const bool reset_cursor) = 0;
    virtual void add_message(const std::string& message, const Colour colour, const bool clear_prior_to_adding_message) = 0;
    
    // Halt the messages - require some form of input from the user to continue
    virtual void halt_messages() = 0;

    // Draws the map
	  virtual void draw(const DisplayMap& current_map) = 0;
	  
	  // Displays a window with the player's equipment
	  virtual void display_equipment(const DisplayEquipmentMap& equipment) = 0;
	  
	  // Displays a window with the player's inventory (non-worn items).
	  // The returned int value is the number of items that were able to be
	  // displayed on the screen.  This is returned so that the engine can
	  // know whether a given keypress/selection is in the range of items displayed.
	  virtual int display_inventory(const DisplayInventoryMap& inventory) = 0;
	  
	  // Displays the player info
	  virtual void display(const DisplayStatistics& player_stats) = 0;

    // Used by the engine to query the display size, so the DisplayMap can be created accordingly.
    virtual MapDisplayArea get_map_display_area() = 0;

	  // Return result is the response to whatever prompt is displayed
	  virtual std::string display_menu(const Menu& current_menu) = 0;
	  
	  // Show confirmation text on the display.
	  virtual void confirm(const std::string& confirmation_message) = 0;

	  virtual void clear_menu() = 0;

    // ISerializable methods
    virtual bool serialize(std::ostream& stream) = 0;
    virtual bool deserialize(std::istream& stream) = 0;

    virtual Display* clone() = 0;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

typedef boost::shared_ptr<Display> DisplayPtr;

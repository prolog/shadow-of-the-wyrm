/*!
 *********************************************************************

 	General definition of an abstract Display so that multiple displays
	can be specified (curses-based, graphical tiles, etc).

 *********************************************************************/
#pragma once
#include <string>
#include "AnimationFactory.hpp"
#include "DisplayConstants.hpp"
#include "DisplayItem.hpp"
#include "DisplayMap.hpp"
#include "DisplayStatistics.hpp"
#include "ISerializable.hpp"
#include "Prompt.hpp"

class Screen;
class MapDisplayArea;
class Animation;

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
    virtual std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool clear_prior) = 0;

    // Halt the messages - require some form of input from the user to continue
    virtual void halt_messages() = 0;

    // Draws the map
	  virtual void draw(const DisplayMap& current_map, const CursorSettings cs) = 0;
    virtual void redraw() = 0;

    // Draws on a portion of the map area.
    virtual void draw_update_map(const DisplayMap& update_map, const CursorSettings cs) = 0;

    // Update a single tile.
    // Engine coordinates are used - the display will calculate the correct coordinates for the display
    // to ignore the message display area.
    virtual void draw_tile(const uint y, const uint x, const DisplayTile& display_tile) = 0;

    // Create an animation factory for the display type.
    virtual AnimationFactoryPtr create_animation_factory() const = 0;

    // Draws an animation.
    virtual void draw_animation(const Animation& animation) = 0;
	  
	  // Displays the player info
	  virtual void display(const DisplayStatistics& player_stats) = 0;

    // Used by the engine to query the display size, so the DisplayMap can be created accordingly.
    virtual MapDisplayArea get_map_display_area() = 0;

	  // Return result is the response to whatever prompt is displayed
	  virtual std::string display_screen(const Screen& current_screen) = 0;
	  
	  // Show confirmation text on the display.
	  virtual void confirm(const std::string& confirmation_message) = 0;

	  virtual void clear_screen() = 0;

    // Property methods.
    virtual void set_properties(const std::map<std::string, std::string>& new_properties);
    virtual void set_property(const std::string& property, const std::string& value);
    virtual std::string get_property(const std::string& property) const;

    // ISerializable methods
    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Display* clone() = 0;

  protected:
    std::map<std::string, std::string> display_properties;

  private:
    virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using DisplayPtr = std::shared_ptr<Display>;

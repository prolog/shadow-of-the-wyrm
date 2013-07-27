#include "IMessageManager.hpp"

// This class does absolutely nothing.  Its purpose is to provide an
// implementation class for messages for creatures that are outside the
// player's view map, and whose messages should not be displayed to the
// screen.
class NullMessageManager : public IMessageManager
{
  public:
    void clear_if_necessary();
    void send(const bool halt_afterwards = false, const bool reset_afterwards = false);
    void send_and_halt();
    
		bool add_new_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
		bool add_new_confirmation_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
    bool add_new_message_with_pause(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
    std::string add_new_message_with_prompt(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal);
		
		Messages get_unread_messages() const;
		Messages get_unread_messages_and_mark_as_read();

    void set_display(DisplayPtr new_display);
};


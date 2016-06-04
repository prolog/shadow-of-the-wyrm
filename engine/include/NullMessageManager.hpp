#include "IMessageManager.hpp"

// This class does absolutely nothing.  Its purpose is to provide an
// implementation class for messages for creatures that are outside the
// player's view map, and whose messages should not be displayed to the
// screen.
class NullMessageManager : public IMessageManager
{
  public:
    void clear_if_necessary() override;
    void send(const MessageSpacing ms, const bool halt_afterwards = false, const bool reset_afterwards = false) override;
    void send_and_halt() override;

    void alert(const std::string& message) override;
    void alert_text(const std::string& message) override;

		bool add_new_message(const std::string& message, const Colour colour = Colour::COLOUR_WHITE, const MessageImportance& importance = MessageImportance::MessageImportance_Normal) override;
		bool add_new_confirmation_message(const std::string& message, const Colour colour = Colour::COLOUR_WHITE, const MessageImportance& importance = MessageImportance::MessageImportance_Normal) override;
    bool add_new_message_with_pause(const std::string& message, const Colour colour = Colour::COLOUR_WHITE, const MessageImportance& importance = MessageImportance::MessageImportance_Normal) override;
    std::string add_new_message_with_prompt(const std::string& message, const Colour colour = Colour::COLOUR_WHITE, const MessageImportance& importance = MessageImportance::MessageImportance_Normal) override;
		
		Messages get_unread_messages() const override;
		Messages get_unread_messages_and_mark_as_read() override;

    void set_display(DisplayPtr new_display) override;

    void set_message_buffer(const MessageBuffer& new_message_buffer) override;
    MessageBuffer get_message_buffer() const override;
};


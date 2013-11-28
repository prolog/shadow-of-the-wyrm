#pragma once
#include "IMessageManager.hpp"

class MessageManager : public IMessageManager
{
	public:
    void clear_if_necessary() override;
    void send(const bool halt_afterwards = false, const bool reset_afterwards = false) override;
    void send_and_halt() override;
    
		bool add_new_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) override;
		bool add_new_confirmation_message(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) override;
    bool add_new_message_with_pause(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) override;
    std::string add_new_message_with_prompt(const std::string& message, const Colour colour = COLOUR_WHITE, const MessageImportance& importance = MessageImportance_Normal) override;
		
		Messages get_unread_messages() const override;
		Messages get_unread_messages_and_mark_as_read() override;

    void set_display(DisplayPtr new_display) override;

private:
    std::string get_count_indicator(const Message& m);
    
    friend class MessageManagerFactory;
    MessageManager();
    MessageManager(const MessageManager&); // Do not implement!
    bool operator=(const MessageManager&); // Do not implement!
    ~MessageManager();

		Messages read;
		Messages unread;
		DisplayPtr user_display;
		bool buffer_has_messages;
};

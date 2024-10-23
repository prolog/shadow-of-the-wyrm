#pragma once
#include <string>

class TileMovementConfirmationDetails
{
  public:
    TileMovementConfirmationDetails();
    TileMovementConfirmationDetails(const bool require_prompt, const std::string& new_confirmation_message, const std::string& new_sound_effect_id, const std::string& new_post_movement_message_sid);
    virtual ~TileMovementConfirmationDetails() = default;

    bool get_require_prompt() const;
    std::string get_confirmation_message() const;
    std::string get_sound_effect_id() const;
    std::string get_post_movement_message_sid() const;

protected:
    bool require_prompt;
    std::string confirmation_message;
    std::string sound_effect_id;
    std::string post_movement_message_sid;
};


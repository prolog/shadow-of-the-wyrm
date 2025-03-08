#include "TileMovementConfirmationDetails.hpp"

using std::string;

TileMovementConfirmationDetails::TileMovementConfirmationDetails()
: require_prompt(false)
{
}

TileMovementConfirmationDetails::TileMovementConfirmationDetails(const bool new_require_prompt, const string& new_confirmation_message, const string& new_sound_effect_id, const string& new_post_movement_message_sid)
: require_prompt(new_require_prompt), confirmation_message(new_confirmation_message), sound_effect_id(new_sound_effect_id), post_movement_message_sid(new_post_movement_message_sid)
{
}

bool TileMovementConfirmationDetails::get_require_prompt() const
{
	return require_prompt;
}

string TileMovementConfirmationDetails::get_confirmation_message() const
{
	return confirmation_message;
}

string TileMovementConfirmationDetails::get_sound_effect_id() const
{
	return sound_effect_id;
}

string TileMovementConfirmationDetails::get_post_movement_message_sid() const
{
	return post_movement_message_sid;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileMovementConfirmationDetails_test.cpp"
#endif

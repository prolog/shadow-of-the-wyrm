#include <boost/algorithm/string/replace.hpp>
#include "SettingTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

SettingTextKeys::SettingTextKeys()
{
}

SettingTextKeys::~SettingTextKeys()
{
}

const string SettingTextKeys::SETTING_AUTOPICKUP = "SETTING_AUTOPICKUP";
const string SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_CORPSES = "SETTING_AUTOPICKUP_EXCLUDE_CORPSES";
const string SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_UNPAID = "SETTING_AUTOPICKUP_EXCLUDE_UNPAID";
const string SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_OVER_WEIGHT = "SETTING_AUTOPICKUP_EXCLUDE_OVER_WEIGHT";
const string SettingTextKeys::SETTING_AUTOMELEE_AT_RANGE = "SETTING_AUTOMELEE_AT_RANGE";
const string SettingTextKeys::SETTING_AUTOMOVE_ALWAYS_STOP_ON_ITEMS = "SETTING_AUTOMOVE_ALWAYS_STOP_ON_ITEMS";

const string SettingTextKeys::SETTING_SOUND_ENABLED = "SETTING_SOUND_ENABLED";
const string SettingTextKeys::SETTING_SOUND_EFFECTS_ENABLED = "SETTING_SOUND_EFFECTS_ENABLED";
const string SettingTextKeys::SETTING_MUSIC_ENABLED = "SETTING_MUSIC_ENABLED";

string SettingTextKeys::get_autopickup_exclude_over_weight_message(const string& weight_in_lbs)
{
	string msg = StringTable::get(SETTING_AUTOPICKUP_EXCLUDE_OVER_WEIGHT);
	boost::replace_first(msg, "%s", weight_in_lbs);
	return msg;
}

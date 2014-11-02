#pragma once
#include <string>

// Settings that can be read from the ini settings.  Each DisplaySetting
// represents the key to a particular common setting.
class DisplaySettings
{
  public:
    static const std::string DISPLAY_SETTING_COLOUR;

  protected:
    DisplaySettings();
    ~DisplaySettings();
};


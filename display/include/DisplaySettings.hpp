#pragma once
#include <string>

// Settings that can be read from the ini settings.  Each DisplaySetting
// represents the key to a particular common setting.
class DisplaySettings
{
  public:
    // Whether or not to use colour - true or false
    static const std::string DISPLAY_SETTING_COLOUR;

    // When not using the full range of colours, what "monochrome" colour
    // should be used?
    static const std::string DISPLAY_SETTING_MONOCHROME_COLOUR;

  protected:
    DisplaySettings();
    ~DisplaySettings();
};


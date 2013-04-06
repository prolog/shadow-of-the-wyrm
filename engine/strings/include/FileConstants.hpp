#pragma once
#include <string>

// Constant filenames, patterns, etc.
class FileConstants
{
  public:
    static const std::string XML_CONFIGURATION_FILE;
    static const std::string SAVEFILE_PATTERN;
    static const std::string CUSTOM_MAPS_DIRECTORY;
    static const std::string CUSTOM_MAPS_PATTERN;

  protected:
    FileConstants();
    ~FileConstants();
};


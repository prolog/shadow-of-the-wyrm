#pragma once
#include <string>

class TextFormatSpecifiers
{
  public:
    static const std::string NEW_PARAGRAPH;
    static const std::string LINE_BREAK;
    static const std::string NEW_PAGE;
    static const std::string SYMBOL;
    static const std::string SPACE;

  protected:
    TextFormatSpecifiers();
    ~TextFormatSpecifiers();
};


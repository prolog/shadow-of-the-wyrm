#pragma once
#include <string>
#include "common.hpp"
#include "Prompt.hpp"

class PromptProcessor
{
  public:
    virtual ~PromptProcessor() = default;

    Coordinate get_prompt_coords(const PromptLocation pl, const std::string& prompt_text, const int row, const int col, const int max_rows, const int max_cols);
};

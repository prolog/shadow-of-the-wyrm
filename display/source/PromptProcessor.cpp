#include "PromptProcessor.hpp"

using namespace std;

Coordinate PromptProcessor::get_prompt_coords(const PromptLocation pl, const string& prompt_text, const int row, const int col, const int max_rows, const int max_cols)
{
  Coordinate c = make_pair(0, 0);

  int prompt_row = row;
  int prompt_col = col;

  if (pl == PromptLocation::PROMPT_LOCATION_LOWER_RIGHT)
  {
    int prompt_text_length = prompt_text.size();
    prompt_col = max_cols - prompt_text_length - 1;
    prompt_row = max_rows - 1;

    c = {prompt_row, prompt_col};
  }

  return c;
}
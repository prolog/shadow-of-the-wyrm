#pragma once

enum struct CellValue
{
  CELL_OFF = 0,
  CELL_ON = 1
};

using CellMap = std::vector<std::vector<CellValue>>;


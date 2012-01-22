#pragma once
#include <fstream>
#include <string>

class FileWriter
{
  public:
    FileWriter(const std::string& filename_minus_extension);
    ~FileWriter();

    bool write(const std::string& str);
    
  protected:
    std::ofstream file;
};

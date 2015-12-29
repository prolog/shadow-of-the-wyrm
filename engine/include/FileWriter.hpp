#pragma once
#include <fstream>
#include <string>

class FileWriter
{
  public:
    FileWriter(const std::string& filename_minus_extension);
    ~FileWriter();

    void set_base_file_name(const std::string& filename_minus_extension);
    bool write(const std::string& str);
    
  protected:
    std::string filename;
    std::ofstream file;
};

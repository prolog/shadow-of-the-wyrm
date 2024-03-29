#pragma once
#include <fstream>
#include <string>

class FileWriter
{
  public:
    FileWriter(const std::string& filename);
    ~FileWriter();

    void set_file_name(const std::string& filename);
    bool write(const std::string& str);
    
  protected:
    std::string filename;
    std::ofstream file;
};

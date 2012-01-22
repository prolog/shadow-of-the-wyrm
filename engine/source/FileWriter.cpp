#include "FileWriter.hpp"

using namespace std;

FileWriter::FileWriter(const string& filename_less_extension)
{
  string filename = filename_less_extension + ".txt";
  file.open(filename.c_str(), ios::out);
}

FileWriter::~FileWriter()
{
  file.close();
}

bool FileWriter::write(const string& str)
{
  bool write_status = false;
  
  if (file.is_open())
  {
    file << str << flush;
    write_status = true;
  }
  
  return write_status;
}

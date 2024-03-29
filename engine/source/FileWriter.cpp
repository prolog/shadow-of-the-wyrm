#include "FileWriter.hpp"

using namespace std;

FileWriter::FileWriter(const string& new_filename)
{
  filename = new_filename;
}

FileWriter::~FileWriter()
{
  if (file.is_open())
  {
    file.close();
  }
}

void FileWriter::set_file_name(const string& new_filename)
{
  filename = new_filename;
}

// Check to see if a file is available.  If it is, write the file.
// If the requested file already exists, return false.
bool FileWriter::write(const string& str)
{
  bool write_status = false;  
  bool file_available = false;

  std::ifstream infile(filename);
  file_available = !infile.good();

  if (file_available)
  {
    file.open(filename.c_str(), ios::out);

    if (file.is_open())
    {
      file << str << flush;
      write_status = true;
    }
  }
  
  return write_status;
}

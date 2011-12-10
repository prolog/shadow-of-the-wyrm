#include "XMLFileReader.hpp"
#include <iostream>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace xercesc;
using namespace std;

void XMLFileReader::check_file_status(const string& filename, struct stat* file_status)
{
  int iretStat = stat(filename.c_str(), file_status);
  if( iretStat == ENOENT )
    throw ( runtime_error("Path does not exist.") );
  else if( iretStat == ENOTDIR )
    throw ( runtime_error("One of the directories specified does not exist."));
  else if( iretStat == EACCES )
    throw ( runtime_error("Permission denied."));
  else if( iretStat == ENAMETOOLONG )
    throw ( runtime_error("File name is too long.  File can not be read\n"));
}

// Read the data from a file, and return the root element.
XMLNode XMLFileReader::get_xml_from_file(const string& filename)
{
  XMLParser* parser = XMLParser::instance();

  struct stat file_status;
  check_file_status(filename, &file_status);

  XMLDocument xml_doc = parser->parse(filename);
  XMLNode root_node = xml_doc.get_document_element();
  return root_node;
}

#pragma once

#include <string>
#include <memory>

#include "XMLDataStructures.hpp"

class XMLFileReader
{
  public:
    // Read the XML from the file, and return the root element.
    XMLNode get_xml_from_file(const std::string& filename);

    // Throwns a runtime error if the status is bad.
    void check_file_status(const std::string& filename, struct stat* file_status);

  protected:
};

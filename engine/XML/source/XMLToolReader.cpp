#include "XMLToolReader.hpp"

using namespace std;

XMLToolReader::XMLToolReader()
{
}

XMLToolReader::~XMLToolReader()
{
}

// Methods for reading in details about tools from XML nodes conformant to the Tool type.
void XMLToolReader::parse(ToolPtr tool, GenerationValues& gv, const XMLNode& tool_node)
{
  if (!tool_node.is_null())
  {
    XMLItemReader::parse(tool, gv, tool_node);
    
    string lock_id = XMLUtils::get_child_node_value(tool_node, "LockID");
    tool->set_lock_id(lock_id);
  }
}

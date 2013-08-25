#include <iostream>
#include "buildinfo.hpp"
#include "XMLDataStructures.hpp"
#include "Conversion.hpp"

using namespace xercesc;
using namespace std;

// XML static vars
// Right now, there is only one namespace used for SavageLands.
string XML::xml_namespace = "urn:savage_lands:1.0.0";

// Routines for setting up/tearing down the XML Library.  Xerces requires these.
void XML::initialize()
{
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch( XMLException &e )
  {
    char* message = XMLString::transcode( e.getMessage() );
    cerr << "Couldn't initialize Xerces: " << message << endl;
  }
}

void XML::tear_down()
{
  try
  {
    delete XMLParser::instance();
    XMLPlatformUtils::Terminate();
  }
  catch( XMLException &e )
  {
    char* message = XMLString::transcode( e.getMessage() );
    cerr << "Error when attempting to teardown Xerces: " << message << endl;
  }
}

// This...is a hack.
void XML::set_namespace(const std::string& new_ns)
{
  xml_namespace = new_ns;
}

string XML::get_namespace()
{
  return xml_namespace;
}

// By default, always search using the Savage Lands namespace - no need to try anything else, yet.
XMLNode XMLUtils::get_next_element_by_local_name(const XMLNode& node, const string& node_name)
{
  XMLNode result_node;

  vector<XMLNode> results = get_elements_by_local_name(node, node_name);
  if (!results.empty())
  {
    result_node = results.at(0);
  }

  return result_node;
}


// JCD FIXME: Supposedly, getItem is actually pretty inefficient (O(n), not O(1)).
// Rewrite?  At least, convert DOMElement to DOMNode and use a getNextSibling() type
// loop.
vector<XMLNode> XMLUtils::get_elements_by_local_name(const XMLNode& node, const string& node_name)
{
  vector<XMLNode> result;

  if (!node.is_null())
  {
    XMLTypeString xml_s_ns(XML::get_namespace().c_str());
    XMLTypeString xml_local_name(node_name.c_str());

    XMLElementImplPtr internal_node = node.get_node();
    XMLNodeListImplPtr node_list = internal_node->getElementsByTagNameNS(xml_s_ns.get_xmlstr(), xml_local_name.get_xmlstr());

    int size = node_list->getLength();
    for (int x = 0; x < size; x++)
    {
      XMLNodeImplPtr current_node = node_list->item(x);
      if (current_node->getNodeType() == DOMNode::ELEMENT_NODE)
      {
        XMLNodeImplPtr parent_node = current_node->getParentNode();
        
        CTypeString parent_name(parent_node->getLocalName());
        CTypeString param_node_name(node.get_node()->getLocalName());
        
        if (strcmp(parent_name.get_cstr(), param_node_name.get_cstr()) == 0)
        {
          XMLElementImplPtr element = static_cast<XMLElementImplPtr>(current_node);
          XMLNode new_result_node(element);
          result.push_back(new_result_node);          
        }
      }
    }
  }

  return result;
}

string XMLUtils::get_node_value(const XMLNode& node)
{
  string result = "";

  XMLElementImplPtr internal_element = node.get_node();
  if (internal_element)
  {
    XMLNodeImplPtr text_node = internal_element->getFirstChild();

    if (text_node)
    {
      CTypeString cts(text_node->getNodeValue());
      result = cts.get_cstr();
    }
  }

  return result;
}

int XMLUtils::get_node_int_value(const XMLNode& node, const int default_value)
{
  string node_value = XMLUtils::get_node_value(node);

  if (!node_value.empty())
  {
    int converted_value = String::to_int(node_value);
    return converted_value;
  }

  return default_value;
}

float XMLUtils::get_node_float_value(const XMLNode& node, const float default_value)
{
  string node_value = XMLUtils::get_node_value(node);

  if (!node_value.empty())
  {
    float converted_value = String::to_float(node_value);
    return converted_value;
  }

  return default_value;
}

bool XMLUtils::get_node_bool_value(const XMLNode& node, const bool default_value)
{
  string node_value = XMLUtils::get_node_value(node);

  if (!node_value.empty())
  {
    bool converted_value = String::to_bool(node_value);
    return converted_value;
  }

  return default_value;
}

string XMLUtils::get_child_node_value(const XMLNode& parent_node, const string& child_node_name)
{
  XMLNode node = XMLUtils::get_next_element_by_local_name(parent_node, child_node_name);
  return XMLUtils::get_node_value(node);
}

int XMLUtils::get_child_node_int_value(const XMLNode& parent_node, const string& child_node_name, const int default_value)
{
  string node_value = XMLUtils::get_child_node_value(parent_node, child_node_name);

  if (!node_value.empty())
  {
    int converted_value = String::to_int(node_value);
    return converted_value;
  }

  return default_value;
}

float XMLUtils::get_child_node_float_value(const XMLNode& parent_node, const string& child_node_name, const float default_value)
{
  string node_value = XMLUtils::get_child_node_value(parent_node, child_node_name);

  if (!node_value.empty())
  {
    float converted_value = String::to_float(node_value);
    return converted_value;
  }

  return default_value;
}

bool XMLUtils::get_child_node_bool_value(const XMLNode& parent_node, const string& child_node_name, const bool default_value)
{
  string node_value = XMLUtils::get_child_node_value(parent_node, child_node_name);

  if (!node_value.empty())
  {
    bool converted_value = String::to_bool(node_value);
    return converted_value;
  }

  return default_value;
}

string XMLUtils::get_attribute_value(const XMLNode& node, const string& attribute_name)
{
  string attribute_value;

  if (!node.is_null())
  {
    XMLNodeImplPtr internal_node = node.get_node();

    if (internal_node->getNodeType() == DOMNode::ELEMENT_NODE)
    {
      XMLElementImplPtr internal_elem = static_cast<DOMElement*>(internal_node);
      XMLTypeString xml_s(attribute_name.c_str());
      XMLCh* xml_attr_name = xml_s.get_xmlstr();
      const XMLCh* xml_ch = internal_elem->getAttribute(xml_attr_name);
      CTypeString cts(xml_ch);
      attribute_value = cts.get_cstr();
    }
  }

  return attribute_value;
}

int XMLUtils::get_attribute_int_value(const XMLNode& node, const string& attribute_name, const int default_value)
{
  string attribute_value = XMLUtils::get_attribute_value(node, attribute_name);

  if (!attribute_value.empty())
  {
    int converted_attribute_value = String::to_int(attribute_value);
    return converted_attribute_value;
  }

  return default_value;
}

float XMLUtils::get_attribute_float_value(const XMLNode& node, const string& attribute_name, const float default_value)
{
  string attribute_value = XMLUtils::get_attribute_value(node, attribute_name);

  if (!attribute_value.empty())
  {
    float converted_attribute_value = String::to_float(attribute_value);
    return converted_attribute_value;
  }

  return default_value;
}

bool XMLUtils::get_attribute_bool_value(const XMLNode& node, const string& attribute_name, const bool default_value)
{
  string attribute_value = XMLUtils::get_attribute_value(node, attribute_name);

  if (!attribute_value.empty())
  {
    bool converted_attribute_value = String::to_bool(attribute_value);
    return converted_attribute_value;
  }

  return default_value;
}

// XML Parser methods/declarations
XMLParser* XMLParser::parser_instance = NULL;

XMLParser* XMLParser::instance()
{
  if (parser_instance == NULL)
  {
    parser_instance = new XMLParser();
  }

  return parser_instance;
}

XMLParser::XMLParser()
{
  internal_parser = new XercesDOMParser;
  initialize_parser();
}

XMLParser::~XMLParser()
{
  if (internal_parser) delete internal_parser;
}

XMLDocument XMLParser::parse(const string& filename)
{
  XMLDocument doc;

  if (internal_parser)
  {
    internal_parser->parse(filename.c_str());
    XMLDocumentImplPtr temp_doc = internal_parser->getDocument();

    if (temp_doc)
    {
      doc.set_document(temp_doc);
    }
  }

  return doc;
}

void XMLParser::initialize_parser()
{
  internal_parser->setValidationScheme(XercesDOMParser::Val_Always);
  internal_parser->setDoNamespaces(true);
  internal_parser->setDoSchema(true);
  internal_parser->setLoadExternalDTD(true);
}



// XMLNode methods
XMLNode::XMLNode()
{
  set_node(NULL);
}

XMLNode::XMLNode(XMLElementImplPtr new_node)
{
  set_node(new_node);
}

XMLNode::~XMLNode()
{
}

void XMLNode::set_node(XMLElementImplPtr new_element)
{
  element = new_element;
}

bool XMLNode::is_null() const
{
  return (element == NULL);
}

XMLElementImplPtr XMLNode::get_node() const
{
  return element;
}

// XMLDocument methods
XMLDocument::XMLDocument()
{
  doc = NULL;
}

XMLDocument::XMLDocument(XMLDocumentImplPtr new_doc)
{
  set_document(new_doc);
}

XMLDocument::~XMLDocument()
{
}

void XMLDocument::set_document(XMLDocumentImplPtr new_doc)
{
  doc = new_doc;
}

XMLNode XMLDocument::get_document_element()
{
  XMLNode node(doc->getDocumentElement());
  return node;
}

// XMLTypeString methods
XMLTypeString::XMLTypeString(const char * c_str)
{
  xml_str = XMLString::transcode(c_str);
}

XMLTypeString::~XMLTypeString()
{
  XMLString::release(&xml_str);
}

XMLCh* XMLTypeString::get_xmlstr()
{
  return xml_str;
}

// CTypeString methods
CTypeString::CTypeString(const XMLCh* xml_str)
{
  c_str = XMLString::transcode(xml_str);
}

CTypeString::~CTypeString()
{
  XMLString::release(&c_str);
}

const char * CTypeString::get_cstr()
{
  return c_str;
}

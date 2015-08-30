#pragma once

#include <vector>
#include <string>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

// Implementations - ifdef these if additional parser support is needed.
// Can't use shared_ptr here - Xerces has its own resource deallocation scheme...
using XMLAttributeImpl = xercesc::DOMAttr;
using XMLElementImpl = xercesc::DOMElement;
using XMLNodeImpl = xercesc::DOMNode;
using XMLNodeListImpl = const xercesc::DOMNodeList;

using XMLAttributeImplPtr = xercesc::DOMAttr*;
using XMLElementImplPtr = xercesc::DOMElement*;
using XMLNodeImplPtr = xercesc::DOMNode*;
using XMLNodeListImplPtr = const xercesc::DOMNodeList*;
using XMLAttributeListImplPtr = const xercesc::DOMNamedNodeMap*;

using XMLDocumentImpl = xercesc::DOMDocument;
using XMLDocumentImplPtr = xercesc::DOMDocument*;

using XMLParserImpl = xercesc::XercesDOMParser;
using XMLParserImplPtr = xercesc::XercesDOMParser*;

using ElementPtr = xercesc::DOMElement*;

class XMLNode
{
  public:
    XMLNode();
    XMLNode(XMLElementImplPtr new_node);
    ~XMLNode();

    void set_node(XMLElementImplPtr new_node);
    XMLElementImplPtr get_node() const;
    

    bool is_null() const;

  protected:
    XMLElementImplPtr element;
};

class XML
{
  public:
    static void initialize();
    static void tear_down();
    
    static void set_namespace(const std::string& new_ns);
    static std::string get_namespace();
    
  protected:
    static std::string xml_namespace;
};

class XMLUtils
{
  public:
    static XMLNode get_next_element_by_local_name(const XMLNode& parent_node, const std::string& node_name);
    static std::vector<XMLNode> get_elements_by_local_name(const XMLNode& parent_node, const std::string& node_name);
    static std::string  get_node_value(const XMLNode& node);
    static int          get_node_int_value(const XMLNode& node, const int default_value = 0);
    static float        get_node_float_value(const XMLNode& node, const float default_value = 0.0);
    static bool         get_node_bool_value(const XMLNode& node, const bool default_value = false);
    static std::string  get_child_node_value(const XMLNode& parent_node, const std::string& child_node_name);
    static int          get_child_node_int_value(const XMLNode& parent_node, const std::string& child_node_name, const int default_value = 0);
    static float        get_child_node_float_value(const XMLNode& parent_node, const std::string& child_node_name, const float default_value = 0.0);
    static bool         get_child_node_bool_value(const XMLNode& parent_node, const std::string& child_node_name, const bool default_value = false);
    static std::string  get_attribute_value(const XMLNode& node, const std::string& attribute_name);
    static int          get_attribute_int_value(const XMLNode& node, const std::string& attribute_name, const int default_value = 0);
    static float        get_attribute_float_value(const XMLNode& node, const std::string& attribute_name, const float default_value = 0.0);
    static bool         get_attribute_bool_value(const XMLNode& node, const std::string& attribute_name, const bool default_value = false);
};

class XMLDocument
{
  public:
    XMLDocument();
    XMLDocument(XMLDocumentImplPtr new_doc);
    ~XMLDocument();

    void set_document(XMLDocumentImplPtr new_doc);
    XMLNode get_document_element();

  protected:
    XMLDocumentImplPtr doc;
};

class XMLParser
{
  public:
    static XMLParser* instance();
    XMLDocument parse(const std::string& filename);

  protected:
    friend class XML;

    static void create_instance();
    static void set_null();

    XMLParser();
    ~XMLParser();
    void release();
    void initialize_parser();
    static XMLParser* parser_instance;
    XMLParserImplPtr internal_parser;
};

class XMLTypeString
{
  public:
    XMLTypeString(const char * c_str);
    ~XMLTypeString();

    XMLCh* get_xmlstr();

  protected:
    XMLCh* xml_str;
};

class CTypeString
{
  public:
    CTypeString(const XMLCh * xml_str);
    ~CTypeString();

    const char * get_cstr();
  protected:
    char* c_str;
};

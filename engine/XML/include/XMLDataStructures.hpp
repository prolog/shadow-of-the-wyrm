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
typedef xercesc::DOMAttr XMLAttributeImpl;
typedef xercesc::DOMElement XMLElementImpl;
typedef xercesc::DOMNode XMLNodeImpl;
typedef const xercesc::DOMNodeList XMLNodeListImpl;

typedef xercesc::DOMAttr* XMLAttributeImplPtr;
typedef xercesc::DOMElement* XMLElementImplPtr;
typedef xercesc::DOMNode* XMLNodeImplPtr;
typedef const xercesc::DOMNodeList* XMLNodeListImplPtr;
typedef const xercesc::DOMNamedNodeMap* XMLAttributeListImplPtr;

typedef xercesc::DOMDocument XMLDocumentImpl;
typedef xercesc::DOMDocument* XMLDocumentImplPtr;

typedef xercesc::XercesDOMParser XMLParserImpl;
typedef xercesc::XercesDOMParser* XMLParserImplPtr;

typedef xercesc::DOMElement* ElementPtr;

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

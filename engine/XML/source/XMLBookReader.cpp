#include "XMLBookReader.hpp"

using namespace std;

XMLBookReader::XMLBookReader()
{
}

XMLBookReader::~XMLBookReader()
{
}

// Methods for reading details about a book/spellbook from an XML node
// conformant to the Book type.
void XMLBookReader::parse(BookPtr book, GenerationValues& igv, const XMLNode& book_node)
{
  if (!book_node.is_null())
  {
    XMLItemReader::parse(book, igv, book_node);

    // The spell which is contained within the book.
    string spell_id = XMLUtils::get_child_node_value(book_node, "SpellID");
    book->set_spell_id(spell_id);
  }
}

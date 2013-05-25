#include "XMLSpellbookReader.hpp"

using namespace std;

XMLSpellbookReader::XMLSpellbookReader()
{
}

XMLSpellbookReader::~XMLSpellbookReader()
{
}

// Methods for reading details about a book/spellbook from an XML node
// conformant to the Book type.
void XMLSpellbookReader::parse(SpellbookPtr book, GenerationValues& igv, const XMLNode& book_node)
{
  if (!book_node.is_null())
  {
    XMLItemReader::parse(book, igv, book_node);

    // The spell which is contained within the book.
    string spell_id = XMLUtils::get_child_node_value(book_node, "SpellID");
    book->set_spell_id(spell_id);

    // The difficulty of learning the spell, as it is described by the book.
    int difficulty = XMLUtils::get_child_node_int_value(book_node, "Difficulty");
    book->set_difficulty(difficulty);
  }
}

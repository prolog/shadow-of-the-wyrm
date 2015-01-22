#pragma once
class Modifier;
class XMLNode;

class XMLModifierReader
{
  public:
    XMLModifierReader();
    ~XMLModifierReader();

    Modifier get_modifier(const XMLNode& modifiers_node);
};

#pragma once
#include "Class.hpp"
#include "XMLReader.hpp"

class XMLNode;
class Skills;

class XMLClassesReader : public XMLReader
{
  public:
    ClassMap get_classes(const XMLNode& xml_configuration_classes_node);

  protected:
    ClassPtr parse_class(const XMLNode& class_node);
    void parse_class_initial_modifiers(Class* current_class, const XMLNode& initial_modifiers_node);
    void parse_class_resistances(Class* current_class, const XMLNode& resistances_node);
    void parse_class_skills(Class* current_class, const XMLNode& skills_node);
    void parse_class_titles(Class* current_class, const XMLNode& titles_node); 
    void parse_class_deity_dislike_multipliers(Class* current_class, const XMLNode& deity_dislike_multipliers_node);
    void parse_crowning_gifts(Class* current_class, const XMLNode& crowning_node);
};

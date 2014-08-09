#pragma once
#include "XMLInitialItemReader.hpp"
#include "Class.hpp"

class XMLNode;
class Skills;

class XMLClassesReader
{
  public:
    ClassMap get_classes(const XMLNode& xml_configuration_classes_node);

  protected:
    ClassPtr parse_class(const XMLNode& class_node);
    void parse_class_initial_modifiers(ClassPtr current_class, const XMLNode& initial_modifiers_node);
    void parse_class_resistances(ClassPtr current_class, const XMLNode& resistances_node);
    void parse_class_skills(ClassPtr current_class, const XMLNode& skills_node);
    void parse_class_titles(ClassPtr current_class, const XMLNode& titles_node);
    
    void parse_initial_equipment_and_inventory(ClassPtr current_class, const XMLNode& initial_equipment_and_inventory_node);
    void parse_initial_equipment(ClassPtr current_class, const XMLNode& initial_equipment_node);
    void parse_initial_inventory(ClassPtr current_class, const XMLNode& initial_inventory_node);
    
    XMLInitialItemReader initial_item_reader;
};

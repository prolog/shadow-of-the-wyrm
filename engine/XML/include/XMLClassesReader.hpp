#pragma once
#include "Class.hpp"

class XMLNode;
class Skills;

class XMLClassesReader
{
  public:
    ClassMap get_classes(const XMLNode& xml_configuration_classes_node);

  protected:
    ClassPtr parse_class(const XMLNode& class_node);
    void parse_class_initial_statistics(ClassPtr current_class, const XMLNode& initial_statistics_node);
    void parse_class_initial_modifiers(ClassPtr current_class, const XMLNode& initial_modifiers_node);
    void parse_class_resistances(ClassPtr current_class, const XMLNode& resistances_node);
    void parse_class_skills(ClassPtr current_class, const XMLNode& skills_node);
};

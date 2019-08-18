#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Display.hpp"

using DisplaySerializationMap = std::map<ClassIdentifier, std::pair<DisplayPtr, ControllerPtr>>;
using DisplayIdentifierMap = std::map<std::string, ClassIdentifier>;

class DisplayFactory
{
  public:
    DisplayFactory();
    ~DisplayFactory();

    std::pair<DisplayPtr, ControllerPtr> create_display_details(const std::string& display_id);
    std::pair<DisplayPtr, ControllerPtr> create_display_details(const ClassIdentifier ci);

  protected:
    ClassIdentifier get_class_id_for_identifier(const std::string& identifier);

    void initialize_display_map();
    void initialize_display_identifier_map();

    static DisplaySerializationMap display_map;
    static DisplayIdentifierMap display_identifier_map;
};


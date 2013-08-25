#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Display.hpp"

typedef std::map<ClassIdentifier, std::pair<DisplayPtr, ControllerPtr>> DisplaySerializationMap;
typedef std::map<std::string, ClassIdentifier> DisplayIdentifierMap;

class DisplayFactory
{
  public:
    static std::pair<DisplayPtr, ControllerPtr> create_display_details(const std::string& display_id);
    static std::pair<DisplayPtr, ControllerPtr> create_display_details(const ClassIdentifier ci);

  protected:
    static ClassIdentifier get_class_id_for_identifier(const std::string& identifier);

  private:
    DisplayFactory();
    ~DisplayFactory();

    static void initialize_display_map();
    static void initialize_display_identifier_map();

    static DisplaySerializationMap display_map;
    static DisplayIdentifierMap display_identifier_map;
};


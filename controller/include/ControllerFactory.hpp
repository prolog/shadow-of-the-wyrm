#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Controller.hpp"

typedef std::map<ClassIdentifier, ControllerPtr> ControllerSerializationMap;

class ControllerFactory
{
  public:
    static ControllerPtr create_controller(const ClassIdentifier ci);

  protected:
    ControllerFactory();
    ~ControllerFactory();

    static void initialize_controller_map();

    static ControllerSerializationMap controller_map;
};


#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Controller.hpp"

using ControllerSerializationMap = std::map<ClassIdentifier, ControllerPtr>;

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


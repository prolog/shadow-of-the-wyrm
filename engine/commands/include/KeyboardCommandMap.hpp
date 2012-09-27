#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

namespace boost 
{ 
  namespace serialization 
  { 
    class access; 
  } 
}

class KeyboardCommandMap
{
  public:
    KeyboardCommandMap();
    virtual ~KeyboardCommandMap();

    virtual std::string get_command_type(const std::string& keyboard_input);

  protected:
    virtual void command_not_found(const std::string& keyboard_input);
    virtual void initialize_command_mapping();
    std::map<std::string, std::string> command_mapping;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};

typedef boost::shared_ptr<KeyboardCommandMap> KeyboardCommandMapPtr;

#pragma once
#include <string>
#include <memory>
#include "common.hpp"
#include "ISerializable.hpp"

class ITimeObserver : public ISerializable
{
  public:
    ITimeObserver();
    virtual ~ITimeObserver() {};
    
    virtual void notify(const ulonglong minutes_elapsed) = 0;
    virtual std::string get_id() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

    virtual ITimeObserver* clone() = 0;

  protected:
    virtual std::string generate_id();
    virtual void update_minutes_elapsed(const ulonglong minutes_elapsed);

    ulonglong minutes_elapsed;
    std::string id;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<ITimeObserver> ITimeObserverPtr;

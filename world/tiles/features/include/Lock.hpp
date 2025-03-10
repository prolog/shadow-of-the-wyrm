#pragma once
#include <memory>
#include "ISerializable.hpp"

class Lock : public ISerializable
{
  public:
    Lock();
    Lock(const std::string& new_lock_id, const bool new_locked_val);

    bool operator==(const Lock& lock) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    void set_lock_id(const std::string& new_lock_id);
    std::string get_lock_id() const;

    void set_locked(bool new_locked);
    bool get_locked() const;

    // Return true if the lock changed state, false otherwise.
    bool handle();

  protected:
    std::string lock_id;
    bool locked;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using LockPtr = std::shared_ptr<Lock>;

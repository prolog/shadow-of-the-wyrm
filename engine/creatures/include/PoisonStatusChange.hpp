#pragma once
#include "StatusChange.hpp"

class PoisonStatusChange : public StatusChange
{
  public:
    virtual void apply_change(boost::shared_ptr<Creature> creature) const;
    virtual void finalize_change(boost::shared_ptr<Creature> creature) const;
    virtual void undo_change(boost::shared_ptr<Creature> creature) const;
    virtual void tick(boost::shared_ptr<Creature> creature) const;

    virtual bool has_status_message() const;
    virtual std::string get_status_message_sid() const;
    virtual Colour get_status_message_colour() const;
};


#pragma once
#include "ISerializable.hpp"

class BoolStatistic : public ISerializable
{
	public:
    BoolStatistic();
    BoolStatistic(const bool new_base_and_current);
    BoolStatistic& operator=(const bool& rhs);
    virtual bool operator==(const BoolStatistic& stat) const;

    void set_base(bool new_base);
    bool get_base() const;

    void set_current(bool new_current);
    bool get_current() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

	protected:
		bool base;
		bool current;

  private:
    ClassIdentifier internal_class_identifier() const;
};


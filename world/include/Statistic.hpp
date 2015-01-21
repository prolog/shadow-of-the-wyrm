#pragma once
#include "ISerializable.hpp"

class Statistic : public ISerializable
{
	public:
    Statistic();
    Statistic(const int new_base_and_current);
    Statistic& operator=(const int& rhs);
    virtual bool operator==(const Statistic& stat) const;

    void set_base(int new_base);
    int  get_base() const;

    void set_current(int new_current);
    int  get_current() const;

    int get_lowest() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

	protected:
		int base;
		int current;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

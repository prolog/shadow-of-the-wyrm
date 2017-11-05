#pragma once
#include "ISerializable.hpp"
#include "Marks.hpp"

enum SetStatisticFailure
{
  SET_STATISTIC_FAILURE_IGNORE = 0,
  SET_STATISTIC_FAILURE_TAKE_HIGHEST = 1
};

class Statistic : public ISerializable
{
	public:
    Statistic();
    Statistic(const int new_base_and_current);
    Statistic& operator=(const int& rhs);
    virtual bool operator==(const Statistic& stat) const;

    void set_base_current(int new_base_and_current, const SetStatisticFailure ssf = SetStatisticFailure::SET_STATISTIC_FAILURE_IGNORE);

    void set_base(int new_base, const SetStatisticFailure ssf = SetStatisticFailure::SET_STATISTIC_FAILURE_IGNORE);
    int  get_base() const;

    void set_current(int new_current, const SetStatisticFailure ssf = SetStatisticFailure::SET_STATISTIC_FAILURE_IGNORE);
    int  get_current() const;

    void set_original(const int new_original);
    int get_original() const;

    void set_max(const int new_max);
    int get_max() const;

    int get_lowest() const;

    bool get_full() const;
    bool get_max_marks() const;

    void set_marks(const Marks& new_marks);
    Marks get_marks() const;
    Marks& get_marks_ref();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

	protected:
		int base;
		int current;
    int original;
    int max;
    Marks marks;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

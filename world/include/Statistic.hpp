#pragma once

class Statistic
{
	public:
    Statistic();
    Statistic(const int new_base_and_current);
    Statistic& operator=(const int& rhs);

    void set_base(int new_base);
    int  get_base() const;

    void set_current(int new_current);
    int  get_current() const;

	protected:
		int base;
		int current;
};

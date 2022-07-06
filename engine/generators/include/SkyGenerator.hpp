#pragma once
#include "Generator.hpp"

class SkyGenerator : public SOTW::Generator
{
	public:
		SkyGenerator(const std::string& map_exit_id);

		virtual MapPtr generate(const Dimensions& dim) override;

};
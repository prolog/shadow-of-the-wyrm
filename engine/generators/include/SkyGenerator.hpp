#pragma once
#include "Generator.hpp"

class SkyGenerator : public SOTW::Generator
{
	public:
		SkyGenerator(const std::string& map_exit_id);
		virtual ~SkyGenerator() = default;

		virtual MapPtr generate(const Dimensions& dim) override;
		virtual MapType get_map_type() const override;
};
#include "GoodAltar.hpp"
#include "MaterialFactory.hpp"

GoodAltar::GoodAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_MARBLE))
{
}

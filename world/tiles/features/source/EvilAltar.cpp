#include "EvilAltar.hpp"
#include "MaterialFactory.hpp"

EvilAltar::EvilAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_ONYX))
{
}

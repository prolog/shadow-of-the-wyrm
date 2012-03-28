#include "NeutralAltar.hpp"
#include "MaterialFactory.hpp"

NeutralAltar::NeutralAltar(const std::string& new_deity_id)
: Altar(new_deity_id, MaterialFactory::create_material(MATERIAL_TYPE_STONE))
{
}

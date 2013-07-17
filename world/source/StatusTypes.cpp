#include "StatusTypes.hpp"

using namespace std;

StatusIdentifiers::StatusIdentifiers()
{
}

StatusIdentifiers::~StatusIdentifiers()
{
}

// The identifiers just need to be unique within those specified in
// StatusIdentifiers.
const string StatusIdentifiers::STATUS_ID_POISON = "_poison";
const string StatusIdentifiers::STATUS_ID_MUTE = "_mute";
const string StatusIdentifiers::STATUS_ID_PARALYSIS = "_para";
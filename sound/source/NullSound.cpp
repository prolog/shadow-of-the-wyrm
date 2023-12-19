#include "NullSound.hpp"

NullSound::NullSound()
{
}

NullSound::~NullSound()
{
}

ClassIdentifier NullSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_NULL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullSound_test.cpp"
#endif
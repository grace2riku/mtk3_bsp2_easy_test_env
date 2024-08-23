#include "CppUTest/TestHarness.h"

TEST_GROUP(CortexM7ArchitectureGroup)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CortexM7ArchitectureGroup, intSize)
{
	// Cortex-M7は32bitのハズ!!!
	LONGS_EQUAL(4, sizeof(int));
}

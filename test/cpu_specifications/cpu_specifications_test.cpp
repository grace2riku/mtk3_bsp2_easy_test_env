#include "CppUTest/TestHarness.h"
#include "cpu_specifications_utilities.h"

TEST_GROUP(CPUSpecificationsGroup)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CPUSpecificationsGroup, endian)
{
	// STM32H723ZGはリトルエンディアンのハズ!!!
	CHECK_TRUE(is_little_endian());
}

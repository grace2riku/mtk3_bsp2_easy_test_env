/*
 * synchronization_and_communication_test.cpp
 *
 *  Created on: 2024/08/25
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>


TEST_GROUP(SynchronizationAndCommunicationTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる

    void setup()  // setupは各TEST実行の際に呼び出される
    {

    }

    void teardown()
    {
    }
};

TEST(SynchronizationAndCommunicationTestGroup, BasicUsageMailbox)
{
	FAIL("FAIL: SynchronizationAndCommunicationTestGroup, BasicUsageMailbox");
}

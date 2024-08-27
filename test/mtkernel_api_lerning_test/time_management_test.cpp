/*
 * time_management_test.cpp
 *
 *  Created on: 2024/08/27
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

TEST_GROUP(TimeManagementTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる

    void setup()  // setupは各TEST実行の際に呼び出される
    {

    }

    void teardown()
    {
    }
};

// システム稼働時間の基本な使い方のテスト
TEST(TimeManagementTestGroup, BasicUsage_tk_get_otm)
{
	ER ercd;
	SYSTIM otm_before, otm_after;
	UW diff_time;
	bool diff_check;

	ercd = tk_get_otm(&otm_before);
	if (ercd != E_OK) {
		FAIL("");
	}

	tk_dly_tsk(2000);

	ercd = tk_get_otm(&otm_after);
	if (ercd != E_OK) {
		FAIL("");
	}

	diff_time = otm_after.lo - otm_before.lo;

	if (2000 <= diff_time && diff_time <= 2020) {
		diff_check = true;
	} else {
		diff_check = false;
	}

	CHECK_TRUE(diff_check);
}

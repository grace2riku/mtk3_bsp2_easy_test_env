/*
 * mtkernel_task_management_lerning_test.cpp
 *
 *  Created on: 2024/08/22
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "mtkernel_task_manegement.h"


TEST_GROUP(MtKernelTaskManegementLerningTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる
	ID	test_tskid; // Task ID number
	ER ercd;

    void setup()  // setupは各TEST実行の際に呼び出される
    {
    	test_tskid = get_mtkernel_task_manegemnrt_test_tskid();
    }

    void teardown()
    {

    }
};

TEST(MtKernelTaskManegementLerningTestGroup, BasicUsage_tk_ref_tsk)
{
	T_RTSK rtsk;

	// タスク状態参照
	ercd = tk_ref_tsk(test_tskid, &rtsk);
	if (ercd != E_OK) {
		FAIL("tk_ref_tsk Error. Fail test.");
	}

	// 拡張情報
	LONGS_EQUAL(1, *((UB*)rtsk.exinf));
	// 現在の優先度
	LONGS_EQUAL(9, rtsk.tskpri);
	// ベース優先度
	LONGS_EQUAL(9, rtsk.tskbpri);
}

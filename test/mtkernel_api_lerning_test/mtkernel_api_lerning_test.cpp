/*
 * mtkernel_api_lerning_test.cpp
 *
 *  Created on: 2024/08/20
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "mtkernel_task.h"


TEST_GROUP(MtKernelApiLerningTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる
	ID	mtkernel_test_tskid; // Task ID number
	ER ercd;

    void setup()  // setupは各TEST実行の際に呼び出される
    {

    }

    void teardown()
    {
		ercd = tk_ter_tsk(mtkernel_test_tskid);
		ercd = tk_del_tsk(mtkernel_test_tskid);
    }
};

TEST(MtKernelApiLerningTestGroup, CreateAndStartTsk)
{
//	CHECK(true);
#if 1
	T_RTSK rtsk;

	/* Create & Start Tasks */
	mtkernel_test_tskid = tk_cre_tsk(&mtkernel_test_ctsk);

	ercd = tk_sta_tsk(mtkernel_test_tskid, 0);
	if (ercd != E_OK) {
		FAIL("tk_sta_tsk Error. Fail test.");
	}

	// タスク状態参照
	ercd = tk_ref_tsk(mtkernel_test_tskid, &rtsk);
	if (ercd != E_OK) {
		FAIL("tk_ref_tsk Error. Fail test.");
	}

	// 拡張情報
	LONGS_EQUAL(123, *((UB*)rtsk.exinf));
	// 現在の優先度
	LONGS_EQUAL(9, rtsk.tskpri);
	// ベース優先度
	LONGS_EQUAL(9, rtsk.tskbpri);
#endif
}

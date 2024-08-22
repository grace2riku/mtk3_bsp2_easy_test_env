/*
 * mtkernel_task_manegemnrt.c
 *
 *  Created on: 2024/08/22
 *      Author: k-abe
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

LOCAL ID	mtkernel_task_manegemnrt_test_tskid; // Task ID number

LOCAL void mtkernel_task_manegemnrt_test_task(INT stacd, void *exinf);
const UB mtkernel_task_manegemnrt_test_task_exinf = 1;

T_CTSK mtkernel_task_manegemnrt_test_ctsk = { // Task creation information
	.exinf		= (UB*)&mtkernel_task_manegemnrt_test_task_exinf,
	.tskatr		= TA_HLNG | TA_RNG3,
	.task		= mtkernel_task_manegemnrt_test_task,
	.itskpri	= 9,
	.stksz		= 1024,
};

ID get_mtkernel_task_manegemnrt_test_tskid(void) {
	return mtkernel_task_manegemnrt_test_tskid;
}

LOCAL void mtkernel_task_manegemnrt_test_task(INT stacd, void *exinf)
{
	// 実行状態タスクのタスクID参照
	mtkernel_task_manegemnrt_test_tskid = tk_get_tid();

	while(1) {
		/* Inverts the LED(LD2) on the board. */
		out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))^(1<<1));

		tk_dly_tsk(200);
	}
}

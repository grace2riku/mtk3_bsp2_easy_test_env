/*
 * mtkernel_task.c
 *
 *  Created on: 2024/08/20
 *      Author: k-abe
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

LOCAL void mtkernel_test_task(INT stacd, void *exinf);
const UB mtkernel_test_task_exinf = 123;

T_CTSK mtkernel_test_ctsk = { // Task creation information
	.exinf		= (UB*)&mtkernel_test_task_exinf,
	.tskatr		= TA_HLNG | TA_RNG3,
	.task		= mtkernel_test_task,
	.itskpri	= 9,
	.stksz		= 1024,
};

LOCAL void mtkernel_test_task(INT stacd, void *exinf)
{
	while(1) {
		/* Inverts the LED(LD2) on the board. */
		out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))^(1<<1));

		tk_dly_tsk(200);
	}
}

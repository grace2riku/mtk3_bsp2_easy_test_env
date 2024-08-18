/*
 * led_blink.c
 *
 *  Created on: Aug 18, 2024
 *      Author: k-abe
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

LOCAL void led_blink_task(INT stacd, void *exinf);	// task execution function
LOCAL T_CTSK led_blink_ctsk = {				// Task creation information
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= led_blink_task,
	.tskatr		= TA_HLNG | TA_RNG3,
};

EXPORT T_CTSK* get_led_blink_ctsk_addr()
{
	return &led_blink_ctsk;
}

LOCAL void led_blink_task(INT stacd, void *exinf)
{
	tm_printf((UB*)"led blink task\n");

	while(1) {
		/* Inverts the LED(LD3) on the board. */
//		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^((1<<0)|(1<<14)));
//		out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))^(1<<1));
		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^(1<<14));

		tk_dly_tsk(200);
	}
}


#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#include "main.h"
#include <stdio.h>
#include "ntshell.h"
#include "usrcmd.h"

extern UART_HandleTypeDef huart3;

int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 100);
	return ch;
}

static int serial_read(char* buf, int cnt, void* extobj) {
	int i = 0;
	while (i < cnt) {
		if (HAL_UART_Receive(&huart3, (uint8_t*)&buf[i], 1, 0xFFFF) == HAL_OK) {
			i++;
		}
	}
	return cnt;
}

static int serial_write(const char* text, int cnt, void* extobj) {
	HAL_UART_Transmit(&huart3, (uint8_t*)text, cnt, 100);
	return cnt;
}

static int user_callback(const char* text, void* extobj) {
	usrcmd_execute(text);
	return 0;
}

LOCAL void task_1(INT stacd, void *exinf);	// task execution function
LOCAL ID	tskid_1;			// Task ID number
LOCAL T_CTSK ctsk_1 = {				// Task creation information
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= task_1,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL void task_2(INT stacd, void *exinf);	// task execution function
LOCAL ID	tskid_2;			// Task ID number
LOCAL T_CTSK ctsk_2 = {				// Task creation information
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= task_2,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL void task_1(INT stacd, void *exinf)
{
	ntshell_t nts;

	setbuf(stdout, NULL);
	ntshell_init(&nts, serial_read, serial_write, user_callback, 0);
	ntshell_set_prompt(&nts, ">");

	while(1) {
//		tm_printf((UB*)"task 1\n");

		/* Inverts the LED on the board. */
		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^((1<<0)|(1<<14)));
		out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))^(1<<1));

		ntshell_execute(&nts);

		tk_dly_tsk(500);
	}
}

LOCAL void task_2(INT stacd, void *exinf)
{
	while(1) {
//		tm_printf((UB*)"task 2\n");
		tk_dly_tsk(700);
	}
}

/* usermain関数 */
EXPORT INT usermain(void)
{
	tm_putstring((UB*)"Start User-main program.\n");

	/* Turn off the LED on the board. */
	out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))&~((1<<0)|(1<<14)));
	out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))&~(1<<1));

	/* Create & Start Tasks */
	tskid_1 = tk_cre_tsk(&ctsk_1);
	tk_sta_tsk(tskid_1, 0);

	tskid_2 = tk_cre_tsk(&ctsk_2);
	tk_sta_tsk(tskid_2, 0);

	tk_slp_tsk(TMO_FEVR);

	return 0;
}

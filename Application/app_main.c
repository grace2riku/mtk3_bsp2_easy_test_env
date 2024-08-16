#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#include "main.h"
#include <stdio.h>
#include "ntshell.h"
#include "usrcmd.h"

#if 1
ID dd_com;

int __io_putchar(int ch) {
	SZ asz_com;

	tk_swri_dev(dd_com, 0, (UB*)&ch, 1, &asz_com);

	return (int)asz_com;
}

static int serial_read(char* buf, int cnt, void* extobj) {
	SZ asz_com;
	ER err;

	err = tk_srea_dev(dd_com, 0, (UB*)buf, cnt, &asz_com);
	if (err != E_OK) {
		tm_printf((UB*)"READ Error %d\n", dd_com);
		return 0;
	}

	return (int)asz_com;
}

static int serial_write(const char* text, int cnt, void* extobj) {
	SZ asz_com;

	tk_swri_dev(dd_com, 0, (UB*)text, cnt, &asz_com);

	return (int)asz_com;
}

static int user_callback(const char* text, void* extobj) {
	usrcmd_execute(text);
	return 0;
}
#endif

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
	.stksz		= 8192,	// 1024
	.task		= task_2,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL void task_1(INT stacd, void *exinf)
{
//	ntshell_t nts;

//	setbuf(stdout, NULL);
//	ntshell_init(&nts, serial_read, serial_write, user_callback, 0);
//	ntshell_set_prompt(&nts, ">");

	while(1) {
//		tm_printf((UB*)"task 1\n");

		/* Inverts the LED on the board. */
//		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^((1<<0)|(1<<14)));
//		out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))^(1<<1));
		out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))^(1<<14));

//		ntshell_execute(&nts);
//		ntshell_execute_nb(&nts);

		tk_dly_tsk(200);
//		tk_dly_tsk(100);
	}
}

LOCAL void task_2(INT stacd, void *exinf)
{
	ntshell_t nts;

	setbuf(stdout, NULL);
	ntshell_init(&nts, serial_read, serial_write, user_callback, 0);
	ntshell_set_prompt(&nts, ">");

	dd_com = tk_opn_dev((UB*)"serc", TD_UPDATE);
	if (dd_com < E_OK) {
		tm_printf((UB*)"Open Error %d\n", dd_com);
		tk_ext_tsk();
	}

	while(1) {
		ntshell_execute(&nts);
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

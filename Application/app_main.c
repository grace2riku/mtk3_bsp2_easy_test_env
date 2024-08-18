#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#include "main.h"

/* usermain関数 */
EXPORT INT usermain(void)
{
	LOCAL ID	led_blink_tskid; // Task ID number
	LOCAL ID	ntshell_tskid; // Task ID number

	tm_putstring((UB*)"Start User-main program.\n");

	/* Turn off the LED on the board. */
	out_w(GPIO_ODR(B), (in_w(GPIO_ODR(B)))&~((1<<0)|(1<<14)));
	out_w(GPIO_ODR(E), (in_w(GPIO_ODR(E)))&~(1<<1));

	/* Create & Start Tasks */
	IMPORT T_CTSK* get_led_blink_ctsk_addr();
	led_blink_tskid = tk_cre_tsk(get_led_blink_ctsk_addr());
	tk_sta_tsk(led_blink_tskid, 0);

	IMPORT T_CTSK* get_ntshell_task_ctsk_addr();
	ntshell_tskid = tk_cre_tsk(get_ntshell_task_ctsk_addr());
	tk_sta_tsk(ntshell_tskid, 2);

	tk_slp_tsk(TMO_FEVR);

	return 0;
}

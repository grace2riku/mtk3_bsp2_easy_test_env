/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP
 *
 *    Copyright (C) 2021-2022 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2022/11.
 *
 *----------------------------------------------------------------------
 */

/*
 *	sysdef_depend.h
 *
 *	System dependencies definition (ARMv6-M core depended)
 *	Included also from assembler program.
 */

#ifndef __SYS_SYSDEF_DEPEND_CORE_H__
#define __SYS_SYSDEF_DEPEND_CORE_H__

/*
 * Program status register (PSR)
 */
#define PSR_N		0x80000000	/* Condition flag Negative */
#define PSR_Z		0x40000000	/* Zero */
#define PSR_C		0x20000000	/* Carry */
#define PSR_V		0x10000000	/* Overflow */
#define PSR_Q		0x08000000	/* Saturation */

#define PSR_INT_MSK	0x000000FF	/* Interrupt status mask */

// Exception model.
#define EXP_M(n)	(n)			/* Exception model */
#define EXP_USR		EXP_M(0)	/* User mode, No Exception */
#define EXP_RST		EXP_M(1)	/* Reset */
#define EXP_NMI		EXP_M(2)	/* Non Maskable Interrupt */
#define EXP_HDF		EXP_M(3)	/* Hardware fault */
#define EXP_SVC		EXP_M(11)	/* SVC call */
#define EXP_PSV		EXP_M(14)	/* Software asynchronous System call */
#define EXP_STK		EXP_M(15)	/* System tick */
#define EXP_EXT(n)	(EXP_M(16) + n)	/* External interrupt */

/* ------------------------------------------------------------------------ */

/*
 * NVIC register - System control block
 */
#define SCB_ICSR	0xE000ED04
#define SCB_VTOR	0xE000ED08
#define SCB_AIRCR	0xE000ED0C

#define SCB_SCR		0xE000ED10
#define SCB_CCR		0xE000ED14
#define SCB_SHPR2	0xE000ED1C
#define SCB_SHPR3	0xE000ED20

#define ICSR_PENDSVSET	0x10000000	/* Set PendSV exception. */
#define ICSR_PENDSVCLR	0x08000000	/* Clear PendSV exception. */
#define ICSR_PENDSTSET	0x04000000	/* Set SysCTick exception */
#define ICSR_PENDSTCLR	0x02000000	/* Clear SysCTick exception */

/*
 * The number of the implemented bit width for priority value fields.
 * The LSB of (8-INTPRI_BITWIDTH) bits priority value is ignored, 
 * Bacause each priory bits is INTPRI_BITWIDTH bits.
 */
#define INTPRI_VAL(x)	((x) << (8-INTPRI_BITWIDTH))


/* SHPR: System Handler Priority Register
 *   SHRP1    (Rev)     (Rev)     (Rev)     (Rev)
 *   SHRP2    SVCall    (Rev)     (Rev)     (Rev)
 *   SHPR3    SysTick   PendSV    (Rsv)     (Rev)
 */
#define	SCB_SHPR2_VAL	((INTPRI_VAL(INTPRI_SVC)<<23))
#define SCB_SHPR3_VAL	((INTPRI_VAL(INTPRI_SYSTICK)<<24)|(INTPRI_VAL(INTPRI_PENDSV)<<16))

/*
 * System Timer
 */
#define SYST_CSR	0xE000E010	/* SysTick Control and Status */
#define SYST_RVR	0xE000E014	/* SysTick Reload value */
#define SYST_CVR	0xE000E018	/* SysTick Current value */

/*
 * NVIC (Nested Vectored Interrupt Controller)
 */
#define NVIC_ISER_BASE	0xE000E100
#define NVIC_ISER(x)	(NVIC_ISER_BASE + (((x) / 32) << 2))

#define NVIC_ICER_BASE	0xE000E180
#define NVIC_ICER(x)	(NVIC_ICER_BASE + (((x) / 32) << 2))

#define NVIC_ISPR_BASE	0xE000E200
#define NVIC_ISPR(x)	(NVIC_ISPR_BASE + (((x) / 32) << 2))

#define NVIC_ICPR_BASE	0xE000E280
#define NVIC_ICPR(x)	(NVIC_ICPR_BASE + (((x) / 32) << 2))

/* Interrupt Priority Registers (IPR) are byte-accessible. */
#define NVIC_IPR_BASE	0xE000E400
#define NVIC_IPR(x)	(NVIC_IPR_BASE + (x))

/* ------------------------------------------------------------------------ */
/*
 * Definition of minimum system stack size
 *	Minimum system stack size when setting the system stack size
 *	per task by 'tk_cre_tsk().'
 *  this size must be larger than the size of SStackFrame
 */
#define MIN_SYS_STACK_SIZE	128

/*
 * Default task system stack 
 */

#define DEFAULT_SYS_STKSZ	MIN_SYS_STACK_SIZE

/* ------------------------------------------------------------------------ */

#endif /* __SYS_SYSDEF_DEPEND_CORE_H__ */

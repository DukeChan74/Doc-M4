/**
  ******************************************************************************
  * @file    main.c
  * @brief   Demo switch privilege level using SVC on Cortex-M
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include <stdint.h>

/* ----------------- Low level helpers ----------------- */

static inline uint32_t get_control(void)
{
	uint32_t control;
	__asm volatile ("MRS %0, CONTROL" : "=r"(control));
	return control;
}

static inline void set_control(uint32_t control)
{
	__asm volatile ("MSR CONTROL, %0" : : "r"(control) : "memory");
	__asm volatile ("ISB");
}

/* Drop privilege: Thread mode privileged -> unprivileged */
void switch_to_unprivileged(void)
{
	uint32_t control = get_control();
	control |= (1U << 0);   // set nPRIV = 1
	set_control(control);
}

/* Request privilege restore via SVC */
void switch_to_privileged_by_svc(void)
{
	__asm volatile ("SVC #0");
}

void generate_interrupt()
{
	uint32_t *pSTIR = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*)0xE000E100;
	//enable IRQ3 interrupt
	*pISER0 |= ( 1 << 3);
	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);
}
/* ----------------- Main program ----------------- */

int main(void)
{
	printf("Start\r\n");
	printf("CONTROL before = 0x%08lx\r\n", get_control());

	/* Ban dau dang o privileged Thread mode */
	printf("Switch to unprivileged Thread mode\r\n");
	switch_to_unprivileged();

	switch_to_privileged_by_svc();

	generate_interrupt();

	while (1)
	{
	}
}

/* ----------------- Exception handler ----------------- */

/* Runs in Handler mode, always privileged */
void SVC_Handler(void)
{
	uint32_t control = get_control();

	/* Clear nPRIV bit -> privileged Thread mode after exception return */
	control &= ~(1U << 0);

	set_control(control);

	printf("In SVC_Handler: switched back to privileged\r\n");
}

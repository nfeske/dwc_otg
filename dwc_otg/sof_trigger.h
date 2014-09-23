#ifndef _SOF_TRIGGER_H_
#define _SOF_TRIGGER_H_

#include <dwc_otg_hcd_if.h>


static inline void schedule_sof_interrupt(dwc_otg_hcd_t *hcd, int frame)
{
	enum { NUM_VALID = 1 << 31, NUM_MASK = 0x3fff };

	uint32_t v = DWC_READ_REG32(&hcd->core_if->core_global_regs->guid);

	v &= ~(NUM_MASK | NUM_VALID);

	DWC_WRITE_REG32(&hcd->core_if->core_global_regs->guid,
	                v | (frame & NUM_MASK) | NUM_VALID);
}


static inline uint16_t scheduled_sof_frame(dwc_otg_hcd_t *hcd)
{
	enum { NUM_MASK = 0x3fff };

	return DWC_READ_REG32(&hcd->core_if->core_global_regs->guid) & NUM_MASK;
}


static inline void kick_sof_interrupt(dwc_otg_hcd_t *hcd, int kick)
{
	enum { KICK = 1 << 30 };

	uint32_t v = DWC_READ_REG32(&hcd->core_if->core_global_regs->guid);

	v &= ~KICK;

	DWC_WRITE_REG32(&hcd->core_if->core_global_regs->guid,
	                v | (kick ? KICK : 0));
}

#endif /* _SOF_TRIGGER_H_ */

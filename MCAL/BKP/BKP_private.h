#ifndef BKP_PRIVATE_H
#define BKP_PRIVATE_H

#define BKP_BASE (0x40006C00)

#define BKP_DR_COUNT	11

struct BKP_t
{
	uint32_t bkp_dr[BKP_DR_COUNT];
	uint32_t bkp_rtccr;
	uint32_t bkp_cr;
	uint32_t bkp_csr;
};

#define BKP (*((volatile struct BKP_t*) BKP_BASE))

#endif

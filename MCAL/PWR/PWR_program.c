#include "PWR_private.h"
#include "PWR_interface.h"

void PWR_disable_backup_protection(void)
{
	PWR_CR |= (1<<8);
}

void PWR_enable_backup_protection(void)
{
	PWR_CR &= ~(1<<8);
}


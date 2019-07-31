/*
 * Copyright (c) 2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "traps.h"
#include "sysreg.h"
#include "synchronization.h"

static void enableDebugTraps(void)
{
    u64 mdcr = GET_SYSREG(mdcr_el2);

    // Trap Debug Exceptions, and accesses to debug registers.
    mdcr |= MDCR_EL2_TDE;

    // Implied from TDE
    mdcr |= MDCR_EL2_TDRA | MDCR_EL2_TDOSA | MDCR_EL2_TDA;

    SET_SYSREG(mdcr_el2, mdcr);
}

void enableTraps(void)
{
    u64 hcr = GET_SYSREG(hcr_el2);

    // Trap *writes* to memory control registers
    //hcr |= HCR_TVM;
    // actually don't

    // Trap SMC instructions
    hcr |= HCR_TSC;

    // Reroute physical IRQs to EL2
    hcr |= HCR_IMO;

    // Make sure HVC is enabled
    hcr &= ~HCR_HCD;

    SET_SYSREG(hcr_el2, hcr);

    enableDebugTraps();
}
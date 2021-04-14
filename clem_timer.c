#include "clem_device.h"
#include "clem_mmio_defs.h"


void clem_timer_reset(struct ClemensDeviceTimer* timer) {
    timer->irq_1sec_us = 0;
    timer->irq_qtrsec_us = 0;
    timer->flags = 0;
}

uint32_t clem_timer_sync(
    struct ClemensDeviceTimer* timer,
    uint32_t delta_us,
    uint32_t irq_line
) {
    timer->irq_1sec_us += delta_us;
    timer->irq_qtrsec_us += delta_us;

    while (timer->irq_1sec_us >= CLEM_MEGA2_TIMER_1SEC_US) {
        timer->irq_1sec_us -= CLEM_MEGA2_TIMER_1SEC_US;
        if (timer->flags & CLEM_MMIO_TIMER_1SEC_ENABLED) {
            irq_line |= CLEM_IRQ_TIMER_RTC_1SEC;
        }
    }
    while (timer->irq_qtrsec_us >= CLEM_MEGA2_TIMER_QSEC_US) {
        timer->irq_qtrsec_us -= CLEM_MEGA2_TIMER_QSEC_US;
        if (timer->flags & CLEM_MMIO_TIMER_QSEC_ENABLED) {
            irq_line |= CLEM_IRQ_TIMER_QSEC;
        }
    }

    return irq_line;
}

#ifndef CLEM_DEVICE_H
#define CLEM_DEVICE_H

#include "clem_mmio_types.h"

/**
 * Device Interface
 * These functions emulate the various peripherals (internal and external)
 */

#ifdef __cplusplus
extern "C" {
#endif

void clem_rtc_reset(struct ClemensDeviceRTC *rtc, clem_clocks_duration_t latency);
void clem_rtc_set_clock_time(struct ClemensDeviceRTC *rtc, uint32_t seconds_since_1904);
bool clem_rtc_clear_bram_dirty(struct ClemensDeviceRTC *rtc);
void clem_rtc_set_bram_dirty(struct ClemensDeviceRTC *rtc);

void clem_rtc_command(struct ClemensDeviceRTC *rtc, clem_clocks_time_t ts, unsigned op);

/**
 * @brief Resets the timer counters and interrupt flags
 *
 * @param timer
 */
void clem_timer_reset(struct ClemensDeviceTimer *timer);

/**
 * @brief Issues interrupts for the 1 sec and 0.266667 timer
 *
 * @param timer
 * @param delta_us Microsecond increment since last sync
 * @param irq_line
 * @return uint32_t modified irq_line
 */
void clem_timer_sync(struct ClemensDeviceTimer *timer, uint32_t delta_us);

/**
 * @brief Resets the ADB state
 *
 * @param adb ADB data
 */
void clem_adb_reset(struct ClemensDeviceADB *adb);

/**
 * @brief This method is provided for testing and custom implementations.
 *
 * Normally this is executed from clemens_input to capture input events from
 * the host application.  This is the 'Device' side of the ADB architecture.
 *
 * @param adb ADB device data
 * @param input The input event from the host OS/application
 */
void clem_adb_device_input(struct ClemensDeviceADB *adb, const struct ClemensInputEvent *input);

/**
 * @brief Supplies the emulator with the current state of a toggle key
 *
 * @param adb
 * @param enabled see CLEM_ADB_KEYB_TOGGLE_xxx
 */
void clem_adb_device_key_toggle(struct ClemensDeviceADB *adb, unsigned enabled);

/**
 * @brief
 *
 * @param input
 * @return uint8_t*
 */
uint8_t *clem_adb_ascii_from_a2code(unsigned input);

/**
 * @brief
 *
 * @param gameport
 * @param clocks
 */
void clem_gameport_sync(struct ClemensDeviceGameport *gameport, struct ClemensClock *clocks);

/**
 * @brief Executed frequently enough to emulate the GLU Microcontroller
 *
 * @param adb ADB device data (1 ms worth of cycles?)
 * @param clocks Microsecond increment since last sync
 */
void clem_adb_glu_sync(struct ClemensDeviceADB *adb, uint32_t delta_us);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param adb ADB data
 * @param ioreg The MMIO register accessed
 * @param value The value written to the MMIO register
 */
void clem_adb_write_switch(struct ClemensDeviceADB *adb, uint8_t ioreg, uint8_t value);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param adb ADB data
 * @param ioreg The MMIO register accessed
 * @param flags Access flags used to determine if the read is a no-op
 * @return uint8_t The value read from the MMIO register
 */
uint8_t clem_adb_read_switch(struct ClemensDeviceADB *adb, uint8_t ioreg, uint8_t flags);

/**
 * @brief Mouse and Apple II keyboard inputs
 *
 * @param adb
 * @param ioreg
 * @param flags
 * @return uint8_t
 */
uint8_t clem_adb_read_mega2_switch(struct ClemensDeviceADB *adb, uint8_t ioreg, uint8_t flags);

/**
 * @brief Resets the Sound state
 *
 * @param glu sound data
 */
void clem_sound_reset(struct ClemensDeviceAudio *glu);

/**
 * @brief Invoked by the host to update the internal audio mixer read pointer
 *
 * @param glu
 * @param consumed
 */
void clem_sound_consume_frames(struct ClemensDeviceAudio *glu, unsigned consumed);

/**
 * @brief Executed frequently enough to emulate the GLU Microcontroller
 *
 * @param glu device data (1 ms worth of cycles?)
 * @param clocks Reference clock
 */
void clem_sound_glu_sync(struct ClemensDeviceAudio *glu, struct ClemensClock *clocks);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param glu GLU data
 * @param ioreg The MMIO register accessed
 * @param value The value written to the MMIO register
 */
void clem_sound_write_switch(struct ClemensDeviceAudio *glu, uint8_t ioreg, uint8_t value);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param glu GLU data
 * @param ioreg The MMIO register accessed
 * @param flags Access flags used to determine if the read is a no-op
 * @return uint8_t The value read from the MMIO register
 */
uint8_t clem_sound_read_switch(struct ClemensDeviceAudio *glu, uint8_t ioreg, uint8_t flags);

/**
 * @brief
 *
 * @param drives
 */
void clem_disk_reset_drives(struct ClemensDriveBay *drives);

/**
 * @brief Resets the IWM controller state
 *
 * @param iwm Device data
 */
void clem_iwm_reset(struct ClemensDeviceIWM *iwm);

/**
 * @brief
 *
 * @param iwm
 * @param drive_type
 * @param disk
 */
void clem_iwm_insert_disk(struct ClemensDeviceIWM *iwm, struct ClemensDrive *drive,
                          struct ClemensNibbleDisk *disk);

/**
 * @brief
 *
 * @param iwm
 * @param drive_type
 * @param disk
 */
void clem_iwm_eject_disk(struct ClemensDeviceIWM *iwm, struct ClemensDrive *drive,
                         struct ClemensNibbleDisk *disk);

/**
 * @brief For 3.5" drives, issues the eject command and polls until complete
 *
 * @param iwm
 * @param drive_type
 * @param disk The output disk once eject is complete
 * @return true Disk has ejected
 * @return false Disk is still ejecting
 */
bool clem_iwm_eject_disk_async(struct ClemensDeviceIWM *iwm, struct ClemensDrive *drive,
                               struct ClemensNibbleDisk *disk);

/**
 * @brief Executed frequently enough to emulate a IWM controller
 *
 * Note, due to the emulation rate (down to the microsecond of machine time),
 * most emulation will occur on demand via swtiches.   This function is here
 * to be consistent with our device/controller pattern.
 *
 * @param iwm device data
 * @param drives the IWM managed drives
 * @param clock Current clock referemce time
 */
void clem_iwm_glu_sync(struct ClemensDeviceIWM *iwm, struct ClemensDriveBay *drives,
                       struct ClemensClock *clock);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param iwm IWM data
 * @param drives Drives to be managed by the IWM
 * @param clock The current reference clock*
 * @param ioreg The MMIO register accessed
 * @param value The value written to the MMIO register
 */
void clem_iwm_write_switch(struct ClemensDeviceIWM *iwm, struct ClemensDriveBay *drives,
                           struct ClemensClock *clock, uint8_t ioreg, uint8_t value);

/**
 * @brief Executed from the memory subsystem for MMIO
 *
 * @param iwm IWM data
 * @param drives Drives to be managed by the IWM
 * @param clock The current reference clock
 * @param ioreg The MMIO register accessed
 * @param flags Access flags used to determine if the read is a no-op
 * @return uint8_t The value read from the MMIO register
 */
uint8_t clem_iwm_read_switch(struct ClemensDeviceIWM *iwm, struct ClemensDriveBay *drives,
                             struct ClemensClock *clock, uint8_t ioreg, uint8_t flags);

/**
 * @brief
 *
 * @param mmio
 * @param tspec
 */
void clem_iwm_speed_disk_gate(ClemensMMIO *mmio, struct ClemensTimeSpec *tspec);

/**
 * @brief
 *
 * @param iwm
 */
void clem_iwm_debug_start(struct ClemensDeviceIWM *iwm);

/**
 * @brief
 *
 * @param iwm
 */
void clem_iwm_debug_stop(struct ClemensDeviceIWM *iwm);

/**
 * @brief
 *
 * @param unit
 * @param unit_count
 * @param io_flags
 * @param out_phase
 * @param delta_ns
 * @return true
 * @return false
 */
bool clem_smartport_bus(struct ClemensSmartPortUnit *unit, unsigned unit_count, unsigned *io_flags,
                        unsigned *out_phase, unsigned delta_ns);

/**
 * @brief
 *
 * @param scc
 */
void clem_scc_reset(struct ClemensDeviceSCC *scc);

/**
 * @brief
 *
 * @param scc
 * @param clock
 */
void clem_scc_glu_sync(struct ClemensDeviceSCC *scc, struct ClemensClock *clock);

/**
 * @brief
 *
 * @param scc
 * @param ioreg
 * @param value
 */
void clem_scc_write_switch(struct ClemensDeviceSCC *scc, uint8_t ioreg, uint8_t value);

/**
 * @brief
 *
 * @param scc
 * @param ioreg
 * @param flags
 * @return uint8_t
 */
uint8_t clem_scc_read_switch(struct ClemensDeviceSCC *scc, uint8_t ioreg, uint8_t flags);

#ifdef __cplusplus
}
#endif

#endif

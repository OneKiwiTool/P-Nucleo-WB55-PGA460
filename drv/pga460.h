#ifndef __PGA460_H
#define __PGA460_H

#include <stdint.h>

#define PGA460_DEFAULT_PORT "/dev/ttyS6"
#define MAX_DETECTABLE_DISTANCE          3.0f
#define MIN_DETECTABLE_DISTANCE          0.05f
#define MAX_DETECTABLE_TEMPERATURE     100.0f
#define MIN_DETECTABLE_TEMPERATURE     -20.0f
#define MODE_SET_THRESH                  0.6f
#define MODE_SET_HYST                    0.0f
#define MAX_SAMPLE_DEVIATION             0.15f
#define NUM_SAMPLES_CONSISTENT           5
// #define POLL_RATE_US 50000ULL
#define POLL_RATE_US 0ULL

#define MODE_SHORT_RANGE P1BL
#define MODE_LONG_RANGE  P2BL

#define SYNCBYTE        0x55

//      Define UART commands by name

// Single Address
#define P1BL            0x00    // Burst and Listen (Preset 1)
#define P2BL            0x01    // Burst and Listen (Preset 2)
#define P1LO            0x02    // Listen Only (Preset 1)
#define P2LO            0x03    // Listen Only (Preset 2)
#define TNLM            0x04    // Temperature and Noise-level measurement
#define UMR             0x05    // Ultrasonic Measurement Result
#define TNLR            0x06    // Temperature and noise level result
#define TEDD            0x07    // Transducer echo data dump
#define SD              0x08    // System diagnostics
#define SRR             0x09    // Register read
#define SRW             0x0A    // Register write
#define EEBR            0x0B    // EEPROM bulk read
#define EEBW            0x0C    // EEPROM bulk write
#define TVGBR           0x0D    // Time-varying-gain bulk read
#define TVGBW           0x0E    // Time-varying-gain bulk write
#define THRBR           0x0F    // Threshold bulk read
#define THRBW           0x10    // Threshold bulk write

// Broadcast -- device will execute command irrespecive of UART address field
#define BC_P1BL         0x11    // Burst and listen (Preset 1)
#define BC_P2BL         0x12    // Burst and listen (Preset 2)
#define BC_P1LO         0x13    // Listen only (Preset 1)
#define BC_P2LO         0x14    // Listen only (Preset 2)
#define BC_TNLM         0x15    // Temperature and noise-level measurement
#define BC_SRW          0x16    // Register write
#define BC_EEBW         0x17    // EEPROM bulk write
#define BC_TVGBW        0x18    // Time varying-gain bulk write
#define BC_THRBW        0x19    // Threshold bulk write

// Addresses and Settings
#define EE_CNTRL_ADDR   0x40
#define EE_UNLOCK_ST1   0x68
#define EE_UNLOCK_ST2   0x69

// EEPROM -- non-volatile
#define USER_DATA1      0xAA    //reg addr      0x0
#define USER_DATA2      0x0     //reg addr      0x1
#define USER_DATA3      0x0     //reg addr      0x2
#define USER_DATA4      0x0     //reg addr      0x3
#define USER_DATA5      0x0     //reg addr      0x4
#define USER_DATA6      0x0     //reg addr      0x5
#define USER_DATA7      0x0     //reg addr      0x6
#define USER_DATA8      0x0     //reg addr      0x7
#define USER_DATA9      0x0     //reg addr      0x8
#define USER_DATA10     0x0     //reg addr      0x9
#define USER_DATA11     0x0     //reg addr      0x0A
#define USER_DATA12     0x0     //reg addr      0x0B
#define USER_DATA13     0x0     //reg addr      0x0C
#define USER_DATA14     0x0     //reg addr      0x0D
#define USER_DATA15     0x0     //reg addr      0x0E
#define USER_DATA16     0x0     //reg addr      0x0F
#define USER_DATA17     0x0     //reg addr      0x10
#define USER_DATA18     0x0     //reg addr      0x11
#define USER_DATA19     0x0     //reg addr      0x12
#define USER_DATA20     0x0     //reg addr      0x13
#define TVGAIN0         0x9D    //reg addr      0x14
#define TVGAIN1         0xBD    //reg addr      0x15
#define TVGAIN2         0xEF    //reg addr      0x16
#define TVGAIN3         0x31    //reg addr      0x17
#define TVGAIN4         0x48    //reg addr      0x18
#define TVGAIN5         0x67    //reg addr      0x19
#define TVGAIN6         0xAC    //reg addr      0x1A
#define INIT_GAIN       0x40    //reg addr      0x1B
//#define FREQUENCY   (uint8_t)(5*(_resonant_frequency - 30.0f))       //reg addr      0x1C
#define FREQUENCY   0x1C
#define DEADTIME        0xF0    //reg addr      0x1D
#define PULSE_P1        0x0C    //reg addr      0x1E
#define PULSE_P2        0x1F    //reg addr      0x1F
#define CURR_LIM_P1     0x7F    //reg addr      0x20
#define CURR_LIM_P2     0x7F    //reg addr      0x21
#define REC_LENGTH      0x44    //reg addr      0x22
#define FREQ_DIAG       0x1B    //reg addr      0x23
#define SAT_FDIAG_TH    0x2C    //reg addr      0x24
#define FVOLT_DEC       0x7C    //reg addr      0x25
#define DECPL_TEMP      0xDF    //reg addr      0x26
#define DSP_SCALE       0x0     //reg addr      0x27
#define TEMP_TRIM       0x0     //reg addr      0x28
#define P1_GAIN_CTRL    0x0     //reg addr      0x29
#define P2_GAIN_CTRL    0x8     //reg addr      0x2A
#define EE_CRC          0x29    //reg addr      0x2B

// Register-based -- volatile
#define EE_CNTRL        0x0     //reg addr      0x40

#define BPF_A2_MSB      0x85    //reg addr      0x41
#define BPF_A2_LSB      0xEA    //reg addr      0x42
#define BPF_A3_MSB      0xF9    //reg addr      0x43
#define BPF_A3_LSB      0xA5    //reg addr      0x44
#define BPF_B1_MSB      0x3     //reg addr      0x45
#define BPF_B1_LSB      0x2D    //reg addr      0x46
#define LPF_A2_MSB      0x7E    //reg addr      0x47
#define LPF_A2_LSB      0x67    //reg addr      0x48
#define LPF_B1_MSB      0x0     //reg addr      0x49
#define LPF_B1_LSB      0xCD    //reg addr      0x4A

#define TEST_MUX        0x0     //reg addr      0x4B
#define DEV_STAT0       0x80    //reg addr      0x4C
#define DEV_STAT1       0x0     //reg addr      0x4D

// Register-based -- volatile
#define P1_THR_0        0x54    //reg addr      0x5F
#define P1_THR_1        0x5C    //reg addr      0x60
#define P1_THR_2        0xBD    //reg addr      0x61
#define P1_THR_3        0xE0    //reg addr      0x62
#define P1_THR_4        0x6     //reg addr      0x63
#define P1_THR_5        0xCF    //reg addr      0x64
#define P1_THR_6        0xEE    //reg addr      0x65
#define P1_THR_7        0x8E    //reg addr      0x66
#define P1_THR_8        0x84    //reg addr      0x67
#define P1_THR_9        0xB6    //reg addr      0x68
#define P1_THR_10       0x5A    //reg addr      0x69
#define P1_THR_11       0xFF    //reg addr      0x6A
#define P1_THR_12       0xFF    //reg addr      0x6B
#define P1_THR_13       0xFF    //reg addr      0x6C
#define P1_THR_14       0xFF    //reg addr      0x6D
#define P1_THR_15       0x0     //reg addr      0x6E
#define P2_THR_0        0xBA    //reg addr      0x6F
#define P2_THR_1        0xCF    //reg addr      0x70
#define P2_THR_2        0xFF    //reg addr      0x71
#define P2_THR_3        0xF5    //reg addr      0x72
#define P2_THR_4        0x1A    //reg addr      0x73
#define P2_THR_5        0x5F    //reg addr      0x74
#define P2_THR_6        0xFA    //reg addr      0x75
#define P2_THR_7        0xD6    //reg addr      0x76
#define P2_THR_8        0xB6    //reg addr      0x77
#define P2_THR_9        0x35    //reg addr      0x78
#define P2_THR_10       0xDF    //reg addr      0x79
#define P2_THR_11       0xFF    //reg addr      0x7A
#define P2_THR_12       0xFF    //reg addr      0x7B
#define P2_THR_13       0xFF    //reg addr      0x7C
#define P2_THR_14       0xFF    //reg addr      0x7D
#define P2_THR_15       0x0     //reg addr      0x7E
#define THR_CRC         0x1D    //reg addr      0x7F


void UART_CharReception_Callback(void);

void pga460_write_register(uint8_t reg, uint8_t data);
uint8_t pga460_read_register(uint8_t reg);

void pga460_init_thresholds(uint8_t thr);
void pga460_default(uint8_t xdcr);
void pga460_init_tvg(uint8_t agr, uint8_t tvg);
void pga460_ultrasonic_cmd(uint8_t cmd, uint8_t numObjUpdate);

#endif /* __PGA460_H */

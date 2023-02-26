#include "pga460.h"
#include <stddef.h>
#include "stm32wbxx_ll_lpuart.h"
#include "stm32wbxx_ll_usart.h"
#include "stm32wbxx_ll_utils.h"
#include <stdio.h>

uint8_t BufferRead[16];
__IO uint8_t receivedChars = 0;

void UART_CharReception_Callback(void){
    /* Read Received character. RXNE flag is cleared by reading of RDR register */
    BufferRead[receivedChars++] = LL_LPUART_ReceiveData8(LPUART1);
}

void uart_transmit(uint8_t *buffer, uint8_t size){
    uint8_t index = 0;
    uint8_t *pchar = buffer;

    /* Send characters one per one, until last char to be sent */
    for (index = 0; index < size; index++)
    {
        /* Wait for TXE flag to be raised */
        while (!LL_LPUART_IsActiveFlag_TXE(LPUART1))
        {
        }

        /* Write character in Transmit Data register.
            TXE flag is cleared by writing data in TDR register */
        LL_LPUART_TransmitData8(LPUART1, *pchar++);
    }

    /* Wait for TC flag to be raised for last char */
    while (!LL_LPUART_IsActiveFlag_TC(LPUART1))
    {
    }
}

uint8_t pga460_calc_checksum(uint8_t *data, const uint8_t size){
    uint8_t checksum_input[size];

    for (size_t i = 0; i < size; i++) {
        checksum_input[i] = *data;
        data++;
    }

    uint16_t carry = 0;

    for (uint8_t j = 0; j < size; j++) {
        if ((checksum_input[j] + carry) < carry) {
            carry = carry + checksum_input[j] + 1;
        } else {
            carry = carry + checksum_input[j];
        }

        if (carry > 0xFF) {
            carry = carry - 255;
        }
    }

    carry = (~carry & 0x00FF);
    return carry;
}

void pga460_write_register(uint8_t reg, uint8_t data){
    uint8_t buffer[5] = {SYNCBYTE, SRW, reg, data, 0x00};
    buffer[4] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));
    LL_mDelay(10);
}

uint8_t pga460_read_register(uint8_t reg){
    uint8_t data = 0;
    receivedChars = 0;
    uint8_t buffer[4] = {SYNCBYTE, SRR, reg, 0x00};
    buffer[3] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);

    uart_transmit(buffer, sizeof(buffer));
    LL_mDelay(10);

    data = BufferRead[1];
    return data;
}

uint8_t pga460_threshold_bulk_read(void){
    uint8_t data = 0;
    receivedChars = 0;
    uint8_t buffer[3] = {SYNCBYTE, THRBR, 0x00};
    buffer[2] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);

    uart_transmit(buffer, sizeof(buffer));
    LL_mDelay(10);

    for(uint8_t i = 0; i < 33; i++)
    {
    	printf("%02d. 0x%02x\n", i, BufferRead[i]);
    }
    receivedChars = 0;
    return data;
}

/*------------------------------------------------- initThresholds -----
 |  Function initThresholds
 |
 |  Purpose:  Updates threshold mapping for both presets, and performs bulk threshold write
 |
 |  Parameters:
 |		thr (IN) -- updates all threshold levels to a fixed level based on specific percentage of the maximum level.
 |			All times are mid-code (1.4ms intervals).
 |			Modify existing case statements, or append additional case-statement for custom user threshold configurations.
 |			• 0 = 25% Levels 64 of 255
 |			• 1 = 50% Levels 128 of 255
 |			• 2 = 75% Levels 192 of 255
 |
 |  Returns:  none
 *-------------------------------------------------------------------*/
void pga460_init_thresholds(uint8_t thr){
    uint8_t p1_thr_0 = 0x00;
    uint8_t p1_thr_1 = 0x00;
    uint8_t p1_thr_2 = 0x00;
    uint8_t p1_thr_3 = 0x00;
    uint8_t p1_thr_4 = 0x00;
    uint8_t p1_thr_5 = 0x00;
    uint8_t p1_thr_6 = 0x00;
    uint8_t p1_thr_7 = 0x00;
    uint8_t p1_thr_8 = 0x00;
    uint8_t p1_thr_9 = 0x00;
    uint8_t p1_thr_10 = 0x00;
    uint8_t p1_thr_11 = 0x00;
    uint8_t p1_thr_12 = 0x00;
    uint8_t p1_thr_13 = 0x00;
    uint8_t p1_thr_14 = 0x00;
    uint8_t p1_thr_15 = 0x00;
    uint8_t p2_thr_0 = 0x00;
    uint8_t p2_thr_1 = 0x00;
    uint8_t p2_thr_2 = 0x00;
    uint8_t p2_thr_3 = 0x00;
    uint8_t p2_thr_4 = 0x00;
    uint8_t p2_thr_5 = 0x00;
    uint8_t p2_thr_6 = 0x00;
    uint8_t p2_thr_7 = 0x00;
    uint8_t p2_thr_8 = 0x00;
    uint8_t p2_thr_9 = 0x00;
    uint8_t p2_thr_10 = 0x00;
    uint8_t p2_thr_11 = 0x00;
    uint8_t p2_thr_12 = 0x00;
    uint8_t p2_thr_13 = 0x00;
    uint8_t p2_thr_14 = 0x00;
    uint8_t p2_thr_15 = 0x00;

    switch (thr){
        case 0: //25% Levels 64 of 255
            p1_thr_0 = 0x88;
            p1_thr_1 = 0x88;
            p1_thr_2 = 0x88;
            p1_thr_3 = 0x88;
            p1_thr_4 = 0x88;
            p1_thr_5 = 0x88;
            p1_thr_6 = 0x42;
            p1_thr_7 = 0x10;
            p1_thr_8 = 0x84;
            p1_thr_9 = 0x21;
            p1_thr_10 = 0x08;
            p1_thr_11 = 0x40;
            p1_thr_12 = 0x40;
            p1_thr_13 = 0x40;
            p1_thr_14 = 0x40;
            p1_thr_15 = 0x00;
            p2_thr_0 = 0x88;
            p2_thr_1 = 0x88;
            p2_thr_2 = 0x88;
            p2_thr_3 = 0x88;
            p2_thr_4 = 0x88;
            p2_thr_5 = 0x88;
            p2_thr_6 = 0x42;
            p2_thr_7 = 0x10;
            p2_thr_8 = 0x84;
            p2_thr_9 = 0x21;
            p2_thr_10 = 0x08;
            p2_thr_11 = 0x40;
            p2_thr_12 = 0x40;
            p2_thr_13 = 0x40;
            p2_thr_14 = 0x40;
            p2_thr_15 = 0x00;
            break;

        case 1: //50% Level (midcode) 128 of 255
            p1_thr_0 = 0x88;
            p1_thr_1 = 0x88;
            p1_thr_2 = 0x88;
            p1_thr_3 = 0x88;
            p1_thr_4 = 0x88;
            p1_thr_5 = 0x88;
            p1_thr_6 = 0x84;
            p1_thr_7 = 0x21;
            p1_thr_8 = 0x08;
            p1_thr_9 = 0x42;
            p1_thr_10 = 0x10;
            p1_thr_11 = 0x80;
            p1_thr_12 = 0x80;
            p1_thr_13 = 0x80;
            p1_thr_14 = 0x80;
            p1_thr_15 = 0x00;
            p2_thr_0 = 0x88;
            p2_thr_1 = 0x88;
            p2_thr_2 = 0x88;
            p2_thr_3 = 0x88;
            p2_thr_4 = 0x88;
            p2_thr_5 = 0x88;
            p2_thr_6 = 0x84;
            p2_thr_7 = 0x21;
            p2_thr_8 = 0x08;
            p2_thr_9 = 0x42;
            p2_thr_10 = 0x10;
            p2_thr_11 = 0x80;
            p2_thr_12 = 0x80;
            p2_thr_13 = 0x80;
            p2_thr_14 = 0x80;
            p2_thr_15 = 0x00;
            break;

        case 2: //75% Levels 192 of 255
            p1_thr_0 = 0x88;
            p1_thr_1 = 0x88;
            p1_thr_2 = 0x88;
            p1_thr_3 = 0x88;
            p1_thr_4 = 0x88;
            p1_thr_5 = 0x88;
            p1_thr_6 = 0xC6;
            p1_thr_7 = 0x31;
            p1_thr_8 = 0x8C;
            p1_thr_9 = 0x63;
            p1_thr_10 = 0x18;
            p1_thr_11 = 0xC0;
            p1_thr_12 = 0xC0;
            p1_thr_13 = 0xC0;
            p1_thr_14 = 0xC0;
            p1_thr_15 = 0x00;
            p2_thr_0 = 0x88;
            p2_thr_1 = 0x88;
            p2_thr_2 = 0x88;
            p2_thr_3 = 0x88;
            p2_thr_4 = 0x88;
            p2_thr_5 = 0x88;
            p2_thr_6 = 0xC6;
            p2_thr_7 = 0x31;
            p2_thr_8 = 0x8C;
            p2_thr_9 = 0x63;
            p2_thr_10 = 0x18;
            p2_thr_11 = 0xC0;
            p2_thr_12 = 0xC0;
            p2_thr_13 = 0xC0;
            p2_thr_14 = 0xC0;
            p2_thr_15 = 0x00;
            break;

        case 3: //Custom00
            p1_thr_0 = 0x41;
            p1_thr_1 = 0x44;
            p1_thr_2 = 0x10;
            p1_thr_3 = 0x06;
            p1_thr_4 = 0x69;
            p1_thr_5 = 0x99;
            p1_thr_6 = 0xDD;
            p1_thr_7 = 0x4C;
            p1_thr_8 = 0x31;
            p1_thr_9 = 0x08;
            p1_thr_10 = 0x42;
            p1_thr_11 = 0x18;
            p1_thr_12 = 0x20;
            p1_thr_13 = 0x24;
            p1_thr_14 = 0x2A;
            p1_thr_15 = 0x00;
            p2_thr_0 = 0x41;
            p2_thr_1 = 0x44;
            p2_thr_2 = 0x10;
            p2_thr_3 = 0x06;
            p2_thr_4 = 0x09;
            p2_thr_5 = 0x99;
            p2_thr_6 = 0xDD;
            p2_thr_7 = 0x4C;
            p2_thr_8 = 0x31;
            p2_thr_9 = 0x08;
            p2_thr_10 = 0x42;
            p2_thr_11 = 0x24;
            p2_thr_12 = 0x30;
            p2_thr_13 = 0x36;
            p2_thr_14 = 0x3C;
            p2_thr_15 = 0x00;
            break;

        default:
            break;
    }

    uint8_t buffer[35] = {SYNCBYTE, THRBW, 
        p1_thr_0, p1_thr_1, p1_thr_2, p1_thr_3, p1_thr_4, p1_thr_5, p1_thr_6, p1_thr_7,
        p1_thr_8, p1_thr_9, p1_thr_10, p1_thr_11, p1_thr_12, p1_thr_13, p1_thr_14, p1_thr_15,
        p2_thr_0, p2_thr_1, p2_thr_2, p2_thr_3, p2_thr_4, p2_thr_5, p2_thr_6, p2_thr_7, 
        p2_thr_8, p2_thr_9, p2_thr_10, p2_thr_11, p2_thr_12, p2_thr_13, p2_thr_14, p2_thr_15,
        0x00
    };
    buffer[34] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));

    LL_mDelay(10);
}

/*------------------------------------------------- defaultPGA460 -----
 |  Function defaultPGA460
 |
 |  Purpose:  Updates user EEPROM values, and performs bulk EEPROM write.
 |
 |  Parameters:
 |		xdcr (IN) -- updates user EEPROM based on predefined listing for a specific transducer.
 |			Modify existing case statements, or append additional case-statement for custom user EEPROM configurations.
 |			• 0 = Murata MA58MF14-7N
 |			• 1 = Murata MA40H1S-R
 |			• 2 = PUI Audio UTR-1440K-TT-R
 |
 |  Returns:  none
 *-------------------------------------------------------------------*/
void pga460_default(uint8_t xdcr){
    uint8_t tUSER_DATA1 = 0x00;
    uint8_t tUSER_DATA2 = 0x00;
    uint8_t tUSER_DATA3 = 0x00;
    uint8_t tUSER_DATA4 = 0x00;
    uint8_t tUSER_DATA5 = 0x00;
    uint8_t tUSER_DATA6 = 0x00;
    uint8_t tUSER_DATA7 = 0x00;
    uint8_t tUSER_DATA8 = 0x00;
    uint8_t tUSER_DATA9 = 0x00;
    uint8_t tUSER_DATA10 = 0x00;
    uint8_t tUSER_DATA11 = 0x00;
    uint8_t tUSER_DATA12 = 0x00;
    uint8_t tUSER_DATA13 = 0x00;
    uint8_t tUSER_DATA14 = 0x00;
    uint8_t tUSER_DATA15 = 0x00;
    uint8_t tUSER_DATA16 = 0x00;
    uint8_t tUSER_DATA17 = 0x00;
    uint8_t tUSER_DATA18 = 0x00;
    uint8_t tUSER_DATA19 = 0x00;
    uint8_t tUSER_DATA20 = 0x00;
    uint8_t tTVGAIN0 = 0x00;
    uint8_t tTVGAIN1 = 0x00;
    uint8_t tTVGAIN2 = 0x00;
    uint8_t tTVGAIN3 = 0x00;
    uint8_t tTVGAIN4 = 0x00;
    uint8_t tTVGAIN5 = 0x00;
    uint8_t tTVGAIN6 = 0x00;
    uint8_t tINIT_GAIN = 0x00;
    uint8_t tFREQUENCY = 0x00;
    uint8_t tDEADTIME = 0x00;
    uint8_t tPULSE_P1 = 0x00;
    uint8_t tPULSE_P2 = 0x00;
    uint8_t tCURR_LIM_P1 = 0x00;
    uint8_t tCURR_LIM_P2 = 0x00;
    uint8_t tREC_LENGTH = 0x00;
    uint8_t tFREQ_DIAG = 0x00;
    uint8_t tSAT_FDIAG_TH = 0x00;
    uint8_t tFVOLT_DEC = 0x00;
    uint8_t tDECPL_TEMP = 0x00;
    uint8_t tDSP_SCALE = 0x00;
    uint8_t tTEMP_TRIM = 0x00;
    uint8_t tP1_GAIN_CTRL = 0x00;
    uint8_t tP2_GAIN_CTRL = 0x00;

    switch (xdcr)
    {
        case 0: // Murata MA58MF14-7N
            tUSER_DATA1 = 0x00;
            tUSER_DATA2 = 0x00;
            tUSER_DATA3 = 0x00;
            tUSER_DATA4 = 0x00;
            tUSER_DATA5 = 0x00;
            tUSER_DATA6 = 0x00;
            tUSER_DATA7 = 0x00;
            tUSER_DATA8 = 0x00;
            tUSER_DATA9 = 0x00;
            tUSER_DATA10 = 0x00;
            tUSER_DATA11 = 0x00;
            tUSER_DATA12 = 0x00;
            tUSER_DATA13 = 0x00;
            tUSER_DATA14 = 0x00;
            tUSER_DATA15 = 0x00;
            tUSER_DATA16 = 0x00;
            tUSER_DATA17 = 0x00;
            tUSER_DATA18 = 0x00;
            tUSER_DATA19 = 0x00;
            tUSER_DATA20 = 0x00;
            tTVGAIN0 = 0xAA;
            tTVGAIN1 = 0xAA;
            tTVGAIN2 = 0xAA;
            tTVGAIN3 = 0x82;
            tTVGAIN4 = 0x08;
            tTVGAIN5 = 0x20;
            tTVGAIN6 = 0x80;
            tINIT_GAIN = 0x60;
            tFREQUENCY  = 0x8F;
            tDEADTIME = 0xA0;
            tPULSE_P1 = 0x04;
            tPULSE_P2 = 0x10;
            tCURR_LIM_P1 = 0x55;
            tCURR_LIM_P2 = 0x55;
            tREC_LENGTH = 0x19;
            tFREQ_DIAG = 0x33;
            tSAT_FDIAG_TH = 0xEE;
            tFVOLT_DEC = 0x7C;
            tDECPL_TEMP = 0x4F;
            tDSP_SCALE = 0x00;
            tTEMP_TRIM = 0x00;
            tP1_GAIN_CTRL = 0x09;
            tP2_GAIN_CTRL = 0x09;
            break;
        case 1: // Murata MA40H1SR
            tUSER_DATA1 = 0x00;
            tUSER_DATA2 = 0x00;
            tUSER_DATA3 = 0x00;
            tUSER_DATA4 = 0x00;
            tUSER_DATA5 = 0x00;
            tUSER_DATA6 = 0x00;
            tUSER_DATA7 = 0x00;
            tUSER_DATA8 = 0x00;
            tUSER_DATA9 = 0x00;
            tUSER_DATA10 = 0x00;
            tUSER_DATA11 = 0x00;
            tUSER_DATA12 = 0x00;
            tUSER_DATA13 = 0x00;
            tUSER_DATA14 = 0x00;
            tUSER_DATA15 = 0x00;
            tUSER_DATA16 = 0x00;
            tUSER_DATA17 = 0x00;
            tUSER_DATA18 = 0x00;
            tUSER_DATA19 = 0x00;
            tUSER_DATA20 = 0x00;
            tTVGAIN0 = 0xAA;
            tTVGAIN1 = 0xAA;
            tTVGAIN2 = 0xAA;
            tTVGAIN3 = 0x51;
            tTVGAIN4 = 0x45;
            tTVGAIN5 = 0x14;
            tTVGAIN6 = 0x50;
            tINIT_GAIN = 0x54;
            tFREQUENCY = 0x32;
            tDEADTIME = 0xA0;
            tPULSE_P1 = 0x08;
            tPULSE_P2 = 0x10;
            tCURR_LIM_P1 = 0x40;
            tCURR_LIM_P2 = 0x40;
            tREC_LENGTH = 0x19;
            tFREQ_DIAG = 0x33;
            tSAT_FDIAG_TH = 0xFE;
            tFVOLT_DEC = 0x7C;
            tDECPL_TEMP = 0x4F;
            tDSP_SCALE = 0x00;
            tTEMP_TRIM = 0x00;
            tP1_GAIN_CTRL = 0x09;
            tP2_GAIN_CTRL = 0x09;
            break;

        case 5: // Murata MA4S4S/R
            tUSER_DATA1 = 0x00;
            tUSER_DATA2 = 0x00;
            tUSER_DATA3 = 0x00;
            tUSER_DATA4 = 0x00;
            tUSER_DATA5 = 0x00;
            tUSER_DATA6 = 0x00;
            tUSER_DATA7 = 0x00;
            tUSER_DATA8 = 0x00;
            tUSER_DATA9 = 0x00;
            tUSER_DATA10 = 0x00;
            tUSER_DATA11 = 0x00;
            tUSER_DATA12 = 0x00;
            tUSER_DATA13 = 0x00;
            tUSER_DATA14 = 0x00;
            tUSER_DATA15 = 0x00;
            tUSER_DATA16 = 0x00;
            tUSER_DATA17 = 0x00;
            tUSER_DATA18 = 0x00;
            tUSER_DATA19 = 0x00;
            tUSER_DATA20 = 0x00;
            tTVGAIN0 = 0xAA;
            tTVGAIN1 = 0xAA;
            tTVGAIN2 = 0xAA;
            tTVGAIN3 = 0x51;
            tTVGAIN4 = 0x45;
            tTVGAIN5 = 0x14;
            tTVGAIN6 = 0x50;
            tINIT_GAIN = 0x54;
            tFREQUENCY  = 0x32;
            tDEADTIME = 0xA0;
            tPULSE_P1 = 0x02;
            tPULSE_P2 = 0x10;
            tCURR_LIM_P1 = 0x40;
            tCURR_LIM_P2 = 0x40;
            tREC_LENGTH = 0x19;
            tFREQ_DIAG = 0x33;
            tSAT_FDIAG_TH = 0xFE;
            tFVOLT_DEC = 0x7C;
            tDECPL_TEMP = 0x4F;
            tDSP_SCALE = 0x00;
            tTEMP_TRIM = 0x00;
            tP1_GAIN_CTRL = 0x00;
            tP2_GAIN_CTRL = 0x00;
            break;

        case 2: // PUI Audio UTR-1440K-TT-R
            tUSER_DATA1 = 0x00;
            tUSER_DATA2 = 0x00;
            tUSER_DATA3 = 0x00;
            tUSER_DATA4 = 0x00;
            tUSER_DATA5 = 0x00;
            tUSER_DATA6 = 0x00;
            tUSER_DATA7 = 0x00;
            tUSER_DATA8 = 0x00;
            tUSER_DATA9 = 0x00;
            tUSER_DATA10 = 0x00;
            tUSER_DATA11 = 0x00;
            tUSER_DATA12 = 0x00;
            tUSER_DATA13 = 0x00;
            tUSER_DATA14 = 0x00;
            tUSER_DATA15 = 0x00;
            tUSER_DATA16 = 0x00;
            tUSER_DATA17 = 0x00;
            tUSER_DATA18 = 0x00;
            tUSER_DATA19 = 0x00;
            tUSER_DATA20 = 0x00;
            tTVGAIN0 = 0x9D;
            tTVGAIN1 = 0xEE;
            tTVGAIN2 = 0xEF;
            tTVGAIN3 = 0x2D;
            tTVGAIN4 = 0xB9;
            tTVGAIN5 = 0xEF;
            tTVGAIN6 = 0xDC;
            tINIT_GAIN = 0x03;
            tFREQUENCY  = 0x32;
            tDEADTIME = 0x80;
            tPULSE_P1 = 0x08;
            tPULSE_P2 = 0x12;
            tCURR_LIM_P1 = 0x72;
            tCURR_LIM_P2 = 0x32;
            tREC_LENGTH = 0x09;
            tFREQ_DIAG = 0x33;
            tSAT_FDIAG_TH = 0xEE;
            tFVOLT_DEC = 0x7C;
            tDECPL_TEMP = 0x8F;
            tDSP_SCALE = 0x00;
            tTEMP_TRIM = 0x00;
            tP1_GAIN_CTRL = 0x09;
            tP2_GAIN_CTRL = 0x29;
            break;

        case 3: // User Custom XDCR
            tUSER_DATA1 = 0x00;
            tUSER_DATA2 = 0x00;
            tUSER_DATA3 = 0x00;
            tUSER_DATA4 = 0x00;
            tUSER_DATA5 = 0x00;
            tUSER_DATA6 = 0x00;
            tUSER_DATA7 = 0x00;
            tUSER_DATA8 = 0x00;
            tUSER_DATA9 = 0x00;
            tUSER_DATA10 = 0x00;
            tUSER_DATA11 = 0x00;
            tUSER_DATA12 = 0x00;
            tUSER_DATA13 = 0x00;
            tUSER_DATA14 = 0x00;
            tUSER_DATA15 = 0x00;
            tUSER_DATA16 = 0x00;
            tUSER_DATA17 = 0x00;
            tUSER_DATA18 = 0x00;
            tUSER_DATA19 = 0x00;
            tUSER_DATA20 = 0x00;
            tTVGAIN0 = 0xAA;
            tTVGAIN1 = 0xAA;
            tTVGAIN2 = 0xAA;
            tTVGAIN3 = 0x82;
            tTVGAIN4 = 0x08;
            tTVGAIN5 = 0x20;
            tTVGAIN6 = 0x80;
            tINIT_GAIN = 0x60;
            tFREQUENCY  = 0x8F;
            tDEADTIME = 0xA0;
            tPULSE_P1 = 0x04;
            tPULSE_P2 = 0x10;
            tCURR_LIM_P1 = 0x55;
            tCURR_LIM_P2 = 0x55;
            tREC_LENGTH = 0x19;
            tFREQ_DIAG = 0x33;
            tSAT_FDIAG_TH = 0xFE;
            tFVOLT_DEC = 0x7C;
            tDECPL_TEMP = 0x4F;
            tDSP_SCALE = 0x00;
            tTEMP_TRIM = 0x00;
            tP1_GAIN_CTRL = 0x09;
            tP2_GAIN_CTRL = 0x09;
            break;
        default:
            break;
    }

    uint8_t buffer[46] = {SYNCBYTE, EEBW, 
        tUSER_DATA1, tUSER_DATA2, tUSER_DATA3, tUSER_DATA4, tUSER_DATA5,
        tUSER_DATA6, tUSER_DATA7, tUSER_DATA8, tUSER_DATA9, tUSER_DATA10, 
        tUSER_DATA11, tUSER_DATA12, tUSER_DATA13, tUSER_DATA14, tUSER_DATA15, 
        tUSER_DATA16, tUSER_DATA17, tUSER_DATA18, tUSER_DATA19, tUSER_DATA20,
        tTVGAIN0, tTVGAIN1, tTVGAIN2, tTVGAIN3, tTVGAIN4, tTVGAIN5, 
        tTVGAIN6, tINIT_GAIN, tFREQUENCY, tDEADTIME, tPULSE_P1, 
        tPULSE_P2, tCURR_LIM_P1, tCURR_LIM_P2, tREC_LENGTH, tFREQ_DIAG,
        tSAT_FDIAG_TH, tFVOLT_DEC, tDECPL_TEMP, tDSP_SCALE, tTEMP_TRIM,
        tP1_GAIN_CTRL, tP2_GAIN_CTRL, 0x00
    };
    
    buffer[45] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));
    LL_mDelay(50);

}

/*------------------------------------------------- initTVG -----
 |  Function initTVG
 |
 |  Purpose:  Updates time varying gain (TVG) range and mapping, and performs bulk TVG write
 |
 |  Parameters:
 |		agr (IN) -- updates the analog gain range for the TVG.
 |			• 0 = 32-64dB
 |			• 1 = 46-78dB
 |			• 2 = 52-84dB
 |			• 3 = 58-90dB
 |		tvg (IN) -- updates all TVG levels to a fixed level based on specific percentage of the maximum level.
 |			All times are mid-code (2.4ms intervals).
 |			Modify existing case statements, or append additional case-statement for custom user TVG configurations
 |			• 0 = 25% Levels of range
 |			• 1 = 50% Levels of range
 |			• 2 = 75% Levels of range
 |
 |  Returns:  none
 *-------------------------------------------------------------------*/
void pga460_init_tvg(uint8_t agr, uint8_t tvg)
{
    uint8_t gain_range = 0x4F;
    uint8_t tvgain0 = 0x00;
    uint8_t tvgain1 = 0x00;
    uint8_t tvgain2 = 0x00;
    uint8_t tvgain3 = 0x00;
    uint8_t tvgain4 = 0x00;
    uint8_t tvgain5 = 0x00;
    uint8_t tvgain6 = 0x00;

    // set AFE gain range
    switch (agr)
    {
        case 3: //58-90dB
            gain_range =  0x0F;
            break;
        case 2: //52-84dB
            gain_range = 0x4F;
            break;
        case 1: //46-78dB
            gain_range = 0x8F;
            break;
        case 0: //32-64dB
            gain_range = 0xCF;
            break;
        default:
            break;
    }

    uint8_t reg = 0x26;
    uint8_t data = gain_range;
    uint8_t buffer[5] = {SYNCBYTE, SRW, reg, data, 0x00};
    buffer[4] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));

    //Set fixed AFE gain value
    switch (tvg)
    {
        case 0: //25% Level
            tvgain0 = 0x88;
            tvgain1 = 0x88;
            tvgain2 = 0x88;
            tvgain3 = 0x41;
            tvgain4 = 0x04;
            tvgain5 = 0x10;
            tvgain6 = 0x40;
            break;

        case 1: //50% Levels
            tvgain0 = 0x88;
            tvgain1 = 0x88;
            tvgain2 = 0x88;
            tvgain3 = 0x82;
            tvgain4 = 0x08;
            tvgain5 = 0x20;
            tvgain6 = 0x80;
            break;

        case 2: //75% Levels
            tvgain0 = 0x88;
            tvgain1 = 0x88;
            tvgain2 = 0x88;
            tvgain3 = 0xC3;
            tvgain4 = 0x0C;
            tvgain5 = 0x30;
            tvgain6 = 0xC0;
            break;

        default:
            break;
    }

    uint8_t tvgain[10] = {SYNCBYTE, TVGBW, tvgain0, tvgain1, tvgain2, 
        tvgain3, tvgain4, tvgain5, tvgain6, 0x00
    };
    tvgain[9] = pga460_calc_checksum(&tvgain[1], sizeof(tvgain) - 2);
    uart_transmit(tvgain, sizeof(tvgain));
}

/*------------------------------------------------- ultrasonicCmd -----
 |  Function ultrasonicCmd
 |
 |  Purpose:  Issues a burst-and-listen or listen-only command based on the number of objects to be detected.
 |
 |  Parameters:
 |		cmd (IN) -- determines which preset command is run
 |			• 0 = Preset 1 Burst + Listen command
 |			• 1 = Preset 2 Burst + Listen command
 |			• 2 = Preset 1 Listen Only command
 |			• 3 = Preset 2 Listen Only command
 |			• 17 = Preset 1 Burst + Listen broadcast command
 |			• 18 = Preset 2 Burst + Listen broadcast command
 |			• 19 = Preset 1 Listen Only broadcast command
 |			• 20 = Preset 2 Listen Only broadcast command
 |		numObjUpdate (IN) -- PGA460 can capture time-of-flight, width, and amplitude for 1 to 8 objects. 
 |			TCI is limited to time-of-flight measurement data only.
 |
 |  Returns:  none
 *-------------------------------------------------------------------*/
void pga460_ultrasonic_cmd(uint8_t cmd, uint8_t numObjUpdate)
{	
    //numObj = numObjUpdate; // number of objects to detect
    uint8_t buffer[4] = {SYNCBYTE, 0x00, numObjUpdate, 0x00}; // prepare buffer with 0x00 placeholders

    //memset(objTime, 0xFF, 8); // reset and idle-high TCI object buffer

    switch (cmd)
    {
        // SINGLE ADDRESS		
        case 0: // Send Preset 1 Burst + Listen command
        {			
            buffer[1] = P1BL;
            break;
        }
        case 1: // Send Preset 2 Burst + Listen command
        {			
            buffer[1] = P2BL;
            break;
        }	
        case 2: // Send Preset 1 Listen Only command
        {			
            buffer[1] = P1LO;
            break;
        }
        case 3: // Send Preset 2 Listen Only command
        {			
            buffer[1] = P2LO;
            break;
        }	

        // BROADCAST
        case 17: // Send Preset 1 Burst + Listen Broadcast command
        {			
            buffer[1] = BC_P1BL;
            break;
        }
        case 18: // Send Preset 2 Burst + Listen Broadcast command
        {			
            buffer[1] = BC_P2BL;
            break;
        }	
        case 19: // Send Preset 1 Listen Only Broadcast command
        {			
            buffer[1] = BC_P1LO;
            break;
        }
        case 20: // Send Preset 2 Listen Only Broadcast command
        {			
            buffer[1] = BC_P2LO;
            break;
        }
        default:
            return;	
    }

    buffer[3] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));

    LL_mDelay(70); // maximum record length is 65ms, so delay with margin
}

void pga460_unlock_eeprom(){
    // Two step EEPROM unlock -- send unlock code w/ prog bit set to 0.
    // This might actually be wrapped into command 11 (ee bulk write) but I am not sure.
    uint8_t buffer[5] = {SYNCBYTE, SRW, EE_CNTRL_ADDR, EE_UNLOCK_ST1, 0x00};
    buffer[4] = pga460_calc_checksum(&buffer[1], sizeof(buffer) - 2);
    uart_transmit(buffer, sizeof(buffer));
}

void pga460_print_device_status()
{
    uint8_t status_flags1 = pga460_read_register(0x4C);
    uint8_t status_flags2 = pga460_read_register(0x4D);

    if ((status_flags1 & 0x0F) || status_flags2) {
        if (status_flags1 & 0x0F & 1) {
            printf("Trim EEPROM space data CRC error\n");
        }

        if (status_flags1 & 0x0F & 1 << 1) {
            printf("User EEPROM space data CRC error\n");
        }

        if (status_flags1 & 0x0F & 1 << 2) {
            printf("Threshold map configuration register data CRC error\n");
        }

        if (status_flags1 & 0x0F & 1 << 3) {
            printf("Wakeup Error\n");
        }

        if (status_flags2 & 1) {
            printf("VPWR pin under voltage\n");
        }

        if (status_flags2 & 1 << 1) {
            printf("VPWR pin over voltage\n");
        }

        if (status_flags2 & 1 << 2) {
            printf("AVDD pin under voltage\n");
        }

        if (status_flags2 & 1 << 3) {
            printf("AVDD pin over voltage\n");
        }

        if (status_flags2 & 1 << 4) {
            printf("IOREG pin under voltage\n");
        }

        if (status_flags2 & 1 << 5) {
            printf("IOREG pin over voltage\n");
        }

        if (status_flags2 & 1 << 6) {
            printf("Thermal shutdown has occured\n");
        }
    }
}

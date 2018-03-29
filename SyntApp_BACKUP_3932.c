<<<<<<< HEAD
/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "SyntApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

typedef struct
{
    double      fVco;
    double      fPFD;
    int32_t     INT;
    int32_t     Mod1;
    double      Fraq;
    int32_t     Fraq1;
    double      remFraq1;
    int32_t     Mod2;
    int32_t     Fraq2;
}SYNTH_CALC_PARAMS;

SYNTH_CALC_PARAMS synthCalcParams;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{

}

void PLLUartInitialize(char* data)
{
    
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateSynthFreq(MODULE_TYPE cType, char* data)
{
    double insertFraqData = GetDoubleFromUartData(data, data[0]);
    uint32_t regSynthArray[4];
    ZeroArray(regSynthArray, sizeof(regSynthArray));
    
    double t = getFractionPartOfDivide(5, 3);
        
    CalcSynthRegParams(regSynthArray, insertFraqData);
    regSynthArray[4] = SYNTH_REG_04;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Calc syntesizers registers params">

bool CalcSynthRegParams(int32_t* regArray, int32_t inputFreq)
{
    int32_t tempVal1 = 0x0, tempVal2 = 0x0, tempVal3 = 0x0;
    synthCalcParams.fVco = inputFreq / 2.0;
    synthCalcParams.fPFD = SYNTH_F_PFD;
    synthCalcParams.INT = (int)(synthCalcParams.fVco / synthCalcParams.fPFD);
    synthCalcParams.Mod1 = SYNTH_MOD1;
    synthCalcParams.Fraq = getFractionPartOfDivide(synthCalcParams.fVco, synthCalcParams.fPFD);
    synthCalcParams.Fraq1 = synthCalcParams.Fraq * SYNTH_MOD1;
    synthCalcParams.remFraq1 = 0; //getFractionPartOfMultiple(synthCalcParams.Fraq, SYNTH_MOD1);
    synthCalcParams.Mod2 = SYNTH_MOD2;
    synthCalcParams.Fraq2 = (int)(synthCalcParams.remFraq1 * synthCalcParams.Mod2);

    regArray[0] =  (int)(synthCalcParams.INT * pow(2,4)) | SYNTH_AUTOCAL | 0x0;
    regArray[1] = synthCalcParams.Fraq1 | 0x1;
    regArray[2] = (int)(synthCalcParams.Fraq2 * pow(2,18)) | SYNTH_MOD2 | 0x2;
    return true;
}

// </editor-fold>


=======
/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "SyntApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">


// </editor-fold>


// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
    
    // Set TX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_TX, HIGH);

    
    // Set TX Synthesizer:
    for(int idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_TX, TEST_PLL_REGISTERS[idx], 3);
    }
    
//    // We use fPdf >= 75 MHz so send REG 4-0 again (according data sheet)
//    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[4], 3);
//    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[2], 3);
//    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[1], 3);
//    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[0], 3);
    
    // Set RX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_RX, HIGH);
    
    // Set RX Synthesizer:
    for(int idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[idx], 3);
    }
    
    // We use fPdf >= 75 MHz so send REG 4-0 again (according data sheet)
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[4], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[2], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[1], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[0], 3);
}

void PLLUartInitialize(char* data)
{
    
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateTxFreq(char* data)
{
//    uint32_t regData = GetIntFromUartData(data);
//    SWSPI_send_word(SYNTH_TX, regData, 3);
//    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
    
    txFreq = GetIntFromUartData(data);
    
    SWSPI_send_word(SYNTH_TX, 0x00C026BA, 3);
    SWSPI_send_word(SYNTH_TX, 0x3501E076, 3);
    SWSPI_send_word(SYNTH_TX, 0x32008B84, 3);
    SWSPI_send_word(SYNTH_TX, 0x00080032, 3);
    SWSPI_send_word(SYNTH_TX, 0x01AAAAA1, 3);
    SWSPI_send_word(SYNTH_TX, 0x00200410, 3);
    SWSPI_send_word(SYNTH_TX, 0x32008B84, 3);
    SWSPI_send_word(SYNTH_TX, 0x00200410, 3);
    
    //SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
}

void UpdateRxFreq(char* data)
{
    rxFreq = GetIntFromUartData(data);
     
    SWSPI_send_word(SYNTH_RX, rxFreq, 3);
    //SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_SET); 
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Reset syntesizers">

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers ISR">

void SYNTH_ISR(void)
{
    
}
// </editor-fold>

>>>>>>> Update1533

/*************************************************************
 * @file      : Init.c
 * @brief     : Peripheral Init Functions
 * @version   : 1.2.4
 * @date      : 05/26/2023  09:59 
 * @author    : Created by CoSmart 1.2.4
**************************************************************/
#include "DrvGPIO.h"
#include "DrvADC.h"

/*************************************************************
 * GPIOE Initialization
**************************************************************/
void GPIOE_Init()
{
   //
   // Set PE0 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 0, E_IO_OUTPUT);
   //
   // Set PE1 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 1, E_IO_OUTPUT);
   //
   // Set PE2 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 2, E_IO_OUTPUT);
   //
   // Set PE3 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 3, E_IO_OUTPUT);
   //
   // Set PE4 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 4, E_IO_OUTPUT);
   //
   // Set PE5 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 5, E_IO_OUTPUT);
   //
   // Set PE6 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 6, E_IO_OUTPUT);
   //
   // Set PE7 Pin Mode
   //
   DrvGPIO_Open(E_GPE, 7, E_IO_OUTPUT);

}

/*************************************************************
 * GPIOB Initialization
**************************************************************/
void GPIOB_Init()
{
   //
   // Set PB11 Pin Mode
   //
   DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT);

}

/*************************************************************
 * GPIOA Initialization
**************************************************************/
void GPIOA_Init()
{
   //
   // Set PA0 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 0, E_IO_QUASI);
   //
   // Set PA1 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 1, E_IO_QUASI);
   //
   // Set PA2 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 2, E_IO_QUASI);
   //
   // Set PA3 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 3, E_IO_QUASI);
   //
   // Set PA4 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 4, E_IO_QUASI);
   //
   // Set PA5 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 5, E_IO_QUASI);
   //
   // Set PA12 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
   //
   // Set PA13 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 13, E_IO_OUTPUT);
   //
   // Set PA14 Pin Mode
   //
   DrvGPIO_Open(E_GPA, 14, E_IO_OUTPUT);

}

/*************************************************************
 * GPIOD Initialization
**************************************************************/
void GPIOD_Init()
{
   //
   // Set PD14 Pin Mode
   //
   DrvGPIO_Open(E_GPD, 14, E_IO_OUTPUT);

}

/*************************************************************
 * GPIOC Initialization
**************************************************************/
void GPIOC_Init()
{
   //
   // Set PC4 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 4, E_IO_OUTPUT);
   //
   // Set PC5 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 5, E_IO_OUTPUT);
   //
   // Set PC6 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 6, E_IO_OUTPUT);
   //
   // Set PC7 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 7, E_IO_OUTPUT);
   //
   // Set PC12 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
   //
   // Set PC13 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 13, E_IO_OUTPUT);
   //
   // Set PC14 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 14, E_IO_OUTPUT);
   //
   // Set PC15 Pin Mode
   //
   DrvGPIO_Open(E_GPC, 15, E_IO_OUTPUT);

}

/*************************************************************
 * ADC Initialization
**************************************************************/
void ADC_Init()
{
    //
    // Configure the relative pins for ADC function
    //
    DrvGPIO_InitFunction(E_FUNC_ADC7);
    //
    // Config clock, input mode, operate mode and convert channel for ADC
    //
    DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP,0x80,INTERNAL_RC22MHZ,2);
    //
    // Select source for ADC channel 7
    //
    DrvADC_ConfigADCChannel7(EXTERNAL_INPUT_SIGNAL);
}

void Init()
{
    GPIOE_Init();
    GPIOB_Init();
    GPIOA_Init();
    GPIOD_Init();
    GPIOC_Init();
    ADC_Init();
}

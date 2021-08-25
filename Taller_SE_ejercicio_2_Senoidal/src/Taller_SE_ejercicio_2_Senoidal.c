/*
===============================================================================
 Name        : Taller_SE_ejercicio_2_Senoidal.c
 Author      : Alejandro Heredia
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>


// INCLUSION DE LIBRERIAS
#include <sapi_gpio.h>
#include <sapi_systick.h>
#include <sapi_rit.h>
#include <sapi_dac.h>
#define K 1000
#define PI 3.1416

// VARIABLES GLOBALES
float A=0;		//amplitud
float F=0;		//frecuencia
int Adig=0;
int T=0;
int t=0;
int y=0;

int main(void) {
#if defined (__USE_LPCOPEN)
    // INICIALIZACION DE LAS VARIABLES Y FUNCIONES DEL RTC
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    //INICIALIZACIONES DE LIBRERIAS
         Init_Tick(TICK_10US);
         dacInit(DAC_ENABLE);
  //INICIALIZACIONES DE ENTRADAS DIGITALES

  //INICIALIZACIONES DE SALIDAS DIGITALES

         F=10*K;
     	A=3.3;
         // functions related to the board hardware
    Board_Init();
    Board_LED_Set(0, true);

    F=10*K;
	A=3.3;
#endif
#endif


    while(1) {

    	// "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}


void SysTick_Handler(void)
{

Adig=A*(1023/3.3);//amplitud digitalizada

//SEÑAL SENOIDAL

t++;
y=(Adig/2)+(Adig)*sin(2*PI*F*t);
dacWrite(0,y);

}

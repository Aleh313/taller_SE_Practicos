/*
===============================================================================
 Name        : Taller_SE_ejercicio_3.c
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
         gpioInit( 0, 21, GPIO_INPUT );  //JACK 23
         gpioInit( 0, 27, GPIO_INPUT );  //JACK 25
         gpioInit( 0, 28, GPIO_INPUT );  //JACK 26
         gpioInit( 2, 13, GPIO_INPUT );  //JACK 27
  //INICIALIZACIONES DE SALIDAS DIGITALES
         gpioInit( 0, 22, GPIO_OUTPUT );

  // functions related to the board hardware
    Board_Init();
    Board_LED_Set(0, true);
#endif
#endif


    int valor=1;
    int valor2=1;
    int valor3=1;
    int valor4=1;
    int antirrebote=8*100000;
	int cont;
    while(1) {

    valor  =!gpioRead(0,21);
    for(cont=0;cont<antirrebote;++cont ){ }
    valor2 =!gpioRead(0,27);
    for(cont=0;cont<antirrebote;++cont ){ }
    valor3 =!gpioRead(0,28);
    for(cont=0;cont<antirrebote;++cont ){ }
    valor4 =!gpioRead(2,13);
    for(cont=0;cont<antirrebote;++cont ){ }

    if (valor==0)//señal 10 KHz 3.3v
    {
    F=10*K;
	A=3.3;
    }
    if (valor2==0)//señal 1KHz 3.3v
    {
    F=1*K;
    A=3.3;
    }
    if (valor3==0)//señal 10KHZ 1.65v
    {
    F=10*K;
    A=1.65;
    }
    if (valor4==0)// señal 1KHz 1.65v
    {
    F=1*K;
    A=1.65;
    }
    	// "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}


void SysTick_Handler(void)
{

Adig=A*(1023/3.3);//amplitud digitalizada
T=(1/F)*1000000;//periodo en uS
// SEÑAL DIENTE DE SIERRA

t++;
if(t>T)
{
t=0;
}

y=t*(Adig/T);
dacWrite(0,y);

//SEÑAL SENOIDAL
/*
t++;
y=(Adig/2)+(Adig)*sin(2*PI*F*t);
dacWrite(0,y);
*/
}

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "BusIn.h"
#include "DigitalIn.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "Thread.h"
#include "mbed.h"
#include "stm32f4xx_hal_pwr.h"

#define TIEMPO_CONTAR     3s
#define TIEMPO_VISUALIZA  11ms


// puertos 
BusOut seg(D2, D3, D4, D5, D6, D7, D8,D9);
DigitalOut U(D10);
DigitalOut D(D11);
DigitalIn bnt1 (BUTTON1);

// variables globales
static int unidades=0;
static int decenas =0;

const char bin_seg[16] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0XE0, 0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E};

// Hilos 
Thread hilo_visualiza;
Thread hilo_cuenta;

// Prototipos de las funcionees 
void visualizar(void);
void contar(void);



int main()
{
    // Activar los hilos
    hilo_visualiza.start(visualizar);
    hilo_cuenta.start(contar);

    while (true) {
    }
}


void visualizar(void)
{
    bool estado;
    while(true)
    {
        if   (!estado)   {U=0; D=1; seg = bin_seg[unidades]; }
        else             {U=1; D=0; seg = bin_seg[decenas];  }
        estado = !estado;
        ThisThread::sleep_for(TIEMPO_VISUALIZA);
    }
}


void contar(void)
{
    while(true)
    {
        unidades++;
        if (unidades==10) 
            {
                unidades=0;
                decenas++;
                if (decenas==10) decenas=0;
            }
    ThisThread::sleep_for(TIEMPO_CONTAR);
    }
}


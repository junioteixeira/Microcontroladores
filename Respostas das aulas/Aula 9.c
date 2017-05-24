Data: 03/05/2017

1. Escreva uma função em C que faz o debounce de botões ligados à porta P1.

void Atraso(volatile unsigned int x)
{
	// Periodo = 1us do clock -> Timer_A++ a cada 1us
	int i = 0; // Contador
	TA0CCR0 = 1000 - 1;
	TA0CTL = TASSEL_2 + ID_0 + MC_1;

	while (i<x)
	{
		while ((TA0CTL & TAIFG) == 0); // Só para quando TimerA chega a 1000. Só sai do while a cada 1ms;
		TA0CTL &= ~TAIFG;
		i++;
	}

	TA0CTL = MC_0;

}

int Debounce(int pin)
{
	while (P1IN & pin != 0); //Esperando uma mudança
	Atraso(10);		// Houve mudança - aguarda 10 ms para pegar o valor
	return P1IN & pin;
}

2. Escreva um código em C que lê 9 botões multiplexados por 6 pinos, e pisca os LEDs da placa Launchpad de acordo com os botões. Por exemplo, se o primeiro botão é pressionado, os LEDs piscam uma vez; se o segundo botão é pressionado, os LEDs piscam duas vezes; e assim por diante. Se mais de um botão é pressionado, os LEDs não piscam.

#include <msp430g2533.h>
#include <legacymsp430.h>


#define SetOut(pin)		 (P1DIR |= pin)
#define SetIn(pin)		 (P1DIR &= ~pin)
#define SetPullUp(pin)	 (P1REN |= pin)
#define SetPullDown(pin) (P1REN &= ~pin)
#define SetHigh(pin)	 (P1OUT |= pin)
#define SetLow(pin)		 (P1OUT &= ~pin)
#define SwitchValue(pin) (P1OUT ^= pin)

byte X[] = { BIT0, BIT1, BIT2 }; // Coluna
byte Y[] = { BIT3, BIT4, BIT5 }; // Linha

void SetupX(byte dir)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (dir)
		{
			SetOut(X[i]);
			SetPullDown(X[i]);
			SetLow(X[i]);
		}
		else
		{
			SetIn(X[i]);
			SetPullUp(X[i]);
			
		}
	}
}

// dir = 0, entrada.
// dir = 1, saída.
void SetupY(byte dir)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (dir)
		{
			SetOut(Y[i]);
			SetPullDown(Y[i]);
			SetLow(Y[i]);
		}
		else
		{
			SetIn(Y[i]);
			SetPullUp(Y[i]);
		}
	}
}



int main()
{
	WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog Timer

	return 0;
}







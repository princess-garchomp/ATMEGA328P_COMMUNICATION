//this is all blocking nonsence, proof of concept but ont the final result
//need to reset the board after each recieve/send

//gnd pins are connected
//rx->tx
//tx->rx

#include "UART.h"
#include "I_O_board.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


//this sets pin 13 high is 's' is recieved
//also on recieving an 's' it sends an 's' this can be observed in the termncal window

int main(void)
{
    USART_config(MYUBRR);

	all_I_O_config();
    while (1) 
    {
//			allows terminal window to recieve and then sednd back cahraters
//			view-> terminal windows

//		USART_Transmit(USART_Receive());
		

 		if(USART_Receive() == 's'){
			 //black is all on
			first_rgb_led_color(BLACK);
			USART_Transmit('s');
		 }
		else{
			//WHITE is all off
			first_rgb_led_color(WHITE);
		}
		while(1){}

    }
}



/*

//this sends a variable to the revieving usart to alster its pin13 led
//the transmit 's' and the transmit 'd' can both be seen in the termincal window and based on I/O state of the other atmega328P

int main(void)
{
	USART_config(MYUBRR);

	all_I_O_config();
	while (1)
	{
		//			allows terminal window to recieve and then sednd back cahraters
		//			view-> terminal windows
		if(A_is_pressed()){
			USART_Transmit('s');
			while(1){}
		}
		else if(E_is_pressed()){
			USART_Transmit('d');
			while(1){}
		}
		else{}

		//		USART_Transmit(USART_Receive());


	}
}


*/
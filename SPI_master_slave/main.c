#include <avr/interrupt.h>

#include "SPI.h"
#include "I_O.h"
#include "timer_global_count.h"



//the following is the program for SPI as masater

/*
uint8_t g_data = 0;
_Bool bool_bool = 0;
_Bool bool_bool_bool = 0;

int main(void)
{
	first_rgb_led_config();
	cli();
	config_SPI_master_one_slave();
	sei();

    while (1) 
    {
		//deselect_slave(); //this will make the slave not send or recieve a signal
		select_slave();
//lazy way of waiting a delay asnd then sending one message of value 24
		if(bool_bool == 0){
			first_rgb_led_color(RED);
			delay(6000000);
				SPI_master_send(24);
				first_rgb_led_color(WHITE);
				bool_bool = 1;
		}	
		else{;}
			
		if(g_data == 25){
			first_rgb_led_color(BLUE);
			while(1);
		}
	}
}

ISR(SPI_STC_vect){
	g_data = SPDR;
}


*/

//no idea why this neas to be volatile, some how it works now?
volatile uint8_t g_data = 0;
	
int main(void){

	first_rgb_led_config();
	cli();
	config_SPI_slave();
	sei();

	while (1){
		slave_SPI_send(25);
		if(g_data == 24){
					first_rgb_led_color(BLUE);
						slave_SPI_send(25);
					
					while(1){;}
		}
	}

}

ISR(SPI_STC_vect){
	g_data = SPDR;
// 			if(g_data == 24){
// 				first_rgb_led_color(BLUE);
// 				slave_SPI_send(25);
// 				while(1){;}
// 			}
}



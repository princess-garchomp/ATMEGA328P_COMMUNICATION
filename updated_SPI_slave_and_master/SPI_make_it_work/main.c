
/*
this is an spi master 
it sends a '0' to the slave over the MOSI and the slave sends its SPDR value over the MISO
the master recieves a 'b' and then after a delay the master incramnets it by 3 and sends a 'e' over the MOSI
at the same time the slave sends the new value of the SPDR register over the MISO and the master recieves a '0' and lights up the led blue 
*/

#include <avr/interrupt.h>

#include "SPI.h"
#include "I_O.h"
#include "timer_global_count.h"

uint32_t g_fake_timer;
volatile uint8_t g_data = 0;
_Bool bool_bool = 0;
_Bool bool_bool_bool = 0;

uint8_t g_coutner;
void send_alphabet_fsm();
void fake_tiemr_counter();

int main(void)
{
	first_rgb_led_config();
	cli();
	//_16_bit_tiemr1_config();
	config_SPI_master_one_slave();
	sei();
//while(1){first_rgb_led_color(BLUE);}
	while (1)
	{
		select_slave();
		//send_alphabet_fsm();
				//deselect_slave(); //this will make the slave not send or recieve a signal
				//lazy way of waiting a delay asnd then sending one message of value 24
				if(bool_bool == 0){
					//truns red
					first_rgb_led_color(RED);
					delay(6000000);
					SPI_master_send('0');
					first_rgb_led_color(WHITE);
					bool_bool = 1;
				}
				else{;}
				/*	delay(600);
									if(g_data == 'a'){
										//turns blue
										first_rgb_led_color(BLUE);
									}
									if(g_data == 'b'){
										//turns red
										first_rgb_led_color(RED);
									}
				//SPI_master_send('z');*/
								if(bool_bool_bool == 0){
									//turns green
									//first_rgb_led_color(GREEN);
									delay(6000000);
									SPI_master_send((g_data+3));
									first_rgb_led_color(WHITE);
									bool_bool_bool = 1;
								}
								else{;}
									

				
				if(g_data == '0'){
					//turns blue
					first_rgb_led_color(BLUE);
				}
								if(g_data == 'b'){
									//turns red
									first_rgb_led_color(GREEN);
								}


	}
}

void send_alphabet_fsm()
{
	static enum {UPDATE_STATE, WAIT_STATE, SEND_STATE}
		local_send_fsm_state = WAIT_STATE;
		
	static unsigned long time_entered = 0;
	static uint8_t send_incramenter=0;

	switch(local_send_fsm_state)
	{
		case(UPDATE_STATE):
		time_entered = _mS_counter();
	//	time_entered = g_fake_timer;
		send_incramenter = (send_incramenter+1)%26;
		local_send_fsm_state = WAIT_STATE;
		break;
		
		case(WAIT_STATE):
	//	if((g_fake_timer - time_entered) > 200000)

		if((_mS_counter() - time_entered) > 200)
		{
			local_send_fsm_state = SEND_STATE;
			//green here causes a flash
			first_rgb_led_color(GREEN);
			//		send_incramenter = (send_incramenter+1)%26;

		}
		//the next if is used to check overflow of the 32bit g_fake_timer variable
		/*
		if(g_fake_timer == 0)
		{
			local_send_fsm_state = SEND_STATE;
			first_rgb_led_color(RED);
		}
		*/
		break;
		
		case(SEND_STATE):
		//char_to_send=('a'+ send_incramenter);
		SPI_master_send('b'+ send_incramenter);
		local_send_fsm_state = UPDATE_STATE;
		break;
	}
}

void fake_tiemr_counter()
{
	g_fake_timer++;
}

ISR(SPI_STC_vect){
	g_data = SPDR;
		//first_rgb_led_color(RED);

}
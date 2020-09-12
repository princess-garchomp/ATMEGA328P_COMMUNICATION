#include <avr/io.h>
#include "SPI.h"
#include "I_O.h"

#define SCK PB5
#define MISO PB4
#define MOSI PB3
#define SS PB2

void config_SPI_master_one_slave(){
	//set outputs
	DDRB |= (1ul<<SCK)|(1ul<<MOSI)|(1ul<<SS);
	//set SS high
	PORTB|=(1ul<<SS);
	//set inputs
	DDRB &= ~(1ul<<MISO);
	SPCR |= (1ul<<SPIE)|(1ul<<SPE)|(1ul<<MSTR)|(1ul<<SPR0)|(1ul<<SPR1);
}

void SPI_master_send(uint8_t data){

	//if the buffer is not transmitting send the data
	if(~(SPSR & (1ul<<SPIF))){
		//send data
		SPDR = data;
	}
}
//I also want to be able to recieve over MISO(as an interupt?)

void config_USART_as_SPI_one_slave(unsigned int baud){
		//set outputs
		DDRB |= (1ul<<SCK)|(1ul<<SS);
		//set SS high
		PORTB|=(1ul<<SS);
		
		UCSR0C = (1ul<<UMSEL01)|(1ul<<UMSEL00)|(0ul<<UCPHA0)|(0ul<<UCPOL0);
		UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
		//enable interupt so this can accept data from slave?
		
		UBRR0 = baud;
}
void USART_SPI_master_send(uint8_t data){
// 	/* Wait for empty transmit buffer */
// 	while (!(UCSRnA & (1<<UDREn)));
// 	/* Put data into buffer, sends the data */
// 	UDRn = data;
// 	/* Wait for data to be received */
// 	while (!(UCSRnA & (1<<RXCn)));
// 	/* Get and return received data from buffer */
// 	return UDRn;
	if ((UCSR0A & (1<<UDRE0))){
		UDR0 = data;
	}
}
//I also want to be able to reciece over MISO (as an interupt?)

void config_SPI_slave(){
	//set outputs
	DDRB |= (1ul<<MISO);
	//set inputs
//	DDRB &= ~(1ul<<MOSI)&~(1ul<<SCK)&~(1ul<<SS);
	
	//menable interrupt and spi as slave
	SPCR |= (1ul<<SPIE)|(1ul<<SPE)/*|(0ul<<MSTR)*/;
}

void slave_SPI_send(uint8_t data){
	if(~(SPSR & (1ul<<SPIF))){
		//send data
		SPDR = data;
	}
}



void select_slave(){
	PORTB &= ~(1ul<<SS);
}
void deselect_slave(){
	PORTB |= (1ul<<SS);
}
#include "SPI_Config.h"

void SPI_Init( Struct_SPI SPI_Config){
	switch(SPI_Config.Operation_Mode){
		case Master : SPCR |= (1U << MSTR);
					  (*((volatile u8*)(SCL_PIN  + 1))) |= (1U << SCL_Bit);	/*	At MASTER SCL Output		*/
					  (*((volatile u8*)(MOSI_PIN + 1))) |= (1U << MOSI_Bit);/*	At MASTER MOSI as Output	*/
					  break;				
					  	  
		case Slave  : SPCR &=~(1U << MSTR);
					  (*((volatile u8*)(MISO_PIN + 1))) |= (1 << MISO_Bit);/*	At SLAVE MISO as Output		*/
					  break;
					  
		default		: SPCR &=~(1U << MSTR);
					  (*((volatile u8*)(MISO_PIN + 1))) |= (1 << MISO_Bit);/*	At SLAVE MISO as Output		*/
					  break;
	}
	
	switch(SPI_Config.SCK_Frequency){
		case Fosc_4			: SPSR &=~(1U << SPI2X); SPCR &=~(1U << SPR1); SPCR &=~(1U << SPR0); break;
		case Fosc_16		: SPSR &=~(1U << SPI2X); SPCR &=~(1U << SPR1); SPCR |= (1U << SPR0); break;
		case Fosc_64		: SPSR &=~(1U << SPI2X); SPCR |= (1U << SPR1); SPCR &=~(1U << SPR0); break;
		case Fosc_128		: SPSR &=~(1U << SPI2X); SPCR |= (1U << SPR1); SPCR |= (1U << SPR0); break;
		case Fosc_2x_2		: SPSR |= (1U << SPI2X); SPCR &=~(1U << SPR1); SPCR &=~(1U << SPR0); break;
		case Fosc_2x_8		: SPSR |= (1U << SPI2X); SPCR &=~(1U << SPR1); SPCR |= (1U << SPR0); break;
		case Fosc_2x_32		: SPSR |= (1U << SPI2X); SPCR |= (1U << SPR1); SPCR &=~(1U << SPR0); break;
		case Fosc_2x_64		: SPSR |= (1U << SPI2X); SPCR |= (1U << SPR1); SPCR |= (1U << SPR0); break;
		default				: SPSR &=~(1U << SPI2X); SPCR &=~(1U << SPR1); SPCR &=~(1U << SPR0); break;
	}
	
	switch(SPI_Config.Data_Order){
		case LSB	: SPCR |= (1U << DORD); break;
		case MSB	: SPCR &=~(1U << DORD); break;
		default		: SPCR &=~(1U << DORD); break;
	}
	
	switch(SPI_Config.SPI_Mode){
		case Leading_Edge_Sample_Rising	 : SPCR &=~(1U << CPOL); SPCR &=~(1U << CPHA); break;
		case Leading_Edge_Sample_Falling : SPCR |= (1U << CPOL); SPCR &=~(1U << CPHA); break;
		case Leading_Edge_Setup_Rising	 : SPCR &=~(1U << CPOL); SPCR |= (1U << CPHA); break;
		case Leading_Edge_Setup_Falling	 : SPCR |= (1U << CPOL); SPCR |= (1U << CPHA); break;
		default							 : SPCR &=~(1U << CPOL); SPCR &=~(1U << CPHA); break;
	}
	
	switch(SPI_Config.Interrupt_Select){
		case Interrupt_Enable	: SPCR |= (1U << SPIE); break;
		default					: SPCR &=~(1U << SPIE); break;
	}
	
	SPCR |= (1 << SPE);		/*	After Finishing the configuration, Enable the SPI	*/
	
}

u8 SPI_Transever ( u8 Data ){
	SPDR = Data;					/*	Send Data to the Data register		*/
	while (!(SPSR & (1 << SPIF)));	/*	Wait until transmission is complete	
										After Transmitting the data it will	
										Be replaced by the received Data	*/
	return SPDR;					/*	Return the Received Data from SPDR	*/
}
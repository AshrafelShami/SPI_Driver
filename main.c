#include "SPI_Config.h"

int main(){
	u8 Rx_Data, Data = 0x00;
	DDRA = 0xFF;
    	Struct_SPI SPI_Init_Struct;
	SPI_Init_Struct.Operation_Mode	= Master;
	SPI_Init_Struct.SCK_Frequency	= Fosc_16;
	SPI_Init(SPI_Init_Struct);
	
	while (1){
		Rx_Data = SPI_Transever(Data++);
		PORTA = Rx_Data;
		_delay_ms(50);
    }
}


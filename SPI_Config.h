
#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#ifndef F_CPU
#define F_CPU	16000000UL
#include <util/delay.h>
#endif

#include "Function_Prototypes.h"
#include "DataTypes.h"
#include <avr/io.h>

#define SS_Bit		4
#define SS_PIN		&PINB

#define MOSI_Bit	5
#define MOSI_PIN	&PINB

#define MISO_Bit	6
#define MISO_PIN	&PINB

#define SCL_Bit		7
#define SCL_PIN		&PINB

typedef enum{
	Interrupt_Enable
	}Interrupt_Set;
	
typedef enum{
	LSB,
	MSB
	}Data;

typedef enum{
	Master,
	Slave
	}Operation;

typedef enum{
	Fosc_4,
	Fosc_16,
	Fosc_64,
	Fosc_128,
	Fosc_2x_2,
	Fosc_2x_8,
	Fosc_2x_32,
	Fosc_2x_64,	
	}Oscillator;
	
typedef enum{
	Leading_Edge_Sample_Rising,
	Leading_Edge_Sample_Falling,
	Leading_Edge_Setup_Rising,
	Leading_Edge_Setup_Falling	
	}Data_Mode;

typedef struct{
	Interrupt_Set	Interrupt_Select;
	Data			Data_Order;
	Operation		Operation_Mode;
	Oscillator		SCK_Frequency;
	Data_Mode		SPI_Mode;
	}Struct_SPI;	

void SPI_Init( Struct_SPI );

#endif /* SPI_CONFIG_H_ */
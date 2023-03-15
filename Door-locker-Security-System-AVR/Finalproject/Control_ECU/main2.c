 /******************************************************************************
 *
 *
 * File Name: main2.c
 *
 * Description: Source file for the Main file of second MC
 *
 * Author: Weli
 *
 *******************************************************************************/
#include "main2.h"

/*******************************************************************************
 *                             global variables                                *
 *******************************************************************************/
uint32 g_tick=0;//the ticks timer will count
int falsePasswords;
/*
 * define Uart struct
 * 8 bits of data,Disable parity ,One stop bit ,Baud rate=9600
 */
UART_ConfigType Config={Eight,Disabled,One_bit,Mode_9600};
/*
 * define TWI Struct
 */
TWI_ConfigType twi_config={Rate_400KBPS,0x01};
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 *description the function that will be included in the main of the Control_ECU
 */
void start(void){
	//Enable I-bit
	SREG|=(1<<7);
	uint8 password[5] , confirmPassword[5] , passwordVerified , command;
	//Initialize buzzer
	Buzzer_init();
	//Initialize DC Motor
	DcMotor_Init();
	//Initialize UART
	UART_init(&Config);
	//Initialize I2C
	TWI_init(&twi_config);

	while(passwordVerified == 0)
	{
		receivePassword(password);

		receivePassword(confirmPassword);

		passwordVerified = verifyPassword(password, confirmPassword);
		UART_sendByte(passwordVerified);

		_delay_ms(UART_DELAY);
	}


	storePasswordeeprom(password);


	while(1)
	{
		uint8 passwordEEPROM[4];
		readPasswordeeprom(passwordEEPROM);
		command = UART_recieveByte();
		_delay_ms(UART_DELAY);

		if(command == '+')
		{
			receivePassword(password);

			if(verifyPassword(password, passwordEEPROM))
			{
				falsePasswords = 0;
				UART_sendByte(1);
				_delay_ms(UART_DELAY);
				openDoor();
			}

			else
			{
				UART_sendByte(0);
				_delay_ms(UART_DELAY);
				falsePasswords++;
				UART_sendByte(falsePasswords);
				_delay_ms(UART_DELAY);
				falsePassword();

			}
		}

		else if(command == '-')
		{
			receivePassword(password);


			passwordVerified = verifyPassword(password, passwordEEPROM);
			_delay_ms(UART_DELAY);
			UART_sendByte(passwordVerified);

			if(passwordVerified)
			{
				falsePasswords = 0;
				receivePassword(password);


				receivePassword(confirmPassword);

				passwordVerified = verifyPassword(password, confirmPassword);
				_delay_ms(UART_DELAY);
				UART_sendByte(passwordVerified);

				if(passwordVerified)
				{
					storePasswordeeprom(password);
				}

				else
				{
					// do nothing
				}

			}

			else
			{
				falsePasswords++;
				UART_sendByte(falsePasswords);
				_delay_ms(UART_DELAY);
				falsePassword();
			}
		}
	}
}


void receivePassword (uint8 password[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		password [i] = UART_recieveByte();
	}
	_delay_ms (UART_DELAY);
}

uint8 verifyPassword (uint8 password[] , uint8 confirmPassword[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		if (password[i] != confirmPassword[i])
		{
			return 0;
		}
	}
	return 1;
}

void openDoor (void)
{

	DcMotor_Rotate(CLOCKWISE);
	wait(15);//wait 15 sec

	DcMotor_Rotate(STOP);
	wait(3);//wait 3 sec


	DcMotor_Rotate(ANTICLOCKWISE);
	wait(15);//wait 15 sec

	DcMotor_Rotate(STOP);
}

void falsePassword (void)
{
	if (falsePasswords >= 3)
	{
		falsePasswords = 0;
		Buzzer_on();
		wait(60);//wait for 1 minute
		Buzzer_off();
	}
}

void storePasswordeeprom (uint8 password[])
{
	uint8 i;
	for (i=0 ; i<5 ; ++i)
	{
	EEPROM_writeByte ((0X0090 + i) , (password[i]));
	_delay_ms(UART_DELAY);
	}
}

void readPasswordeeprom (uint8 password [])
{
	uint8 i;
	for (i=0 ; i<5 ; ++i)
	{
		EEPROM_readByte ((0x0090 + i) , (password + i));
		_delay_ms(100);
	}
}


void timer_tick(void){
	g_tick++;
}

void wait(uint16 seconds){
	g_tick=0;
	uint32 counter=seconds;/*the seconds required to be waited */
	Timer1_ConfigType timerS={0,7813,F_1024,CTC};
	Timer1_init(&timerS);
	Timer1_setCallBack(timer_tick);
	while(g_tick<counter);
	Timer1_deInit();
}

/*******************************************************************************
 *                              MAIN Function                                  *
 *******************************************************************************/
int main()
{
	start();
}


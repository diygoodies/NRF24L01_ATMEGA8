/*
nrf24l01 lib sample

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "board.h"
#include "nrf24l01.h"
#include "nrf24l01registers.h"

//define debug print enable or disable on uart
#define DEBUGENABLED 1

//include uart
#if DEBUGENABLED == 1
#include "uart/uart.h"
#define UART_BAUD_RATE 9600
#endif

//include nrf24l01
#include "nrf24l01/nrf24l01.h"

//role definitions
#define ROLETX 1
#define ROLERX 0

#define LEDOUTPAUSESLOW 300
#define LEDOUTPAUSEFAST 150

	uint8_t txrxrole = 0; // 1 transmitter 0 receiver

	//sending buffer addresses
	uint8_t txpipe = 1;
	uint8_t addrtx0[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP0;
	uint8_t addrtx1[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP1;
	uint8_t addrtx2[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP2;
	uint8_t addrtx3[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP3;
	uint8_t addrtx4[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP4;
	uint8_t addrtx5[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP5;

		//nrf24l01 variables
	uint8_t bufferout[NRF24L01_PAYLOAD];
	uint8_t bufferin[NRF24L01_PAYLOAD];
	uint8_t i = 0;
	char pipebuffer[5];
	unsigned int timercounter=0;

ISR(INT0_vect)
{
		uart_puts("Int0 \r\n");
		led_green_on;
		uint8_t status = nrf24l01_getstatus();
		nrf24l01_writeregister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_RX_DR) | (1<<NRF24L01_REG_TX_DS) | (1<<NRF24L01_REG_MAX_RT)); //reset status
		/*

			if (status & (1<<NRF24L01_REG_MASK_TX_DS))							// IRQ: Package has been sent
		{
			nrf24l01_writeregister(NRF24L01_REG_STATUS, (1<<NRF24L01_REG_TX_DS));	//Clear Interrupt Bit
			led_green_on;
			PTX=0;
		}
		
		if (status & (1<<NRF24L01_REG_MASK_MAX_RT))							// IRQ: Package has not been sent, send again
		{
			nrf24l01_writeregister(NRF24L01_REG_STATUS,(1<<NRF24L01_REG_MAX_RT));	// Clear Interrupt Bit
			led_green_off;
			nrf24l01_CSNhi;								// Start transmission
			_delay_us(10);								
			nrf24l01_CSNlo;
		}
		
		if (status & (1<<NRF24L01_REG_TX_FULL))							//TX_FIFO Full <-- this is not an IRQ
		{
			nrf24l01_CSNlo;                               // Pull down chip select
			spi_writereadbyte(NRF24L01_CMD_FLUSH_TX);						// Flush TX-FIFO
			nrf24l01_CSNhi;                               // Pull up chip select
		}
*/
}

ISR(TIMER0_OVF_vect)
{
	timercounter++;
	
}

void reg_disp(void)
{
	uart_puts("\r\n");
	uart_puts("Timer counter( ");
	itoa(timercounter, pipebuffer, 10);
	uart_puts(pipebuffer);
	uart_puts(" )\r\n");
						
	uart_puts("Status register: ");
	itoa(nrf24l01_readregister(NRF24L01_REG_STATUS), pipebuffer, 10);
	uart_puts(pipebuffer);
	uart_puts("\r\n");

	uart_puts("Config register: ");
	itoa(nrf24l01_readregister(NRF24L01_REG_CONFIG), pipebuffer, 10);
	uart_puts(pipebuffer);
	uart_puts("\r\n");
	_delay_ms(500);

}				


void role_init(void)
{
		//select a role
	if ((BUTTONROLE_PIN & (1<<BUTTONROLE)) == 1)
		txrxrole = ROLERX;
	else
		txrxrole = ROLETX;

	//blink led depending on role
/*
	if(txrxrole == ROLETX) 
	{
		led_yellow_on; _delay_ms(LEDOUTPAUSESLOW);
		led_yellow_off; _delay_ms(LEDOUTPAUSESLOW);
	} 
	else if(txrxrole == ROLERX) 
	{
		led_yellow_on; _delay_ms(LEDOUTPAUSEFAST);
		led_yellow_off; _delay_ms(LEDOUTPAUSEFAST);
		led_yellow_on; _delay_ms(LEDOUTPAUSEFAST);
		led_yellow_off; _delay_ms(LEDOUTPAUSEFAST);
	}
*/
/*
	#if DEBUGENABLED == 1
	if(txrxrole == ROLETX)
		uart_puts("starting as tx...\r\n");
	else if(txrxrole == ROLERX)
		uart_puts("starting as rx...\r\n");
	#endif
	*/
}


void send_packet(uint8_t *buffer, unsigned char sendpipe)

{
//tx
			#if DEBUGENABLED == 0
			if ((BUTTONSEND_PIN & (1<<BUTTONSEND)) == 0) { //if button pressed
			#endif

				#if DEBUGENABLED == 1
				//char pipebuffer[5];
				uart_puts("sending data, on pipe ");
				reg_disp();
				itoa(sendpipe, pipebuffer, 10);
				uart_puts(pipebuffer);
				uart_puts("... ");
				#endif

				if(sendpipe == 0) {
					//set tx address for pipe 0
					nrf24l01_settxaddr(addrtx0);
				} else if(sendpipe == 1) {
					//set tx address for pipe 1
					nrf24l01_settxaddr(addrtx1);
				} else if(sendpipe == 2) {
					//set tx address for pipe 2
					nrf24l01_settxaddr(addrtx2);
				} else if(sendpipe == 3) {
					//set tx address for pipe 3
					nrf24l01_settxaddr(addrtx3);
				} else if(sendpipe == 4) {
					//set tx address for pipe 4
					nrf24l01_settxaddr(addrtx4);
				} else if(sendpipe == 5) {
					//set tx address for pipe 5
					nrf24l01_settxaddr(addrtx5);
				}

				//write buffer
				uint8_t writeret = nrf24l01_write(buffer);

				#if DEBUGENABLED == 1
				if(writeret == 1)
				{
					uart_puts("ok\r\n");


					
					if (sendpipe==0)
					{
						led_green_on; _delay_ms(LEDOUTPAUSESLOW);
						led_green_off; _delay_ms(LEDOUTPAUSESLOW);
					}
					else
					{
						led_yellow_on; _delay_ms(LEDOUTPAUSESLOW);
						led_yellow_off; _delay_ms(LEDOUTPAUSESLOW);

					}
				}
				else
					uart_puts("failed\r\n");
				#endif

				sendpipe++;
				sendpipe%=6;


			
			#if DEBUGENABLED == 0
			}
			#endif
			#if DEBUGENABLED == 1
			reg_disp();
			_delay_ms(1000);
			#endif
}

void recieve_packet(void)
{
			//rx
			uint8_t i = 0;
			uint8_t pipe = 0;
			reg_disp();
			if(nrf24l01_readready(&pipe)) { //if data is ready

				#if DEBUGENABLED == 1
				char pipebuffer[5];
				uart_puts("getting data, on pipe ");
				itoa(pipe, pipebuffer, 10);
				uart_puts(pipebuffer);
				uart_puts("\r\n");
				#endif

				//read buffer
				nrf24l01_read(bufferin);

				#if DEBUGENABLED == 1
				uint8_t samecheck = 1;
				uart_puts("  data: ");
				for(i=0; i<sizeof(bufferin); i++) {
					if(bufferin[i] != bufferout[i])
						samecheck = 0;
					uart_putc(bufferin[i]);
				}
				uart_puts("\r\n");
				if(samecheck)
					
					{
					uart_puts("  check ok\r\n");
					
					//blink led for input data
						if (pipe==0)
						{
							led_green_on; _delay_ms(LEDOUTPAUSEFAST);
							led_green_off; _delay_ms(LEDOUTPAUSEFAST);
						}
						else
						{
							led_yellow_on; _delay_ms(LEDOUTPAUSEFAST);
							led_yellow_off; _delay_ms(LEDOUTPAUSEFAST);

						}
					
					}
				else
					uart_puts("  check fails\r\n");
				for(i=0; i<sizeof(bufferin); i++)
					bufferin[i] = 0;
				#endif
				}
				_delay_ms(10);
			reg_disp();
			
}


//main here
int main(void) 
{
	

 	gpio_init();

	#if DEBUGENABLED == 1
	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	#endif

	//init nrf24l01
	nrf24l01_init();

	TCCR0 |= ( (1<<CS02) | (1<<CS00));		//Prescaler auf 1024 ATMEGA8
	TIMSK |= ( (1<<TOIE0));					//enable TOVF ATMEGA8
	
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 0<<ISC00;	// Trigger INT0 on falling edge


	//init interrupt
	sei();

	//role_init();



	//setup buffer
	for(i=0; i<sizeof(bufferout); i++)
		bufferout[i] = i+'a';
	for(i=0; i<sizeof(bufferin); i++)
		bufferin[i] = 0;






	#if DEBUGENABLED == 1 && NRF24L01_PRINTENABLE == 1
		nrf24l01_printinfo(uart_puts, uart_putc);
	#endif


	//main loop
	for(;;) 
	{
		
		role_init();

		if (txrxrole == ROLETX) {//((BUTTONSEND_PIN & (1<<BUTTONSEND)) == 0)
			
			if ((BUTTONSEND_PIN & (1<<BUTTONSEND)) == 0)
			{
				send_packet(bufferout,0);
				//led_green_off;	
			}
			else
			{
				send_packet(bufferout,txpipe);
				//led_green_on;
			}

		} else if(txrxrole == ROLERX) 
		
		{
			recieve_packet();

		}
	}
}





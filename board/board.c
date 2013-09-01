#include <avr/io.h>
#include "board.h"



void gpio_init(void)
{
	//setup port
	BUTTONROLE_DDR &= ~(1<<BUTTONROLE); //input
	BUTTONSEND_DDR &= ~(1<<BUTTONSEND); //input


	LEDOUTG_DDR |= (1<<LEDOUTG); //output
	LEDOUTG_PORT &= ~(1<<LEDOUTG); //off

	LEDOUTY_DDR |= (1<<LEDOUTY); //output
	LEDOUTY_PORT &= ~(1<<LEDOUTY); //off

	POWER_DDR |= (1<<POWER); //output
	POWER_PORT |= (1<<POWER);//on

}

//role button/pin
#define BUTTONROLE_DDR DDRC
#define BUTTONROLE_PORT PORTC
#define BUTTONROLE_PIN PINC
#define BUTTONROLE PC0
//send button
#define BUTTONSEND_DDR DDRC
#define BUTTONSEND_PORT PORTC
#define BUTTONSEND_PIN PINC
#define BUTTONSEND PC1
//output led Yellow
#define LEDOUTY_DDR DDRC
#define LEDOUTY_PORT PORTC
#define LEDOUTY PC2

//output led Green
#define LEDOUTG_DDR DDRC
#define LEDOUTG_PORT PORTC
#define LEDOUTG PC3


//tps7633 power controll
#define POWER_DDR DDRB
#define POWER_PORT PORTB
#define POWER PB2


#define Led1 0x01;
#define Led2 0x02;
#define Led3 0x04;

#define led_yellow_on LEDOUTY_PORT |= 1<<LEDOUTY;
#define led_green_on LEDOUTG_PORT |= 1<<LEDOUTG;
#define tps7633_on LEDOUTY_PORT |= 1<<POWER;

#define led_yellow_off PORTC&= ~(1<<LEDOUTY);
#define led_green_off PORTC&= ~(1<<LEDOUTG);
#define tps7633_off PORTC&= ~(1<<POWER);



#define led_yellow_toggle LEDOUTY_PORT ^= LEDOUTY;
#define led_green_toggle LEDOUTG_PORT ^= LEDOUTG;

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x),(BIT((y))))

void gpio_init(void);

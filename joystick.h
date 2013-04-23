#include <stdio.h>
#include "system.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard.h"

#define JOYSTICK_PLAYER_ONE_UP 256
#define JOYSTICK_PLAYER_ONE_DOWN 128
#define JOYSTICK_PLAYER_ONE_LEFT 64
#define JOYSTICK_PLAYER_ONE_RIGHT 32
#define JOYSTICK_PLAYER_ONE_SHOOT 512

#define JOYSTICK_PLAYER_TWO_UP 2
#define JOYSTICK_PLAYER_TWO_DOWN 4
#define JOYSTICK_PLAYER_TWO_LEFT 8
#define JOYSTICK_PLAYER_TWO_RIGHT 16
#define JOYSTICK_PLAYER_TWO_SHOOT 1

#define KEYBOARD_PLAYER_ONE_UP 0x75
#define KEYBOARD_PLAYER_ONE_DOWN 0x72
#define KEYBOARD_PLAYER_ONE_LEFT 0x6b
#define KEYBOARD_PLAYER_ONE_RIGHT 0x74
#define KEYBOARD_PLAYER_ONE_SHOOT 0x59
#define KEYBOARD_PLAYER_ONE_SHOOT_ALT 0x29

#define KEYBOARD_PLAYER_TWO_UP 0x1d
#define KEYBOARD_PLAYER_TWO_DOWN 0x1b
#define KEYBOARD_PLAYER_TWO_LEFT 0x1c
#define KEYBOARD_PLAYER_TWO_RIGHT 0x23
#define KEYBOARD_PLAYER_TWO_SHOOT 0x12

#define DIRECTION_UP 'U'
#define DIRECTION_DOWN 'D'
#define DIRECTION_LEFT 'L'
#define DIRECTION_RIGHT 'R'
#define DIRECTION_NONE 'N'

unsigned int * keys = PIO_0_BASE;
unsigned long *GIO = GIO_BASE;

alt_u8 getKeyboard();

int keyboard_init = 1;
alt_up_ps2_dev *ps2;
KB_CODE_TYPE decode_mode;
char ascii;
char *p;


char getmovement(int player) {
	int direction;
	alt_u8 data = getKeyboard();
	direction = DIRECTION_NONE;
    // These are different cases for the different controllers that can be used
    // They correspond to:
    // JOYSTICK - DE2 Board keys - KEYBOARD
    // TODO: Add infrared controller.  
	if (player == 1) {
		if ((*GIO & JOYSTICK_PLAYER_ONE_UP) || data == KEYBOARD_PLAYER_ONE_UP)
			direction = DIRECTION_UP;
		if ((*GIO & JOYSTICK_PLAYER_ONE_DOWN) || data == KEYBOARD_PLAYER_ONE_DOWN)
			direction = DIRECTION_DOWN;
		if ((*GIO & JOYSTICK_PLAYER_ONE_LEFT) || (!(*keys & KEY_1_PRESSED)) || data == KEYBOARD_PLAYER_ONE_LEFT)
			direction = DIRECTION_LEFT;
		if ((*GIO & JOYSTICK_PLAYER_ONE_RIGHT) || (!(*keys & KEY_0_PRESSED)) || data == KEYBOARD_PLAYER_ONE_RIGHT)
			direction = DIRECTION_RIGHT;
	}

	if (player == 2) {
		if ((*GIO & JOYSTICK_PLAYER_TWO_UP) || data == KEYBOARD_PLAYER_TWO_UP)
			direction = DIRECTION_UP;
		if (*GIO & JOYSTICK_PLAYER_TWO_DOWN || data == KEYBOARD_PLAYER_TWO_DOWN)
			direction = DIRECTION_DOWN;
		if ((*GIO & JOYSTICK_PLAYER_TWO_LEFT) || (!(*keys & KEY_3_PRESSED)) || data == KEYBOARD_PLAYER_TWO_LEFT)
			direction = DIRECTION_LEFT;
		if ((*GIO & JOYSTICK_PLAYER_TWO_RIGHT) || (!(*keys & KEY_2_PRESSED)) || data == KEYBOARD_PLAYER_TWO_RIGHT)
			direction = DIRECTION_RIGHT;
	}
	data = 0;
	return direction;
}

int is_shooting(int player) {
    // TODO: Add shoot for keyboard (space key)
	int shooting = 0;
	alt_u8 data = getKeyboard();
	if (player == 1) {
		if ((*GIO & JOYSTICK_PLAYER_ONE_SHOOT) || (!(*keys & KEY_3_PRESSED)) || data == KEYBOARD_PLAYER_ONE_SHOOT || data == KEYBOARD_PLAYER_ONE_SHOOT_ALT)
			shooting = 1;
	}
	if (player == 2) {
		if (*GIO & JOYSTICK_PLAYER_TWO_SHOOT || data == KEYBOARD_PLAYER_TWO_SHOOT)
			shooting = 1;
	}
	data = 0;
	return shooting;
}

alt_u8 getKeyboard(){
	alt_u8 data;
	// Initializing the keyboard
	// Only needs to be done once
	if (keyboard_init == 1){
		ps2 = alt_up_ps2_open_dev(PS2_0_NAME); //assign the new structure to the device.
		alt_up_ps2_init(ps2);
		alt_up_ps2_clear_fifo(ps2);
	    // This is the delay that the keyboard will experience.
	    // The smaller the number, the faster the paddle moves.
		set_keyboard_rate(ps2, 0x00);
		keyboard_init = 0;
	}
	decode_scancode(ps2, &decode_mode, &data, &ascii);
	return data;
}

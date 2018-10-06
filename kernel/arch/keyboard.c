#include <arch/keyboard.h>

int shift = 0;
int capslock = 0;

char keyboard_to_scan[] = {
		0,   // 0
		27,  // ESCAPE
		'1', // 1
		'2', // 2
		'3', // 3
		'4', // 4
		'5', // 5
		'6', // 6
		'7', // 7
		'8', // 8
		'9', // 9
		'0', // 0
		'-', // -
		'=', // =
		'\b', // Backspace
		'\t', // Tab
		'q', // q
		'w', // w
		'e', // e
		'r', // r
		't', // t
		'y', // y
		'u', // u
		'i', // i
		'o', // o
		'p', // p
		'[', // [
		']', // ]
		'\n', // enter
		0,   // lctrl
		'a', // a
		's', // s
		'd', // d
		'f', // f
		'g', // g
		'h', // h
		'j', // j
		'k', // k
		'l', // l
		';', // ;
		'\'', // '
		'`', // `
		0,   // lshift
		8,   // backslash
		'z', // z
		'x', // x
		'c', // c
		'v', // v
		'b', // b
		'n', // n
		'm', // m
		',', // ,
		'.', // .
		'/', // /
		0,   // rightshift
		'*', // keypad *
		0,   // lalt
		' ', // space
		0,   //capslock
		0, // F1
		0, // F2
		0, // F3
		0, // F4
		0, // F5
		0, // F6
		0, // F7
		0, // F8
		0, // F9
		0, // F10
		0, // Numlock
		0, // Scrolllock
		'7', // k7
		'8', // k8
		'9', // k9
		'-', // k-
		'4', // k4
		'5', // k5
		'6', // k6
		'+', // k+
		'1', // k1
		'2', // k2
		'3', // k3
		'0', // k0
		'.', // k.
		0,   // F11
		0,    // F12
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27,  // ESCAPE
		'!', // 1
		'@', // 2
		'#', // 3
		'$', // 4
		'%', // 5
		'^', // 6
		'&', // 7
		'*', // 8
		'(', // 9
		')', // 0
		'_', // -
		'+', // =
		'\b', // Backspace
		'\t', // Tab
		'Q', // q
		'W', // w
		'E', // e
		'R', // r
		'T', // t
		'Y', // y
		'U', // u
		'I', // i
		'O', // o
		'P', // p
		'{', // [
		'}', // ]
		'\n', // enter
		0,   // lctrl
		'A', // a
		'S', // s
		'D', // d
		'F', // f
		'G', // g
		'H', // h
		'J', // j
		'K', // k
		'L', // l
		':', // ;
		'"', // '
		'~', // `
		0,   // lshift
		8,   // backslash
		'Z', // z
		'X', // x
		'C', // c
		'V', // v
		'B', // b
		'N', // n
		'M', // m
		'<', // ,
		'>', // .
		'?', // /
		0,   // rightshift
		'*', // keypad *
		0,   // lalt
		' ', // space
		0,   //capslock
		0, // F1
		0, // F2
		0, // F3
		0, // F4
		0, // F5
		0, // F6
		0, // F7
		0, // F8
		0, // F9
		0, // F10
		0, // Numlock
		0, // Scrolllock
		'7', // k7
		'8', // k8
		'9', // k9
		'-', // k-
		'4', // k4
		'5', // k5
		'6', // k6
		'+', // k+
		'1', // k1
		'2', // k2
		'3', // k3
		'0', // k0
		'.', // k.
		0,   // F11
		0    // F12
		};

char keyboard_state[256];

int keyboard_pull() {
	int k = keyboard_get();

	int previous = keyboard_state[k & 0x7f];
	int new = (k > 0x80) ? (0) : (1);

	keyboard_state[k & 0x7f] = new;

	if (previous != new) {
		return k;
	}
	return 0;
}

int keyboard_toascii(int scan) {

	if(scan >= 0x80)
			return 0;

	if (keyboard_state[KEY_LEFT_SHIFT] == 0) {
		shift = 0;
	}
	else
	{
		shift = 1;
	}


	return keyboard_to_scan[scan + shift * 0x80];
}

int keyboard_get() {
	return inb(0x0060);
}

int keyboard_press() {
	return inb(0x0061);
}

/*** This file is part of FragmentFramework project ***/

#ifndef FFW_CONSTANTS
#define FFW_CONSTANTS

namespace ffw {
	/*!
	 * @memberof ffw
	 * @brief Image pixel format enum
	 * @see getOpenGLFormat
	 * @details Use this to check pixel format of images.
	 *
	 * To get OpenGL texture format out of this enum, use function ffw::getOpenGLFormat()
	 * 
	 * | Enum value           | Red bits | Green bits | Blue bits | Alpha bits |
	 * |----------------------|----------|------------|-----------|------------|
	 * | BITMAP\_1            |     1    |      0     |     0     |      0     |
	 * | GRAYSCALE\_4         |     4    |      0     |     0     |      0     |
	 * | GRAYSCALE\_8         |     8    |      0     |     0     |      0     |
	 * | GRAYSCALE\_16        |     16   |      0     |     0     |      0     |
	 * | GRAYSCALE\_32        |     32   |      0     |     0     |      0     |
	 * | GRAYSCALE\_ALPHA\_4  |     4    |      0     |     0     |      4     |
	 * | GRAYSCALE\_ALPHA\_8  |     8    |      0     |     0     |      8     |
	 * | GRAYSCALE\_ALPHA\_16 |     16   |      0     |     0     |      16    |
	 * | GRAYSCALE\_ALPHA\_32 |     32   |      0     |     0     |      32    |
	 * | GRB\_565             |     5    |      6     |     5     |      0     |
	 * | RGB\_888             |     8    |      8     |     8     |      0     |
	 * | RGB\_161616          |     16   |      16    |     16    |      0     |
	 * | RGB\_323232          |     32   |      32    |     32    |      0     |
	 * | RGB\_ALPHA\_5551     |     5    |      5     |     5     |      1     |
	 * | RGB\_ALPHA\_4444     |     4    |      4     |     4     |      4     |
	 * | RGB\_ALPHA\_8888     |     8    |      8     |     8     |      8     |
	 * | RGB\_ALPHA\_16161616 |     16   |      16    |     16    |      16    |
	 * | RGB\_ALPHA\_32323232 |     32   |      32    |     32    |      32    |
	 */
	enum imageType {
        BITMAP_1 = 1,
        GRAYSCALE_4 = 2,
        GRAYSCALE_ALPHA_4 = 3,
        GRAYSCALE_8 = 4,
        GRAYSCALE_ALPHA_8 = 5,
        GRAYSCALE_16 = 6,
        GRAYSCALE_ALPHA_16 = 7,
        GRAYSCALE_32 = 8,
        GRAYSCALE_ALPHA_32 = 9,
        RGB_565 = 10,
        RGB_888 = 11,
        RGB_161616 = 12,
        RGB_323232 = 13,
        RGB_ALPHA_5551 = 14,
        RGB_ALPHA_4444 = 15,
        RGB_ALPHA_8888 = 16,
        RGB_ALPHA_16161616 = 17,
        RGB_ALPHA_32323232 = 18,
    };
	
	/*!
	 * @memberof ffw
	 * @brief Mouse button enum
	 * @details Use this to check which mouse button
	 * has been used. To check press/release use enum 
	 * called mode.
	 * 
	 * Values:
	 *
	 * * left - Left mouse button
	 * * right - Right mouse button
	 * * middle - Middle mouse button
	 * * xbutton1 - First extra mouse button
	 * * xbutton2 - Second extra mouse button
	 * @see mode
	 */
	enum mouseButton {
		left = 0,
		right = 1,
		middle = 2,
		xbutton1 = 3,
		xbutton2 = 4,
	};
	/*!
	 * @memberof ffw
	 * @brief Mouse & kayboard button mode enum
	 * @details Use this to check if a mouse button
	 * or keyboard button has been pressed, released, or
	 * is repeating.
	 * 
	 * Values:
	 * 
	 * * pressed
	 * * released
	 * * repeat - Only used by keyboard
	 */
	enum mode {
		pressed = 1,
		released = 0,
		repeat = 2,
	};
	/*!
	 * @memberof ffw
	 * @brief Keyboard key codes enum
	 * @details Use this to check for keyboard keys in
	 * an event function.
	 * 
	 * Values:
	 *
	 * __ Unknown character __
	 * * key::unknown
	 * 
	 * __ Basic characters from A to Z __
	 * * key::a, key::b, key::c, ... , key::z
	 * 
	 * __ Numbers at the top row of the keyboard __
	 * * key::num\_0, key::num\_1, ... , key::num\_9
	 * 
	 * __ Numbers on the numeric keypad __
	 * * key::numpad\_0, key::numpad\_1, ... , key::numpad\_9
	 * 
	 * __ Other keys on the numeric kaypad __
	 * * key::numpadDivide "/"
	 * * key::numpadMultiply "\*"
	 * * key::numpadSubstract "-"
	 * * key::numpadAdd "+"
	 * * key::numpadEnter
	 * * key::numpadDecimal "." or ","
	 * * key::numpadEqual "="
	 * 
	 * __ Functions keys __
	 * * key::F1, key::F2, ... , key::F25
	 * 
	 * __ Other character keys __
	 * * key::apostrophe - "'"
	 * * key::comma ","
	 * * key::period "."
	 * * key::minus "-"
	 * * key::plus "+"
	 * * key::slash "/"
	 * * key::space
	 * * key::semicolon ":"
	 * * key::equal "="
	 * * key::bracketLeft "("
	 * * key::bracketRight ")"
	 * * key::backslash "\"
	 * * key::graveAccent "\`"
	 * * key::tab
	 * * key::world\_1, key::world\_2 - Keys depend on keyboard language
	 *
	 * __ Special keys __
	 * * key::escape
	 * * key::enter
	 * * key::backspace
	 * * key::insert
	 * * key::deleteKey
	 * * key::arrowLeft, key::arrowRight, key::arrowUp, key::arrowDown
	 * * key::pageUp, kay::pageDown
	 * * key::home
	 * * key::end
	 * * key::capsLock
	 * * key::scrollLock
	 * * key::numLock
	 * * key::printScreen
	 * * key::pause
	 * * key::shiftLeft, key::shiftRight
	 * * key::altLeft, key::altRight
	 * * key::superLeft, key::superRight
	 * * key::shiftleft, key::shiftRight
	 * * key::menu
	 * * key::separator
	 *
	 * __ Special function keys __
	 *
	 * (not all keyboards support these keys and
	 * only available in User Interface (class ffw::uiWindow)
	 *
	 * * key::browserBack
	 * * key::browserFavorites
	 * * key::browserForward
	 * * key::browserHome
	 * * key::browserRefresh
	 * * key::browserSearch
	 * * key::browserStop
	 * * key::mediaMute
	 * * key::mediaVolumeDown, key::mediaVolumeUp
	 * * key::mediaNext
	 * * key::mediaPrev
	 * * key::mediaStop
	 * * key::mediaPlay
	 * * key::mediaMail
	 * * key::mediaSelect
	 * * key::mediaApp1
	 * * key::mediaApp2
	 */
	enum key {
		unknown = -1,
		space = 32,
		apostrophe = 39,
		comma = 44,
		minus = 45,
		period = 46,
		slash = 47,
		num_0 = 48,
		num_1 = 49,
		num_2 = 50,
		num_3 = 51,
		num_4 = 52,
		num_5 = 53,
		num_6 = 54,
		num_7 = 55,
		num_8 = 56,
		num_9 = 57,
		semicolon = 59,
		equal = 61,
		a = 65,
		b = 66,
		c = 67,
		d = 68,
		e = 69,
		f = 70,
		g = 71,
		h = 72,
		i = 73,
		j = 74,
		k = 75,
		l = 76,
		m = 77,
		n = 78,
		o = 79,
		p = 80,
		q = 81,
		r = 82,
		s = 83,
		t = 84,
		u = 85,
		v = 86,
		w = 87,
		x = 88,
		y = 89,
		z = 90,
		bracketLeft = 91,
		backslash = 92,
		bracketRight = 93,
		graveAccent = 96,
		world_1 = 161,
		world_2 = 162,
		escape = 256,
		enter = 257,
		tab = 258,
		backspace = 259,
		insert = 260,
		deleteKey = 261,
		arrowRight = 262,
		arrowLeft = 263,
		arrowDown = 264,
		arrowUp = 265,
		pageUp = 266,
		pageDown = 267,
		home = 268,
		end = 269,
		capsLock = 280,
		scrollLock = 281,
		numLock = 282,
		printScreen = 283,
		pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		numpad_0 = 320,
		numpad_1 = 321,
		numpad_2 = 322,
		numpad_3 = 323,
		numpad_4 = 324,
		numpad_5 = 325,
		numpad_6 = 326,
		numpad_7 = 327,
		numpad_8 = 328,
		numpad_9 = 329,
		numpadDecimal = 330,
		numpadDivide = 331,
		numpadMultiply = 332,
		numpadSubstract = 333,
		numpadAdd = 334,
		numpadEnter = 335,
		numpadEqual = 336,
		shiftLeft = 340,
		controlLeft = 341,
		altLeft = 342,
		superLeft = 343,
		shiftRight = 344,
		controlRight = 345,
		altRight = 346,
		superRight = 347,
		menu = 348,
		last = 348,
		clear = 348,
		separator = 349,
		select = 350,
		zoom = 351,
		browserBack = 352,
		browserFavorites = 353,
		browserForward = 354,
		browserHome = 353,
		browserRefresh = 354,
		browserSearch = 355,
		browserStop = 356,
		mediaMute = 357,
		mediaVolumeDown = 358,
		mediaVolumeUp = 359,
		mediaNext = 360,
		mediaPrev = 361,
		mediaStop = 362,
		mediaPlay = 363,
		mediaMail = 364,
		mediaSelect = 365,
		mediaApp1 = 366,
		mediaApp2 = 367,
	};

	//8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0, 44100.0, 48000.0, 88200.0, 96000.0, 192000.0}
};

#endif
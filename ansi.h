/*
 * ANSI-Project: C
 * 
 * Make quick ANSI formats to beautify terminal output
 * 
 * @see https://github.com/bruneo32/ANSI-Project
 * @see https://en.wikipedia.org/wiki/ANSI_escape_code
 * 
 * @author Bruno Castro
 * @version 1.0
 * @since January 2022
 */


#ifndef _ANSI_H
#define _ANSI_H


#ifndef ANSI_ESC
	#define ANSI_ESC	"\x1B"
#endif
#ifndef ANSI_CSI
	#define ANSI_CSI	"\x9B"
#endif
#ifndef ANSI_DSC
	#define ANSI_DSC	"\x90"
#endif
#ifndef ANSI_OSC
	#define ANSI_OSC	"\x9D"
#endif


/*
 *  Colors	[quick]
 */

// BASIC
#define ANSI_RESET			ANSI_ESC "[0m"

#define ANSI_BOLD			ANSI_ESC "[1m"
#define ANSI_FAINT			ANSI_ESC "[2m"
#define ANSI_ITALIC			ANSI_ESC "[3m"
#define ANSI_UNDER			ANSI_ESC "[4m"
#define ANSI_SBLINK			ANSI_ESC "[5m"
#define ANSI_RBLINK			ANSI_ESC "[6m"
#define ANSI_REVERSE		ANSI_ESC "[7m"
#define ANSI_HIDE			ANSI_ESC "[8m"
#define ANSI_STRIKE			ANSI_ESC "[9m"

/**
 * Default font
 */
#define ANSI_DEF_FONT		ANSI_ESC "[10m"

/**
 * Rarely supported font
 */
#define ANSI_Franktur		ANSI_ESC "[20m"

#define ANSI_BOLD_OFF		ANSI_ESC "[21m"
#define ANSI_HI_OFF			ANSI_ESC "[22m"
#define ANSI_ITALIC_OFF		ANSI_ESC "[23m"
#define ANSI_UNDER_OFF		ANSI_ESC "[24m"
#define ANSI_BLINK_OFF		ANSI_ESC "[25m"
#define ANSI_REVERSE_OFF	ANSI_ESC "[27m"
#define ANSI_REVEAL			ANSI_ESC "[28m"
#define ANSI_STRIKE_OFF		ANSI_ESC "[29m"

// FOREGROUND
#define ANSI_BLACK			ANSI_ESC "[30m"
#define ANSI_RED			ANSI_ESC "[31m"
#define ANSI_GREEN			ANSI_ESC "[32m"
#define ANSI_YELLOW			ANSI_ESC "[33m"
#define ANSI_BLUE			ANSI_ESC "[34m"
#define ANSI_PURPLE			ANSI_ESC "[35m"
#define ANSI_CYAN			ANSI_ESC "[36m"
#define ANSI_WHITE			ANSI_ESC "[37m"

#define ANSI_DEFAULT		ANSI_ESC "[39m"

// BACKGROUND
#define ANSI_BK_BLACK		ANSI_ESC "[40m"
#define ANSI_BK_RED			ANSI_ESC "[41m"
#define ANSI_BK_GREEN		ANSI_ESC "[42m"
#define ANSI_BK_YELLOW		ANSI_ESC "[43m"
#define ANSI_BK_BLUE		ANSI_ESC "[44m"
#define ANSI_BK_PURPLE		ANSI_ESC "[45m"
#define ANSI_BK_CYAN		ANSI_ESC "[46m"
#define ANSI_BK_WHITE		ANSI_ESC "[47m"

#define ANSI_BK_DEFAULT		ANSI_ESC "[49m"

// HIGH INTENSITY
#define ANSI_BLACK_HI		ANSI_ESC "[90m"
#define ANSI_RED_HI			ANSI_ESC "[91m"
#define ANSI_GREEN_HI		ANSI_ESC "[92m"
#define ANSI_YELLOW_HI		ANSI_ESC "[93m"
#define ANSI_BLUE_HI		ANSI_ESC "[94m"
#define ANSI_PURPLE_HI		ANSI_ESC "[95m"
#define ANSI_CYAN_HI		ANSI_ESC "[96m"
#define ANSI_WHITE_HI		ANSI_ESC "[97m"


// HI BACKGROUND
#define ANSI_BK_BLACK_HI	ANSI_ESC "[100m"
#define ANSI_BK_RED_HI		ANSI_ESC "[101m"
#define ANSI_BK_GREEN_HI	ANSI_ESC "[102m"
#define ANSI_BK_YELLOW_HI	ANSI_ESC "[103m"
#define ANSI_BK_BLUE_HI		ANSI_ESC "[104m"
#define ANSI_BK_PURPLE_HI	ANSI_ESC "[105m"
#define ANSI_BK_CYAN_HI		ANSI_ESC "[106m"
#define ANSI_BK_WHITE_HI	ANSI_ESC "[107m"


/*
 *  Colors	[bake]
 */

/**
 * Sets colors and style of the characters following this code
 * Example: ANSI_SGR(40;91) makes RED_HI over BK_BLACK
 * 
 * @param str
 */
#define ANSI_SGR(str)			ANSI_ESC "[" #str "m"

/**
 * Specify the Foreground color in RGB
 * 
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return String to be printed
 */
#define ANSI_RGB(r, g, b)		ANSI_ESC "[38;2;" #r ";" #g ";" #b "m"

/**
 * Specify the Background color in RGB
 * 
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return String to be printed
 */
#define ANSI_BK_RGB(r, g, b)	ANSI_ESC "[48;2;" #r ";" #g ";" #b "m"



/*
 *  CONTROLS	[quick]
 */

/**
 * Place the cursor in top-left corner
 * Same as CUP(1,1)
 * 
 * @return ESC [1;1H
 */
#define ANSI_C0			ANSI_ESC "[1;1H"

/**
 * Move the cursor 1 row up
 * 
 * @return ESC [1A
 */
#define ANSI_CUU1		ANSI_ESC "[1A"

/**
 * Move the cursor 1 row down
 * 
 * @return ESC [1B
 */
#define ANSI_CUD1		ANSI_ESC "[1B"

/**
 * Move the cursor 1 cell forwards
 * 
 * @return ESC [1C
 */
#define ANSI_CUF1		ANSI_ESC "[1C"

/**
 * Move the cursor 1 cell backwards
 * 
 * @return ESC [1D
 */
#define ANSI_CUB1		ANSI_ESC "[1D"

/**
 * Moves cursor to beginning of the next line
 * 
 * @return ESC [1E
 */
#define ANSI_CNL1		ANSI_ESC "[1E"

/**
 * Moves cursor to beginning of the previous line
 * 
 * @return ESC [1F
 */
#define ANSI_CPL1		ANSI_ESC "[1F"

/**
 * Scroll whole page up by 1 line
 * 
 * @return ESC [1S
 */
#define ANSI_SU1		ANSI_ESC "[1S"

/**
 * Scroll whole page down by 1 line
 * 
 * @return ESC [1T
 */
#define ANSI_SD1		ANSI_ESC "[1T"

/**
 * Clear from cursor to end of screen.
 * 
 * @return ESC [0J
 */
#define ANSI_ED0		ANSI_ESC "[0J"

/**
 * Clear from cursor to beginning of the screen
 * 
 * @return ESC [1J
 */
#define ANSI_ED1		ANSI_ESC "[1J"

/**
 * Clear entire screen (and moves cursor to upper left on DOS ANSI.SYS)
 * 
 * @return ESC [2J
 */
#define ANSI_ED2		ANSI_ESC "[2J"

/**
 * Clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications)
 * 
 * @return ESC [3J
 */
#define ANSI_ED3		ANSI_ESC "[3J"


/**
 * Clear from cursor to the end of the line
 * 
 * @return ESC [0K
 */
#define ANSI_EL0		ANSI_ESC "[0K"

/**
 * Clear from cursor to beginning of the line
 * 
 * @return ESC [1K
 */
#define ANSI_EL1		ANSI_ESC "[1K"

/**
 * Clear entire line. Cursor position does not change.
 * 
 * @return ESC [2K
 */
#define ANSI_EL2		ANSI_ESC "[2K"


/**
 * Enable aux serial port usually for local serial printer
 * 
 * @return ESC [5i
 */
#define ANSI_AUX_PORT_ON		ANSI_ESC "[5i"

/**
 * Enable aux serial port usually for local serial printer
 * 
 * @return ESC [4i
 */
#define ANSI_AUX_PORT_OFF		ANSI_ESC "[4i"

/**
 * Reports the cursor position (CPR) by transmitting ESC[n;mR, where n is the row and m is the column.
 * 
 * @return ESC [6n
 */
#define ANSI_DSR		ANSI_ESC "[6n"

/**
 * Saves the cursor position/state in SCO console mode
 * In vertical split screen mode, instead used to set (as CSI n ; n s) or reset left and right margins.
 * 
 * @return ESC [s
 */
#define ANSI_SCP		ANSI_ESC "[s"

/**
 * Restores the cursor position/state in SCO console mode.
 * 
 * @return ESC [u
 */
#define ANSI_RCP		ANSI_ESC "[u"


/*
 *  CONTROLS	[bake]
 */

/**
 * Moves the cursor n (default 1) cells up
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CUU(n)			ANSI_ESC "[" #n "A"

/**
 * Moves the cursor n (default 1) cells down
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CUD(n)			ANSI_ESC "[" #n "B"

/**
 * Moves the cursor n (default 1) cells forwards
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CUF(n)			ANSI_ESC "[" #n "C"

/**
 * Moves the cursor n (default 1) cells backwards
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CUB(n)			ANSI_ESC "[" #n "D"


/**
 * Moves cursor to beginning of the line n (default 1) lines down.
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CNL(n)			ANSI_ESC "[" #n "E"

/**
 * Moves cursor to beginning of the line n (default 1) lines up.
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CPL(n)			ANSI_ESC "[" #n "F"

/**
 * Moves the cursor to column n (default 1)
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_CHA(n)			ANSI_ESC "[" #n "G"

/**
 * Moves the cursor to [row, column]. The values are 1-based.
 * 
 * @param row
 * @param col
 * @return String to be printed
 */
#define ANSI_CUP(row, col)	ANSI_ESC "[" #row ";" #col "H"


/**
 * Clears part of the screen.
 * If n is 0 (or missing), clear from cursor to end of screen.
 * If n is 1, clear from cursor to beginning of the screen.
 * If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS).
 * If n is 3, clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications).
 *
 * @param n
 * @return String to be printed
 */
#define ANSI_ED(n)			ANSI_ESC "[" #n "J"

/**
 * Erases part of the line
 * If n is 0 (or missing), clear from cursor to the end of the line
 * If n is 1, clear from cursor to beginning of the line
 * If n is 2, clear entire line. Cursor position does not change.
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_EL(n)			ANSI_ESC "[" #n "K"

/**
 * Scroll whole page up by n (default 1) lines. New lines are added at the bottom. (not ANSI.SYS)
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_SU(n)			ANSI_ESC "[" #n "S"

/**
 * Scroll whole page down by n (default 1) lines. New lines are added at the top. (not ANSI.SYS)
 * 
 * @param n
 * @return String to be printed
 */
#define ANSI_SD(n)			ANSI_ESC "[" #n "T"

/**
 * Same as CUP, but counts as a format effector function (like CR or LF) rather than an editor function (like CUD or CNL)
 * This can lead to different handling in certain terminal modes
 * 
 * @param row
 * @param col
 * @return String to be printed
 */
#define ANSI_HVP(row, col)	ANSI_ESC "[" #row ";" #col "f"


/*
 * CUSTOM
 */

/**
 * Returns a custom ANSI ESCAPE SEQUENCE
 * 
 * @param str
 * @return ESC "[" str
 */
#define ANSI_custom(str)	ANSI_ESC "[" #str



#ifdef __cplusplus
	/*
	 * Code for C++ only
	 */

	/**
	 * Namespace only for C++
	 */
	namespace ansi {
		
		std::string ESC = std::string(ANSI_ESC);
		std::string CSI = std::string(ANSI_CSI);
		std::string DSC = std::string(ANSI_DSC);
		std::string OSC = std::string(ANSI_OSC);

		/*
		 *  Colors	[bake]
		 */

		/**
		 * Sets colors and style of the characters following this code
		 * Example: ansi::SGR("40;91") makes RED_HI over BK_BLACK
		 * 
		 * @param str
		 * @return (std::string) String to be printed
		 */
		std::string SGR(std::string str) {
			return	ansi::ESC+"["+str+"m";
		}

		/**
		 * Specify the Foreground color in RGB
		 * 
		 * @param r Red value
		 * @param g Green value
		 * @param b Blue value
		 * @return (std::string) String to be printed
		 */
		std::string RGB(int r, int g, int b) {
			return	ansi::ESC+"[38;2;"+
					std::to_string(r)+";"+
					std::to_string(g)+";"+
					std::to_string(b)+"m";
		}

		/**
		 * Specify the Background color in RGB
		 * 
		 * @param r Red value
		 * @param g Green value
		 * @param b Blue value
		 * @return (std::string) String to be printed
		 */
		std::string BK_RGB(int r, int g, int b) {
			return	ansi::ESC+"[48;2;"+
					std::to_string(r)+";"+
					std::to_string(g)+";"+
					std::to_string(b)+"m";
		}


		/*
		 *  CONTROLS	[bake]
		 */

		/**
		 * Moves the cursor n (default 1) cells up
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CUU(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"A";
		}

		/**
		 * Moves the cursor n (default 1) cells down
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CUD(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"B";
		}

		/**
		 * Moves the cursor n (default 1) cells forwards
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CUF(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"C";
		}

		/**
		 * Moves the cursor n (default 1) cells backwards
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CUB(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"D";
		}


		/**
		 * Moves cursor to beginning of the line n (default 1) lines down.
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CNL(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"E";
		}

		/**
		 * Moves cursor to beginning of the line n (default 1) lines up.
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CPL(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"F";
		}

		/**
		 * Moves the cursor to column n (default 1)
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string CHA(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"G";
		}

		/**
		 * Moves the cursor to [row, column]. The values are 1-based.
		 * 
		 * @param row
		 * @param col
		 * @return (std::string) String to be printed
		 */
		std::string CUP(int row, int col) {
			return	ansi::ESC+"["+ std::to_string(row)+";"+std::to_string(col) +"H";
		}


		/**
		 * Clears part of the screen.
		 * If n is 0 (or missing), clear from cursor to end of screen.
		 * If n is 1, clear from cursor to beginning of the screen.
		 * If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS).
		 * If n is 3, clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications).
		 *
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string ED(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"J";
		}

		/**
		 * Erases part of the line
		 * If n is 0 (or missing), clear from cursor to the end of the line
		 * If n is 1, clear from cursor to beginning of the line
		 * If n is 2, clear entire line. Cursor position does not change.
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string EL(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"K";
		}

		/**
		 * Scroll whole page up by n (default 1) lines. New lines are added at the bottom. (not ANSI.SYS)
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string SU(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"S";
		}

		/**
		 * Scroll whole page down by n (default 1) lines. New lines are added at the top. (not ANSI.SYS)
		 * 
		 * @param n
		 * @return (std::string) String to be printed
		 */
		std::string SD(int n) {
			return	ansi::ESC+"["+ std::to_string(n) +"T";
		}

		/**
		 * Same as CUP, but counts as a format effector function (like CR or LF) rather than an editor function (like CUD or CNL)
		 * This can lead to different handling in certain terminal modes
		 * 
		 * @param row
		 * @param col
		 * @return (std::string) String to be printed
		 */
		std::string HVP(int row, int col) {
			return	ansi::ESC+"["+ std::to_string(row)+";"+std::to_string(col) +"f";
		}


		/*
		 * CUSTOM
		 */

		/**
		 * Returns a custom ANSI ESCAPE SEQUENCE
		 * 
		 * @param str
		 * @return (std::string) ESC + "[" + str
		 */
		std::string custom(std::string str) {
			return	ansi::ESC+"["+str;
		}

	}

#endif // __cplusplus

#endif // _ANSI_H

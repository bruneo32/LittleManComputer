/*
 * Little Man Computer
 * [Runtime Interpreter]
 * 
 * @see https://github.com/bruneo32/LittleManComputer
 * @see https://en.wikipedia.org/wiki/Little_man_computer
 * 
 * @author Bruno Castro
 * @version 1.0
 * @since January 2022
 */


#include <stdio.h>
#include "ansi.h"

#define bool		char
#define true		1
#define false		0


bool debug=false;

// Numbers from 0-99 does not need int so... char
char pc = 0;
short ax = 0;
bool neg = false;

short mailbox[100]; // Data max is 99, but opcodes are 999

// Functions
char cton(char);
char loadmailbox(char*,short);
char loadmailboxfile(char*);

int main(int argc, char *argv[]){
	
	// Parse args
	if(argc<2){
		printf(	ANSI_RED_HI "No file specified." ANSI_RESET"\n\n"
				ANSI_BOLD"Usage:" ANSI_RESET "\n"
				"        From File:   " ANSI_YELLOW_HI "lmc " ANSI_CYAN_HI ANSI_UNDER "file.txt" ANSI_RESET"\n"
				"  Debug From File:   " ANSI_YELLOW_HI "lmc " ANSI_RESET"+" ANSI_CYAN_HI ANSI_UNDER "file.txt" ANSI_RESET"\n"
				"        Immediate:   " ANSI_YELLOW_HI "lmc " ANSI_RESET":" ANSI_CYAN_HI"901308901309508209902000" ANSI_RESET"\n"
				"  Debug Immediate:   " ANSI_YELLOW_HI "lmc " ANSI_RESET"+:" ANSI_CYAN_HI"901308901309508209902000" ANSI_RESET"\n");
		printf(ANSI_RESET "\n");
		return 1;
	}
	
	
	if(argv[1][0] == '+'){
		// Debug mode
		debug=true;

		if(argv[1][1] == ':'){
			// Debug imm
			if(loadmailbox(argv[1], 2)){return 1;}
		}else{
			// Debug file

			if(loadmailboxfile((argv[1]+1))){return 1;}
		}

	}else if(argv[1][0] == ':'){
		// Load imm to mailbox
		
		if(loadmailbox(argv[1], 1)){return 1;}
		
	}else{
		// Load from file
		if(loadmailboxfile(argv[1])){return 1;}
	}
	
	
	// Execute program
	while(pc<100){
		
		short code = mailbox[pc];
		short opcode = code/100*100;
		
		if(debug){
			if(pc!=0){
				char ignore;
				scanf("%c", &ignore);
			}

			printf(ANSI_ED2 ANSI_C0);
			fflush(stdout);

			printf(ANSI_UNDER " LMC + DEBUG MODE" ANSI_EL0 ANSI_RESET "\n");
			printf(ANSI_BK_GREEN ANSI_BLACK " AX: %03i " ANSI_RESET" " ANSI_BK_RED "    %c    " ANSI_RESET" " ANSI_BK_CYAN ANSI_BLACK" PC: %03i " ANSI_RESET" \n", ax, (neg?'-':'+'), pc);

			for(char i=0; i<100; i++){
				printf("%s%s" ANSI_BLACK " %2i: " ANSI_PURPLE"%03i " ANSI_RESET, (i%10==0)? "\n":" ", (pc==i?ANSI_BK_CYAN:ANSI_BK_WHITE), i, mailbox[i]);
			}
			printf(ANSI_RESET"\n" ANSI_UNDER " [ENTER] = step"ANSI_EL0 "\n\n" ANSI_RESET);
		}


		if(mailbox[pc] == 000){
			// 000	HLT
			// Stop working/end the program.
			
			break;
			
		}else if(mailbox[pc] == 901){
			// 901	INPUT
			// Go to the INBOX, fetch the value from the user, and put it in the accumulator (calculator)
			
			printf("INPUT: " ANSI_CYAN_HI);
			scanf("%hd", &ax);
			printf(ANSI_RESET);
			
		}else if(mailbox[pc] == 902){
			// 902	OUTPUT
			// Copy the value from the accumulator (calculator) to the OUTBOX.
			
			printf("OUTPUT: " ANSI_YELLOW_HI "%i" ANSI_RESET "\n",ax);
			
		}else
		
		if(opcode == 100){
			// 1xx	ADD
			// Add the value stored in mailbox xx to whatever value is currently on the accumulator (calculator).
			
			short xx = code-opcode;
			ax += mailbox[xx];
			
		}else if(opcode == 200){
			// 2xx	SUB
			// Subtract the value stored in mailbox xx from whatever value is currently on the accumulator (calculator). If value is below 0, a negative flag is set
			
			short xx = code-opcode;
			ax -= mailbox[xx];
			if(ax<0){neg=true;}else{neg=false;}
			
		}else if(opcode == 300){
			// 3xx	STA
			// Store the contents of the accumulator in mailbox xx (destructive).
			
			short xx = code-opcode;
			mailbox[xx] = ax;
			
		}
			// 4xx	??? (this is a benefit for arrays,)
		 else if(opcode == 500){
			// 5xx	LDA
			// Load the value from mailbox xx (non-destructive) and enter it in the accumulator (destructive).
			
			short xx = code-opcode;
			ax = mailbox[xx];
			
		}else if(opcode == 600){
			// 6xx	BRA
			// Set the program counter to the given address (value xx). That is, the value in mailbox xx will be the next instruction executed.
			
			short xx = code-opcode;
			pc = xx;
			continue;
			
		}else if(opcode == 700){
			// 7xx	BRZ
			// If the accumulator (calculator) contains the value 000, set the program counter to the value xx. Otherwise, do nothing.
			
			short xx = code-opcode;
			
			if(ax==0){
				pc = xx;
				continue;
			}
			
		}else if(opcode == 800){
			// 8xx	BRP
			// If the accumulator (calculator) is 0 or positive, set the program counter to the value xx. Otherwise, do nothing.
			
			short xx = code-opcode;
			
			if(ax >= 0){
				pc = xx;
				continue;
			}
			
		}else{
			// Unknown opcode
			printf(ANSI_RED_HI "Error: Unknown opcode '" ANSI_CYAN_HI "%03i" ANSI_RED_HI "'", code);
			printf(ANSI_RESET  "\n");
			return 1;
		}

		pc++;
	}
	
	
	// End
	printf(ANSI_RESET "\n");
	return 0;
}

char cton(char c){
	// ASCII based
	// @see: https://www.asciitable.com
	
	// If any whitespace return 10
	if(c<=' '){return 10;}
	
	// If error: Return 0xFF
	if(c<'0' || c>'9'){return -1;}
	
	return (c-'0');
}

char loadmailbox(char *input, short offset){
	short i=offset;
	char mbi=0;
	while(input[i]!=0 && i<300){
		
		// Repeat 3 times
		for(char _t=3; _t>0; _t--){
			if(input[i]==0){break;}
			
			char x = cton(input[i]);
			if(x==10){
				i++;
				_t--;
				continue;
			}else if(x==-1){
				printf(ANSI_RED_HI "Error: Non-numeric character '" ANSI_CYAN_HI "%c" ANSI_RED_HI "' given at position " ANSI_YELLOW_HI "%i", input[i], i-offset);
				printf(ANSI_RESET  "\n");
				return 1;
			}
			
			mailbox[mbi] *= 10;
			mailbox[mbi] += x;
			i++;
		}
		
		mbi++;
	}
	return 0;
}

char loadmailboxfile(char *input){
	FILE *fp = fopen(input, "r");
	if(!fp){
		printf(ANSI_RED_HI "Error: Cannot open " ANSI_UNDER ANSI_YELLOW_HI "%s" ANSI_UNDER_OFF ANSI_RED_HI " or file not found", input);
		printf(ANSI_RESET  "\n");
		return 1;
	}
	
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);


	char filestr[fsize+1];
	*(filestr+fsize) = 0;

	fread(filestr, sizeof(filestr[0]), fsize, fp);
	fclose(fp);


	loadmailbox(filestr, 0);
}

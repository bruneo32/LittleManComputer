/*
 * Little Man Computer
 * [Assembler]
 * 
 * @see https://github.com/bruneo32/LittleManComputer
 * @see https://en.wikipedia.org/wiki/Little_man_computer
 * 
 * @author Bruno Castro
 * @version 1.0
 * @since January 2022
 */

#include <stdio.h>
#include <string.h>
#include "ansi.h"

#define bool		char
#define true		1
#define false		0


FILE *fp;


#define TT_INSTR	1
#define TT_NUMBR	2
#define TT_LABEL	3

#define tvalc 16
struct Token{
    char type;
    char value[tvalc+1];
	short mbi; // Mailbox Index [0-99]

	int line;
	int pos;
};


void clearstr(char*, int);
bool isInstr(char*);
short atos(char *str);
void printError(char*, struct Token, char*, char*);

int main(int argc, char *argv[]){
	
	// Parse args
	if(argc<2){
		printf(	ANSI_RED_HI "No file specified." ANSI_RESET"\n\n"
				ANSI_BOLD"Usage:" ANSI_BOLD_OFF"\n"
				"    " ANSI_YELLOW_HI "lma " ANSI_CYAN_HI ANSI_UNDER "inputfile.txt" ANSI_RESET ANSI_PURPLE_HI " > "ANSI_UNDER"outputfile.lmc" ANSI_RESET"\n");
		printf(ANSI_RESET "\n");
		return 1;
	}


    // Read File
	fp = fopen(argv[1], "r");
	if(!fp){
		printf(ANSI_RED_HI "Error: Cannot open " ANSI_UNDER ANSI_YELLOW_HI "%s" ANSI_UNDER_OFF ANSI_RED_HI " or file not found", argv[1]);
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


	// Tokenize
	#define tc 200
	struct Token tokens[tc];
	int  t=0;
	long k=0;
	bool comment=false;

	int line=1;
	int pos=1;
	while(k<fsize){
		if(filestr[k]=='\r' || filestr[k]=='\n' && filestr[k-1]!='\r'){
			// New line
			if(comment){comment=false;}
		
			line++;
			pos=1;

			k++;
			continue;
		}
		if(comment){
			k++;
			continue;
		}

		if(filestr[k]==';' || filestr[k]=='/'){
			// Avoid comments
			comment=true;
		}else if(filestr[k] <= ' '){
			// Ignore whitespace

			// Do not overcount in CRLF
			if(filestr[k]!='\r' && filestr[k]!='\n'){pos++;}

			k++;
			continue;
		}else if(filestr[k]>='0' && filestr[k]<='9'){
			// Make number
			
			char numstr[4];
			clearstr(numstr, 4);
			for(char i=0; i<3; i++){
				if(filestr[k]<'0' || filestr[k]>'9'){break;}

				numstr[i] = filestr[k];

				if(i<2){k++;pos++;}
			}

			tokens[t].mbi = atos(numstr);
			tokens[t].type = TT_NUMBR;
			tokens[t].line = line;
			tokens[t].pos = pos;

			t++;
		}else{
			// Make from text
			
			char str[tvalc+1];
			clearstr(str, tvalc+1);
			for(char i=0; i<tvalc; i++){
				if(filestr[k]<=' '){break;}
				
				// Make UPPERCASE
				char x = filestr[k];
				if(x>='a' && x<='z'){x -= ('a'-'A');}

				str[i] = x;

				if(i<tvalc-1){k++;pos++;}
			}

			strcpy(tokens[t].value, str);

			if(isInstr(str)){
				tokens[t].type = TT_INSTR;
				tokens[t].mbi = 0; // If not defined
			}else{
				tokens[t].type = TT_LABEL;
				tokens[t].mbi = -1; // If not defined
			}
			tokens[t].line = line;
			tokens[t].pos = pos;
			
			t++;
		}

		k++;pos++;
	}
	tokens[t].type = 0; // Mark the end


	// Parse labels
	t=0;
	char mbi=0;
	while(tokens[t].type != 0){

		if(tokens[t].type == TT_INSTR){
			mbi++;
		}else if(tokens[t].type == TT_LABEL){
			if(tokens[t-1].type==TT_INSTR
			&& (strcmp(tokens[t-1].value, "ADD") == 0
			||  strcmp(tokens[t-1].value, "SUB") == 0
			||  strcmp(tokens[t-1].value, "STA") == 0
			||  strcmp(tokens[t-1].value, "LDA") == 0
			||  strcmp(tokens[t-1].value, "BRA") == 0
			||  strcmp(tokens[t-1].value, "BRZ") == 0
			||  strcmp(tokens[t-1].value, "BRP") == 0
			)){
				// This is not a label definition
				t++;
				continue;
			}

			int tt=0;
			while(tokens[tt].type != 0){
				
				if(tokens[tt].type == TT_LABEL && strcmp(tokens[t].value, tokens[tt].value)==0){
					tokens[tt].mbi = mbi;
				}

				tt++;
			}
		}

		t++;
	}


	// Debug tokens
	// for (int i = 0; i < tc; i++){
	// 	if(tokens[i].type==0){break;}
	// 	printf("[%3i, %10s, %3i | %i:%i ]\n", tokens[i].type, tokens[i].value, tokens[i].mbi, tokens[i].line, tokens[i].pos);
	// }
	

	// Assemble
	char outstr[300];
	k=0;
	t=0;
	while(tokens[t].type != 0){

		if(tokens[t].type == TT_NUMBR){
			// ERROR: Unexpected number
			printError(argv[1], tokens[t], "%s", "Instruction or Label expected, Number given");
			return 1;
		}else
		if(tokens[t].type == TT_INSTR){
			if(strcmp(tokens[t].value, "HLT") == 0
			|| strcmp(tokens[t].value, "CBO") == 0){
				// 000 HLT/CBO
				
				outstr[k] = '0';
				k++;
				outstr[k] = '0';
				k++;
				outstr[k] = '0';
				k++;

			}else if(strcmp(tokens[t].value, "INP") == 0){
				// 901	INP
				
				outstr[k] = '9';
				k++;
				outstr[k] = '0';
				k++;
				outstr[k] = '1';
				k++;

			}else if(strcmp(tokens[t].value, "OUT") == 0){
				// 901	INP
				
				outstr[k] = '9';
				k++;
				outstr[k] = '0';
				k++;
				outstr[k] = '2';
				k++;

			}else if(strcmp(tokens[t].value, "DAT") == 0){
				// xxx	DAT
				
				t++;
				if(tokens[t].type==TT_NUMBR){
					sprintf(&outstr[k], "%03i", tokens[t].mbi);
					k+=3;
				}else{
					t--;
					outstr[k] = '0';
					k++;
					outstr[k] = '0';
					k++;
					outstr[k] = '0';
					k++;
				}

			}else
			if(strcmp(tokens[t].value, "ADD") == 0){
				// 1xx	ADD
				outstr[k] = '1';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"ADD");
					return 1;
				}

			}else if(strcmp(tokens[t].value, "SUB") == 0){
				// 2xx	SUB
				outstr[k] = '2';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"SUB");
					return 1;
				}
			}else if(strcmp(tokens[t].value, "STA") == 0){
				// 3xx	STA
				outstr[k] = '3';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"STA");
					return 1;
				}
			}else if(strcmp(tokens[t].value, "LDA") == 0){
				// 5xx	LDA
				outstr[k] = '5';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"LDA");
					return 1;
				}
			}else if(strcmp(tokens[t].value, "BRA") == 0){
				// 6xx	BRA
				outstr[k] = '6';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"BRA");
					return 1;
				}
			}else if(strcmp(tokens[t].value, "BRZ") == 0){
				// 7xx	BRZ
				outstr[k] = '7';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"BRZ");
					return 1;
				}
			}else if(strcmp(tokens[t].value, "BRP") == 0){
				// 8xx	BRP
				outstr[k] = '8';
				k++;

				t++;
				if(tokens[t].type==TT_NUMBR || tokens[t].type==TT_LABEL){
					if(tokens[t].mbi == -1){
						// ERROR: Undefined label
						printError(argv[1], tokens[t], "Label '" ANSI_BLUE_HI"%s"ANSI_RED_HI "' is not defined", tokens[t].value);
						return 1;
					}

					sprintf(&outstr[k], "%02i", tokens[t].mbi);
					k+=2;
				}else{
					// ERROR: Expected argument
					printError(argv[1], tokens[t],
						"Expected Number or Label after " ANSI_BLUE_HI "%s" ANSI_RED_HI " Instruction",
						"BRP");
					return 1;
				}
			}
		}

		t++;
	}
	outstr[k]=0; // Mark the end

	// End
	printf("%s\n", outstr);
	return 0;
}

void clearstr(char *str, int size){
	for(int i=0; i<size; i++){
		str[i]=0;
	}
}

bool isInstr(char *str){

	if(strcmp(str, "ADD") == 0
	|| strcmp(str, "SUB") == 0
	|| strcmp(str, "STA") == 0
	|| strcmp(str, "LDA") == 0
	|| strcmp(str, "BRA") == 0
	|| strcmp(str, "BRZ") == 0
	|| strcmp(str, "BRP") == 0
	|| strcmp(str, "INP") == 0
	|| strcmp(str, "OUT") == 0
	|| strcmp(str, "HLT") == 0 || strcmp(str, "COB") == 0
	|| strcmp(str, "DAT") == 0
	){
		return true;
	}

	return false;
}

short atos(char *str){
	short s=0;
	while(*str != 0){
		if(*str<'0' || *str>'9'){return s;}

		s *= 10;
		s += (*str-'0');

		str++;
	}
	return s;
}

void printError(char* file, struct Token tok, char *format, char *arg){
	printf(ANSI_RED_HI "Error in file " ANSI_YELLOW_HI ANSI_UNDER "%s" ANSI_PURPLE_HI":%i:%i" ANSI_UNDER_OFF ANSI_RED_HI "\n", file, tok.line, tok.pos);
	
	printf(format, arg);
	
	printf(ANSI_RESET "\n\n");
}

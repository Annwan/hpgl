#include "hpgl.h"

#define UNKNOWNCOMMANDERROR(str) \
{char* msg="";\
sprintf(msg,"hpgl:parse: unknown operation `%c%c'",*str, *(str+1));\
log_error(msg);}


int untangleStr(HPGLArgument *li, char *buf, char delim, int maxlen){
	int i = 0;
	while(i < maxlen - 1 && li[i].c != delim){
		buf[i] = li[i].c;
		i++;
	}
	buf[i] = '\0';
	return i;
}

int parse(char *input, HPGLInstruction **prog) {
	int maxinstc = 32; 
	int curinstc = 0;
	*prog = malloc(maxinstc * sizeof(HPGLInstruction));
	if (*prog == NULL) {
		log_error("hpgl:parse: couldn't allocate enough memory for program");
		return -1;
	}
	char delim = '\3';
	char *msg = "";
	for(;;)
	{
		HPGLInstruction current;
		switch (*input)
		{
		case 'A': // AA,AF,AR
			switch (*(input+1))
			{
			case 'A':
				break;
			case 'F':
				break;
			case 'R':
				break;
			
			default:
				UNKNOWNCOMMANDERROR(input);
				free(*prog);
				*prog = NULL;
				return -1;
			}
			break;
		case 'B':
			if (*(input+1) == 'L') {
				current.cmd = hpgl_BL;
				input += parse_delimtext(input, &current, delim);
				input += readTerminator(input);
			} else {
				UNKNOWNCOMMANDERROR(input);
				free(*prog);
				*prog = NULL;
				return -1;
			}
			break;
		case 'C': // CA, CI, CP, CS, CT
			switch (*(input+1))
			{
			case 'A':
				current.cmd = hpgl_CA;
				input += 2;
				input += parse_n(input, &current);
				input += readTerminator(input);
				break;
			case 'I':
				current.cmd = hpgl_CI;
				input += 2;
				input += parse_no(input, &current);
				input += readTerminator(input);
				break;
			case 'P':
				current.cmd = hpgl_CP;
				input += 2;
				input += parse_oo(input, &current);
				input += readTerminator(input);
				break;
			case 'S':
				current.cmd = hpgl_CS;
				input += 2;
				input += parse_n(input, &current);
				input += readTerminator(input);
				break;
			case 'T':
				current.cmd = hpgl_CT;
				input += 2;
				input += parse_n(input, &current);
				input += readTerminator(input);
				break;
			default:
				UNKNOWNCOMMANDERROR(input);
				free(*prog);
				*prog = NULL;
				return -1;
			}
			break;
		case 'D': //DF, DI, DR, DT, DU, DV
			switch (*(input+1))
			{
			case 'F':
				current.cmd = hpgl_DF;
				input += 2;
				input += readTerminator(input);
				break;
			case 'I':
				current.cmd = hpgl_DI;
				input += 2;
				input += parse_nn(input, &current);
				input += readTerminator(input);
				break;
			case 'R':
				current.cmd = hpgl_DR;
				input += 2;
				input += parse_nn(input, &current);
				input += readTerminator(input);
				break;
			case 'T':
				input += 2;
				delim = *input;
				input++;
				input += readTerminator(input);
				sprintf(msg, "Delimiter is now `%c'", delim);
				log_notice(msg);
				break;
			case 'U':
				current.cmd = hpgl_DU;
				input += 2;
				input += parse_nn(input, &current);
				input += readTerminator(input);
				break;
			case 'V':
				current.cmd = hpgl_DV;
				input += 2;
				input += parse_n(input, &current);
				input += readTerminator(input);
			default:
				UNKNOWNCOMMANDERROR(input);
				free(*prog);
				*prog = NULL;
				return -1;
			}
			break;
		case 'E': // EA,EP,ER,ES,EW*/
			break;
		case 'F': // FP,FT
			break;
		case 'I': // IN,IP,IW
			break;
		case 'L': // LB,LO,LT
			break;
		case 'N': // NR
			if (*(input+1) == 'R') {
				current.cmd = hpgl_NR;
				current.argc = 0;
				input += 2;
				input += readTerminator(input);
			} else {
				UNKNOWNCOMMANDERROR(input);
				free(*prog);
				*prog = NULL;
				return -1;
			}
			break;
		case 'P':
			/* PA,PB,PD,PG,¨PM,PR,PS,PT,PU */
			break;
		case 'R':
			/* RA,RR,RO */
			break;
		case 'S':
			/* SA,SC,SI,SL,SP,SS,SR,SU */
			break;
		case 'W':
			/* WG */
			break;
		default:
			UNKNOWNCOMMANDERROR(input);
			free(*prog);
			*prog = NULL;
			return -1;
		}

		// if we filled 
		if (curinstc == maxinstc) {
			maxinstc *= 2;
			HPGLInstruction* t = realloc(prog, maxinstc * sizeof(HPGLInstruction));
			if (t == NULL) {
				free(*prog);
				*prog = NULL;
				log_error("hpgl:parse: couldn't allocate enough memory for program");
				return -1;
			} else {
				*prog = t;
			}
		}
	}
	return curinstc;
}

int readTerminator(char* input){
	switch (*input)
	{
	case '\n':
	case ';':
		return 1;
	case '\r':
		return 2;
	default:
		return 0;
	}
}

// TO DO: Actually implement those
int parse_oo(char *input, HPGLInstruction *instr){return 0;}
int parse_no(char *input, HPGLInstruction *instr){return 0;}
int parse_nn(char *input, HPGLInstruction *instr){return 0;}
int parse_n(char *input, HPGLInstruction *instr){return 0;}
int parse_delimtext(char *input, HPGLInstruction *instr, char delim){return 0;}
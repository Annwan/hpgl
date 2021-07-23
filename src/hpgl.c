#include "hpgl.h"

typedef struct ParserContext
{
	char* input;
	HPGLOpcode op;
	int instc;
	int maxinstc;
	HPGLInstruction* prog;
	char delim;
} ParserContext;

int parse_t(ParserContext *ctx){
	HPGLInstruction current;
	current.cmd = ctx->op;
	current.argc = 0;
	while(*(ctx->input) != ctx->delim){
		if (current.argc < 256) {
			HPGLArgument a = {.c = *(ctx->input++)};
			current.args[current.argc++] = a;
		}
	}
	ctx->input++; // consume the delimiter
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_0(ParserContext *ctx){
	HPGLInstruction current = {
		.cmd = ctx->op,
		.argc = 0
	};
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_4(ParserContext *ctx){
	HPGLInstruction current;
	current.cmd = ctx->op;
	
	HPGLArgument a,b,c,d;
	int argc = sscanf(ctx->input, "%f,%f,%f,%f", &(a.n), &(b.n), &(c.n), &(d.n));
	current.argc = argc;
	current.args[0] = a;
	current.args[1] = b;
	current.args[2] = c;
	current.args[3] = d;
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_n(ParserContext *ctx){
	HPGLInstruction current;
	current.cmd = ctx->op;
	int read;
	HPGLArgument a;
	while (sscanf(ctx->input, "%f,", &(a.n)) > 0 && current.argc < 256){
		current.args[current.argc++] = a;
	}
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_c(ParserContext *ctx){
	HPGLInstruction current;
	current.cmd = ctx->op;
	current.argc = 1;
	HPGLArgument a = {.c = *(ctx->input)};
	current.args[0] = a; 
	ctx->input++;
	ctx->delim = a.c;
	ctx->prog[ctx->instc++] = current;
	return 0;
}

struct {
	char cmd[2];
	HPGLOpcode op;
	int (*parser)(ParserContext*);
} jumpTable[50] = {
	{.cmd="AA",.op=hpgl_AA,.parser=parse_4},
	{.cmd="AF",.op=hpgl_AF,.parser=parse_0},
	{.cmd="AR",.op=hpgl_AR,.parser=parse_4},
	{.cmd="BL",.op=hpgl_BL,.parser=parse_t},
	{.cmd="CA",.op=hpgl_CA,.parser=parse_4},
	{.cmd="CI",.op=hpgl_CI,.parser=parse_4},
	{.cmd="CP",.op=hpgl_CP,.parser=parse_4},
	{.cmd="CS",.op=hpgl_CS,.parser=parse_4},
	{.cmd="CT",.op=hpgl_CT,.parser=parse_4},
	{.cmd="DF",.op=hpgl_DF,.parser=parse_0},
	{.cmd="DI",.op=hpgl_DI,.parser=parse_4},
	{.cmd="DR",.op=hpgl_DR,.parser=parse_4},
	{.cmd="DT",.op=hpgl_DT,.parser=parse_c},
	{.cmd="DU",.op=hpgl_DU,.parser=parse_4},
	{.cmd="DV",.op=hpgl_DV,.parser=parse_4},
	{.cmd="EA",.op=hpgl_EA,.parser=parse_4},
	{.cmd="EP",.op=hpgl_EP,.parser=parse_0},
	{.cmd="ER",.op=hpgl_ER,.parser=parse_4},
	{.cmd="ES",.op=hpgl_ES,.parser=parse_4},
	{.cmd="EW",.op=hpgl_EW,.parser=parse_4},
	{.cmd="FP",.op=hpgl_FP,.parser=parse_0},
	{.cmd="FT",.op=hpgl_FT,.parser=parse_4},
	{.cmd="IN",.op=hpgl_IN,.parser=parse_0},
	{.cmd="IP",.op=hpgl_IP,.parser=parse_4},
	{.cmd="IW",.op=hpgl_IW,.parser=parse_4},
	{.cmd="LB",.op=hpgl_LB,.parser=parse_t},
	{.cmd="LO",.op=hpgl_LO,.parser=parse_4},
	{.cmd="LT",.op=hpgl_LT,.parser=parse_4},
	{.cmd="NR",.op=hpgl_NR,.parser=parse_0},
	{.cmd="PA",.op=hpgl_PA,.parser=parse_n},
	{.cmd="PB",.op=hpgl_PB,.parser=parse_0},
	{.cmd="PD",.op=hpgl_PD,.parser=parse_n},
	{.cmd="PG",.op=hpgl_PG,.parser=parse_0},
	{.cmd="PM",.op=hpgl_PM,.parser=parse_4},
	{.cmd="PR",.op=hpgl_PR,.parser=parse_n},
	{.cmd="PS",.op=hpgl_PS,.parser=parse_4},
	{.cmd="PT",.op=hpgl_PT,.parser=parse_4},
	{.cmd="PU",.op=hpgl_PU,.parser=parse_n},
	{.cmd="RA",.op=hpgl_RA,.parser=parse_4},
	{.cmd="RR",.op=hpgl_RR,.parser=parse_4},
	{.cmd="RO",.op=hpgl_RO,.parser=parse_4},
	{.cmd="SA",.op=hpgl_SA,.parser=parse_0},
	{.cmd="SC",.op=hpgl_SC,.parser=parse_4},
	{.cmd="SI",.op=hpgl_SI,.parser=parse_4},
	{.cmd="SL",.op=hpgl_SL,.parser=parse_4},
	{.cmd="SP",.op=hpgl_SP,.parser=parse_4},
	{.cmd="SS",.op=hpgl_SS,.parser=parse_0},
	{.cmd="SR",.op=hpgl_SR,.parser=parse_4},
	{.cmd="SU",.op=hpgl_SU,.parser=parse_4},
	{.cmd="WG",.op=hpgl_WG,.parser=parse_4}
};

int HPGLParse(char *input, HPGLInstruction **prog)
{
	return 0;
}
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

int parse_none(ParserContext *ctx){
	HPGLInstruction current = {
		.cmd = ctx->op,
		.argc = 0
	};
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_nnno(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_dtxt(ParserContext *ctx){
	HPGLInstruction current;
	current.cmd = ctx->op;
	current.argc = 0;
	while(*(ctx->input) != ctx->delim){
		if (current.argc < 256) {
			HPGLArgument a = {.c = *(ctx->input++)};
			current.args[current.argc++] = a;
		}
	}
	ctx->input++;
	ctx->prog[ctx->instc++] = current;
	return 0;
}
int parse_n(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_no(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_oo(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_nn(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_ooo(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_oooo(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_k2n(ParserContext *ctx){
	// TODO impl
	return 0;
}
int parse_k2o(ParserContext *ctx){
	// TODO impl
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
	{.cmd="AA",.op=hpgl_AA,.parser=parse_nnno},
	{.cmd="AF",.op=hpgl_AF,.parser=parse_none},
	{.cmd="AR",.op=hpgl_AR,.parser=parse_nnno},
	{.cmd="BL",.op=hpgl_BL,.parser=parse_dtxt},
	{.cmd="CA",.op=hpgl_CA,.parser=parse_n   },
	{.cmd="CI",.op=hpgl_CI,.parser=parse_no  },
	{.cmd="CP",.op=hpgl_CP,.parser=parse_oo  },
	{.cmd="CS",.op=hpgl_CS,.parser=parse_n   },
	{.cmd="CT",.op=hpgl_CT,.parser=parse_n   },
	{.cmd="DF",.op=hpgl_DF,.parser=parse_none},
	{.cmd="DI",.op=hpgl_DI,.parser=parse_nn  },
	{.cmd="DR",.op=hpgl_DR,.parser=parse_nn  },
	{.cmd="DT",.op=hpgl_DT,.parser=parse_c   },
	{.cmd="DU",.op=hpgl_DU,.parser=parse_nn  },
	{.cmd="DV",.op=hpgl_DV,.parser=parse_n   },
	{.cmd="EA",.op=hpgl_EA,.parser=parse_nn  },
	{.cmd="EP",.op=hpgl_EP,.parser=parse_none},
	{.cmd="ER",.op=hpgl_ER,.parser=parse_nn  },
	{.cmd="ES",.op=hpgl_ES,.parser=parse_no  },
	{.cmd="EW",.op=hpgl_EW,.parser=parse_nnno},
	{.cmd="FP",.op=hpgl_FP,.parser=parse_none},
	{.cmd="FT",.op=hpgl_FT,.parser=parse_ooo },
	{.cmd="IN",.op=hpgl_IN,.parser=parse_none},
	{.cmd="IP",.op=hpgl_IP,.parser=parse_oooo},
	{.cmd="IW",.op=hpgl_IW,.parser=parse_oooo},
	{.cmd="LB",.op=hpgl_LB,.parser=parse_dtxt},
	{.cmd="LO",.op=hpgl_LO,.parser=parse_n   },
	{.cmd="LT",.op=hpgl_LT,.parser=parse_no  },
	{.cmd="NR",.op=hpgl_NR,.parser=parse_none},
	{.cmd="PA",.op=hpgl_PA,.parser=parse_k2n },
	{.cmd="PB",.op=hpgl_PB,.parser=parse_none},
	{.cmd="PD",.op=hpgl_PD,.parser=parse_k2o },
	{.cmd="PG",.op=hpgl_PG,.parser=parse_none},
	{.cmd="PM",.op=hpgl_PM,.parser=parse_n   },
	{.cmd="PR",.op=hpgl_PR,.parser=parse_k2n },
	{.cmd="PS",.op=hpgl_PS,.parser=parse_n   },
	{.cmd="PT",.op=hpgl_PT,.parser=parse_n   },
	{.cmd="PU",.op=hpgl_PU,.parser=parse_k2o },
	{.cmd="RA",.op=hpgl_RA,.parser=parse_nn  },
	{.cmd="RR",.op=hpgl_RR,.parser=parse_no  },
	{.cmd="RO",.op=hpgl_RO,.parser=parse_n   },
	{.cmd="SA",.op=hpgl_SA,.parser=parse_none},
	{.cmd="SC",.op=hpgl_SC,.parser=parse_oooo},
	{.cmd="SI",.op=hpgl_SI,.parser=parse_nn  },
	{.cmd="SL",.op=hpgl_SL,.parser=parse_n   },
	{.cmd="SP",.op=hpgl_SP,.parser=parse_n   },
	{.cmd="SS",.op=hpgl_SS,.parser=parse_none},
	{.cmd="SR",.op=hpgl_SR,.parser=parse_nn  },
	{.cmd="SU",.op=hpgl_SU,.parser=parse_nn  },
	{.cmd="WG",.op=hpgl_WG,.parser=parse_nnno}
};

int HPGLParse(char *input, HPGLInstruction **prog)
{
	return 0;
}
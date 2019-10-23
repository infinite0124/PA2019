#include "cpu/instr.h"

int pop()
{
	opr_src.type=OPR_IMM;
	opr_src.data_size=data_size;
	opr_src.addr=cpu.esp;
	//printf("esp=%x\n",cpu.esp);
	operand_read(&opr_src);
	cpu.esp+=data_size;
	//printf("opr_src.val=%x\n",opr_src.val);
	return opr_src.val;
}

static void instr_execute_1op()
{
	OPERAND imm;
	imm.type=OPR_IMM;
        imm.data_size=data_size;
        imm.addr=cpu.esp;
       //printf("esp=%x\n",cpu.esp);
        operand_read(&opr_imm);
        cpu.esp+=data_size;
	opr_src.val=imm.val;
	operand_write(&opr_src);
}

make_instr_impl_1op(pop,r,v)



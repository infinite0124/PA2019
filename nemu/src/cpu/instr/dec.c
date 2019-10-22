#include "cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	alu_sub(opr_src.val,1,data_size);
	operand_write(&opr_src);
}

make_instr_impl_1op(dec,r,v)

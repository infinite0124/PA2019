#include "cpu/instr.h"

static void instr_execute_2op()
{
	operand_read(&opr_src);
	opr_dest.val-=sign_ext(opr_src.val,data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(cmp,i,rm,bv);

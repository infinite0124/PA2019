#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
	if((opr_dest.type==OPR_SREG))
	{
		load_sreg(opr_dest.addr);
	}
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)
make_instr_impl_2op(mov, rm, s, w)

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
	operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_r2c_l)
{
	MODRM modrm;
	modrm.val=instr_fetch(eip+1,1);
	OPERAND creg,reg;
	creg.type=OPR_CREG;
	creg.addr=modrm.reg_opcode;

	reg.type=OPR_REG;
	reg.addr=modrm.rm;
	reg.data_size=32;

	operand_read(&reg);
	creg.val=reg.val;

	operand_write(&creg);
	return 2;
}

make_instr_func(mov_c2r_l)
{
	MODRM modrm;
	modrm.val=instr_fetch(eip+1,1);
	OPERAND creg,reg;
	creg.type=OPR_CREG;
	creg.addr=modrm.reg_opcode;
	creg.data_size=32;

	reg.type=OPR_REG;
	reg.addr=modrm.rm;
	reg.data_size=32;

	operand_read(&creg);
	reg.val=creg.val;
	operand_write(&reg);
	return 2;
}

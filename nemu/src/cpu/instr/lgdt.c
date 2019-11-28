#include "cpu/instr.h"

make_instr_func(lgdt)
{
	OPERAND test;
	test.type=IMM;
	test.data_size=32;
	test.addr=eip-1;
	operand_read(&test);
	printf("opcode=%x\n",test.val);

	OPERAND start;
	start.type=OPR_IMM;
	start.data_size=32;
	start.addr=eip+2;

	operand_read(&start);
	printf("addr=%x\n",start.val);

	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=16;
	limit.addr=start.val;
	operand_read(&limit);
	printf("limit=%x\n",limit.val);

	OPERAND base;
	base.type=OPR_IMM;
	base.data_size=32;
	base.addr=start.val+16;
	operand_read(&base);
	printf("base=%x\n",base.val);

	cpu.gdtr.limit=limit.val;
	cpu.gdtr.base=base.val;

	return 7;

}

#include <Common.S>

PATCH_BL_START(0x803B6D34, 0)
	lis r5, 0x809C
	lwz r5, -10520(r5)
	lwz r5, 60(r5)
	lwz r5, 0(r5)
	lwz r5, 0(r5)
	lwz r5, 0(r5)
	lbz r0, 0(r5)
	stb r0, 2957(r4)
PATCH_BL_END(0x803B6D34, 0)


PATCH_REPLACE_START(0x803B7B3C, 0)
	nop
PATCH_REPLACE_END(0x803B7B3C, 0)


PATCH_REPLACE_START(0x803B87D4, 0)
	nop
PATCH_REPLACE_END(0x803B87D4, 0)


PATCH_REPLACE_START(0x803B9040, 0)
	nop
PATCH_REPLACE_END(0x803B9040, 0)


PATCH_REPLACE_START(0x805A88AC, 0)
	cmplwi r29, 9
PATCH_REPLACE_END(0x805A88AC, 0)


PATCH_REPLACE_START(0x805A88DC, 0)
	li r29, 9
PATCH_REPLACE_END(0x805A88DC, 0)


PATCH_BL_START(0x805A88EC, 0)
	bl loc_0x2C
	lis r28, 0x0

	loc_0x14:
		bdnzf- 0, loc_0x14

	loc_0x18:
		bdzf- 0, loc_0x18

	loc_0x1C:
		bge- loc_0x1C

	loc_0x20:
		bge+ loc_0x20

	loc_0x24:
		bge- loc_0x24

	loc_0x28:
		bge+ loc_0x28

	loc_0x2C:
		mflr r5
		li r4, 0x3
PATCH_BL_END(0x805A88EC, 0)

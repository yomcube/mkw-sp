// TAS Code [Vega]
// https://mariokartwii.com/showthread.php?tid=1036

#include <Common.S>

PATCH_BL_START(TASCode_Activation, 0)
	lis r12, TASCode_Controller@ha
	ori r12, r12, TASCode_Controller@l
	lhz r12, 0(r12)
	li r11, 0x0480 // ZZZZ
	li r4, 0x0880 // zzzz
	and r0, r12, r11
	cmpw r0, r11
	beq- set_activator
	and r0, r12, r4
	cmpw r0, r4
	beq- set_deactivator
	b end

	set_activator:
		lis r12, 0x8000
		li r11, 0x1
		b store_byte

	set_deactivator:
		lis r12, 0x8000
		li r11, 0x0

	store_byte:
		stb r11, 5710(r12)

	end:
		mflr r0
		blr

PATCH_BL_END(TASCode_Activation, 0)

PATCH_BL_START(TASCode_TASCode, 0)
	stb r0, 0x0014 (r30)
	lis r12, 0x8000
	lbz r12, 0x164e (r12)
	cmpwi r12, 0x1
	bne+ deactivate_tas

	mr r12, r30
	lmw r28, 0x4 (r12)
	stmw r28, -0x0364 (r12)
	stmw r28, -0x27e4 (r12)

	deactivate_tas:
		blr
	
PATCH_BL_END(TASCode_TASCode, 0)

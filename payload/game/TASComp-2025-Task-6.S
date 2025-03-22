#include <Common.S>

// Charge Mini-Turbos While Airborne [Gaberboo]
// 0457eaf4 418100ec
PATCH_REPLACE_START(TASComp2025Task6_1A, 0)
	bgt- 0xEC
PATCH_REPLACE_END(TASComp2025Task6_1A, 0)

// IDBs Have MK8 Inward Drift [Gaberboo]
// c257eb10 00000003
// 4800000d 00000000
// 42340000 7d4802a6
// c3ea0000 60000000
PATCH_BL_START(TASComp2025Task6_2A, 0)
	bl b

	a:
		bdnz+ a

	b:
		mflr r10
		lfs f31, 0(r10)
	
PATCH_BL_END(TASComp2025Task6_2A, 0)
// 04591fe8 38a00001
PATCH_REPLACE_START(TASComp2025Task6_2B, 0)
	li r5, 1
PATCH_REPLACE_END(TASComp2025Task6_2B, 0)
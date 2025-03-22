#include <Common.S>

// Charge Mini-Turbos While Airborne [Gaberboo]
PATCH_REPLACE_START(TASComp2025Task6_1A, 0)
	bgt- TASComp2025Task6_1B
PATCH_REPLACE_END(TASComp2025Task6_1A, 0)

// IDBs Have MK8 Inward Drift [Gaberboo]
PATCH_BL_START(TASComp2025Task6_2A, 0)
	bl loc_0xC

	loc_0x8:
		bdnz+ loc_0x8

	loc_0xC:
		mflr r10
		lfs f31, 0(r10)
PATCH_BL_END(TASComp2025Task6_2A, 0)

PATCH_REPLACE_START(TASComp2025Task6_2B, 0)
	li r5, 1
PATCH_REPLACE_END(TASComp2025Task6_2B, 0)
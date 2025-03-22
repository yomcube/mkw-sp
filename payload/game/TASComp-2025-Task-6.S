#include <Common.S>

// IDBs Have MK8 Inward Drift [Gaberboo]
PATCH_BRANCH_START(TASComp2025Task6_2A, 0, 1)
	bl loc_0xC

	loc_0x8:
		bdnz+ loc_0x8

	loc_0xC:
		mflr r10
		lfs f31, 0(r10)
PATCH_BRANCH_END(TASComp2025Task6_2A, 0, 1)

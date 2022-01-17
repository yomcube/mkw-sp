#include "LicenseSettingsPage.h"

#include <stdio.h>

static const Page_vt s_LicenseSettingsPage_vt;

static void onBack(InputHandler *this, u32 localPlayerId) {
    UNUSED(localPlayerId);

    LicenseSettingsPage *page = container_of(this, LicenseSettingsPage, onBack);
    Page_startReplace(page, PAGE_ANIMATION_PREV, 0.0f);
}

static const InputHandler_vt onBack_vt = {
    .handle = onBack,
};

static void onSettingFront(RadioButtonControlHandler *this, RadioButtonControl *control, u32 localPlayerId, s32 selected) {
    UNUSED(localPlayerId);
    UNUSED(selected); // TODO use

    LicenseSettingsPage *page = container_of(this, LicenseSettingsPage, onSettingFront);
    if (control->index < ARRAY_SIZE(page->settingControls) - 1) {
        RadioButtonControl_select(&page->settingControls[control->index + 1], 0);
    } else {
        page->resetSelection = true;
        // TODO delay?
        Page_startReplace(page, PAGE_ANIMATION_PREV, 0.0f);
    }
}

static const RadioButtonControlHandler_vt onSettingFront_vt = {
    .handle = onSettingFront,
};

static void onSettingSelect(RadioButtonControlHandler *this, RadioButtonControl *control, u32 localPlayerId, s32 selected) {
    UNUSED(localPlayerId);

    if (selected < 0) {
        return;
    }

    LicenseSettingsPage *page = container_of(this, LicenseSettingsPage, onSettingSelect);
    u32 messageId = 0x3007 + control->index * 5 + selected;
    CtrlMenuInstructionText_setMessage(&page->instructionText, messageId, NULL);
}

static const RadioButtonControlHandler_vt onSettingSelect_vt = {
    .handle = onSettingSelect,
};

extern void LicenseRecordsPage_ct;

static LicenseSettingsPage *LicenseSettingsPage_ct(LicenseSettingsPage *this) {
    Page_ct(this);
    this->vt = &s_LicenseSettingsPage_vt;

    MultiControlInputManager_ct(&this->inputManager);
    CtrlMenuPageTitleText_ct(&this->pageTitleText);
    CtrlMenuInstructionText_ct(&this->instructionText);
    CtrlMenuBackButton_ct(&this->backButton);
    for (u32 i = 0; i < ARRAY_SIZE(this->settingControls); i++) {
        RadioButtonControl_ct(&this->settingControls[i]);
    }
    this->onBack.vt = &onBack_vt;
    this->onSettingFront.vt = &onSettingFront_vt;
    this->onSettingSelect.vt = &onSettingSelect_vt;

    return this;
}
PATCH_B(LicenseRecordsPage_ct, LicenseSettingsPage_ct);

static void LicenseSettingsPage_dt(Page *base, s32 type) {
    LicenseSettingsPage *this = (LicenseSettingsPage *)base;

    for (u32 i = ARRAY_SIZE(this->settingControls); i --> 0;) {
        RadioButtonControl_dt(&this->settingControls[i], -1);
    }
    CtrlMenuBackButton_dt(&this->backButton, -1);
    CtrlMenuInstructionText_dt(&this->instructionText, -1);
    CtrlMenuPageTitleText_dt(&this->pageTitleText, -1);
    MultiControlInputManager_dt(&this->inputManager, -1);

    Page_dt(this, 0);
    if (type > 0) {
        delete(this);
    }
}

static s32 LicenseSettingsPage_getReplacement(Page *base) {
    UNUSED(base);

    return 0x67; // TODO enum
}

static void LicenseSettingsPage_onInit(Page *base) {
    LicenseSettingsPage *this = (LicenseSettingsPage *)base;

    MultiControlInputManager_init(&this->inputManager, 0x1, false);
    this->baseInputManager = &this->inputManager;
    MultiControlInputManager_setPointerMode(&this->inputManager, 0x1);

    Page_initChildren(this, 3 + ARRAY_SIZE(this->settingControls));
    Page_insertChild(this, 0, &this->pageTitleText, 0);
    Page_insertChild(this, 1, &this->instructionText, 0);
    Page_insertChild(this, 2, &this->backButton, 0);
    for (u32 i = 0; i < ARRAY_SIZE(this->settingControls); i++) {
        Page_insertChild(this, 3 + i, &this->settingControls[i], 0);
    }

    CtrlMenuPageTitleText_load(&this->pageTitleText, false);
    CtrlMenuInstructionText_load(&this->instructionText);
    PushButton_load(&this->backButton, "button", "Back", "ButtonBackPopup", 0x1, false, true);
    const char *names[] = {
        "HudLabels",
        "169Fov",
    };
    for (u32 i = 0; i < ARRAY_SIZE(this->settingControls); i++) {
        char variant[0x20];
        snprintf(variant, sizeof(variant), "Radio%s", names[i]);
        char buffers[2][0x20];
        const char *buttonVariants[2];
        for (u32 j = 0; j < 2; j++) {
            snprintf(buffers[j], sizeof(*buffers), "Option%s%lu", names[i], j);
            buttonVariants[j] = buffers[j];
        }
        RadioButtonControl_load(&this->settingControls[i], 2, 0, "control", "LicenseSettingRadioBase", variant, "LicenseSettingRadioOption", buttonVariants, 0x1, false, false);
        this->settingControls[i].index = i;
    }

    MultiControlInputManager_setHandler(&this->inputManager, INPUT_ID_BACK, &this->onBack, false, false);
    for (u32 i = 0; i < ARRAY_SIZE(this->settingControls); i++) {
        RadioButtonControl_setFrontHandler(&this->settingControls[i], &this->onSettingFront);
        RadioButtonControl_setSelectHandler(&this->settingControls[i], &this->onSettingSelect);
    }

    CtrlMenuPageTitleText_setMessage(&this->pageTitleText, 0x7df, NULL);

    this->resetSelection = true;
}

static void LicenseSettingsPage_onActivate(Page *base) {
    LicenseSettingsPage *this = (LicenseSettingsPage *)base;

    if (this->resetSelection) {
        RadioButtonControl_selectDefault(&this->settingControls[0], 0);
        u32 messageId = 0x3007 + this->settingControls[0].selected;
        CtrlMenuInstructionText_setMessage(&this->instructionText, messageId, NULL);
        this->resetSelection = false;
    }
}

static const Page_vt s_LicenseSettingsPage_vt = {
    .dt = LicenseSettingsPage_dt,
    .vf_0c = &Page_vf_0c,
    .getReplacement = LicenseSettingsPage_getReplacement,
    .vf_14 = &Page_vf_14,
    .vf_18 = &Page_vf_18,
    .changeSection = Page_changeSection,
    .vf_20 = &Page_vf_20,
    .push = &Page_push,
    .onInit = LicenseSettingsPage_onInit,
    .vf_2c = &Page_vf_2c,
    .onActivate = LicenseSettingsPage_onActivate,
    .vf_34 = &Page_vf_34,
    .vf_38 = &Page_vf_38,
    .vf_3c = &Page_vf_3c,
    .vf_40 = &Page_vf_40,
    .vf_44 = &Page_vf_44,
    .vf_48 = &Page_vf_48,
    .vf_4c = &Page_vf_4c,
    .vf_50 = &Page_vf_50,
    .onRefocus = Page_onRefocus,
    .vf_58 = &Page_vf_58,
    .vf_5c = &Page_vf_5c,
    .vf_60 = &Page_vf_60,
};
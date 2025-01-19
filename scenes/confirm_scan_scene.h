#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void confirm_scan_scene_on_enter(void* context);
bool confirm_scan_scene_on_event(void* context, SceneManagerEvent event);
void confirm_scan_scene_on_exit(void* context);

typedef enum {
    ConfirmScanResultRescan,
    ConfirmScanResultContinue,
} ConfirmScanResult;

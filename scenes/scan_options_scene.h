#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void scan_options_scene_on_enter(void* context);
bool scan_options_scene_on_event(void* context, SceneManagerEvent event);
void scan_options_scene_on_exit(void* context);

// Scan configuration options
typedef enum {
    ScanDuration5s,
    ScanDuration10s,
    ScanDuration30s,
    ScanDurationContinuous,
} ScanDurationOption;

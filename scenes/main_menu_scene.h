#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

// Main menu scene events
void main_menu_scene_on_enter(void* context);
bool main_menu_scene_on_event(void* context, SceneManagerEvent event);
void main_menu_scene_on_exit(void* context);

// Dialog result enum
typedef enum {
    MainMenuResultScan,
    MainMenuResultWrite,
    MainMenuResultLoad,
    MainMenuResultSave,
} MainMenuResult;

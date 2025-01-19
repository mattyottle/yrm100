#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void scanning_scene_on_enter(void* context);
bool scanning_scene_on_event(void* context, SceneManagerEvent event);
void scanning_scene_on_exit(void* context);

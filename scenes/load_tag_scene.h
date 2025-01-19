#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void load_tag_scene_on_enter(void* context);
bool load_tag_scene_on_event(void* context, SceneManagerEvent event);
void load_tag_scene_on_exit(void* context);

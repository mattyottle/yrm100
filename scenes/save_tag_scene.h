#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void save_tag_scene_on_enter(void* context);
bool save_tag_scene_on_event(void* context, SceneManagerEvent event);
void save_tag_scene_on_exit(void* context);

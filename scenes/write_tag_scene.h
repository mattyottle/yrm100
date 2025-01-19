#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void write_tag_scene_on_enter(void* context);
bool write_tag_scene_on_event(void* context, SceneManagerEvent event);
void write_tag_scene_on_exit(void* context);

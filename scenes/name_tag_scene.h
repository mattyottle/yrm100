#pragma once
#include "../yrm100.h"
#include "../gui.h"
#include <gui/scene_manager.h>
#include <gui/modules/text_input.h>

void name_tag_scene_on_enter(void* context);
bool name_tag_scene_on_event(void* context, SceneManagerEvent event);
void name_tag_scene_on_exit(void* context);

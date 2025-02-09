#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void load_tag_scene_on_enter(void* context);
bool load_tag_scene_on_event(void* context, SceneManagerEvent event);
void load_tag_scene_on_exit(void* context);

void load_tag_scene_on_enter(void* context) {
    app_context* app = context;
    Submenu* submenu = app->gui_components->submenu;

    submenu_reset(submenu);
    // TODO: Add submenu items from saved tags
    // Will need to implement file browsing functionality

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewSubmenu_Index);
}

bool load_tag_scene_on_event(void* context, SceneManagerEvent event) {
    app_context* app = context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        // Handle tag selection
        break;
    default:
        break;
    }

    return consumed;
}

void load_tag_scene_on_exit(void* context) {
    app_context* app = context;
    submenu_reset(app->gui_components->submenu);
}

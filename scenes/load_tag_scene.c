#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void load_tag_scene_on_enter(void* _context);
bool load_tag_scene_on_event(void* _context, SceneManagerEvent event);
void load_tag_scene_on_exit(void* _context);

void load_tag_scene_on_enter(void* _context) {
    app_context* context = _context;
    Submenu* submenu = context->gui_components->submenu;

    submenu_reset(submenu);
    // TODO: Add submenu items from saved tags
    // Will need to implement file browsing functionality

    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewSubmenu_Index);
}

bool load_tag_scene_on_event(void* _context, SceneManagerEvent event) {
    app_context* context = _context;
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

void load_tag_scene_on_exit(void* _context) {
    app_context* context = _context;
    submenu_reset(context->gui_components->submenu);
}

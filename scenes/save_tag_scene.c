#pragma once
#include "../yrm100.h"
#include "../gui.h"
#include "scene_events.h"
#include <gui/modules/loading.h>

#include <gui/scene_manager.h>

void save_tag_scene_on_enter(void* context);
bool save_tag_scene_on_event(void* context, SceneManagerEvent event);
void save_tag_scene_on_exit(void* context);

void save_tag_scene_on_enter(void* context) {
    app_context* app = context;
    Loading* loading = app->gui_components->loading;

    loading_set_header(loading, "Saving Tag");
    loading_set_icon(loading, &I_Loading_24);
    loading_set_text(loading, "Saving tag data\nto storage...");

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewLoading_Index);

    // TODO: Add actual save functionality here
    // This should be done in a separate thread to avoid blocking UI
}

bool save_tag_scene_on_event(void* context, SceneManagerEvent event) {
    app_context* app = context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        if(event.event == ViewEventSaveComplete) {
            scene_manager_previous_scene(app->gui_components->scene_manager);
            consumed = true;
        }
        break;
    default:
        break;
    }

    return consumed;
}

void save_tag_scene_on_exit(void* context) {
    app_context* app = context;
    loading_reset(app->gui_components->loading);
}

#pragma once
#include "../yrm100.h"
#include "../gui.h"
#include <gui/modules/loading.h>
#include <gui/scene_manager.h>
#include <icons.h>

void scanning_scene_on_enter(void* context);
bool scanning_scene_on_event(void* context, SceneManagerEvent event);
void scanning_scene_on_exit(void* context);

void loading_set_header(Loading* loading, const char* text);
void loading_set_text(Loading* loading, const char* text);
void loading_set_icon(Loading* loading, const Icon* icon);
void loading_set_callback(Loading* loading, LoadingCallback callback);
void loading_set_context(Loading* loading, void* context);

static void scanning_timeout_callback(void* context) {
    app_context* app = context;
    scene_manager_next_scene(app->gui_components->scene_manager, ConfirmScanScene_Index);
}

void scanning_scene_on_enter(void* context) {
    app_context* app = context;
    Loading* loading = app->gui_components->loading;

    loading_reset(loading);
    loading_set_header(loading, "Scanning");
    loading_set_text(loading, "Searching for UHF tags...");
    loading_set_icon(loading, &I_Loading_24); // Built-in loading animation
    loading_set_callback(loading, scanning_timeout_callback);
    loading_set_context(loading, app);

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewLoading_Index);

    // Start the actual scanning process
    // TODO: Implement your tag scanning logic here
}

bool scanning_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeTick:
        // Update scan progress if needed
        consumed = true;
        break;
    default:
        break;
    }

    return consumed;
}

void scanning_scene_on_exit(void* context) {
    app_context* app = context;
    loading_reset(app->gui_components->loading);
}

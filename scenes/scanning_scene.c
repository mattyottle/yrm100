#include "scanning_scene.h"

static void scanning_timeout_callback(void* context) {
    YRM100* app = context;
    scene_manager_next_scene(app->gui_m->scene_manager, ConfirmScanScene_Index);
}

void scanning_scene_on_enter(void* context) {
    YRM100* app = context;
    Loading* loading = app->gui_m->LoadingView;

    loading_reset(loading);
    loading_set_header(loading, "Scanning");
    loading_set_text(loading, "Searching for UHF tags...");
    loading_set_icon(loading, &A_Loading_24); // Built-in loading animation
    loading_set_callback(loading, scanning_timeout_callback);
    loading_set_context(loading, app);

    view_dispatcher_switch_to_view(app->gui_m->view_dispatcher, LoadingView_Index);

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
    YRM100* app = context;
    loading_reset(app->gui_m->LoadingView);
    // TODO: Stop any ongoing scan process
}

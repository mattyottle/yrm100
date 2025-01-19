#include "save_tag_scene.h"

void save_tag_scene_on_enter(void* context) {
    YRM100* app = context;
    Loading* loading = ((gui_managers*)app->gui_context)->LoadingView;

    // Setup loading view
    loading_set_header(loading, "Saving Tag");
    loading_set_icon(loading, &I_Loading_24);
    loading_set_msg(loading, "Saving tag data\nto storage...");

    view_dispatcher_switch_to_view(
        ((gui_managers*)app->gui_context)->view_dispatcher, LoadingView_Index);

    // TODO: Add actual save functionality here
    // This should be done in a separate thread to avoid blocking UI
}

bool save_tag_scene_on_event(void* context, SceneManagerEvent event) {
    YRM100* app = context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        if(event.event == SaveCompleted) {
            scene_manager_previous_scene(((gui_managers*)app->gui_context)->scene_manager);
            consumed = true;
        }
        break;
    default:
        break;
    }

    return consumed;
}

void save_tag_scene_on_exit(void* context) {
    YRM100* app = context;
    Loading* loading = ((gui_managers*)app->gui_context)->LoadingView;
    loading_reset(loading);
}

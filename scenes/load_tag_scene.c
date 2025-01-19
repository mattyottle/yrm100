#include "load_tag_scene.h"

void load_tag_scene_on_enter(void* context) {
    YRM100* app = context;
    Submenu* submenu = ((gui_managers*)app->gui_context)->SubMenuView;

    submenu_reset(submenu);
    // TODO: Add submenu items from saved tags
    // Will need to implement file browsing functionality

    view_dispatcher_switch_to_view(
        ((gui_managers*)app->gui_context)->view_dispatcher, SubMenuView_Index);
}

bool load_tag_scene_on_event(void* context, SceneManagerEvent event) {
    YRM100* app = context;
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
    YRM100* app = context;
    submenu_reset(((gui_managers*)app->gui_context)->SubMenuView);
}

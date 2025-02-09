#pragma once
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>
#include "../types.h"
#include "../gui.h"

// Scene event handlers
void main_menu_scene_on_enter(void* context);
bool main_menu_scene_on_event(void* context, SceneManagerEvent event);
void main_menu_scene_on_exit(void* context);

static void main_menu_dialog_callback(DialogExResult result, void* context) {
    app_context* app = context;

    if(result == DialogExResultLeft) {
        scene_manager_next_scene(app->gui_components->scene_manager, SceneScanOptions_Index);
    } else if(result == DialogExResultRight && app->uhf_tag->is_loaded) {
        // Only handle write button if tag is loaded
        scene_manager_next_scene(app->gui_components->scene_manager, SceneWriteTag_Index);
    } else if(result == DialogExResultCenter) {
        if(app->uhf_tag->is_loaded) {
            scene_manager_next_scene(app->gui_components->scene_manager, SceneSaveTag_Index);
        } else {
            scene_manager_next_scene(app->gui_components->scene_manager, SceneLoadTag_Index);
        }
    }
    // Other results (Back, etc) do nothing
}

void main_menu_scene_on_enter(void* context) {
    app_context* app = context;
    DialogEx* dialog = app->gui_components->dialog;

    dialog_ex_reset(dialog);

    if(app->uhf_tag->is_loaded) {
        char header[32];
        snprintf(header, sizeof(header), "[Loaded] %s", app->uhf_tag->tag_name);
        dialog_ex_set_header(dialog, header, 64, 2, AlignCenter, AlignTop);
        dialog_ex_set_right_button_text(dialog, "Write"); // Only show write button when tag loaded
    } else {
        dialog_ex_set_header(dialog, "[No Tag]", 64, 2, AlignCenter, AlignTop);
        dialog_ex_set_right_button_text(dialog, NULL); // Hide write button when no tag
    }

    dialog_ex_set_text(dialog, "Choose action:", 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(dialog, "Scan");
    dialog_ex_set_center_button_text(dialog, "Load");
    dialog_ex_set_result_callback(dialog, main_menu_dialog_callback);
    dialog_ex_set_context(dialog, app);

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewDialog_Index);
}

bool main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void main_menu_scene_on_exit(void* context) {
    app_context* app = context;
    dialog_ex_reset(app->gui_components->dialog);
}

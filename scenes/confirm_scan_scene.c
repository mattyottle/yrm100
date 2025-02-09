#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>

void confirm_scan_scene_on_enter(void* context);
bool confirm_scan_scene_on_event(void* context, SceneManagerEvent event);
void confirm_scan_scene_on_exit(void* context);

typedef enum {
    ConfirmScanResultRescan,
    ConfirmScanResultContinue,
} ConfirmScanResult;

static void confirm_scan_dialog_callback(DialogExResult result, void* context) {
    app_context* app = context;

    if(result == DialogExResultLeft) {
        scene_manager_next_scene(app->gui_components->scene_manager, SceneScanning_Index);
    } else if(result == DialogExResultRight) {
        scene_manager_next_scene(app->gui_components->scene_manager, SceneNameTag_Index);
    }
}

void confirm_scan_scene_on_enter(void* context) {
    app_context* app = context;
    DialogEx* dialog = app->gui_components->dialog;

    // Format scanned tag data for display
    char tag_info[64];

    dialog_ex_reset(dialog);
    dialog_ex_set_header(dialog, "Tag Found!", 64, 2, AlignCenter, AlignTop);
    dialog_ex_set_text(dialog, tag_info, 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(dialog, "Rescan");
    dialog_ex_set_right_button_text(dialog, "Continue");
    dialog_ex_set_result_callback(dialog, confirm_scan_dialog_callback);
    dialog_ex_set_context(dialog, app);

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewDialog_Index);
}

bool confirm_scan_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
    }

    return consumed;
}

void confirm_scan_scene_on_exit(void* context) {
    app_context* app = context;
    dialog_ex_reset(app->gui_components->dialog);
}

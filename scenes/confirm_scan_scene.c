#include "confirm_scan_scene.h"

static void confirm_scan_dialog_callback(void* context) {
    YRM100* app = context;
    DialogEx* dialog = app->gui_m->DialogView;
    ConfirmScanResult result = dialog_ex_get_result(dialog);

    if(result == ConfirmScanResultRescan) {
        scene_manager_next_scene(app->gui_m->scene_manager, ScanningScene_Index);
    } else {
        scene_manager_next_scene(app->gui_m->scene_manager, NameTagScene_Index);
    }
}

void confirm_scan_scene_on_enter(void* context) {
    YRM100* app = context;
    DialogEx* dialog = app->gui_m->DialogView;

    // Format scanned tag data for display
    char tag_info[64];
    snprintf(tag_info, sizeof(tag_info), "Tag ID: %s\nType: %s", app->tag_id, app->tag_type);

    dialog_ex_reset(dialog);
    dialog_ex_set_header(dialog, "Tag Found!", 64, 2, AlignCenter, AlignTop);
    dialog_ex_set_text(dialog, tag_info, 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(dialog, "Rescan");
    dialog_ex_set_right_button_text(dialog, "Continue");
    dialog_ex_set_result_callback(dialog, confirm_scan_dialog_callback);
    dialog_ex_set_context(dialog, app);

    view_dispatcher_switch_to_view(app->gui_m->view_dispatcher, DialogView_Index);
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
    YRM100* app = context;
    dialog_ex_reset(app->gui_m->DialogView);
}

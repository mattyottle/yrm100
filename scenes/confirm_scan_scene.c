#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>

void confirm_scan_scene_on_enter(void* _context);
bool confirm_scan_scene_on_event(void* _context, SceneManagerEvent event);
void confirm_scan_scene_on_exit(void* _context);

typedef enum {
    ConfirmScanResultRescan,
    ConfirmScanResultContinue,
} ConfirmScanResult;

static void confirm_scan_dialog_callback(DialogExResult result, void* _context) {
    app_context* context = _context;

    if(result == DialogExResultLeft) {
        scene_manager_next_scene(context->gui_components->scene_manager, SceneScanning_Index);
    } else if(result == DialogExResultRight) {
        scene_manager_next_scene(context->gui_components->scene_manager, SceneNameTag_Index);
    }
}

void confirm_scan_scene_on_enter(void* _context) {
    app_context* context = _context;
    DialogEx* dialog = context->gui_components->dialog;

    dialog_ex_reset(dialog);
    dialog_ex_set_header(dialog, "Scan Result", 64, 2, AlignCenter, AlignTop);

    if(context->uhf_tag->is_loaded) {
        // Format scanned tag data for display
        char tag_info[64];
        snprintf(tag_info, sizeof(tag_info), "EPC: %.20s", context->uhf_tag->tag_epc_data);
        dialog_ex_set_text(dialog, tag_info, 64, 32, AlignCenter, AlignCenter);
        dialog_ex_set_left_button_text(dialog, "Rescan");
        dialog_ex_set_right_button_text(dialog, "Confirm");
    } else {
        dialog_ex_set_text(dialog, "No tag detected.", 64, 32, AlignCenter, AlignCenter);
        dialog_ex_set_left_button_text(dialog, "Rescan");
        dialog_ex_set_right_button_text(dialog, NULL); // Hide confirm button
    }

    dialog_ex_set_result_callback(dialog, confirm_scan_dialog_callback);
    dialog_ex_set_context(dialog, context);

    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewDialog_Index);
}

bool confirm_scan_scene_on_event(void* _context, SceneManagerEvent event) {
    UNUSED(_context);
    //no events anticipated
    return false;
}

void confirm_scan_scene_on_exit(void* _context) {
    app_context* context = _context;
    dialog_ex_reset(context->gui_components->dialog);
}

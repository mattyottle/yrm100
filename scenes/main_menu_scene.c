#pragma once
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>
#include "../yrm100_app.h"
#include "../gui.h"

// Scene event handlers
void main_menu_scene_on_enter(void* _context);
bool main_menu_scene_on_event(void* _context, SceneManagerEvent event);
void main_menu_scene_on_exit(void* _context);

static void main_menu_dialog_callback(DialogExResult result, void* _context) {
    app_context* context = _context;

    if(result == DialogExResultLeft) {
        // Selection is "scan"
        scene_manager_next_scene(context->gui_components->scene_manager, SceneScanOptions_Index);
    } else if(result == DialogExResultRight) {
        // Selection is "write"
        // to do: write functionality
        // scene_manager_next_scene(context->gui_components->scene_manager, SceneWriteTag_Index);
        quick_vibration_pulses(2);
    } else if(result == DialogExResultCenter) {
        // selection is "load"
        // to do: load functionality
        // scene_manager_next_scene(context->gui_components->scene_manager, SceneLoadTag_Index);
        quick_vibration_pulses(2);
    } else {
        FURI_LOG_W(TAG, "unexpected result in main menu dialog callback: %d", result);
        quick_vibration_pulses(2);
    }
}

void main_menu_scene_on_enter(void* _context) {
    app_context* context = _context;
    DialogEx* dialog = context->gui_components->dialog;

    dialog_ex_reset(dialog);

    dialog_ex_set_header(dialog, "UHF RFID", 64, 2, AlignCenter, AlignTop);
    if(context->uhf_tag->is_loaded) {
        char textarray[32];
        snprintf(textarray, sizeof(textarray), "[Tag Loaded] %s", context->uhf_tag->tag_name);
        dialog_ex_set_text(dialog, textarray, 64, 32, AlignCenter, AlignCenter);
        dialog_ex_set_right_button_text(dialog, "Write"); // Only show write button when tag loaded
    } else {
        dialog_ex_set_header(dialog, "[No Tag Loaded]", 64, 2, AlignCenter, AlignTop);
        dialog_ex_set_right_button_text(dialog, NULL); // Hide write button when no tag
    }

    dialog_ex_set_left_button_text(dialog, "Scan");
    dialog_ex_set_center_button_text(dialog, "Load");
    dialog_ex_set_result_callback(dialog, main_menu_dialog_callback);
    dialog_ex_set_context(dialog, context);

    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewDialog_Index);
}

bool main_menu_scene_on_event(void* _context, SceneManagerEvent event) {
    UNUSED(_context);
    UNUSED(event);
    //no external events anticipated during this scene
    return false;
}

void main_menu_scene_on_exit(void* _context) {
    app_context* context = _context;
    dialog_ex_reset(context->gui_components->dialog);
}

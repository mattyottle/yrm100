#pragma once
#include "../yrm100.h"
#include <gui/scene_manager.h>

void write_tag_scene_on_enter(void* _context);
bool write_tag_scene_on_event(void* _context, SceneManagerEvent event);
void write_tag_scene_on_exit(void* _context);

void write_tag_scene_on_enter(void* _context) {
    app_context* context = _context;
    DialogEx* dialog = context->gui_components->dialog;

    dialog_ex_set_header(dialog, "Write Tag", 64, 2, AlignCenter, AlignTop);
    dialog_ex_set_text(
        dialog, "Place tag near\ndevice to write", 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(dialog, "Cancel");
    dialog_ex_set_right_button_text(dialog, "Write");

    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewDialog_Index);
}

bool write_tag_scene_on_event(void* _context, SceneManagerEvent event) {
    app_context* context = _context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        if(event.event == DialogExResultLeft) {
            consumed = scene_manager_previous_scene(context->gui_components->scene_manager);
        } else if(event.event == DialogExResultRight) {
            // Handle write button press
            // TODO: Implement tag writing logic
        }
        break;
    default:
        break;
    }

    return consumed;
}

void write_tag_scene_on_exit(void* _context) {
    app_context* context = _context;
    dialog_ex_reset(context->gui_components->dialog);
}

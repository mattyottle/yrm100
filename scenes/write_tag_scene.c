#include "write_tag_scene.h"

void write_tag_scene_on_enter(void* context) {
    YRM100* app = context;
    DialogEx* write_tag_view = ((gui_managers*)app->gui_context)->WriteTagView;

    dialog_ex_set_header(write_tag_view, "Write Tag", 64, 2, AlignCenter, AlignTop);
    dialog_ex_set_text(
        write_tag_view, "Place tag near\ndevice to write", 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(write_tag_view, "Cancel");
    dialog_ex_set_right_button_text(write_tag_view, "Write");

    view_dispatcher_switch_to_view(
        ((gui_managers*)app->gui_context)->view_dispatcher, WriteTagView_Index);
}

bool write_tag_scene_on_event(void* context, SceneManagerEvent event) {
    YRM100* app = context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        if(event.event == DialogExResultLeft) {
            consumed =
                scene_manager_previous_scene(((gui_managers*)app->gui_context)->scene_manager);
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

void write_tag_scene_on_exit(void* context) {
    YRM100* app = context;
    DialogEx* write_tag_view = ((gui_managers*)app->gui_context)->WriteTagView;
    dialog_ex_reset(write_tag_view);
}

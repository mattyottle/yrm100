#include "name_tag_scene.h"

static void name_tag_text_input_callback(void* context) {
    void** ctx_array = context;
    gui_managers* gui_m = ctx_array[gui_context];
    uhf_tag* active_tag = ctx_array[tag_data];
    char* buffer = ctx_array[text_buffer];

    // Copy buffer contents to tag name
    strncpy(active_tag->tag_name, buffer, TAG_NAME_MAX_LENGTH);
    active_tag->is_loaded = true;

    // Move to main menu
    scene_manager_next_scene(gui_m->scene_manager, MainMenuScene_Index);
}

void name_tag_scene_on_enter(void* context) {
    void** ctx_array = context;
    gui_managers* gui_m = ctx_array[gui_context];
    char* buffer = ctx_array[text_buffer];
    TextInput* text_input = gui_m->TextInputView;

    text_input_reset(text_input);
    text_input_set_header_text(text_input, "Enter Tag Name");
    text_input_set_result_callback(
        text_input, name_tag_text_input_callback, context, buffer, TAG_NAME_MAX_LENGTH, true);

    text_input_set_minimum_length(text_input, 1);
    text_input_set_maximum_length(text_input, TAG_NAME_MAX_LENGTH);

    view_dispatcher_switch_to_view(gui_m->view_dispatcher, TextInputView_Index);
}

bool name_tag_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
    }

    return consumed;
}

void name_tag_scene_on_exit(void* context) {
    void** ctx_array = context;
    gui_managers* gui_m = ctx_array[gui_context];
    text_input_reset(gui_m->TextInputView);
}

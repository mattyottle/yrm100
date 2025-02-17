#pragma once
#include "../yrm100.h"
#include "../gui.h"
#include <gui/scene_manager.h>
#include <gui/modules/text_input.h>

void name_tag_scene_on_enter(void* _context);
bool name_tag_scene_on_event(void* _context, SceneManagerEvent event);
void name_tag_scene_on_exit(void* _context);

static void name_tag_text_input_callback(void* _context) {
    app_context* context = _context;
    TextInput* text_input = context->gui_components->text_input;
    const char* input_text = text_input_get_text(text_input);

    // Copy buffer contents to tag name
    strncpy(context->uhf_tag->tag_name, input_text, TAG_NAME_MAX_LENGTH);
    context->uhf_tag->is_loaded = true;

    // Move to main menu
    scene_manager_next_scene(context->gui_components->scene_manager, SceneMainMenu_Index);
}

void name_tag_scene_on_enter(void* _context) {
    app_context* context = _context;
    TextInput* text_input = context->gui_components->text_input;

    text_input_reset(text_input);
    text_input_set_header_text(text_input, "Enter Tag Name");
    text_input_set_result_callback(
        text_input, name_tag_text_input_callback, context);
    text_input_set_min_length(text_input, 1);
    text_input_set_max_length(text_input, TAG_NAME_MAX_LENGTH);

    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewTextInput_Index);
}

bool name_tag_scene_on_event(void* _context, SceneManagerEvent event) {
    UNUSED(_context);
    //no events anticipated
    return false;
}

void name_tag_scene_on_exit(void* _context) {
    app_context* context = _context;
    text_input_reset(context->gui_components->text_input);
}

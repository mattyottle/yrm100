#pragma once
#include "../yrm100.h"
#include "../gui.h"
#include <gui/scene_manager.h>
#include <gui/modules/variable_item_list.h>

void scan_options_scene_on_enter(void* context);
bool scan_options_scene_on_event(void* context, SceneManagerEvent event);
void scan_options_scene_on_exit(void* context);

void variable_item_set_current_value_text(VariableItem* item, const char* text);
void variable_item_set_values_array(
    VariableItem* item,
    const char* const values[],
    uint8_t values_count);

// Scan configuration options
typedef enum {
    ScanDuration5s,
    ScanDuration10s,
    ScanDuration30s,
    ScanDurationContinuous,
} ScanDurationOption;

static void scan_duration_changed_callback(void* context) {
    app_context* app = context;
    scene_manager_next_scene(app->gui_components->scene_manager, ScanningScene_Index);
}

void scan_options_scene_on_enter(void* context) {
    app_context* app = context;
    VariableItemList* list = app->gui_components->variable_item_list;

    variable_item_list_reset(list);
    variable_item_list_set_header(list, "Scan Options");

    VariableItem* item =
        variable_item_list_add(list, "Duration", 4, scan_duration_changed_callback, app);

    char* const durations[] = {"5s", "10s", "30s", "Cont."};
    uint8_t current_duration = 0;
    variable_item_set_current_value_index(item, current_duration);
    variable_item_set_values_array(item, durations, COUNT_OF(durations), NULL);

    view_dispatcher_switch_to_view(app->gui_components->view_dispatcher, ViewVariableList_Index);
}

bool scan_options_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void scan_options_scene_on_exit(void* context) {
    app_context* app = context;
    variable_item_list_reset(app->gui_components->variable_item_list);
}

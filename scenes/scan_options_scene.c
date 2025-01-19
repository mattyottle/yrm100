#include "scan_options_scene.h"

static void scan_duration_changed_callback(void* context) {
    YRM100* app = context;
    scene_manager_next_scene(app->gui_m->scene_manager, ScanningScene_Index);
}

void scan_options_scene_on_enter(void* context) {
    YRM100* app = context;
    VariableItemList* variable_item_list = app->gui_m->ItemListView;

    variable_item_list_reset(variable_item_list);
    variable_item_list_set_header(variable_item_list, "Scan Options");

    VariableItem* item = variable_item_list_add(
        variable_item_list, "Duration", 4, scan_duration_changed_callback, app);

    char* const durations[] = {"5s", "10s", "30s", "Cont."};
    uint8_t current_duration = 0;
    variable_item_set_current_value_index(item, current_duration);
    variable_item_set_values_array(item, durations, COUNT_OF(durations), NULL);

    view_dispatcher_switch_to_view(app->gui_m->view_dispatcher, ItemListView_Index);
}

bool scan_options_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void scan_options_scene_on_exit(void* context) {
    YRM100* app = context;
    variable_item_list_reset(app->gui_m->ItemListView);
}

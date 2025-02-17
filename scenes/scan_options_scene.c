#pragma once
#include <gui/scene_manager.h>
#include <gui/modules/variable_item_list.h>
#include "../yrm100_app.h"
#include "../gui.h"
#include "../yrm100_hw_device.h"

// Define menu indices - order of items in the options menu
typedef enum {
    MenuItemDuration,  // Scan duration selector
    MenuItemScan,      // Start scan button
    MenuItemCount
} MenuItems;

// Callbacks and UI event handlers use the hardware-defined options
static void duration_changed_callback(VariableItem* item) {
    app_context* context = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    
    context->hw_state.scan_duration_ms = YRM100_DURATIONS[index];
    variable_item_set_current_value_text(item, YRM100_DURATION_NAMES[index]);
}

static void list_enter_callback(void* _context, uint32_t index) {
    app_context* context = _context;
    
    if(index == MenuItemScan) {
        // Change to the scanning scene
        scene_manager_next_scene(context->gui_components->scene_manager, SceneScanning_Index);
    }
}

void scan_options_scene_on_enter(void* _context) {
    app_context* context = _context;
    VariableItemList* list = context->gui_components->variable_item_list;

    variable_item_list_reset(list);

    // Add duration selector
    VariableItem* item = variable_item_list_add(
        list, 
        "Duration",
        YRM100_DURATION_COUNT,
        duration_changed_callback,
        context);
    uint8_t duration_idx = 0;
    for(uint8_t i = 0; i < YRM100_DURATION_COUNT; i++) {
        if(YRM100_DURATIONS[i] == context->scan_config.scan_duration_ms) {
            duration_idx = i;
            break;
        }
    }
    variable_item_set_current_value_index(item, duration_idx);
    variable_item_set_current_value_text(item, YRM100_DURATION_NAMES[duration_idx]);

    // Add Start Scan button
    variable_item_list_add(list, "Start Scan", 0, NULL, context);

    variable_item_list_set_enter_callback(list, list_enter_callback, context);        
    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewVariableList_Index);
}

bool scan_options_scene_on_event(void* _context, SceneManagerEvent event) {
    UNUSED(_context);
    UNUSED(event);
    // no external events needing handling anticipated
    return false;
}

void scan_options_scene_on_exit(void* _context) {
    app_context* context = _context;
    variable_item_list_reset(context->gui_components->variable_item_list);
}

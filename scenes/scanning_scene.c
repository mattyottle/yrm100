#include "../yrm100_app.h"
#include "../gui.h"
#include <gui/modules/loading.h>
#include <gui/scene_manager.h>
#include <notification/notification_messages.h>

void scanning_scene_on_enter(void* _context) {
    app_context* context = _context;
    Loading* loading = context->gui_components->loading;

    // Reset and configure loading view
    loading_reset(loading);
    
    // Switch to loading view before starting scan
    view_dispatcher_switch_to_view(context->gui_components->view_dispatcher, ViewLoading_Index);

    // to do allocate buffer for tag data

    // Indicate scan start with vibration
    quick_vibration_pulses(1);
    
    context->hw_state->status_flag = Yrm100StatusScanning;

    if (!yrm100_start_scan(context, buffer)){
        // log error if the scan didn't start
        FURI_LOG_E(TAG, "Scanning scene failed to start scan");

    }

}

bool scanning_scene_on_event(void* _context, SceneManagerEvent event) {
    app_context* context = _context;
    bool consumed = false;

    switch(event.type) {
        case SceneManagerEventTypeTick:
            // Check current status
            if(context->hw_state->status_flag != Yrm100StatusScanning) {
                // Only transition when we're no longer scanning
                scene_manager_next_scene(context->gui_components->scene_manager, SceneConfirmScan_Index);
                consumed = true;
            }
            break;
           
        case SceneManagerEventTypeBack:
            // Stop scan.  Leads to a return to previous scene on next tick.
            yrm100_stop_scan();
            consumed = true;
            break;
            
        default:
            FURI_LOG_W(TAG, "Scanning scene unhandled event: type %d, event %ld", event.type, event.event);
            break;
    }

    return consumed;
}

void scanning_scene_on_exit(void* _context) {
    app_context* context = _context;
    Loading* loading = context->gui_components->loading;

    // Ensure scan is stopped
    yrm100_stop_scan();

    // to do - free buffer for tag data
    
    // Reset loading view
    loading_reset(loading);
}
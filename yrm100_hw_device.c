#include "yrm100_hw_device.h"
#include "uart_control.h"
#include "yrm_100_app.h"

bool yrm100_hw_init(void) {
    FURI_LOG_I(TAG, "Initializing YRM100 hardware device");
    // TODO: set up and confirm hw parameters, maybe check status, alloc mutex
    return false;
}

//to do - clarify data type
static void uart_rx_callback(void* _context, void* _data, size_t length) {
    // assume data was received. sanity undefined.
    // if the status is still scanning, claim mutex or break
    // process data, maybe put it somewhere, and set tag status flags as appropriate
    // release mutex
    // stop scan 
}

bool yrm100_start_scan(void* _context, void* _buffer) {
    app_context* context = _context;

    // Argument validation
    if(tag == NULL || config == NULL) {
        FURI_LOG_E(TAG, "Invalid scan arguments");
        context->hw_state->status_flag = Yrm100StatusError;
        return false;
    }

    // Validate scan duration matches allowed options
    bool valid_duration = false;
    for(uint8_t i = 0; i < YRM100_DURATION_COUNT; i++) {
        if(context->hw_state->scan_duration_ms == YRM100_DURATIONS[i]) {
            valid_duration = true;
            break;
        }
    }
    if(!valid_duration) {
        FURI_LOG_E(TAG, "Invalid scan duration: %lu", config->scan_duration_ms);
        return false;
    }

    // mark tag data as not loaded if it existed
    context->uhf_tag->is_loaded = false;

    //initialize hw device 
    if(!yrm100_hw_init()) {
        FURI_LOG_E(TAG, "Failed to initialize hardware device");
        return false;
    }

    //get hw versions
    //check version data is ok?

    //star timer in new thread w/ stop callback

    //send scan command in new thread w/ rx callback

    return true;
}

bool yrm100_hw_stop_scan(void* _context) {
    FURI_LOG_I(TAG, "Stopping scan");
    // claim mutex or break
    // Stop timer thread if running
    // Stop scan thread if running
    // Update hw status flag
    // free mutex
}

bool yrm100_hw_write_tag(const uhf_tag* tag) {
    FURI_LOG_I(TAG, "Writing tag");
    // TODO: Implement tag write
    return false;
}
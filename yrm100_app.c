#pragma once
#include <furi.h>
#include <furi_hal.h>
#include "yrm100_app.h"  
#include "gui.h"

/*/ to do:
    // set pointers to null after freeing
    // Scenes generally unloaded when not in use
*/

//static prototypes
static bool _tag_data_init(app_context* context);
static bool _tag_data_free(app_context* context);
static void log_memory_usage(const char* label, const char* message);

bool main_entry(void* p) {
    UNUSED(p);

    FURI_LOG_I(TAG, "YRM100 FAP entry point");

    quick_vibration_pulses(1);

    log_memory_usage("Memory at entry");

    app_context* context = malloc(sizeof(app_context));
    if(!context) {
        FURI_LOG_E(TAG, "Failed to allocate context");
        return false;
    }

    context->gui_components = NULL;
    context->uhf_tag = NULL;
    context->hw_state = NULL; //not initialized until a scan or write is requested
    context->uart_state = NULL; //not initialized until a scan or write is requested

    if(!tag_data_init(context)) {
        FURI_LOG_E(TAG, "Failed to initialize tag data");
        free(context);
        log_memory_usage("Memory at exit");
        return false;
    }

    if(!gui_init(context)) {
        FURI_LOG_E(TAG, "Failed to initialize GUI");
        tag_data_free(context);
        free(context);
        log_memory_usage("Memory at exit");
        return false;
    }

    //start main menu scene
    scene_manager_next_scene(context->gui_components->scene_manager, SceneMainMenu_Index);
    view_dispatcher_run(context->gui_components->view_dispatcher);

    //free all allocated objects
    gui_free(context);
    tag_data_free(context);
    free(context);

    log_memory_usage(TAG, "Memory at exit");
    return true;
}

bool tag_data_init(app_context* context) {
    return _tag_data_init(context); 
}

static bool _tag_data_init(app_context* context) {
    FURI_LOG_T(TAG, "tag data init");
    uhf_tag* tag = NULL;
    tag = malloc(sizeof(uhf_tag));
    if(tag == NULL) {
        update_error(Yrm100ErrorInit, TAG, "Tag data struct malloc failed");
        return false;
    }

    // Initialize tag values
    tag->is_loaded = false;
    tag->tag_length = 0;
    tag->tag_epc_data_length = 0;
    tag->tag_tid_data_length = 0;
    tag->tag_user_data_length = 0;
    tag->scan_duration = 0; // Initialize scan duration to zero (continuous)

    // Clear all data buffers
    memset(tag->tag_name, 0, TAG_NAME_MAX_LENGTH);
    memset(tag->tag_epc_data, 0, TAG_EPC_DATA_MAX_LENGTH);
    memset(tag->tag_tid_data, 0, TAG_TID_DATA_MAX_LENGTH);
    memset(tag->tag_user_data, 0, TAG_USER_DATA_MAX_LENGTH);
    memset(tag->access_password, 0, TAG_ACCESS_PASS_LENGTH); // Initialize access password to 0x00000000

    // Assign to context
    context->uhf_tag = tag;
    return true;
}

bool tag_data_free(app_context* context) {
    return _tag_data_free(context);
}

static bool _tag_data_free(app_context* context) {
    free(context->uhf_tag); // Updated from tag
    context->uhf_tag = NULL; // Updated from tag
    return true;
}


static void log_memory_usage(const char* message) {
    FURI_LOG_D(
        TAG,
        "%s - Heap used: %zu bytes, Heap free: %zu bytes",
        message,
        memmgr_get_total_heap(),
        memmgr_get_free_heap()
    );
}

void quick_vibration_pulses(uint8_t pulse_count) {
    // flag if pulse_count is not between 1 and 3 
    if(pulse_count < 1 || pulse_count > 3) {
        FURI_LOG_W(TAG, "Unexpected vibration pulse count: %d", pulse_count);
        return;
    }

    for(uint8_t i = 0; i < pulse_count; i++) {
        furi_hal_vibro_on(true);
        furi_delay_ms(100);
        furi_hal_vibro_on(false);
        if(i < pulse_count - 1) {
            furi_delay_ms(100);
        }
    }
}
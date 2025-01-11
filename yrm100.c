// Set the logging level
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_TRACE   // Most detailed logs, for tracing execution flow
#define FURI_LOG_LEVEL FURI_LOG_LEVEL_DEBUG // Current level: DEBUG
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_INFO    // General informational logs
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_WARNING // Warnings that indicate potential issues
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_ERROR   // Errors that affect functionality
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_FATAL   // Critical errors that may terminate the application

#include "yrm100.h"
#include "gui.h"

static bool _tag_data_init(uhf_tag** uhf_tag);
static bool _tag_data_free(void* context[CONTEXT_SIZE]);

bool main_entry(void* arg1) {
    UNUSED(arg1); //avoid compiler warning- arg1 isn't used

    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm yrm100!");

    furi_hal_vibro_on(true);
    furi_delay_ms(1000);
    furi_hal_vibro_on(false);

    /*
    FURI_LOG_I(
        "MEMORY",
        "Heap used: %zu bytes, Heap free: %zu bytes",
        memmgr_get_total_heap(),
        memmgr_get_free_heap());*/

    /*
    void* context[CONTEXT_SIZE] = {[gui_context] = NULL, [tag_data] = NULL};

    tag_data_init(context);
    //context[2] now points to a malloc'ed and partially initialized struct

    gui_init(context); //gui_context is an enum for 1, so this is the first item in the array
    //gui_managers now points to a malloc'ed gui_managers struct

    gui_free(context);

    tag_data_free(context);
    */
    FURI_LOG_I(
        "MEMORY",
        "Heap used: %zu bytes, Heap free: %zu bytes",
        memmgr_get_total_heap(),
        memmgr_get_free_heap());
    return true;
}

bool tag_data_init(void* context[CONTEXT_SIZE]) {
    FURI_LOG_T(TAG, "tag data init");

    return _tag_data_init((uhf_tag**)&context[tag_data]);
}

static bool _tag_data_init(uhf_tag** uhf_tag) {
    *uhf_tag = malloc(sizeof(**uhf_tag));
    if(*uhf_tag == NULL) {
        //log warning malloc of main uhf_tag struct failed
        FURI_LOG_E(TAG, "tag data struct malloc failed");
        return false; //init failed
    }

    //leaving active_tag mostly uninitialized, do not access while is_loaded == false. Always check.
    (*uhf_tag)->is_loaded = false;

    return true;
}

bool tag_data_free(void* context[CONTEXT_SIZE]) {
    return _tag_data_free(context);
}

static bool _tag_data_free(void* context[CONTEXT_SIZE]) {
    uhf_tag* uhf_tag = context[tag_data];
    free(uhf_tag);
    return false;
}

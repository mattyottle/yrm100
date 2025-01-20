// Set the logging level
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_TRACE   // Most detailed logs, for tracing execution flow
#define FURI_LOG_LEVEL FURI_LOG_LEVEL_DEBUG // Current level: DEBUG
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_INFO    // General informational logs
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_WARNING // Warnings that indicate potential issues
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_ERROR   // Errors that affect functionality
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_FATAL   // Critical errors that may terminate the application

#include "yrm100.h"
#include "gui.h"

static void log_memory_usage(const char* label, const char* message) {
    FURI_LOG_D(
        label,
        "%s - Heap used: %zu bytes, Heap free: %zu bytes",
        message,
        memmgr_get_total_heap(),
        memmgr_get_free_heap());
}

static bool _tag_data_init(app_context* context);
static bool _tag_data_free(app_context* context);

bool main_entry(void* p) {
    UNUSED(p);

    FURI_LOG_I(TAG, "YRM100 FAP entry point");

    //for debugging remove this later
    furi_hal_vibro_on(true);
    furi_delay_ms(1000);
    furi_hal_vibro_on(false);

    log_memory_usage(TAG, "Memory at entry");

    app_context* context = malloc(sizeof(app_context));
    if(!context) {
        FURI_LOG_E(TAG, "Failed to allocate context");
        return false;
    }
    context->gui_components = NULL;
    context->uhf_tag = NULL;

    if(!tag_data_init(context)) {
        FURI_LOG_E(TAG, "Failed to initialize tag data");
        free(context);
        log_memory_usage(TAG, "Memory at exit");
        return false;
    }

    if(!gui_init(context)) {
        FURI_LOG_E(TAG, "Failed to initialize GUI");
        tag_data_free(context);
        free(context);
        log_memory_usage(TAG, "Memory at exit");
        return false;
    }

    //call main menu

    //free all allocated objects
    gui_free(context);
    tag_data_free(context);
    free(context);

    log_memory_usage(TAG, "Memory at exit");
    return true;
}

bool tag_data_init(app_context* context) {
    FURI_LOG_T(TAG, "tag data init");

    return _tag_data_init(context); // Updated from tag
}

static bool _tag_data_init(app_context* context) {
    uhf_tag* tag = NULL;
    tag = malloc(sizeof(uhf_tag));
    if(tag == NULL) {
        FURI_LOG_E(TAG, "tag data struct malloc failed");
        return false;
    }

    // Initialize tag values
    tag->is_loaded = false;
    tag->tag_length = 0;
    tag->tag_epc_data_length = 0;
    tag->tag_tid_data_length = 0;
    tag->tag_user_data_length = 0;

    // Clear all data buffers
    memset(tag->tag_name, 0, TAG_NAME_MAX_LENGTH);
    memset(tag->tag_epc_data, 0, TAG_EPC_DATA_MAX_LENGTH);
    memset(tag->tag_tid_data, 0, TAG_TID_DATA_MAX_LENGTH);
    memset(tag->tag_user_data, 0, TAG_USER_DATA_MAX_LENGTH);

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

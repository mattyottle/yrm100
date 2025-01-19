// Set the logging level
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_TRACE   // Most detailed logs, for tracing execution flow
#define FURI_LOG_LEVEL FURI_LOG_LEVEL_DEBUG // Current level: DEBUG
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_INFO    // General informational logs
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_WARNING // Warnings that indicate potential issues
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_ERROR   // Errors that affect functionality
// #define FURI_LOG_LEVEL FURI_LOG_LEVEL_FATAL   // Critical errors that may terminate the application

#include "gui.h"
#include "yrm100.h"

static bool _gui_free(void* context[CONTEXT_SIZE]);
static bool _gui_init(void* context[CONTEXT_SIZE]);

bool gui_init(void* context[CONTEXT_SIZE]) {
    FURI_LOG_T(TAG, "gui managers init");
    return _gui_init(context);
}

static bool _gui_init(void* context[CONTEXT_SIZE]) {
    gui_managers* gui_managers = malloc(sizeof(*gui_managers));

    if(gui_managers == NULL) {
        //log warning that gui_managers malloc failed
        FURI_LOG_E(TAG, "gui_managers malloc failed");
        return false; //gui init failed
    }

    //make sure to free later
    FURI_LOG_D(TAG, "allocating scene manager and view dispatcher");
    gui_managers->scene_manager = scene_manager_alloc(&yrm_SceneManagerHandlers, context);
    gui_managers->view_dispatcher =
        view_dispatcher_alloc(); //this does the actual displaying and input handling. The ViewDispatcher manages the views and routes events (like button presses) to the appropriate handlers.

    FURI_LOG_D(TAG, "setting dispatcher callbacks");
    view_dispatcher_set_event_callback_context(gui_managers->view_dispatcher, context);
    view_dispatcher_set_custom_event_callback(
        gui_managers->view_dispatcher, custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        gui_managers->view_dispatcher, back_event_callback);
    view_dispatcher_set_tick_event_callback(
        gui_managers->view_dispatcher, uhf_tick_event_callback, 100);

    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(
        gui_managers->view_dispatcher, gui, ViewDispatcherTypeFullscreen);

    //allocate each view
    //need to make sure they are freed later
    FURI_LOG_D(TAG, "allocating views");
    gui_managers->TextInputView = text_input_alloc();
    gui_managers->SubMenuView = submenu_alloc();
    gui_managers->ItemListView = variable_item_list_alloc();
    gui_managers->DialogView = dialog_ex_alloc();
    gui_managers->LoadingView = loading_alloc(); // Add Loading view allocation
    gui_managers->WriteTagView = dialog_ex_alloc(); // Changed allocation

    //after allocating the views, need to add them to the view dispatcher
    //need to remove them before freeing the view_dispatcher
    FURI_LOG_D(TAG, "adding views to dispatcher");
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        TextInputView_Index,
        text_input_get_view(gui_managers->TextInputView));
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        SubMenuView_Index,
        submenu_get_view(gui_managers->SubMenuView));
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        ItemListView_Index,
        variable_item_list_get_view(gui_managers->ItemListView));
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        DialogView_Index,
        dialog_ex_get_view(gui_managers->DialogView));
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        LoadingView_Index,
        loading_get_view(gui_managers->LoadingView)); // Add Loading view to dispatcher
    view_dispatcher_add_view(
        gui_managers->view_dispatcher,
        WriteTagView_Index,
        dialog_ex_get_view(gui_managers->WriteTagView)); // Changed view getter

    context[gui_context] = gui_managers;
    FURI_LOG_D(TAG, "gui allocation done");
    return true;
}

bool gui_free(void* context[CONTEXT_SIZE]) {
    FURI_LOG_D(TAG, "freeing gui stuff");
    return _gui_free(context);
}

static bool _gui_free(void* context[CONTEXT_SIZE]) {
    furi_assert(context);
    furi_assert(context[gui_context]);
    gui_managers* gui_managers = context[gui_context];

    FURI_LOG_D(TAG, "removing views from view dispatcher");
    view_dispatcher_remove_view(gui_managers->view_dispatcher, TextInputView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, SubMenuView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, ItemListView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, DialogView_Index);
    view_dispatcher_remove_view(
        gui_managers->view_dispatcher, LoadingView_Index); // Remove Loading view
    view_dispatcher_remove_view(gui_managers->view_dispatcher, WriteTagView_Index);

    // Free all components and set to NULL properly
    FURI_LOG_D(TAG, "removing scene manager");
    scene_manager_free(gui_managers->scene_manager);
    gui_managers->scene_manager = NULL;

    FURI_LOG_D(TAG, "removing view dispatcher");
    view_dispatcher_free(gui_managers->view_dispatcher);
    gui_managers->view_dispatcher = NULL;

    FURI_LOG_D(TAG, "free views from gui_managers");
    text_input_free(gui_managers->TextInputView);
    gui_managers->TextInputView = NULL;

    submenu_free(gui_managers->SubMenuView);
    gui_managers->SubMenuView = NULL;

    variable_item_list_free(gui_managers->ItemListView);
    gui_managers->ItemListView = NULL;

    dialog_ex_free(gui_managers->DialogView);
    gui_managers->DialogView = NULL;

    loading_free(gui_managers->LoadingView); // Free Loading view
    gui_managers->LoadingView = NULL;

    dialog_ex_free(gui_managers->WriteTagView); // Changed free function
    gui_managers->WriteTagView = NULL;

    FURI_LOG_D(TAG, "free gui_managers");
    free(gui_managers);
    context[gui_context] = NULL;

    return true;
}

bool custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    furi_assert(
        ((void**)context)
            [gui_context]); //had to do it this way because the built-in set_callback functions expect a void* not a void**.
    return scene_manager_handle_custom_event(
        ((gui_managers*)((void**)context)[gui_context])->scene_manager, event);
}

bool back_event_callback(
    void* context) { //had to do it this way because the built-in set_callback functions expect a void* not a void**.
    furi_assert(context);
    furi_assert(((void**)context)[gui_context]);
    return scene_manager_handle_back_event(
        ((gui_managers*)((void**)context)[gui_context])->scene_manager);
}

void uhf_tick_event_callback(
    void* context) { //had to do it this way because the built-in set_callback functions expect a void* not a void**.
    furi_assert(context);
    furi_assert(((void**)context)[gui_context]);
    scene_manager_handle_tick_event(
        ((gui_managers*)((void**)context)[gui_context])->scene_manager);
}

// Remove LoadTagScene handlers, keep only array entries

void (*const Scene_On_Enter_Handlers[])(void*) = {
    main_menu_scene_on_enter, // Updated to snake_case
    scan_options_scene_on_enter,
    scanning_scene_on_enter,
    confirm_scan_scene_on_enter, // Updated to match new name
    name_tag_scene_on_enter, // Updated to snake_case
    write_tag_scene_on_enter, // Updated to snake_case
    save_tag_scene_on_enter, // Keep this entry
    load_tag_scene_on_enter // Updated to use new name
};

bool (*const Scene_On_Event_Handlers[])(void*, SceneManagerEvent) = {
    main_menu_scene_on_event, // Updated to snake_case
    scan_options_scene_on_event,
    scanning_scene_on_event,
    confirm_scan_scene_on_event, // Updated to match new name
    name_tag_scene_on_event, // Updated to snake_case
    write_tag_scene_on_event, // Updated to snake_case
    save_tag_scene_on_event, // Keep this entry
    load_tag_scene_on_event // Updated to use new name
};

void (*const Scene_On_Exit_Handlers[])(void*) = {
    main_menu_scene_on_exit, // Updated to snake_case
    scan_options_scene_on_exit,
    scanning_scene_on_exit,
    confirm_scan_scene_on_exit, // Updated to match new name
    name_tag_scene_on_exit, // Updated to snake_case
    write_tag_scene_on_exit, // Updated to snake_case
    save_tag_scene_on_exit, // Keep this entry
    load_tag_scene_on_exit // Updated to use new name
};

//need an array of all three arrays of handlers
static const SceneManagerHandlers yrm_SceneManagerHandlers = {
    .on_enter_handlers = Scene_On_Enter_Handlers,
    .on_event_handlers = Scene_On_Event_Handlers,
    .on_exit_handlers = Scene_On_Exit_Handlers,
    .scene_num = NumberOfScenes_Index,
};

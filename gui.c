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

    context[gui_context] = gui_managers;
    FURI_LOG_T(TAG, "gui allocation done");
    return true;
}

bool gui_free(void* context[CONTEXT_SIZE]) {
    FURI_LOG_T(TAG, "freeing gui stuff");
    return _gui_free(context);
}

static bool _gui_free(void* context[CONTEXT_SIZE]) {
    furi_assert(context);
    furi_assert(context[gui_context]);
    gui_managers* gui_managers = context[gui_context];

    view_dispatcher_remove_view(gui_managers->view_dispatcher, DialogView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, SubMenuView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, ItemListView_Index);
    view_dispatcher_remove_view(gui_managers->view_dispatcher, DialogView_Index);
    scene_manager_free(gui_managers->scene_manager);
    view_dispatcher_free(gui_managers->view_dispatcher);
    text_input_free(gui_managers->TextInputView);
    submenu_free(gui_managers->SubMenuView);
    variable_item_list_free(gui_managers->ItemListView);
    dialog_ex_free(gui_managers->DialogView);
    free(gui_managers);
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

//each scene needs an on_enter handler
void MainMenuScene_On_Enter(void* context) {
    UNUSED(context);
}
void ScanOptionsScene_On_Enter(void* context) {
    UNUSED(context);
}
void ScanningScene_On_Enter(void* context) {
    UNUSED(context);
}
void ConfirmScanScene_On_Enter(void* context) {
    UNUSED(context);
}
void NameTagScene_On_Enter(void* context) {
    UNUSED(context);
}
void WriteTagScene_On_Enter(void* context) {
    UNUSED(context);
}
void SaveTagScene_On_Enter(void* context) {
    UNUSED(context);
}
void LoadTagScene_On_Enter(void* context) {
    UNUSED(context);
}

//each scene needs an on_event handler.  They return false for failure or if not handled
bool MainMenuScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool ScanOptionsScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool ScanningScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool ConfirmScanScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool NameTagScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool WriteTagScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool SaveTagScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}
bool LoadTagScene_On_Event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return true;
}

//each scene needs an on_exit handler
void MainMenuScene_On_Exit(void* context) {
    UNUSED(context);
}
void ScanOptionsScene_On_Exit(void* context) {
    UNUSED(context);
}
void ScanningScene_On_Exit(void* context) {
    UNUSED(context);
}
void ConfirmScanScene_On_Exit(void* context) {
    UNUSED(context);
}
void NameTagScene_On_Exit(void* context) {
    UNUSED(context);
}
void WriteTagScene_On_Exit(void* context) {
    UNUSED(context);
}
void SaveTagScene_On_Exit(void* context) {
    UNUSED(context);
}
void LoadTagScene_On_Exit(void* context) {
    UNUSED(context);
}

//need an array of each type of handler. The indexes need to be the same as the enums for the scenes
void (*const Scene_On_Enter_Handlers[])(void*) = {
    MainMenuScene_On_Enter,
    ScanOptionsScene_On_Enter,
    ScanningScene_On_Enter,
    ConfirmScanScene_On_Enter,
    NameTagScene_On_Enter,
    WriteTagScene_On_Enter,
    SaveTagScene_On_Enter,
    LoadTagScene_On_Enter

};

bool (*const Scene_On_Event_Handlers[])(void*, SceneManagerEvent) = {
    MainMenuScene_On_Event,
    ScanOptionsScene_On_Event,
    ScanningScene_On_Event,
    ConfirmScanScene_On_Event,
    NameTagScene_On_Event,
    WriteTagScene_On_Event,
    SaveTagScene_On_Event,
    LoadTagScene_On_Event

};

void (*const Scene_On_Exit_Handlers[])(void*) = {
    MainMenuScene_On_Exit,
    ScanOptionsScene_On_Exit,
    ScanningScene_On_Exit,
    ConfirmScanScene_On_Exit,
    NameTagScene_On_Exit,
    WriteTagScene_On_Exit,
    SaveTagScene_On_Exit,
    LoadTagScene_On_Exit};

//need an array of all three arrays of handlers
static const SceneManagerHandlers yrm_SceneManagerHandlers = {
    .on_enter_handlers = Scene_On_Enter_Handlers,
    .on_event_handlers = Scene_On_Event_Handlers,
    .on_exit_handlers = Scene_On_Exit_Handlers,
    .scene_num = NumberOfScenes_Index,
};

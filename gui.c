#include "gui.h"
#include "yrm100.h"
#include "types.h"

// Function prototypes
static bool _gui_init(app_context* context);
static bool _gui_free(app_context* context);

bool gui_init(app_context* context) {
    FURI_LOG_T(TAG, "gui managers init");
    bool initialized = _gui_init(context);
    if(!initialized && context->gui_components != NULL) {
        // Clean up any partially initialized components
        gui_free(context);
    }
    return initialized;
}

static bool _gui_init(app_context* context) {
    struct gui_components* gui_components = NULL;
    gui_components = malloc(sizeof(struct gui_components));

    if(gui_components == NULL) {
        FURI_LOG_E(TAG, "gui_components malloc failed");
        return false;
    }

    // Set context early so cleanup can work
    context->gui_components = gui_components;

    // Initialize all pointers to NULL
    gui_components->view_dispatcher = NULL;
    gui_components->scene_manager = NULL;
    gui_components->submenu = NULL;
    gui_components->text_input = NULL;
    gui_components->variable_item_list = NULL;
    gui_components->dialog = NULL;
    gui_components->loading = NULL;
    gui_components->button_menu = NULL;
    gui_components->button_panel = NULL;
    gui_components->byte_input = NULL;
    gui_components->popup = NULL;
    gui_components->text_box = NULL;
    gui_components->widget = NULL;
    gui_components->system_gui = NULL;

    FURI_LOG_D(TAG, "allocating scene manager and view dispatcher");
    gui_components->scene_manager = scene_manager_alloc(&SceneManager_Handlers_Arrays, context);
    if(gui_components->scene_manager == NULL) {
        FURI_LOG_E(TAG, "scene_manager allocation failed");
        return false;
    }

    gui_components->view_dispatcher = view_dispatcher_alloc();
    if(gui_components->view_dispatcher == NULL) {
        FURI_LOG_E(TAG, "view_dispatcher allocation failed");
        return false;
    }

    FURI_LOG_D(TAG, "setting dispatcher callbacks");
    view_dispatcher_set_event_callback_context(gui_components->view_dispatcher, context);
    view_dispatcher_set_custom_event_callback(
        gui_components->view_dispatcher, custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        gui_components->view_dispatcher, back_event_callback);
    view_dispatcher_set_tick_event_callback(
        gui_components->view_dispatcher, uhf_tick_event_callback, 100);

    gui_components->system_gui = furi_record_open(RECORD_GUI);
    if(gui_components->system_gui == NULL) {
        FURI_LOG_E(TAG, "failed to open system GUI");
        return false;
    }

    view_dispatcher_attach_to_gui(
        gui_components->view_dispatcher, gui_components->system_gui, ViewDispatcherTypeFullscreen);

    // Allocate views and add to dispatcher
    FURI_LOG_D(TAG, "allocating views and adding to dispatcher");

#if USE_SUBMENU
    gui_components->submenu = submenu_alloc();
    if(gui_components->submenu == NULL) {
        FURI_LOG_E(TAG, "submenu allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewSubmenu_Index, // Updated from SubmenuView_Index
        submenu_get_view(gui_components->submenu));
#endif

#if USE_TEXT_INPUT
    gui_components->text_input = text_input_alloc();
    if(gui_components->text_input == NULL) {
        FURI_LOG_E(TAG, "text_input allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewTextInput_Index, // Updated from TextInputView_Index
        text_input_get_view(gui_components->text_input));
#endif

#if USE_VARIABLE_LIST
    gui_components->variable_item_list = variable_item_list_alloc();
    if(gui_components->variable_item_list == NULL) {
        FURI_LOG_E(TAG, "variable_item_list allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewVariableList_Index, // Updated from VariableItemListView_Index
        variable_item_list_get_view(gui_components->variable_item_list));
#endif

#if USE_DIALOG
    gui_components->dialog = dialog_ex_alloc();
    if(gui_components->dialog == NULL) {
        FURI_LOG_E(TAG, "dialog allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewDialog_Index, // Updated from DialogView_Index
        dialog_ex_get_view(gui_components->dialog));
#endif

#if USE_LOADING
    gui_components->loading = loading_alloc();
    if(gui_components->loading == NULL) {
        FURI_LOG_E(TAG, "loading allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewLoading_Index, // Updated from LoadingView_Index
        loading_get_view(gui_components->loading));
#endif

#if USE_BUTTON_MENU
    gui_components->button_menu = button_menu_alloc();
    if(gui_components->button_menu == NULL) {
        FURI_LOG_E(TAG, "button_menu allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewButtonMenu_Index, // Updated from ButtonMenuView_Index
        button_menu_get_view(gui_components->button_menu));
#endif

#if USE_BUTTON_PANEL
    gui_components->button_panel = button_panel_alloc();
    if(gui_components->button_panel == NULL) {
        FURI_LOG_E(TAG, "button_panel allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewButtonPanel_Index, // Updated from ButtonPanelView_Index
        button_panel_get_view(gui_components->button_panel));
#endif

#if USE_BYTE_INPUT
    gui_components->byte_input = byte_input_alloc();
    if(gui_components->byte_input == NULL) {
        FURI_LOG_E(TAG, "byte_input allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewByteInput_Index, // Updated from ByteInputView_Index
        byte_input_get_view(gui_components->byte_input));
#endif

#if USE_POPUP
    gui_components->popup = popup_alloc();
    if(gui_components->popup == NULL) {
        FURI_LOG_E(TAG, "popup allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewPopup_Index, // Updated from PopupView_Index
        popup_get_view(gui_components->popup));
#endif

#if USE_TEXT_BOX
    gui_components->text_box = text_box_alloc();
    if(gui_components->text_box == NULL) {
        FURI_LOG_E(TAG, "text_box allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewTextBox_Index, // Updated from TextBoxView_Index
        text_box_get_view(gui_components->text_box));
#endif

#if USE_WIDGET
    gui_components->widget = widget_alloc();
    if(gui_components->widget == NULL) {
        FURI_LOG_E(TAG, "widget allocation failed");
        return false;
    }
    view_dispatcher_add_view(
        gui_components->view_dispatcher,
        ViewWidget_Index, // Updated from WidgetView_Index
        widget_get_view(gui_components->widget));
#endif

    FURI_LOG_D(TAG, "gui allocation done");
    return true;
}

bool gui_free(app_context* context) {
    FURI_LOG_D(TAG, "freeing gui stuff");
    return _gui_free(context);
}

static bool _gui_free(app_context* context) {
    furi_assert(context);
    furi_assert(context->gui_components);
    struct gui_components* gui_components = context->gui_components;

    FURI_LOG_D(TAG, "removing views and freeing components");

    // Remove views and free their components
    if(gui_components->submenu) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewSubmenu_Index); // Updated from SubmenuView_Index
        submenu_free(gui_components->submenu);
        gui_components->submenu = NULL;
    }

    if(gui_components->text_input) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher,
            ViewTextInput_Index); // Updated from TextInputView_Index
        text_input_free(gui_components->text_input);
        gui_components->text_input = NULL;
    }

    if(gui_components->variable_item_list) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher,
            ViewVariableList_Index); // Updated from VariableItemListView_Index
        variable_item_list_free(gui_components->variable_item_list);
        gui_components->variable_item_list = NULL;
    }

    if(gui_components->dialog) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewDialog_Index); // Updated from DialogView_Index
        dialog_ex_free(gui_components->dialog);
        gui_components->dialog = NULL;
    }

    if(gui_components->loading) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewLoading_Index); // Updated from LoadingView_Index
        loading_free(gui_components->loading);
        gui_components->loading = NULL;
    }

    if(gui_components->button_menu) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher,
            ViewButtonMenu_Index); // Updated from ButtonMenuView_Index
        button_menu_free(gui_components->button_menu);
        gui_components->button_menu = NULL;
    }

    if(gui_components->button_panel) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher,
            ViewButtonPanel_Index); // Updated from ButtonPanelView_Index
        button_panel_free(gui_components->button_panel);
        gui_components->button_panel = NULL;
    }

    if(gui_components->byte_input) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher,
            ViewByteInput_Index); // Updated from ByteInputView_Index
        byte_input_free(gui_components->byte_input);
        gui_components->byte_input = NULL;
    }

    if(gui_components->popup) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewPopup_Index); // Updated from PopupView_Index
        popup_free(gui_components->popup);
        gui_components->popup = NULL;
    }

    if(gui_components->text_box) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewTextBox_Index); // Updated from TextBoxView_Index
        text_box_free(gui_components->text_box);
        gui_components->text_box = NULL;
    }

    if(gui_components->widget) {
        view_dispatcher_remove_view(
            gui_components->view_dispatcher, ViewWidget_Index); // Updated from WidgetView_Index
        widget_free(gui_components->widget);
        gui_components->widget = NULL;
    }

    // Free core components
    FURI_LOG_D(TAG, "removing scene manager and view dispatcher");
    if(gui_components->scene_manager) {
        scene_manager_free(gui_components->scene_manager);
        gui_components->scene_manager = NULL;
    }

    if(gui_components->view_dispatcher) {
        view_dispatcher_free(gui_components->view_dispatcher);
        gui_components->view_dispatcher = NULL;
    }

    if(gui_components->system_gui) {
        furi_record_close(RECORD_GUI);
        gui_components->system_gui = NULL;
    }

    FURI_LOG_D(TAG, "free gui");
    free(gui_components);
    context->gui_components = NULL;

    return true;
}

//currently a generic template
bool custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    app_context* app = context;
    return scene_manager_handle_custom_event(app->gui_components->scene_manager, event);
}

//currently a generic template
bool back_event_callback(void* context) {
    furi_assert(context);
    app_context* app = context;
    return scene_manager_handle_back_event(app->gui_components->scene_manager);
}

//currently a generic template
void uhf_tick_event_callback(void* context) {
    furi_assert(context);
    app_context* app = context;
    scene_manager_handle_tick_event(app->gui_components->scene_manager);
}

//the scene manager needs an array that contains arrays of all the event handler functions, by type
//they should be in the same order as the enumeration index so they can be refered to that way
void (*const Scene_On_Enter_Handlers[])(void*) = {
    main_menu_scene_on_enter,
    scan_options_scene_on_enter,
    scanning_scene_on_enter,
    confirm_scan_scene_on_enter,
    name_tag_scene_on_enter,
    write_tag_scene_on_enter,
    save_tag_scene_on_enter,
    load_tag_scene_on_enter};

bool (*const Scene_On_Event_Handlers[])(void*, SceneManagerEvent) = {
    main_menu_scene_on_event,
    scan_options_scene_on_event,
    scanning_scene_on_event,
    confirm_scan_scene_on_event,
    name_tag_scene_on_event,
    write_tag_scene_on_event,
    save_tag_scene_on_event,
    load_tag_scene_on_event};

void (*const Scene_On_Exit_Handlers[])(void*) = {
    main_menu_scene_on_exit,
    scan_options_scene_on_exit,
    scanning_scene_on_exit,
    confirm_scan_scene_on_exit,
    name_tag_scene_on_exit,
    write_tag_scene_on_exit,
    save_tag_scene_on_exit,
    load_tag_scene_on_exit};

static const SceneManagerHandlers SceneManager_Handlers_Arrays = {
    .on_enter_handlers = Scene_On_Enter_Handlers,
    .on_event_handlers = Scene_On_Event_Handlers,
    .on_exit_handlers = Scene_On_Exit_Handlers,
    .scene_num = SceneCount_Index,
};

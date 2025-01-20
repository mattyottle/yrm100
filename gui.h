#pragma once

// Include all GUI-related headers first
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/loading.h>
#include <gui/modules/button_menu.h>
#include <gui/modules/button_panel.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/popup.h>
#include <gui/modules/text_box.h>
#include <gui/modules/widget.h>

// Full definition of the forward-declared struct
struct gui_components {
    ViewDispatcher* view_dispatcher; // Manages switching between views
    SceneManager* scene_manager; // Manages scene transitions and state
    Gui* system_gui; // System GUI handle for cleanup

    // Core view modules
    Submenu* submenu; // Menu with text items and optional header
    TextInput* text_input; // Text entry field with keyboard
    VariableItemList* variable_item_list; // List of items with changeable values
    DialogEx* dialog; // Message box with 2-3 buttons
    Loading* loading; // Shows loading animation
    ButtonMenu* button_menu; // Horizontal list of buttons
    ButtonPanel* button_panel; // Grid of buttons
    ByteInput* byte_input; // Changed from Byte_Input
    Popup* popup; // Temporary notification overlay
    TextBox* text_box; // Scrollable text display
    Widget* widget; // Custom drawing canvas
};

// View module usage tracking
#define USE_SUBMENU       true // Main menu, load menu
#define USE_TEXT_INPUT    true // Tag naming
#define USE_VARIABLE_LIST true // Scan options
#define USE_DIALOG        true // Confirmations
#define USE_LOADING       true // During scan/write
#define USE_BUTTON_MENU   false // Not currently used
#define USE_BUTTON_PANEL  false // Not currently used
#define USE_BYTE_INPUT    false // Not currently used
#define USE_POPUP         false // Not currently used
#define USE_TEXT_BOX      false // Not currently used
#define USE_WIDGET        false // Not currently used

// Now include files that need the full struct definition
#include "types.h"
#include "yrm100.h"

// Scene includes
#include "scenes/main_menu_scene.h"
#include "scenes/scan_options_scene.h"
#include "scenes/scanning_scene.h"
#include "scenes/confirm_scan_scene.h"
#include "scenes/name_tag_scene.h"
#include "scenes/write_tag_scene.h"
#include "scenes/save_tag_scene.h"
#include "scenes/load_tag_scene.h"

//the different views get referred to by number
typedef enum {
    ViewSubmenu_Index,
    ViewTextInput_Index,
    ViewVariableList_Index,
    ViewDialog_Index,
    ViewLoading_Index,
    ViewButtonMenu_Index,
    ViewButtonPanel_Index,
    ViewByteInput_Index,
    ViewPopup_Index,
    ViewTextBox_Index,
    ViewWidget_Index,
} ViewType;

//flipper also refers to the scenes by number
typedef enum {
    SceneMainMenu_Index, // Main menu, scan, write, load, save (if a tag is active)
    SceneScanOptions_Index, // Select how long to scan for
    SceneScanning_Index, // Hourglass animation
    SceneConfirmScan_Index, // Rescan, ok
    SceneNameTag_Index, // Give the tag a name
    SceneWriteTag_Index, // Write data to a tag
    SceneSaveTag_Index, // Save tag data to storage
    SceneLoadTag_Index, // Read tag data from storage
    SceneCount_Index, // This should be the last one in the enum list
} Scene;

static const SceneManagerHandlers SceneManager_Handlers_Arrays;

// Prototypes for functions
bool gui_init(app_context* context);
bool gui_free(app_context* context);
bool custom_event_callback(void* context, uint32_t event);
bool back_event_callback(void* context);
void uhf_tick_event_callback(void* context);

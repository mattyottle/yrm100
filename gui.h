#pragma once

#include "yrm100.h"

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>

//need to include the header for each module being used below
#include <gui/modules/variable_item_list.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>

typedef struct {
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;

    //also include view modules needed for whatever scenes I'll be using
    //visual guide to built in view modules found here: https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/
    TextInput*
        TextInputView; ///The TextInput module is used for capturing a text value as a string for later usage in an application.
    Submenu*
        SubMenuView; //The SubMenu module is another horizontal-scrolling menu but with a text header and without icons next to each option.
    VariableItemList*
        ItemListView; //The VariableItemList module is useful for views such as configuration menus that deal with multiple types data being configured at once.
    DialogEx*
        DialogView; //The Dialog module displays a header and detail text and prompts the user with 2 (or 3) options which can be selected using the d-pad.

    //check on purpose of device_verified and view_device_info "view settings" in uhf_app_i.h later

} gui_managers;

//the different views get referred to by number
typedef enum {
    TextInputView_Index,
    SubMenuView_Index,
    ItemListView_Index,
    DialogView_Index,
} Views;

//flipper also refers to the scenes by number
typedef enum {
    MainMenuScene_Index, //the main menu, scan, write, load, save (if a tag is active)
    ScanOptionsScene_Index, //select how long to scan for
    ScannigScene_Idnex, //list tags that were found/read
    ConfirmScanScene_Index, //rescan, ok
    NameTagScene_Index, //give the tag a name
    WriteTagScene_Index, //write data to a tag
    SaveTagScene_Index, //Save tag data to storage
    LoadTagScene_Index, //read tag data from storage
    NumberOfScenes_Index, //this should be the last one in the enun list
} Scenes;

static const SceneManagerHandlers yrm_SceneManagerHandlers;

// Prototypes for functions
bool gui_init(void* context[CONTEXT_SIZE]);
bool gui_free(void* context[CONTEXT_SIZE]);
bool custom_event_callback(void* context, uint32_t event);
bool back_event_callback(void* context);
void uhf_tick_event_callback(void* context);

// Scene handlers
void MainMenuScene_On_Enter(void* context);
void ScanOptionsScene_On_Enter(void* context);
void ScanningScene_On_Enter(void* context);
void ConfirmScanScene_On_Enter(void* context);
void NameTagScene_On_Enter(void* context);
void WriteTagScene_On_Enter(void* context);
void SaveTagScene_On_Enter(void* context);
void LoadTagScene_On_Enter(void* context);

bool MainMenuScene_On_Event(void* context, SceneManagerEvent event);
bool ScanOptionsScene_On_Event(void* context, SceneManagerEvent event);
bool ScanningScene_On_Event(void* context, SceneManagerEvent event);
bool ConfirmScanScene_On_Event(void* context, SceneManagerEvent event);
bool NameTagScene_On_Event(void* context, SceneManagerEvent event);
bool WriteTagScene_On_Event(void* context, SceneManagerEvent event);
bool SaveTagScene_On_Event(void* context, SceneManagerEvent event);
bool LoadTagScene_On_Event(void* context, SceneManagerEvent event);

void MainMenuScene_On_Exit(void* context);
void ScanOptionsScene_On_Exit(void* context);
void ScanningScene_On_Exit(void* context);
void ConfirmScanScene_On_Exit(void* context);
void NameTagScene_On_Exit(void* context);
void WriteTagScene_On_Exit(void* context);
void SaveTagScene_On_Exit(void* context);
void LoadTagScene_On_Exit(void* context);

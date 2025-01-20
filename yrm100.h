// This program reads a UHF RFID tag, stores the tag, and writes tags from the store

/*/ Things to remember:
    // Wrapper function between all functions just in case I need it later
    // set pointers to null after freeing
    // the function that calls an allocating function must also call a freeing function
    // Scenes are generally unloaded when not in use
*/

#pragma once

#include <furi.h>
#include <furi_hal.h>
#include "types.h"
#include "gui.h"

#define TAG "yrm100"

//prototypes
bool main_entry(void* p);
bool tag_data_init(app_context* context);
bool tag_data_free(app_context* context);

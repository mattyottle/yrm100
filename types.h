#pragma once

#include <furi.h>
#include <stdint.h>
#include <stdbool.h>

#define TAG_NAME_MAX_LENGTH      20
#define TAG_EPC_DATA_MAX_LENGTH  62
#define TAG_TID_DATA_MAX_LENGTH  16
#define TAG_USER_DATA_MAX_LENGTH 64

typedef struct uhf_tag {
    bool is_loaded;
    char tag_name[TAG_NAME_MAX_LENGTH];
    uint8_t tag_length;
    char tag_epc_data[TAG_EPC_DATA_MAX_LENGTH];
    uint8_t tag_epc_data_length;
    char tag_tid_data[TAG_TID_DATA_MAX_LENGTH];
    uint8_t tag_tid_data_length;
    char tag_user_data[TAG_USER_DATA_MAX_LENGTH];
    uint8_t tag_user_data_length;
} uhf_tag;

// Forward declare only, no struct definition here
struct gui_components;

typedef struct app_context {
    struct gui_components* gui_components;
    uhf_tag* uhf_tag;
} app_context;

#pragma once

#include <furi.h>
#include <stdint.h>
#include <stdbool.h>

#define TAG "yrm100" //used for log labels
#define TAG_NAME_MAX_LENGTH      20
#define TAG_EPC_DATA_MAX_LENGTH  62
#define TAG_TID_DATA_MAX_LENGTH  16
#define TAG_USER_DATA_MAX_LENGTH 64
#define TAG_ACCESS_PASS_LENGTH   4

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
    uint8_t access_password[TAG_ACCESS_PASS_LENGTH];  
} uhf_tag;

// Forward declare only, no struct definition here
struct gui_components;
struct yrm100_config;
struct uart_state;

typedef struct app_context {
    gui_components* gui_components;  //typedef found in gui.h
    uhf_tag* uhf_tag;
    yrm100_hw_state* hw_state; //typedef found in yrm100_hw_device.h
    uart_state* uart_state; //typedef found in uart_control.h
} app_context;

/**
 * @brief Perform quick vibration pulses.
 * 
 * @param pulse_count Number of pulses.
 */
void quick_vibration_pulses(uint8_t pulse_count);

/**
 * @brief Main entry point for the application.
 * 
 * @param p Pointer to application parameters.
 * @return true if the application ran successfully, false otherwise.
 */
bool main_entry(void* p);

/**
 * @brief Initialize tag data.
 * 
 * @param context The application context.
 * @return true if initialization was successful, false otherwise.
 */
bool tag_data_init(app_context* context);

/**
 * @brief Free tag data.
 * 
 * @param context The application context.
 * @return true if freeing was successful, false otherwise.
 */
bool tag_data_free(app_context* context);

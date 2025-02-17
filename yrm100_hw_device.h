#pragma once

#include <furi.h>
#include <furi_hal.h>
#include "yrm100_app.h"
#include "yrm100_hw_device.h"
#include "uart_control.h"
#include "yrm_100.h"

#define YRM100_VERSION_LENGTH 16    // Typical format: "vX.Y.Z" (8 chars + null)
#define YRM100_MANUFACTURER_LENGTH 32  // Allow for longer manufacturer names

#define YRM100_CMD_START 0xBB
#define YRM100_CMD_END 0x7E
#define YRM100_MIN_RESPONSE_LENGTH 8
#define YRM100_STATUS_READY 0x00

static const uint8_t CMD_STOP_SCAN[] = {0xBB, 0x00, 0x28, 0x00, 0x00, 0x28, 0x7E};
static const uint8_t CMD_GET_STATUS[] = {0xBB, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x7E};
static const uint8_t CMD_SET_RF_POWER[] = {0xBB, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x00, 0x7E};
static const uint8_t CMD_SET_FREQUENCY[] = {0xBB, 0x00, 0x0F, 0x00, 0x02, 0x00, 0x00, 0x00, 0x7E};
static const uint8_t CMD_SET_SESSION[] = {0xBB, 0x00, 0x12, 0x00, 0x02, 0x00, 0x00, 0x00, 0x7E};
static const uint8_t CMD_SINGLE_MODE[] = {0xBB, 0x00, 0x1B, 0x00, 0x01, 0x01, 0x1C, 0x7E};
static const uint8_t CMD_SET_HOPPING[] = {0xBB, 0x00, 0x0D, 0x00, 0x01, 0x01, 0x0F, 0x7E}; // Enable hopping
static const uint8_t CMD_SET_MULTIPLE_MODE[] = {0xBB, 0x00, 0x1B, 0x00, 0x01, 0x00, 0x1C, 0x7E}; // Multiple tag mode
static const uint8_t CMD_START_INVENTORY[] = {0xBB, 0x00, 0x27, 0x00, 0x03, 0x22, 0x27, 0x10, 0x83, 0x7E};
static const uint8_t CMD_READ_TAG_DATA[] = {0xBB, 0x00, 0x39, 0x00, 0x00, 0x39, 0x7E};
static const uint8_t CMD_LOW_POWER[] = {0xBB, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x0C, 0x7E};

// Command response timeouts (ms)
#define YRM100_POWER_TIMEOUT 100
#define YRM100_FREQ_TIMEOUT 100
#define YRM100_SESSION_TIMEOUT 100
#define YRM100_MODE_TIMEOUT 100
#define YRM100_INVENTORY_TIMEOUT 500    // Longer timeout for inventory
#define YRM100_TAG_READ_TIMEOUT 200     // Timeout for reading tag dataus
#define YRM100_CLEANUP_TIMEOUT 100      // Timeout for cleanup operations

// Device configuration options
const uint16_t YRM100_DURATIONS[YRM100_DURATION_COUNT] = {0, 5000, 10000, 30000};
const char* const YRM100_DURATION_NAMES[YRM100_DURATION_COUNT] = {"Cont.", "5s", "10s", "30s"};

// YRM100 device status possibilities
typedef enum {
    Yrm100StatusIdle,
    Yrm100StatusScanning,
    Yrm100StatusWriting,
    Yrm100StatusError
} yrm100_hw_status_flag;

// Fixed device parameters
#define YRM100_FIXED_SESSION 0x01      // Session 1 (S1)
#define YRM100_FIXED_RF_POWER 26       // Fixed RF power output (26 dBm)
#define YRM100_BAUD_RATE 115200        // Conservative baud rate 

// TO DO  - see if these are really needed
#define YRM100_POLL_DELAY_MS 50        // Delay between polls
#define YRM100_MAX_POLLS_PER_SCAN 100  // Maximum number of polling attempts per scan cycle
#define YRM100_HOP_INTERVAL_MS 400     // Time between frequency hops/ Whether scan was manually stopped


typedef struct {
    yrm100_hw_status_flag status_flag;
    uint16_t scan_duration_ms;    
    mutex_t* mutex;
    thread_info* rx_tx_thread_handle;
    thread_info* timer_thread_handle;

    // Device information
    char hw_version[YRM100_VERSION_LENGTH];     // Hardware version string
    char sw_version[YRM100_VERSION_LENGTH];     // Software version string
    char manufacturer[YRM100_MANUFACTURER_LENGTH]; // Manufacturer name

} yrm100_hw_state;

// callback type for nonblocking scan
typedef void (*yrm100_rx_callback)(uint8_t* data, size_t length, void* context);

bool yrm100_hw_init(void); 

bool yrm100_hw_get_version(void);

bool yrm100_hw_stop_scan(void);

bool yrm100_hw_start_scan(void);

bool yrm100_hw_read_tag(void);

bool yrm100_hw_write_tag(void);

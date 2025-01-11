#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//#include <core/memmgr.h>
//#include <furi_hal_memory.h>

#define TAG_NAME_MAX_LENGTH      20 //max 21 characters fits on the screen (I think?)
#define TAG_EPC_DATA_MAX_LENGTH  62
#define TAG_TID_DATA_MAX_LENGTH  16
#define TAG_USER_DATA_MAX_LENGTH 64

#define CONTEXT_SIZE 2 //the number of items in the context array

#define TAG "yrm100"

typedef enum {
    gui_context,
    tag_data,
} context_index;

/*  Tag formats
    // Standard EPC Gen2 Tag:
        // EPC Memory: 96 bits = 12 bytes.
        // TID Memory: 64 bits = 8 bytes.
        // User Memory: 128 bits = 16 bytes (typical for low-cost tags).
    
    // Specialized UHF RFID Tag:
        // EPC Memory: 496 bits = 62 bytes.
        // TID Memory: 128 bits = 16 bytes.
        // User Memory: 64 KB (max for high-memory tags).
*/

typedef struct yrm100 yrm100_entry;

// This program reads an UHF RFID tag, stores the tag, and writes tags from the store
// Scenes are generally unloaded when not in use

/*/ Things to remember:
    // Abstraction function between all functions to unpack a single void* argument
    // set pointers to null after freeing
    // the function that mallocs frees
*/

/*yrm100_entry
    //entry point
    //malloc active_tag
    //call gui init
    //on enter, alloc, free, exit - log trace stack size
*/

/*gui
    //stuff to initialize scene manager with view dispatcher
*/

/*main - has own scene
    //main menu
        // options to scan, save, load, and write
    //display active tag name
*/

/*save_load
    //scene uses loading & submenu views

    //save
        //save save tag to storage
        //args name & data
        //returns true if successful

    //load
        //display list of tags in storage, return name & data
*/

/*read_write - 
    //read - has own scene
        //args -
            //uhf_tag* to already allocated scanned_tag, by calling function. make sure to check if it's valid
            //void* callback maybe?
        //uses variable item list view to select number of seconds to scan
        //starts a separate thread to scan for that many seconds, whenever a tag is read, it goes into scanned_tag
            //every second, update the screen with the most recent scanned tag, plus the number of tags read so far
            //after the chosen time period, prompt to replace active_tag with the scanned_tag using a dialog view
                //warn if multiple tags were read
        //options - cancel, rescan, keep
            //cancel goes to callback, returns false
            //rescan goes to original scanning prompt view 
            //keep goes to callback, returns true
        //returns true if a tag was read and scanned_tag has something in it
    //write - basically the same thing
        //args
            //uhf_tag* that's the active tag, make sure to check if it's valid
        //variable item list to select number of seconds to try to write
        //similar separate thread
        //once write is complete, read the tag and compare
        //if write failed (didn't complete in time or tag not the same), offer retry
        //if successful, offer "ok" that takes you back to the main menu
            
*/

/* uhf
    init
    hardware level read
    hardware level write
    hardware config interface
*/

typedef struct {
    /*One of these will be allocated all the time as an "active tag", and will represent the program's operating state.
    //The read function will temporarily use another one.
    //make sure to actively shorten the data when writing to this struct
    */

    bool is_loaded; //this byte could be shortened, but that would require a classy helper function to stay readable
    char tag_name[TAG_NAME_MAX_LENGTH];
    uint8_t tag_length;
    char tag_epc_data[TAG_EPC_DATA_MAX_LENGTH];
    uint8_t tag_epc_data_length;
    char tag_tid_data[TAG_TID_DATA_MAX_LENGTH];
    uint8_t tag_tid_data_length;
    char tag_user_data[TAG_USER_DATA_MAX_LENGTH];
    uint8_t tag_user_data_length;
    //if is_loaded == false, the other members will be uninitialized and should not be accessed.
} uhf_tag;

//prototypes
bool main_entry(void* arg1);
bool tempname(void* arg1);
bool tag_data_init(void* context[CONTEXT_SIZE]);
bool tag_data_free(void* context[CONTEXT_SIZE]);

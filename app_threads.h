#pragma once

#include <furi.h>
#include <furi_hal.h>

// Thread states for better state management
typedef enum {
    ThreadStateUninitialized,
    ThreadStateReady,
    ThreadStateRunning,
    ThreadStateSuspended,
    ThreadStateStopping,
    ThreadStateStopped,
    ThreadStateError
} ThreadState;

// Error codes for better error handling
typedef enum {
    ThreadErrorNone,
    ThreadErrorAllocationFailed,
    ThreadErrorAlreadyRunning,
    ThreadErrorNotRunning,
    ThreadErrorTimeout,
    ThreadErrorInvalidState,
    ThreadErrorQueueFull,
    ThreadErrorQueueEmpty
} ThreadError;

// Structure to hold thread information
typedef struct {
    void* thread_handle;
    void (*thread_func)(void*);
    void* arg;
    int priority;
    bool is_running;
    FuriMutex* mutex;
    FuriSemaphore* semaphore;
    FuriMessageQueue* event_queue;
    ThreadState state;
    ThreadError last_error;
    char thread_name[32];
    uint32_t timeout_ms;
} thread_info;

/**
 * @brief Allocate resources for a new thread.
 * 
 * @return Pointer to the allocated thread_info structure, or NULL if allocation failed.
 */
thread_info* thread_alloc(void);

/**
 * @brief Start a thread with the specified function and argument.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param thread_func Function to be executed by the thread.
 * @param arg Argument to be passed to the thread function.
 * @return true if the thread was started successfully, false otherwise.
 */
bool thread_start(thread_info* thread, void (*thread_func)(void*), void* arg);

/**
 * @brief Stop the specified thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the thread was stopped successfully, false otherwise.
 */
bool thread_stop(thread_info* thread);

/**
 * @brief Free resources allocated for the specified thread.
 * 
 * @param thread Pointer to the thread_info structure.
 */
void thread_free(thread_info* thread);

/**
 * @brief Set the priority of a thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param priority The priority to be set.
 * @return true if the priority was set successfully, false otherwise.
 */
bool thread_set_priority(thread_info* thread, int priority);

/**
 * @brief Get the priority of a thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return The priority of the thread, or -1 if an error occurred.
 */
int thread_get_priority(thread_info* thread);

/**
 * @brief Put the thread to sleep for a specified duration.
 * 
 * @param duration The duration to sleep in milliseconds.
 */
void thread_sleep(uint32_t duration);

/**
 * @brief Wake up a sleeping thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the thread was woken up successfully, false otherwise.
 */
bool thread_wakeup(thread_info* thread);

/**
 * @brief Wait for a thread to finish execution.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the thread finished successfully, false otherwise.
 */
bool thread_join(thread_info* thread);

/**
 * @brief Lock the thread's mutex.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the mutex was locked successfully, false otherwise.
 */
bool thread_lock(thread_info* thread);

/**
 * @brief Unlock the thread's mutex.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the mutex was unlocked successfully, false otherwise.
 */
bool thread_unlock(thread_info* thread);

/**
 * @brief Wait for the thread's semaphore.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the semaphore was waited successfully, false otherwise.
 */
bool thread_wait(thread_info* thread);

/**
 * @brief Signal the thread's semaphore.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the semaphore was signaled successfully, false otherwise.
 */
bool thread_signal(thread_info* thread);

/**
 * @brief Send an event to the thread's event queue.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param event The event to be sent.
 * @return true if the event was sent successfully, false otherwise.
 */
bool thread_send_event(thread_info* thread, uint32_t event);

/**
 * @brief Receive an event from the thread's event queue.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param event Pointer to store the received event.
 * @return true if the event was received successfully, false otherwise.
 */
bool thread_receive_event(thread_info* thread, uint32_t* event);

/**
 * @brief Set the thread name for debugging purposes.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param name Name to set for the thread.
 * @return true if the name was set successfully, false otherwise.
 */
bool thread_set_name(thread_info* thread, const char* name);

/**
 * @brief Get the current state of the thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return Current ThreadState of the thread.
 */
ThreadState thread_get_state(thread_info* thread);

/**
 * @brief Get the last error that occurred in the thread.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return Last ThreadError that occurred.
 */
ThreadError thread_get_last_error(thread_info* thread);

/**
 * @brief Set the timeout for thread operations.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param timeout_ms Timeout in milliseconds.
 */
void thread_set_timeout(thread_info* thread, uint32_t timeout_ms);

/**
 * @brief Send an event to the thread's event queue with timeout.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param event The event to be sent.
 * @param timeout_ms Timeout in milliseconds.
 * @return true if the event was sent successfully, false otherwise.
 */
bool thread_send_event_timeout(thread_info* thread, uint32_t event, uint32_t timeout_ms);

/**
 * @brief Receive an event from the thread's event queue with timeout.
 * 
 * @param thread Pointer to the thread_info structure.
 * @param event Pointer to store the received event.
 * @param timeout_ms Timeout in milliseconds.
 * @return true if the event was received successfully, false otherwise.
 */
bool thread_receive_event_timeout(thread_info* thread, uint32_t* event, uint32_t timeout_ms);

/**
 * @brief Suspend thread execution.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the thread was suspended successfully, false otherwise.
 */
bool thread_suspend(thread_info* thread);

/**
 * @brief Resume thread execution.
 * 
 * @param thread Pointer to the thread_info structure.
 * @return true if the thread was resumed successfully, false otherwise.
 */
bool thread_resume(thread_info* thread);

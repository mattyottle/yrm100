#pragma once

#include <furi.h>
#include <furi_hal.h>

/* refugees


    // UART status
    bool uart_initialized;
    yrm100_rx_callback rx_callback;
    void* callback_context;




*/

// UART error codes
typedef enum {
    UartErrorNone,
    UartErrorInit,
    UartErrorConfig,
    UartErrorTransmit,
    UartErrorReceive,
    UartErrorTimeout,
    UartErrorBufferOverflow,
    UartErrorBufferUnderflow,
    UartErrorParity,
    UartErrorFraming
} uart_error_t;

// UART statistics
typedef struct {
    uint32_t tx_bytes;
    uint32_t rx_bytes;
    uint32_t errors;
    uint32_t overflow_count;
    uint32_t parity_errors;
    uint32_t framing_errors;
} uart_stats_t;

// UART configuration
typedef struct {
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t parity;
    bool flow_control;
    uint32_t rx_buffer_size;
    uint32_t tx_buffer_size;
    uart_rx_callback_t rx_callback;
    void* callback_context;
} uart_config_t;

// Add TX/RX configuration
#define UART_RX_BUF_SIZE 256
#define UART_TX_BUF_SIZE 256

// Add callback type definition
typedef void (*uart_rx_callback_t)(uint8_t* data, size_t length, void* context);

/**
 * @brief Initialize the UART interface.
 * 
 * @return true if initialization was successful, false otherwise.
 */
bool uart_init(void);

/**
 * @brief Configure UART settings.
 * 
 * @param baud_rate The baud rate for UART communication.
 * @param parity The parity setting (e.g., none, even, odd).
 * @param stop_bits The number of stop bits (e.g., 1, 2).
 * @return true if configuration was successful, false otherwise.
 */
bool uart_configure(uint32_t baud_rate, uint8_t parity, uint8_t stop_bits);

/**
 * @brief Send data over UART.
 * 
 * @param data Pointer to the data to be sent.
 * @param length Length of the data to be sent.
 * @return Number of bytes sent, or -1 if an error occurred.
 */
int uart_send(const uint8_t* data, size_t length);

/**
 * @brief Receive data from UART.
 * 
 * @param buffer Pointer to the buffer to store received data.
 * @param length Length of the buffer.
 * @return Number of bytes received, or -1 if an error occurred.
 */
int uart_receive(uint8_t* buffer, size_t length);

/**
 * @brief Deinitialize the UART interface.
 * 
 * @return true if deinitialization was successful, false otherwise.
 */
bool uart_deinit(void);

/**
 * @brief Initialize the UART buffer.
 * 
 * @return true if buffer initialization was successful, false otherwise.
 */
bool uart_buffer_init(void);

/**
 * @brief Write data to the UART buffer.
 * 
 * @param data Pointer to the data to be written.
 * @param length Length of the data to be written.
 * @return Number of bytes written, or -1 if an error occurred.
 */
int uart_buffer_write(const uint8_t* data, size_t length);

/**
 * @brief Read data from the UART buffer.
 * 
 * @param buffer Pointer to the buffer to store read data.
 * @param length Length of the buffer.
 * @return Number of bytes read, or -1 if an error occurred.
 */
int uart_buffer_read(uint8_t* buffer, size_t length);

/**
 * @brief Clear the UART buffer.
 */
void uart_buffer_clear(void);

/**
 * @brief Get the last error that occurred on the UART.
 * 
 * @return The last uart_error_t that occurred.
 */
uart_error_t uart_get_last_error(void);

/**
 * @brief Get UART statistics.
 * 
 * @param stats Pointer to uart_stats_t structure to store statistics.
 */
void uart_get_stats(uart_stats_t* stats);

/**
 * @brief Reset UART statistics.
 */
void uart_reset_stats(void);

/**
 * @brief Get the number of bytes available to read.
 * 
 * @return Number of bytes available in the receive buffer.
 */
size_t uart_available(void);

/**
 * @brief Get the space available in the transmit buffer.
 * 
 * @return Number of bytes that can be written to the transmit buffer.
 */
size_t uart_tx_space_available(void);

/**
 * @brief Enable UART interrupts.
 * 
 * @param rx_interrupt Enable receive interrupt.
 * @param tx_interrupt Enable transmit interrupt.
 * @return true if successful, false otherwise.
 */
bool uart_enable_interrupts(bool rx_interrupt, bool tx_interrupt);

/**
 * @brief Set UART callback for receive events.
 * 
 * @param callback Function to call when data is received.
 * @param context Context pointer to pass to callback.
 */
void uart_set_rx_callback(void (*callback)(void* context), void* context);

/**
 * @brief Flush UART buffers.
 * 
 * @param rx Flush receive buffer.
 * @param tx Flush transmit buffer.
 */
void uart_flush(bool rx, bool tx);

/**
 * @brief Set timeout for UART operations.
 * 
 * @param timeout_ms Timeout in milliseconds.
 */
void uart_set_timeout(uint32_t timeout_ms);

/**
 * @brief Wait for all data to be transmitted.
 * 
 * @param timeout_ms Maximum time to wait in milliseconds.
 * @return true if all data transmitted, false if timeout occurred.
 */
bool uart_wait_tx_complete(uint32_t timeout_ms);

/**
 * @brief Check if UART is busy transmitting.
 * 
 * @return true if UART is transmitting, false otherwise.
 */
bool uart_is_tx_busy(void);

/**
 * @brief Configure UART flow control.
 * 
 * @param enabled Enable or disable flow control.
 * @return true if successful, false otherwise.
 */
bool uart_set_flow_control(bool enabled);

/**
 * @brief Set callback for UART receive events
 * 
 * @param callback Function to call when data is received
 * @param context Context pointer to pass to callback
 * @return true if successful, false otherwise
 */
bool uart_set_callback(uart_rx_callback_t callback, void* context);

/**
 * @brief Send command and wait for response
 * 
 * @param cmd Command buffer to send
 * @param cmd_len Length of command
 * @param response Buffer to store response
 * @param resp_len Maximum length of response buffer
 * @param timeout_ms Timeout in milliseconds
 * @return Number of bytes received or -1 on error
 */
int uart_tx_with_response(const uint8_t* cmd, size_t cmd_len, uint8_t* response, size_t resp_len, uint32_t timeout_ms);

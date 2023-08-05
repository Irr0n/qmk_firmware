#pragma once

/* handedness */
#define MASTER_RIGHT

/* trackball */
/* scrolling sensitivity */
#define CHARYBDIS_MINIMUM_SNIPING_DPI 150
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 400

#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 32 // layer activation sensitivity

#define CHARYBDIS_DRAGSCROLL_REVERSE_Y // natural scroll

/* auto pointer layer activation */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 6
#define AUTO_MOUSE_TIME 500 // Time layer remains active after activation 	ideally (250-1000) 	ms 	650 ms
// #define AUTO_MOUSE_DELAY 	// Lockout time after non-mouse key is pressed 	ideally (100-1000) 	ms 	TAPPING_TERM or 200 ms

// #define MOUSE_EXTENDED_REPORT // increase sensor range

// Enable use of pointing device on slave split.
// #define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
// #define POINTING_DEVICE_RIGHT
// Limits the frequency that the sensor is polled for motion.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 1
// Invert X axis on mouse reports.
// #define POINTING_DEVICE_INVERT_X

/* keyboard duration terms */
//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 150
#define COMBO_TERM 20
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 25


/* tri-layer config */
#define TRI_LAYER_LOWER_LAYER 1 // extension layer
#define TRI_LAYER_UPPER_LAYER 2 // symbol layer
#define TRI_LAYER_ADJUST_LAYER 5 // media layer

#define TAPPING_TOGGLE 1 // tap-toggle keys must be pressed one time to do tap action
//#define PERMISSIVE_HOLD

/* miscellaneous */
//#define DEBOUNCE 5

// /* SPI & PMW3360 settings. */
// #define SPI_DRIVER SPID0
// #define SPI_SCK_PIN GP22
// #define SPI_MISO_PIN GP20
// #define SPI_MOSI_PIN GP23
// #define POINTING_DEVICE_CS_PIN GP16

// /* reset settings */
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

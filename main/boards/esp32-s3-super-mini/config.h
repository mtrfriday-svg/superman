#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

#define AUDIO_INPUT_SAMPLE_RATE  16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// Two separate I2S buses: one for the INMP441 mic (input only),
// one for the MAX98357A amp (output only). Do not comment this out
// on this board, since mic and speaker are wired to different pins.
#define AUDIO_I2S_METHOD_SIMPLEX

#ifdef AUDIO_I2S_METHOD_SIMPLEX

// INMP441 (I2S microphone)
#define AUDIO_I2S_MIC_GPIO_WS   GPIO_NUM_2
#define AUDIO_I2S_MIC_GPIO_SCK  GPIO_NUM_3
#define AUDIO_I2S_MIC_GPIO_DIN  GPIO_NUM_4

// MAX98357A (I2S amplifier)
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_5
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_6
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_7

#else

#define AUDIO_I2S_GPIO_WS GPIO_NUM_2
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_6
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_4
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_5

#endif

// Onboard/general purpose status LED
#define BUILTIN_LED_GPIO        GPIO_NUM_48

// Wake/Boot button (software button, separate from the module's own
// GPIO0 download-mode strap)
#define BOOT_BUTTON_GPIO        GPIO_NUM_1

// Volume buttons
#define VOLUME_UP_BUTTON_GPIO   GPIO_NUM_10
#define VOLUME_DOWN_BUTTON_GPIO GPIO_NUM_11

// SSD1306 / SH1106 OLED over I2C
#define DISPLAY_SDA_PIN GPIO_NUM_8
#define DISPLAY_SCL_PIN GPIO_NUM_9
#define DISPLAY_WIDTH   128

#if CONFIG_OLED_SSD1306_128X32
#define DISPLAY_HEIGHT  32
#elif CONFIG_OLED_SSD1306_128X64
#define DISPLAY_HEIGHT  64
#elif CONFIG_OLED_SH1106_128X64
#define DISPLAY_HEIGHT  64
#define SH1106
#else
#error "OLED display type is not selected"
#endif

#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y true

// MCP demo tool: control a lamp on a free GPIO (not physically required)
#define LAMP_GPIO GPIO_NUM_18

#endif // _BOARD_CONFIG_H_

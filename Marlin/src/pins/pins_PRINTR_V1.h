/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#if !defined(__STM32F4__) && !defined(STM32F4xx)
  #error "Oops!  Make sure you have an STM32F4 board selected from the 'Tools -> Boards' menu."
#endif

/**
 * 21017 Venelin Efremov Marlin for stm32f4 test
 */

#define DEFAULT_MACHINE_NAME "STM32F4"
#define BOARD_NAME "Marlin for STM32F4"

// Enable I2C_EEPROM for testing
#define I2C_EEPROM

// Ignore temp readings during develpment.
#define BOGUS_TEMPERATURE_FAILSAFE_OVERRIDE

#define NUM_SERIAL 1

//
// Steppers
//
#define STEPPER_ENABLE_PIN PA5

#define X_STEP_PIN         PA4
#define X_DIR_PIN          PC4
#define X_ENABLE_PIN       STEPPER_ENABLE_PIN
#define X_MIN_PIN          PC10
#define X_MAX_PIN          PD2

#define Y_STEP_PIN         PC5
#define Y_DIR_PIN          PB12
#define Y_ENABLE_PIN       STEPPER_ENABLE_PIN
#define Y_MIN_PIN          PC11
#define Y_MAX_PIN          PB4

#define Z_STEP_PIN         PB13
#define Z_DIR_PIN          PB15
#define Z_ENABLE_PIN       STEPPER_ENABLE_PIN
#define Z_MIN_PIN          PC12
#define Z_MAX_PIN          PB5

#define Y2_STEP_PIN        -1
#define Y2_DIR_PIN         -1
#define Y2_ENABLE_PIN      -1

#define Z2_STEP_PIN        -1
#define Z2_DIR_PIN         -1
#define Z2_ENABLE_PIN      -1

#define E0_STEP_PIN        PC7
#define E0_DIR_PIN         PC8
#define E0_ENABLE_PIN      STEPPER_ENABLE_PIN

#define E1_STEP_PIN        PC9
#define E1_DIR_PIN         PA9
#define E1_ENABLE_PIN      STEPPER_ENABLE_PIN

#define E2_STEP_PIN        -1
#define E2_DIR_PIN         -1
#define E2_ENABLE_PIN      -1

//
// Misc. Functions
//
//#define SDPOWER            -1
#define SDSS               -1
#define LED_PIN            -1

//#define PS_ON_PIN          -1
//#define KILL_PIN           -1

//
// Heaters / Fans
//
#define HEATER_0_PIN       PA6   // EXTRUDER 0
#define HEATER_1_PIN       PA7   // EXTRUDER 1
//#define HEATER_2_PIN       -1

#define HEATER_BED_PIN     PB0   // BED
//#define HEATER_BED2_PIN    -1   // BED2
//#define HEATER_BED3_PIN    -1   // BED3

#define FAN_PIN            PB2
#define FAN1_PIN           PC6
#define FAN2_PIN           PB14
#define FAN3_PIN           PA8

//#define FAN_SOFT_PWM

//
// Temperature Sensors
//
#define TEMP_BED_PIN       PC0
#define TEMP_0_PIN         PA0
#define TEMP_1_PIN         PA1
#define TEMP_2_PIN         -1

// Laser control
#if ENABLED(SPINDLE_LASER_ENABLE)
#define SPINDLE_LASER_PWM_PIN       PB8
#define SPINDLE_LASER_ENABLE_PIN    PD5
#endif

//
// LCD Pins
//
#if ENABLED(ULTRA_LCD)

  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)
    #define LCD_PINS_RS         49   // CS chip select /SS chip slave select
    #define LCD_PINS_ENABLE     51   // SID (MOSI)
    #define LCD_PINS_D4         52   // SCK (CLK) clock
  #elif ENABLED(NEWPANEL) && ENABLED(PANEL_ONE)
    #define LCD_PINS_RS         PB8
    #define LCD_PINS_ENABLE     PD2
    #define LCD_PINS_D4         PB12
    #define LCD_PINS_D5         PB13
    #define LCD_PINS_D6         PB14
    #define LCD_PINS_D7         PB15
  #else
    #define LCD_PINS_RS         PB8
    #define LCD_PINS_ENABLE     PD2
    #define LCD_PINS_D4         PB12
    #define LCD_PINS_D5         PB13
    #define LCD_PINS_D6         PB14
    #define LCD_PINS_D7         PB15
    #if DISABLED(NEWPANEL)
      #define BEEPER_PIN        33
      // Buttons are attached to a shift register
      // Not wired yet
      //#define SHIFT_CLK 38
      //#define SHIFT_LD 42
      //#define SHIFT_OUT 40
      //#define SHIFT_EN 17
    #endif
  #endif

  #if ENABLED(NEWPANEL)

    #if ENABLED(REPRAP_DISCOUNT_SMART_CONTROLLER)

      #define BEEPER_PIN        37

      #define BTN_EN1           31
      #define BTN_EN2           33
      #define BTN_ENC           35

      #define SD_DETECT_PIN     49
      #define KILL_PIN          41

      #if ENABLED(BQ_LCD_SMART_CONTROLLER)
        #define LCD_BACKLIGHT_PIN 39
      #endif

    #elif ENABLED(REPRAPWORLD_GRAPHICAL_LCD)

      #define BTN_EN1           64
      #define BTN_EN2           59
      #define BTN_ENC           63
      #define SD_DETECT_PIN     42

    #elif ENABLED(LCD_I2C_PANELOLU2)

      #define BTN_EN1           47
      #define BTN_EN2           43
      #define BTN_ENC           32
      #define LCD_SDSS          53
      #define SD_DETECT_PIN     -1
      #define KILL_PIN          41

    #elif ENABLED(LCD_I2C_VIKI)

      #define BTN_EN1           22   // http://files.panucatt.com/datasheets/viki_wiring_diagram.pdf explains 40/42.
      #define BTN_EN2            7   // 22/7 are unused on RAMPS_14. 22 is unused and 7 the SERVO0_PIN on RAMPS_13.

      #define BTN_ENC           -1
      #define LCD_SDSS          53
      #define SD_DETECT_PIN     49

    #elif ENABLED(VIKI2) || ENABLED(miniVIKI)

      #define BEEPER_PIN        33

      // Pins for DOGM SPI LCD Support
      #define DOGLCD_A0         44
      #define DOGLCD_CS         45
      #define LCD_SCREEN_ROT_180

      #define BTN_EN1           22
      #define BTN_EN2            7
      #define BTN_ENC           39

      #define SDSS              53
      #define SD_DETECT_PIN     -1   // Pin 49 for display sd interface, 72 for easy adapter board

      #define KILL_PIN          31

      #define STAT_LED_RED_PIN  32
      #define STAT_LED_BLUE_PIN 35

    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)

      #define BTN_EN1           35
      #define BTN_EN2           37
      #define BTN_ENC           31
      #define SD_DETECT_PIN     49
      #define LCD_SDSS          53
      #define KILL_PIN          41
      #define BEEPER_PIN        23
      #define DOGLCD_CS         29
      #define DOGLCD_A0         27
      #define LCD_BACKLIGHT_PIN 33

    #elif ENABLED(MINIPANEL)

      #define BEEPER_PIN        42
      // Pins for DOGM SPI LCD Support
      #define DOGLCD_A0         44
      #define DOGLCD_CS         66
      #define LCD_BACKLIGHT_PIN 65   // backlight LED on A11/D65
      #define SDSS              53

      #define KILL_PIN          64
      // GLCD features
      //#define LCD_CONTRAST   190
      // Uncomment screen orientation
      //#define LCD_SCREEN_ROT_90
      //#define LCD_SCREEN_ROT_180
      //#define LCD_SCREEN_ROT_270
      // The encoder and click button
      #define BTN_EN1           40
      #define BTN_EN2           63
      #define BTN_ENC           59
      // not connected to a pin
      #define SD_DETECT_PIN     49

    #else

      // Beeper on AUX-4
      #define BEEPER_PIN        33

      // buttons are directly attached using AUX-2
      #if ENABLED(REPRAPWORLD_KEYPAD)
        #define BTN_EN1         64
        #define BTN_EN2         59
        #define BTN_ENC         63
        #define SHIFT_OUT       40
        #define SHIFT_CLK       44
        #define SHIFT_LD        42
      #elif ENABLED(PANEL_ONE)
        #define BTN_EN1         59   // AUX2 PIN 3
        #define BTN_EN2         63   // AUX2 PIN 4
        #define BTN_ENC         49   // AUX3 PIN 7
      #else
        #define BTN_EN1         37
        #define BTN_EN2         35
        #define BTN_ENC         31
      #endif

      #if ENABLED(G3D_PANEL)
        #define SD_DETECT_PIN   49
        #define KILL_PIN        41
      #else
        //#define SD_DETECT_PIN -1   // Ramps doesn't use this
      #endif

    #endif
  #endif // NEWPANEL

#endif // ULTRA_LCD

// Extruder filament end detectors
#define U_MIN_PIN          PB6
#define V_MIN_PIN          PB7
#define W_MIN_PIN          -1

#define STEPPER_SPI_MOSI   PC1
#define STEPPER_SPI_MISO   PC2
#define STEPPER_SPI_SCK    PB10
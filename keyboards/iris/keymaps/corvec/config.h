/*
Copyright 2018 Corey Kump <Corey.Kump@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define PERMISSIVE_HOLD
#define AUTO_SHIFT_TIMEOUT 135
#define NO_AUTO_SHIFT_SPECIAL
#define TAPPING_TERM 150
/*
Without this setting, sometimes there is an issue pressing the apostrophe and
then quickly pressing a key after, e.g., let's, which causes it to register
Ctrl+S instead of 's.
*/
#define IGNORE_MOD_TAP_INTERRUPT
#define SHIFT_LOCK_TIMEOUT 750
#define SHIFT_LOCK_REFRESH
/*
Generally I would recommend setting either both SHIFT_LOCK_REFRESH and SHIFT_LOCK_TOGGLE.
However, if you have a very short SHIFT_LOCK_TIMEOUT set (less than 0.5 seconds),
it's reasonable to set REFRESH but not TOGGLE.
*/
#define SHIFT_LOCK_TOGGLE
#define NO_SHIFT_LOCK_SYMBOLS


#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#endif

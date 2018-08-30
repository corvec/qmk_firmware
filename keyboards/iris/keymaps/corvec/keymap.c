/*
Copyright 2017 Corey Kump <Corey.Kump@gmail.com>

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

#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _COLEMAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3

#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  TG_SLCK,
  KC_MSFT // shift when held, activate shift for SHIFT_LOCK_TIMEOUT time when tapped
};

enum {
  TD_LSHIFT_CTL = 0,
  TD_RSHIFT_CTL,
  TD_ALT_CTL,
  TD_ALT_SHIFT
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Alt, twice for Shift
  [TD_ALT_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RSFT),
  // TAP once for Alt, twice for Control
  [TD_ALT_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RCTL),

  // Tap once for Shift, twice for Control
  [TD_LSHIFT_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LCTL),
  [TD_RSHIFT_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_RCTL)
};

#define KC_ KC_TRNS
#define KC_____ KC_TRNS
#define KC_XXXX KC_NO
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE

/**
 * Custom Corvec Bindings
 * 
 * Previously used but currently unused bindings are commented out.
 **/

/*Dual function with Raise*/
#define KC_RESC LT(_RAISE, KC_ESC)
// #define KC_RTAB LT(_RAISE, KC_TAB)
#define KC_RSPC LT(_RAISE, KC_SPC)

/*Dual function with Lower*/
#define KC_LENT LT(_LOWER, KC_ENT)
// #define KC_LDEL LT(_LOWER, KC_DEL)
// will have to create an extra layer before this key can be used,
// since the Lower layer has a key in the same location as KC_QUOT
// #define KC_LQUT LT(_LOWER, KC_QUOT)

/*Dual function with Shift*/
// #define KC_SESC SFT_T(KC_ESC)
// Used only if shift lock is enabled. Shift on hold, caps lock on tap.
#define KC_SFCL SFT_T(KC_CAPSLOCK)

/*Dual function with Alt*/
// #define KC_AENT ALT_T(KC_ENT)
#define KC_ASPC ALT_T(KC_SPC)

/*Dual function with Ctrl*/
// #define KC_CESC CTL_T(KC_ESC)
// #define KC_CTAB CTL_T(KC_TAB)
// #define KC_CDEL CTL_T(KC_DEL)
#define KC_CENT CTL_T(KC_ENT)
#define KC_CQUT CTL_T(KC_QUOT)

/*Tap dance keys*/
#define KC_TLSC TD(TD_LSHIFT_CTL)
#define KC_TRSC TD(TD_RSHIFT_CTL)
// TALS is used as ALT generally and as Shift when I want to type something all in CAPS
// The intent is to at some point use this key to activate a Shift toggle - like caps lock,
// but affecting numbers as well, and deactivating after 10-15 seconds.
#define KC_TALS TD(TD_ALT_CTL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RESC, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,CQUT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
#ifdef SHIFT_LOCK_TIMEOUT
     TLSC, Z  , X  , C  , V  , B  ,LGUI,     BSPC, K  , M  ,COMM,DOT ,SLSH,MSFT,
#else
     TLSC, Z  , X  , C  , V  , B  ,LGUI,     BSPC, K  , M  ,COMM,DOT ,SLSH,SFCL,
#endif
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LENT,CENT,         RSPC,SPC ,TALS
  //                  `----+----+----'        `----+----+----'
  ),


/**
 *  NOTE: The modifier keys on the QWERTY layer are intentionally different. The reasons for this are two-fold:
 *
 * 1. To make it easier for people to try out the keyboard.
 * 2. To make it more suitable as a gaming layer.
 *
 * Furthermore, at some point Auto-shift will be activated automatically upon swapping to the QWERTY layer.
 **/

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RESC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,CQUT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,LGUI,     BSPC, N  , M  ,COMM,DOT ,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LOWR,ENT ,         SPC ,RASE,RALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      F11, F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F12,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,LPRN,RPRN,LBRC,RBRC,MINS,               LEFT,DOWN, UP ,RGHT,PLUS,MINS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,BSLS,TILD,PIPE,EQL ,UNDS,    ,         ,HOME,PGDN,PGUP,END ,BSLS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,INS ,PSCR,    ,               MPRV,MPLY,MNXT,MUTE,VOLD,VOLU,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,LPRN,RPRN,LCBR,RCBR,XXXX,               XXXX, 4  , 5  , 6  ,PLUS,MINS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,BSLS,TILD,PIPE,EQL ,UNDS,    ,         ,XXXX, 1  , 2  , 3  ,BSLS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                   ,--------+--------+--------+--------+--------+--------.
      COLEMAK, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, QWERTY,
  //|--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                     _______, _______, _______, _______, KC_ASON, KC_ASUP,
  //|--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------+--------|
      _______, DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                     TG_SLCK, _______, _______, KC_ASRP,KC_ASOFF, KC_ASDN,
  //|--------+--------+--------+--------+--------+--------+--------. ,--------|--------+--------+--------+--------+--------+--------|
      BL_STEP, RESET  , _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,   RESET,
  //`--------+--------+--------+----+---+--------+--------+--------/ \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,           _______, _______, _______
  //                                `--------+--------+--------'         `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#include "shift_lock.c"

keypos_t last_press;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  /* used to determine if a key has been pressed since the currently released key was pressed. */
  if (record->event.pressed) {
    last_press = record->event.key;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
    case LOWER:
    case KC_LENT:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return keycode != LOWER;
    case KC_RSPC:
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return keycode != RAISE;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
#ifdef SHIFT_LOCK_TIMEOUT
    case KC_MSFT:
      return handle_shift_lock_keypress(keycode, record, last_press);
    case TG_SLCK:
      shift_lock_enabled = !shift_lock_enabled;
      return false;
#endif
  }
#ifdef SHIFT_LOCK_TIMEOUT
  if (!conditionally_apply_shift_lock(keycode, record)) {
    return false;
  }
#endif

  return true;
}


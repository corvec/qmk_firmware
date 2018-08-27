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

#define KEY_POSITION_MATCHES(key1,key2) ((key1.col==key2.col) && (key2.row==key2.row))
uint16_t custom_shift_timer;
bool shift_lock_active = false;

#ifdef SHIFT_LOCK_TIMEOUT
  int shift_lock_timeout = SHIFT_LOCK_TIMEOUT;
  bool shift_lock_enabled = true;
  #ifdef SHIFT_LOCK_REFRESH
    bool shift_lock_refresh = true;
  #else
    bool shift_lock_refresh = false;
  #endif
  #ifdef SHIFT_LOCK_TOGGLE
    bool shift_lock_toggle = true;
  #else
    bool shift_lock_toggle = false;
  #endif
#else
  bool shift_lock_refresh = false;
  bool shift_lock_toggle = false;
  int shift_lock_timeout = 0;
  bool shift_lock_enabled = false;
#endif

/**
 * Some more Shift Lock specific functions
 **/
bool shift_lock_terminate(uint16_t keycode) {
  switch (keycode) {
    case KC_LCTL:
    case KC_RCTL:
    case KC_LALT:
    case KC_RALT:
    case KC_LGUI:
    case KC_RGUI:
    case KC_TAB:
    case KC_ESC:
    case KC_LEFT:
    case KC_DOWN:
    case KC_UP:
    case KC_RGHT:
    // my specific keycodes...:
    case KC_RESC:
    case KC_CQUT:
    case KC_CENT:
    case KC_LENT:
    case KC_RSPC:
      return true;
    default:
      return false;
  }
}
bool shift_lock_skip_refresh(uint16_t keycode) {
  switch (keycode) {
#ifndef NO_SHIFT_LOCK_ALPHA
      case KC_A:
      case KC_B:
      case KC_C:
      case KC_D:
      case KC_E:
      case KC_F:
      case KC_G:
      case KC_H:
      case KC_I:
      case KC_J:
      case KC_K:
      case KC_L:
      case KC_M:
      case KC_N:
      case KC_O:
      case KC_P:
      case KC_Q:
      case KC_R:
      case KC_S:
      case KC_T:
      case KC_U:
      case KC_V:
      case KC_W:
      case KC_X:
      case KC_Y:
      case KC_Z:
#endif
#ifndef NO_SHIFT_LOCK_NUMERIC
      case KC_1:
      case KC_2:
      case KC_3:
      case KC_4:
      case KC_5:
      case KC_6:
      case KC_7:
      case KC_8:
      case KC_9:
      case KC_0:
#endif
#ifndef NO_SHIFT_LOCK_SPECIAL
      case KC_MINUS:
      case KC_EQL:
      case KC_TAB:
      case KC_LBRC:
      case KC_RBRC:
      case KC_BSLS:
      case KC_SCLN:
      case KC_QUOT:
      case KC_COMM:
      case KC_DOT:
      case KC_SLSH:
#endif
      return false;
    default:
      return true;
  }
}

bool shift_lock_skip(uint16_t keycode) {
  return shift_lock_skip_refresh(keycode);
}

bool handle_shift_lock_keypress(uint16_t keycode, keyrecord_t *record, keypos_t last_press) {
  if (shift_lock_enabled) {
    if (record->event.pressed) {
      register_code(KC_RSFT);
      custom_shift_timer = timer_read();
      return false;
    }
    unregister_code(KC_RSFT);

    if (shift_lock_toggle && shift_lock_active) {
      shift_lock_active = false;
    } else if (timer_elapsed(custom_shift_timer) < TAPPING_TERM &&
        (KEY_POSITION_MATCHES(last_press, record->event.key))) {
      custom_shift_timer = timer_read();
      shift_lock_active = true;
    }
  } else if (record->event.pressed) {
    register_code(KC_RSFT);
  } else {
    unregister_code(KC_RSFT);
  }
  return false;
}

/**
 * return true if the keycode should be handled as normal
 */
bool conditionally_apply_shift_lock(uint16_t keycode, keyrecord_t *record) {
  if (shift_lock_enabled) {
    if (record->event.pressed && shift_lock_active) {
      if (timer_elapsed(custom_shift_timer) > shift_lock_timeout) {
        shift_lock_active = false;
        unregister_code(KC_RSFT);
      } else if (shift_lock_refresh && !shift_lock_skip_refresh(keycode)) {
        custom_shift_timer = timer_read();
      }

      if (!shift_lock_skip(keycode)) {
        register_code(KC_RSFT);
        register_code(keycode);
        unregister_code(keycode);
        unregister_code(KC_RSFT);
        return false;
      } else if (shift_lock_terminate(keycode)) {
        shift_lock_active = false;
      }
    }
  }
  return true;
}

// An Ergodox EZ keymap meant to be used with a bépo layout (FR ergonomic
// layout, dvorak style). The overall design is slightly inspired by the
// TypeMatrix keyboard. Switching between a TypeMatrix and an Ergodox with this
// layout should be relatively easy.
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

#ifdef LEADER_TIMEOUT
#undef LEADER_TIMEOUT
#endif
#define LEADER_TIMEOUT 600

// The layers that we are defining for this keyboards.
#define BASE 0
#define FN    1
#define MOUSE 2
#define NUMS  3
#define SWAP  4
#define SYSLEDS 5

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
#define TAP_MACRO 0
#define TAP_CP    1 // Copy pasting with tap dance
#define TAP_LH    2 // Left arrow and Home
#define TAP_RE    3 // Right arrow and End
#define TAP_UP    4 // Up arrow and Page Up
#define TAP_DP    5 // Down arrow and Page Down
#define TAPB      6 // Tab tap

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define ESC_FN    LT(FN, KC_ESC)        // ESC key and FN layer toggle.
#define M_RSFT    MT(MOD_RSFT, BP_M)    // 'M' key and right shift modifier.
#define W_RCTL    MT(MOD_RCTL, BP_W)    // 'W' key and right control modifier.
#define SPC_RALT  MT(MOD_RALT, KC_SPC)  // SPACE key and right alt modifier.
#define SPC_LGUI  MT(MOD_LGUI, KC_SPC)  // SPACE key and left gui modifier.
#define ENT_RALT  MT(MOD_RALT, KC_ENT)  // ENTER key and right alt modifier.
#define TAB_RALT  MT(MOD_RALT, KC_TAB)  // TAB key and right alt modifier.
#define LCTL_TAB  LCTL(KC_TAB)          // TAB key and right alt modifier.
#define LCTL_LSFT_TAB  LCTL(S(KC_TAB))  // TAB key and right alt modifier.
#define LSFT_ESC  MT(MOD_LSFT, KC_ESC)  // ESCAPE key and left shift modifier.
#define LALT_ESC  MT(KC_LALT, KC_ESC)   // ESCAPE key and left alt modifier.
#define PERC_FN    LT(FN, BP_PERC)      // '%' key and FN layer toggle.
#define PERC_CLT    MT(MOD_LCTL | MOD_LALT, BP_PERC)      // '%' key and LCTL+LALT.
#define LCTL_ALT    LCTL(KC_LALT)       // Ctrl+LAlt
#define ALT_APP   ALT_T(KC_APPLICATION) // Alt and App menu
#define OSM_HYPR   OSM(MOD_HYPR)        // Hyper with one-shot mod
#define OSM_MEH   OSM(MOD_MEH)          // Meh with one-shot mod

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

// Custom keycodes
enum {
  // SAFE_RANGE must be used to tag the first element of the enum.
  // DYNAMIC_MACRO_RANGE must always be the last element of the enum if other
  // values are added (as its value is used to create a couple of other keycodes
  // after it).
  DYNAMIC_MACRO_RANGE = SAFE_RANGE,
  PAD_00, // 00 on numpad
  PAD_000, // 000 on numpad
};

// This file must be included after DYNAMIC_MACRO_RANGE is defined...
#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: basic keys.
  [BASE] = KEYMAP(
    /* left hand */
    BP_DLR,   BP_DQOT, BP_LGIL, BP_RGIL,    BP_LPRN, BP_RPRN, KC_LEAD,
    TD(TAPB),   BP_B,    BP_ECUT, BP_P,       BP_O,    BP_EGRV, TT(MOUSE),
    LSFT_ESC, BP_A,    BP_U,    BP_I,       BP_E,    BP_COMM,
    KC_LCTL,  BP_AGRV, BP_Y,    BP_X,       BP_DOT,  BP_K,    OSM_MEH,
    OSM_HYPR,   LCTL_ALT, ALT_APP, KC_LEFT, KC_RIGHT,
                                                     TO(BASE), TT(SYSLEDS),
                                                                   KC_CAPS,
                                               SPC_LGUI, TT(MOUSE), TT(FN),
    /* right hand */
        KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL,
        KC_BSPC, BP_DCRC, BP_V,     BP_D,    BP_L,        BP_J,    BP_Z,
                 BP_C,    BP_T,     BP_S,    BP_R,        BP_N,    M_RSFT,
        TD(TAP_CP),   BP_APOS, BP_Q,     BP_G,    BP_H,        BP_F,    W_RCTL,
                               KC_UP, KC_DOWN, KC_LALT, BP_CCED, BP_PERC,
    KC_LOCK, RESET,
    TD(TAP_MACRO),
    TT(NUMS), TAB_RALT, KC_ENT),

  // Layer 1: function and media keys.
  [FN] = KEYMAP(
    /* left hand */
    ___, ___,     ___,     ___,     ___,      ___,   ___,
    ___, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5, ___,
    ___, KC_SLEP, KC_VOLD, KC_VOLU, KC_MUTE,   ___,
    ___, KC_PSCR, KC_CUT,  KC_COPY, KC_PASTE,  ___,  ___,
    ___, ___,     ___,     ___,     ___,
                                                     ___, ___,
                                                          ___,
                                             ___,    ___, ___,
    /* right hand */
        ___, ___,     ___,     ___,     ___,     ___,     ___,
        ___, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
             KC_F12,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,  ___,
        ___, KC_WBAK, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, ___,
                      ___,     ___,     ___,     KC_WAKE, ___,
    ___, ___,
    ___,
    ___, ___,    ___),

  // Layer 2: Mouse control.
  [MOUSE] = KEYMAP(
    /* left hand */
    ___, ___,     ___,     ___,     ___,     ___, ___,
    ___, ___,     KC_BTN4, KC_BTN5, ___,     ___, ___,
    ___, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, ___,
    ___, MK_CUT,  ___,     ___,     ___,     ___, ___,
    ___, ___,     ___,     ___,     ___,
                                                  ___, ___,
                                                       ___,
                                             ___, ___, ___,
    /* right hand */
         ___, ___,           ___,     ___,     ___,     ___,           ___,
         ___, LALT(KC_BTN1), KC_BTN3, KC_WH_L, KC_WH_R, LCTL(KC_WH_U), ___,
              S(KC_BTN1),    KC_BTN1, KC_WH_D, KC_WH_U, KC_BTN2,       ___,
         ___, LCTL(KC_BTN1), KC_ACL0, KC_ACL1, KC_ACL2, LCTL(KC_WH_D), ___,
                             ___,     ___,     ___,     ___,     ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 3: Numeric keypad over 2 hands and system keys.
  [NUMS] = KEYMAP(
    /* left hand */
    ___, ___, ___,     ___,     ___,      ___, ___,
    ___, BP_DLR, ALTGR(BP_E), BP_COMM, BP_DOT,   BP_EQL, ___,
    ___, BP_1,   BP_2,        BP_3,    BP_4,     BP_5,
    ___, KC_INS,    MK_CUT,      MK_COPY, MK_PASTE, KC_PAUS, ___,
    ___, ___,    ___,         ___,     ___,
                                              ___, ___,
                                                   ___,
                                         ___, ___, ___,
    /* right hand */
         ___, ___,  ___,     ___,     ___,     ___, ___,
         ___,  BP_PLUS, BP_MINS, BP_ASTR, BP_SLSH, BP_ASTR, BP_PERC,
              BP_6, BP_7,    BP_8,    BP_9,    BP_0,    ___,
         ___, ___,  PAD_00, PAD_000,  KC_SLCK,     KC_NLCK,     ___,
                      ___,     ___,     ___,     ___,     ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 4: hand swap, all keys are mirrored to the other side of the keyboard
  // except for the layer toggle itself (so there is no right arrow when this
  // layer is activated).
  [SWAP] = KEYMAP(
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                             TT(SWAP), ___,
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
              ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
                   ___, ___, ___, ___, ___,
    ___, TT(SWAP),
    ___,
    ___, ___,      ___),

  // Layer 5: The LEDs are showing the "standard" caps/num/scroll lock indicator
  // instead of their default which shows the currently active layers
  [SYSLEDS] = KEYMAP(
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                           ___, TT(SYSLEDS),
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
              ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
                   ___, ___, ___, ___, ___,
    ___, ___,
    ___,
    ___, ___, ___),
};

// Whether the macro 1 is currently being recorded.
static bool is_macro1_recording = false;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static uint32_t current_layer_state = 0;
uint32_t layer_state_set_user(uint32_t state);

// Method called at the end of the tap dance on the TAP_MACRO key. That key is
// used to start recording a macro (double tap or more), to stop recording (any
// number of tap), or to play the recorded macro (1 tap).
void macro_tapdance_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DYN_REC_STOP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DYN_MACRO_PLAY1;
  } else {
    keycode = DYN_REC_START1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_record_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_record_dynamic_macro(keycode, &record);
}

// The definition of the tap dance actions:
qk_tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
  // Easy copy pasting
  [TAP_CP] = ACTION_TAP_DANCE_DOUBLE(MK_COPY, MK_PASTE),
  // Double arrow key
  [TAP_LH] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
  [TAP_RE] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
  [TAP_UP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
  [TAP_DP] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
  [TAPB] = ACTION_TAP_DANCE_DOUBLE(LCTL_TAB, LCTL_LSFT_TAB),
};

// Runs for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Process static custom macro___
  if (record->event.pressed) {
    switch(keycode) {
    case PAD_00:
      SEND_STRING(SS_LSFT("00"));
      return false;
    case PAD_000:
      SEND_STRING(SS_LSFT("000")); // selects all and copies___t
      return false;
    }
  }

  if (keycode != TD(TAP_MACRO)) {
    // That key is processed by the macro_tapdance_fn. Not ignoring it here is
    // mostly a no-op except that it is recorded in the macros (and uses space).
    // We can't just return false when the key is a tap dance, because
    // process_record_user, is called before the tap dance processing (and
    // returning false would eat the tap dance).
    if (!process_record_dynamic_macro(keycode, record)) {
      return false;
    }
  }

  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  // Unicode support
  set_unicode_input_mode(UC_LNX);
};

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    // Place leader keys on keys that are independant from layer
    leading = false;
    leader_end();

    // for single key sequences
    SEQ_ONE_KEY(BP_DQOT) {
      SEND_STRING("c6joly.pw");
    }

    SEQ_ONE_KEY(BP_LGIL) {
      SEND_STRING("l6"SS_LSFT("131719")".xyz");
    }

    SEQ_ONE_KEY(BP_RGIL) {
      SEND_STRING("leowzukw");
    }

    SEQ_ONE_KEY(BP_LPRN) {
      SEND_STRING("WzukW");
    }

    SEQ_ONE_KEY(KC_ENT) {
      SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }

    SEQ_ONE_KEY(BP_CCED) {
      SEND_STRING(SS_TAP(X_POWER));
    }
  }
};

// The state of the LEDs requested by the system, as a bitmask.
static uint8_t sys_led_state = 0;

// Use these masks to read the system LEDs state.
static const uint8_t sys_led_mask_num_lock = 1 << USB_LED_NUM_LOCK;
static const uint8_t sys_led_mask_caps_lock = 1 << USB_LED_CAPS_LOCK;
static const uint8_t sys_led_mask_scroll_lock = 1 << USB_LED_SCROLL_LOCK;

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 100;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(layer) (current_layer_state & (1<<layer))

void led_1_on(void) {
  ergodox_right_led_1_on();
  ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
  ergodox_right_led_2_on();
  ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
  ergodox_right_led_3_on();
  ergodox_right_led_3_set(max_led_value);
}

void led_1_off(void) {
  ergodox_right_led_1_off();
}

void led_2_off(void) {
  ergodox_right_led_2_off();
}

void led_3_off(void) {
  ergodox_right_led_3_off();
}

// Called when the computer wants to change the state of the keyboard LEDs.
void led_set_user(uint8_t usb_led) {
  sys_led_state = usb_led;
  if (LAYER_ON(SYSLEDS)) {
    if (sys_led_state & sys_led_mask_caps_lock) {
      led_1_on();
    } else {
      led_1_off();
    }
    if (sys_led_state & sys_led_mask_num_lock) {
      led_2_on();
    } else {
      led_2_off();
    }
    if (sys_led_state & sys_led_mask_scroll_lock) {
      led_3_on();
    } else {
      led_3_off();
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  current_layer_state = state;
  swap_hands = LAYER_ON(SWAP);

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return state;
  }

  if (LAYER_ON(SYSLEDS)) {
    led_set_user(sys_led_state);
    return state;
  }

  if (LAYER_ON(FN)) {
    led_1_on();
  } else {
    led_1_off();
  }

  if (LAYER_ON(NUMS)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(MOUSE)) {
    led_3_on();
  } else {
    led_3_off();
  }

  return state;
};

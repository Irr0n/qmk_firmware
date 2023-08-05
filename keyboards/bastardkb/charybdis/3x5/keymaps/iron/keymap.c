#include QMK_KEYBOARD_H
#include <stdio.h>


enum custom_layers {
    _BASE = 0,
    _EXTENSION,
    _SYMBOL,
    _NUMBER,
    _FUNCTION,
    _MEDIA,
    _POINTER
};

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,

  DBPRN, // double parenthesis with arrow back
  DBBRC, // double brackets
  DBCBR, // double curly brackets
  DBABK,  // double angled brackets

  DDPI_T, // default dpi cycle not retained on EEPROM cycle
  SDPI_T // sniper dpi cycle not retained on EEPROM cycle
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// TODO: change finger combos to location instead of specific keys
// https://docs.qmk.fm/#/feature_combo?id=layer-independent-combosd

// keycode combos
const uint16_t PROGMEM dbprn_key_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM dbbrc_key_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM dbcbr_key_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM dbabk_key_combo[] = {KC_LABK, KC_RABK, COMBO_END};

// row: bottom, _middle, top, side: left, right, finger: thumb, index, middle, ring, pinky
// modifier, layer combos
const uint16_t PROGMEM tlt_blii_combo[] = {TL_LOWR, KC_Q, COMBO_END};
const uint16_t PROGMEM trt_brii_combo[] = {TL_UPPR, KC_P, COMBO_END};

const uint16_t PROGMEM blp_blr_combo[] = {KC_X, KC_J, COMBO_END};
const uint16_t PROGMEM blr_blm_combo[] = {KC_J, KC_B, COMBO_END};
const uint16_t PROGMEM blp_blm_combo[] = {KC_X, KC_B, COMBO_END};
const uint16_t PROGMEM blm_bli_combo[] = {KC_B, KC_M, COMBO_END};
const uint16_t PROGMEM blr_bli_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM tlp_tlr_combo[] = {KC_F, KC_L, COMBO_END};

const uint16_t PROGMEM brp_brr_combo[] = {KC_SCLN, KC_DOT, COMBO_END};
const uint16_t PROGMEM brr_brm_combo[] = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM brp_brm_combo[] = {KC_SCLN, KC_COMM, COMBO_END};
const uint16_t PROGMEM brm_bri_combo[] = {KC_COMM, KC_G, COMBO_END};
const uint16_t PROGMEM brr_bri_combo[] = {KC_DOT, KC_G, COMBO_END};
const uint16_t PROGMEM trp_trr_combo[] = {KC_Y, KC_O, COMBO_END};

combo_t key_combos[] = {

  COMBO(tlt_blii_combo, MO(3)),
  COMBO(trt_brii_combo, MO(5)),

  COMBO(dbbrc_key_combo, DBBRC),
  COMBO(dbcbr_key_combo, DBCBR),
  COMBO(dbabk_key_combo, DBABK),

  COMBO(brr_brm_combo, OSM(MOD_LSFT)),
  COMBO(blr_blm_combo, OSM(MOD_LSFT)),

  COMBO(blp_blr_combo, CW_TOGG),
  COMBO(brm_bri_combo, KC_BSPC),
  COMBO(brr_bri_combo, C(KC_BSPC)),
  COMBO(tlp_tlr_combo, KC_ESC),
  COMBO(brp_brr_combo, KC_TAB)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DDPI_T:
      if (record->event.pressed) {
        charybdis_cycle_pointer_default_dpi_noeeprom(true);
      }
      break;

    case SDPI_T:
      if (record->event.pressed) {
        charybdis_cycle_pointer_sniping_dpi_noeeprom(true);
      }
      break;

    case DBPRN:
      if (record->event.pressed) {
        tap_code16(KC_LPRN);
        tap_code16(KC_RPRN);
      } else {
        tap_code(KC_LEFT);
      }
      break;

    case DBBRC:
      if (record->event.pressed) {
        tap_code16(KC_LBRC);
        tap_code16(KC_RBRC);
      } else {
        tap_code(KC_LEFT);
      }
      break;

    case DBCBR:
      if (record->event.pressed) {
        tap_code16(KC_LCBR);
        tap_code16(KC_RCBR);
      } else {
        tap_code(KC_LEFT);
      }
      break;

    case DBABK:
      if (record->event.pressed) {
        tap_code16(KC_LABK);
        tap_code16(KC_RABK);
      } else {
        tap_code(KC_LEFT);
      }
      break;

    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
};

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
};

/* auto mouse management*/

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(_POINTER);
    set_auto_mouse_enable(true);
}

// fix sticky scroll?
// called right before layer changes                v state about to be applied
layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) != _POINTER) {
        charybdis_set_pointer_sniping_enabled(false);
        charybdis_set_pointer_dragscroll_enabled(false);
    }
    return state; // don't change state
}


// aliases
#define OSC OSM(MOD_LCTL)
#define OSS OSM(MOD_LSFT)
#define OSG OSM(MOD_LGUI)
#define OSA OSM(MOD_LALT)

#define NEXTTAB C(KC_TAB)
#define PREVTAB C(S(KC_TAB))

#define NONE XXXXXXX

#define CHARYBDIS_AUTO_SNIPING_ON_LAYER _POINTER


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,    KC_QUOT,    KC_W,    KC_U,    KC_O,    KC_Y,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_S,    KC_R,    KC_N,    KC_T,    KC_K,       KC_C,    KC_D,    KC_E,    KC_A,    KC_I,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,       KC_P,    KC_G, KC_COMM,  KC_DOT, KC_SCLN,
  // ╰─────────────────────────────────────────────┤ ├────────────────────╭───╮────────────────────╯
                           MO(6), TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR //│   │
  //                   ╰───────────────────────────╯ ╰──────────────────╯ ╰───╯
  ),

  [_EXTENSION] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_ESC, KC_LGUI, PREVTAB, NEXTTAB,    NONE,       NONE, KC_HOME,   KC_UP,  KC_END,    NONE,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
           OSG,     OSA,     OSS,     OSC,    NONE,       NONE, KC_LEFT, KC_DOWN, KC_RGHT,  KC_TAB,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    NONE,       NONE,KC_BSPC,C(KC_BSPC), KC_DEL,    NONE,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,  S(KC_ENT), _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [_SYMBOL] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_LABK, KC_RABK, KC_LCBR, KC_RCBR,    NONE,     KC_GRV, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_BSLS, KC_SLSH, KC_LPRN, KC_RPRN,    NONE,    KC_TILD, KC_UNDS,  KC_EQL, KC_QUES, KC_EXLM,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE, KC_PIPE, KC_LBRC, KC_RBRC,    NONE,    KC_PERC, KC_HASH,  KC_DLR,   KC_AT, KC_CIRC,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,    _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [_NUMBER] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,    KC_7,    KC_8,    KC_9,  KC_DOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,    KC_4,    KC_5,    KC_6,  KC_ENT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,    KC_1,    KC_2,    KC_3, KC_BSPC,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,      MO(4),    KC_0
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [_FUNCTION] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE,    NONE, QK_MAKE, QK_BOOT,    NONE,       NONE,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                            NONE,    NONE,    NONE,    _______,    NONE
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [_MEDIA] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       NONE,    NONE,    NONE,    NONE,    NONE,          NONE,    NONE,    NONE,    NONE,    NONE,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY,    NONE,       NONE,    NONE,    NONE,    NONE,    NONE,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       NONE,    KC_MUTE, KC_VOLD, KC_VOLU,    NONE,       NONE,    NONE,    NONE,    NONE,    NONE,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,    _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [_POINTER] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          NONE,    NONE,    NONE,    NONE,    NONE,       NONE,    NONE,    NONE,    NONE,    NONE,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          NONE,    NONE, KC_LSFT, KC_LCTL,    NONE,       NONE, KC_BTN1, KC_BTN2, KC_BTN3,    NONE,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       C(KC_Z), C(KC_X), C(KC_C), C(KC_V),    NONE,       NONE,KC_BSPC,C(KC_BSPC), KC_DEL,    NONE,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, DRGSCRL, SNIPING,       NONE,    NONE
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  )
};

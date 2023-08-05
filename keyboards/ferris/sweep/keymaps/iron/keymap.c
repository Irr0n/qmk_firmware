// qmk flash -c -kb ferris/sweep -km iron -e CONVERT_TO=blok -bl uf2-split-<left|right>

#include QMK_KEYBOARD_H
#include <stdio.h>


enum user_layers {
    _BSE,
    _EXT,
    _SYM,
    _SYS,
    _NUM,
    _FNC,
    _MSE,
    _MED
};

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  DBPRN, // double parenthesis with arrow back
  DBBRC, // double brackets
  DBCBR, // double curly brackets
  DBABK  // double angled brackets
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// modifier, layer combos
const uint16_t PROGMEM tlt_blii_combo[] = {TL_LOWR, KC_Q, COMBO_END};
const uint16_t PROGMEM trt_brii_combo[] = {TL_UPPR, KC_P, COMBO_END};
// keycode combos
const uint16_t PROGMEM dbprn_key_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM dbbrc_key_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM dbcbr_key_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM dbabk_key_combo[] = {KC_LABK, KC_RABK, COMBO_END};

// row: bottom, _middle, top, side: left, right, finger: thumb, index, middle, ring, pinky
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

  COMBO(tlt_blii_combo, MO(4)),
  COMBO(trt_brii_combo, MO(6)),

  COMBO(dbbrc_key_combo, DBBRC),
  COMBO(dbcbr_key_combo, DBCBR),
  COMBO(dbabk_key_combo, DBABK),

  COMBO(brr_brm_combo, OSM(MOD_LSFT)),
  COMBO(blr_blm_combo, OSM(MOD_LSFT)),

  COMBO(blp_blr_combo, CW_TOGG),
  COMBO(brm_bri_combo, KC_BSPC),
  COMBO(brr_bri_combo, C(KC_BSPC)),
  COMBO(tlp_tlr_combo, KC_ESC)
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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


// one shot mods
#define OSC OSM(MOD_LCTL)
#define OSS OSM(MOD_LSFT)
#define OSG OSM(MOD_LGUI)
#define OSA OSM(MOD_LALT)

#define NEXTTAB C(KC_TAB)
#define PREVTAB C(S(KC_TAB))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //base
  [_BSE] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,                      KC_QUOT,    KC_W,    KC_U,    KC_O,    KC_Y,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_S,    KC_R,    KC_N,    KC_T,    KC_K,                         KC_C,    KC_D,    KC_E,    KC_A,    KC_I,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,                         KC_P,    KC_G, KC_COMM,  KC_DOT, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          TL_LOWR,  KC_SPC,     KC_ENT,  TL_UPPR
                                      //`-----------------'  `-----------------'

  ),
    //extension
  [_EXT] = LAYOUT(
  //,-------------------------------------------.                    ,--------------------------------------------.
      KC_ESC, KC_LGUI, PREVTAB, NEXTTAB, XXXXXXX,                      XXXXXXX, KC_HOME,   KC_UP,  KC_END, XXXXXXX,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         OSG,     OSA,     OSS,     OSC, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  KC_TAB,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
     C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,                      XXXXXXX,KC_BSPC,C(KC_BSPC), KC_DEL, XXXXXXX,
  //|-------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                         _______, _______,    _______, _______
                                      //`----------------'  `-----------------'
  ),
    //symbol
  [_SYM] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, XXXXXXX,                       KC_GRV, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_BSLS, KC_SLSH, KC_LPRN, KC_RPRN, XXXXXXX,                      KC_TILD, KC_UNDS,  KC_EQL, KC_QUES, KC_EXLM,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, KC_PIPE, KC_LBRC, KC_RBRC, XXXXXXX,                      KC_PERC, KC_HASH,  KC_DLR,   KC_AT, KC_CIRC,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          _______, _______,    _______, _______
                                      //`-----------------'  `-----------------'
  ),
    //system controls
  [_SYS] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_S),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,    XXXXXXX, _______
                                      //`-----------------'  `-----------------'
  ),
    //numpad
  [_NUM] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9,  KC_DOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6,  KC_ENT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          _______, _______,      MO(5),    KC_0
                                      //`-----------------'  `-----------------'
  ),
    //function
  [_FNC] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, QK_MAKE, QK_BOOT, XXXXXXX,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,    _______, XXXXXXX
                                      //`-----------------'  `-----------------'
  ),
    //mouse
  [_MSE] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_WH_L, KC_WH_R, C(KC_V), C(KC_C),
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,    _______, _______
                                      //`-----------------'  `-----------------'
  ),
    //media
  [_MED] = LAYOUT(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,    XXXXXXX, _______
                                      //`-----------------'  `-----------------'
  )
};

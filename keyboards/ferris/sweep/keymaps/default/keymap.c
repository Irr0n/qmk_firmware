/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// qmk flash -c -kb crkbd -km iron -e CONVERT_TO=blok


#include QMK_KEYBOARD_H
#include <stdio.h>

enum user_layers {
    _BSE,
    _EXT,
    _SYM,
    _NUM,
    _FNC,
    _MSE,
    _MED
};

// defining any key combo greater than seven characters

// one shot mods
#define OSC OSM(MOD_LCTL)
#define OSS OSM(MOD_LSFT)
#define OSG OSM(MOD_LGUI)
#define OSA OSM(MOD_LALT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //base
  [_BSE] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,                      KC_QUOT,    KC_W,    KC_U,    KC_O,    KC_Y,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_S,    KC_R,    KC_N,    KC_T,    KC_K,                         KC_C,    KC_D,    KC_E,    KC_A,    KC_I,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,                         KC_P,    KC_G, KC_COMM,  KC_DOT,   TT(3),
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                            TT(2),  KC_SPC,      TT(1),     OSS
                                      //`-----------------'  `-----------------'

  ),
    //extension
  [_EXT] = LAYOUT_split_3x5_2(
  //,-------------------------------------------.                    ,--------------------------------------------.
     XXXXXXX, KC_LGUI, CW_TOGG,   TO(6), XXXXXXX,                      XXXXXXX, KC_HOME,   KC_UP,  KC_END, XXXXXXX,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_ESC, KC_DEL,C(KC_BSPC),KC_BSPC, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  KC_TAB,
  //|-------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         OSA,     OSG,     OSS,     OSC, XXXXXXX,                      C(KC_S), C(KC_V), C(KC_C), C(KC_X), C(KC_Z),
  //|-------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                           TO(5),  KC_ENT,      TO(0), _______
                                      //`----------------'  `-----------------'
  ),
    //symbol
  [_SYM] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, XXXXXXX,                       KC_GRV, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_BSLS, KC_SLSH, KC_LPRN, KC_RPRN, KC_PIPE,                      KC_TILD, KC_COLN, KC_SCLN, KC_QUES, KC_EXLM,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_UNDS,  KC_EQL, KC_LBRC, KC_RBRC, XXXXXXX,                      KC_CIRC,   KC_AT, KC_PERC,  KC_DLR, KC_HASH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                              OSS,  KC_SPC,      TO(0), _______
                                      //`-----------------'  `-----------------'
  ),
    //numpad
  [_NUM] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9,  KC_DOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6,    KC_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                            MO(4), _______,      TO(0),   KC_ENT
                                      //`-----------------'  `------------------'
  ),
    //function
  [_FNC] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, QK_MAKE, QK_BOOT, XXXXXXX,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,    XXXXXXX, XXXXXXX
                                      //`-----------------'  `-----------------'
  ),
    //mouse
  [_MSE] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_WH_L, KC_WH_R, C(KC_V), C(KC_C),
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,      TO(0), XXXXXXX
                                      //`-----------------'  `-----------------'
  ),
    //media
  [_MED] = LAYOUT_split_3x5_2(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,      TO(0), XXXXXXX
                                      //`-----------------'  `-----------------'
  )
};

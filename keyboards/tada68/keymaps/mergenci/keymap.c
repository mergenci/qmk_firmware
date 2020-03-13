#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0 // Base layer
#define _FL 1 // Function layer
#define _CL 2 // CTRL layer
#define _AL 3 // ALT layer
#define _CX 4 // Emacs C-X layer

enum custom_keycodes {
    EMACS_CX = SAFE_RANGE
};

int is_emacs_cx_layer_on;
char my_debug_msg[512];

void my_print_keycode_and_record(uint16_t keycode, keyrecord_t *record) {
    snprintf(my_debug_msg, 512, "keycode %d col %d row %d %s\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed ? "down" : "up");
    send_string(my_debug_msg);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     my_print_keycode_and_record(keycode, record);

    switch (keycode) {
        case LT(_CL, KC_ESC):
            if (!record->event.pressed && is_emacs_cx_layer_on) {  // On caps lock key up when Emacs C-X layer is on
                clear_mods();
                clear_oneshot_mods();
                return true;
            }
            break;
    }

    return true;
};

void oneshot_layer_changed_user(uint8_t layer) {
  if (layer == _CX) {
    is_emacs_cx_layer_on = 1;
    backlight_level(1);

    tap_code16(C(KC_X));
    set_oneshot_mods(MOD_LCTL);
  }
  else if (!layer) { // One shot layer is off
    is_emacs_cx_layer_on = 0;
    backlight_level(0);
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |PgUp|
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgDn|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Del |
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Cmd |        Space          |Cmd| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,    KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,  KC_DEL, \
  LT(_CL, KC_ESC),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,  KC_ENT, KC_PGUP,  \
  MT(MOD_LSFT, KC_CAPS),   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,        KC_UP,  KC_PGDN, \
  KC_LCTL, KC_LALT,LM(_AL,0x08),           LT(_CL, KC_SPC),                   LM(_AL,0x18),MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |SLP|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    | ^  |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   | > |<< | >>|     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |MUT|VU-|VU+|   |      |   |End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  KC_SLEP, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_EJCT,  \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPLY,KC_MRWD,KC_MFFD, _______, _______, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,KC_HOME, \
  _______,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______, _______, KC_END, \
  _______,_______,_______,                 _______,               _______,_______,_______,_______,_______, _______),

  /* Keymap _CL: Caps Layer
   */
[_CL] = LAYOUT_ansi(
  C(KC_GESC), C(KC_1), C(KC_2), C(KC_3), C(KC_4), C(KC_5), C(KC_6), C(KC_7), C(KC_8), C(KC_9), C(KC_0), C(KC_MINS), C(KC_EQL), C(KC_BSPC), C(KC_GRV), \
  C(KC_TAB), C(KC_Q), C(KC_W), C(KC_E), C(KC_R), C(KC_T), C(KC_Y), C(KC_U), C(KC_I), C(KC_O), KC_UP, C(KC_LBRC), C(KC_RBRC), C(KC_BSLS), C(KC_DEL), \
  KC_LCTL, C(KC_A), C(KC_S), C(KC_D), KC_RIGHT, C(KC_G), KC_BSPC, C(KC_J), C(KC_K), C(KC_L), C(KC_SCLN), C(KC_QUOT), C(KC_ENT), C(KC_PGUP), \
  C(KC_LSFT), C(KC_Z), /* EMACS_CX */ OSL(_CX), C(KC_C), C(KC_V), KC_LEFT, KC_DOWN, C(KC_M), C(KC_COMM), C(KC_DOT), C(KC_SLSH), C(KC_RSFT), C(KC_UP), C(KC_PGDN), \
  _______, C(KC_LALT), C(KC_LGUI),                 C(KC_SPC),               C(KC_RGUI), _______, _______, C(KC_LEFT), C(KC_DOWN), C(KC_RGHT)),

  /* Keymap _AL: ALT Layer
   * ,----------------------------------------------------------------.
   * |` ~|   |   |   |   |   |   |   |   |   |   |   |   |       | ` ~|
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_AL] = LAYOUT_ansi(
  KC_GRV, _______ ,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_GRV , \
  _______,_______, _______, _______,_______, _______,_______,_______,_______,_______,_______,_______,_______, _______,_______, \
  _______,_______, _______, _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______, \
  _______,_______,_______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______,  _______, \
  _______,_______,_______,                 _______,               _______,_______,_______, _______, _______,  _______),

  /* Keymap _CX: Emacx C-X layer
   * Disables emacs shortcuts defined in _CL layer, when preceded by C-X, so that they work in emacs.
   */
[_CX] = LAYOUT_ansi(
  KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,    KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,  KC_DEL, \
  KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,  KC_ENT, KC_PGUP,  \
  MT(MOD_LSFT, KC_CAPS),   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,        KC_UP,  KC_PGDN, \
  KC_LCTL, KC_LALT,LM(_AL,0x08),                KC_SPC,                       LM(_AL,0x18),MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

};

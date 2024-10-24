#include QMK_KEYBOARD_H
#include "keymap_german.h"

#define _MALT 0
#define _MOUSE 1
#define _SYMBOL 2
#define _FN 3
#define _NUM 4
#define _GW1 5
#define _GW2 6
#define _RUS 7

/* Symbol explanation
 *
 * ↓↓   double tap
 * ⇩    with Shift
 * ⤓    hold
 * →    move to layer
 *
 */

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

// e⤓SYMBOL
#define LT_SYM_E LT(_SYMBOL, KC_E)
// space⤓MOUSE
#define LT_MOU_SPC LT(_MOUSE, KC_SPC)
// Shift+Ctrl combos
#define SC(kc) S(C(kc))
// dodge⤓GW2
#define DGE_GW2 LT(_GW2, KC_SPC)

// Tap Dance
enum {
  TD_OESZ,
}
qk_tap_dance_action_t tap_dance_actions[] = {
  // ö&↓↓ß
  [TD_OESZ] = ACTION_TAP_DANCE_DOUBLE(DE_ODIA, DE_SS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* MALT++
 * TODO ⤓MOUSE under tab to easier repeat spaces?
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   ä  |   f  |   y  |   m  |   b  |           |   q  |   l  |   u  | .&⇩: | ö&↓↓ß|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |a⤓shft| c⤓ctl| i⤓win| t⤓alt|  d⤓hyp|           |r⤓meh | n⤓alt| h⤓win| o⤓ctl|s⤓shft|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ü  |   p  |   j  |   g  |   k  |           |   x  |   w  |   v  | ,&⇩; |   z  |
 * `----------------------------------'           `----------------------------------'
 *                ,-----+---------+------.    ,------,------------+------.
 *                | esc | e⤓SYMBOL|      |    |      |space⤓MOUSE| enter|
 *                `-----+---------|bckspc|    | tab  |------------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_MALT] = LAYOUT_split_3x5_3( \
     DE_ADIA,       KC_F,       DE_Y,       KC_M,       KC_B,         KC_Q,       KC_L,       KC_U,     DE_DOT, TD(TD_OESZ), \
  LSFT(KC_A), LCTL(KC_C), LGUI(KC_I), LALT(KC_T), HYPR(KC_D),    MEH(KC_R), RALT(KC_N), RGUI(KC_H), RCTL(KC_O),  RSFT(KC_S), \
     DE_UDIA,       KC_P,       KC_J,       KC_G,       KC_K,         KC_X,       KC_W,       KC_V,    DE_COMM,        DE_Z, \
                              KC_ESC,    LT_SYM_E,   KC_BSPC,       KC_TAB, LT_MOU_SPC,     KC_ENT                           \
),

/* MOUSE+NAV
 * - Modifiers:
 * ctl = Ctrl (navigate words) - ctlalt = Ctrl + Alt (switch desktops)
 * MEH = Shift + Ctl + Alt (move window across desktops) - sftctl = Shift + Ctrl (mark words)
 *
 * - Mouse:
 * ms = move mouse in indicated direction
 * msleft = Mouse Left Click - msrght = Mouse Right Click - mswhl = Mouse Wheel Click
 * scrol = scroll in indicated direction
 * Acc0-2 = set acceleration of mouse (KC_ACL0)
 *
 * ,----------------------------------.           ,----------------------------------.
 * | mswhl|msleft|  ms↑ |msrght|  MEH |           |      |msleft|   ↑  |msrght| mswhl|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |scrol↑|  ms← |  ms↓ |  ms→ |ctlalt|           | pos1 |   ←  |   ↓  |   →  | Ende |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |scrol↓|scrol←|scrol→|  Ctl |sftctl|           |      | Acc2 | Acc1 | Acc0 |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | shift| caps |    |      | ENTRY|   X  |
 *                  `-------------| lock |    |   X  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_MOUSE] = LAYOUT_split_3x5_3( \
  KC_BTN3, KC_BTN1, KC_MS_U, KC_BTN2,     KC_MEH,    _______, KC_BTN1,   KC_UP,  KC_BTN2, KC_BTN3, \
  KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, C(KC_LALT),    KC_HOME, KC_LEFT, KC_DOWN,  KC_RGHT,  KC_END, \
  KC_WH_D, KC_WH_L, KC_WH_R, KC_LCTL, S(KC_LCTL),    _______, KC_ACL2, KC_ACL1,  KC_ACL0, _______, \
                    _______, KC_LSFT,    KC_CAPS,    _______, _______, _______                     \
),

/* SYMBOL
 * idea-c - Commenting out in IDEA (Ctrl + NUM /) C(KC_PSLS)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   `  |   &  |   +  |   =  |   @  |           |   !  |   *  |   #  |   /  |   |  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ^  |   [  |   {  |   (  |   $  |           |   _  |   )  |   }  |   ]  |   -  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ~  |   \  |   %  |   <  |   €  |           |idea-c|   >  |   ´  |   '  |   ?  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |  ⤓FN | ENTRY|      |    |      | Entf |   "  |
 *                  `-------------|   X  |    | ⤓NUM |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYMBOL] = LAYOUT_split_3x5_3( \
   DE_GRV, DE_AMPR, DE_PLUS,  DE_EQL,   DE_AT,       DE_EXLM, DE_ASTR, DE_HASH, DE_SLSH, DE_PIPE, \
  DE_CIRC, DE_LBRC, DE_LCBR, DE_LPRN,  DE_DLR,       DE_UNDS, DE_RPRN, DE_RCBR, DE_RBRC, DE_MINS, \
  DE_TILD, DE_BSLS, DE_PERC, DE_LABK, DE_EURO,    C(KC_PSLS), DE_RABK, DE_ACUT, DE_QUOT, DE_QUES, \
                    MO(_FN), _______, _______,      MO(_NUM),  KC_DEL, DE_DQUO                    \
),

/* F-Keys & Shortcuts for Mouse
 * X = Cut, C = Copy, V = Paste, B = copy username from KeePass
 * sfcl (shift ctrl) = with Shift for Terminal
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |ctrl+B|ctrl+V|   X  |   X  |           |      |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |ctrl+X|ctrl+C|ctrl+V|   X  |   X  |           | sf+cl|  F4  |  F5  |  F6  |  F11 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |sfcl+X|sfcl+C|sfcl+V|   X  |   X  |           | einfg|  F1  |  F2  |  F3  |  F12 |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |ENTRY2|ENTRY1|      |    | ctrl |  alt | ctrl |
 *                  `-------------|   X  |    | +alt |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_FN] = LAYOUT_split_3x5_3( \
   _______,  C(KC_B),  C(KC_V), _______, _______,       _______,   KC_F7,   KC_F8, KC_F9, KC_F10, \
   C(KC_X),  C(KC_C),  C(KC_V), _______, _______,    S(KC_LCTL),   KC_F4,   KC_F5, KC_F6, KC_F11, \
  SC(KC_X), SC(KC_C), SC(KC_V), _______, _______,        KC_INS,   KC_F1,   KC_F2, KC_F3, KC_F12, \
                       _______, _______, _______,    C(KC_LALT), KC_LALT, KC_LCTL                 \
),

/* Numbers & Fitting Symbols
 * →GW = move to Guild Wars 2 layer
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |   °  |   §  |      |           |      |   7  |   8  |   9  | →GW1 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |   €  |   .  |   ,  |      |           |      |   4  |   5  |   6  |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |   1  |   2  |   3  |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |ENTRY1|      |    |      |      |   0  |
 *                  `-------------|   X  |    |ENTRY2|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NUM] = LAYOUT_split_3x5_3( \
  _______, _______,  DE_DEG, DE_SECT, _______,      _______,    KC_7, KC_8, KC_9, TO(_GW1), \
  _______, DE_EURO,  DE_DOT, DE_COMM, _______,      _______,    KC_4, KC_5, KC_6,  _______, \
  _______, _______, _______, _______, _______,      _______,    KC_1, KC_2, KC_3,  _______, \
                    _______, _______, _______,      _______, _______, KC_0                  \
),

/* Guild Wars 2
 * enemy = next enemy & roller beetle slide
 *
 * ,----------------------------------.           ,----------------------------------.
 * |skill2|skill3|skill4|skill5|skill8|           |  esc |  LFG |      |      | EXIT | (ENTRY unheld)
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |skill7| heal |   ↑  | elite|skill9|           | GUILD|  MAP | HERO | BLTC |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |swapWp|   ←  |   ↓  |   →  |action|           |      |  INV |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | enemy| dodge| jump |    |      |      |action|
 *                  `--------⤓GW2-| swim↑|    |skill1|------+------.
 *                                | fly↑ |    |      |
 *                                `------'    `------'
 */
[_GW1] = LAYOUT_split_3x5_3( \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, TG(_GW1), \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, DGE_GW2, _______,      _______, _______, _______                    \
),

/* Guild Wars 2 II
 *
 * ,----------------------------------.           ,----------------------------------.
 * | RAPT | HASI |ROCHEN| SCHAK| KÄFER|           |      | STUHL| MUSIK|      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   F1 |   F2 |   F3 |   F4 |WARCLW|           |      | DEKO | VERW |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | REIT |      |      | WAFFE|SKYSCL|           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | ENTRY|      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_GW2] = LAYOUT_split_3x5_3( \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______                    \
),

/* Russian Layout
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RUS] = LAYOUT_split_3x5_3( \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______                    \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

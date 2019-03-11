// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include "Kaleidoscope.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-USB-Quirks.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-LED-ActiveModColor.h"

enum { PRIMARY, NUMPAD, FUNCTION }; // layers
#define PRIMARY_KEYMAP_CUSTOM
KEYMAPS(

#if defined (PRIMARY_KEYMAP_CUSTOM)
  // Edit this keymap to make a custom layout
  [PRIMARY] = KEYMAP_STACKED
  (___,               Key_1,         Key_2,         Key_3, Key_4, Key_5, ___,
   Key_Backtick,      Key_Q,         Key_W,         Key_E, Key_R, Key_T, Key_Tab,
   OSM(LeftControl),  Key_A,         Key_S,         Key_D, Key_F, Key_G,
   Key_Escape, Key_Z, Key_X,         Key_C,         Key_V, Key_B,        ___,
   Key_Home,   Key_Backspace, OSM(LeftGui), OSM(LeftShift),
   OSL(FUNCTION),

   ___,               Key_6,        Key_7,        Key_8,     Key_9,         Key_0,         ___,
   ___,               Key_Y,        Key_U,        Key_I,     Key_O,         Key_P,         Key_Equals,
                      Key_H,        Key_J,        Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,      Key_N,        Key_M,        Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_Enter,         Key_End, Key_Spacebar, Key_RightControl,
   OSL(FUNCTION)),

#else

#error "No default keymap defined. You should make sure that you have a line like '#define PRIMARY_KEYMAP_QWERTY' in your sketch"

#endif

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   ___,                    ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,         Key_F5, Key_CapsLock,
   Key_Tab,  ___,              ___, ___,        ___,         ___,    ___,
   Key_LeftControl, ___,       ___, Key_Esc,    ___,         ___,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        ___,         ___,    ___,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, Key_RightAlt, ___, ___,
   ___)
	) // KEYMAPS(

void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

KALEIDOSCOPE_INIT_PLUGINS(
  HostPowerManagement,
  USBQuirks,
  EscapeOneShot,
  LEDControl,
  ActiveModColorEffect,
  OneShot
);

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  OneShot.disableStickabilityForLayers();
  OneShot.disableStickabilityForModifiers();
  ActiveModColorEffect.highlight_color = CRGB(0x00, 0xff, 0xff);
  //ActiveModColorEffect.sticky_color = CRGB(0xff, 0x00, 0x00);
  LEDOff.activate();
}

void loop() {
  Kaleidoscope.loop();
}

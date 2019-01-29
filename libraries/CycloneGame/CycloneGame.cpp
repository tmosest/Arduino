#include "Arduino.h"
#include "AsyncButtonRow.h"
#include "AsyncLightRow.h"
#include "CycloneGame.h"

CycloneGame::CycloneGame(unsigned int firstLight,
                         unsigned int lastLast,
                         unsigned int firstButton,
                         unsigned int lastButton) {
  playing = false;
  _asyncButtonRow = new AsyncButtonRow(firstButton, lastButton, _menuSpeed);
  _asyncLightRow = new AsyncLightRow(firstLight, lastLast, _menuSpeed);
  players = new bool[_asyncButtonRow->buttonCount()];
}

void CycloneGame::loop() {
  if (!playing) {
    bool* buttonStates = _asyncButtonRow->loop();
    _asyncLightRow->loop();
    int buttonCount = _asyncButtonRow->buttonCount();
    for (int i = 0; i < buttonCount; i++) {
      players[i] = buttonStates[i];
      if (players[i]) {
        playing = true;
      }
    }
    if (playing) {
      _asyncLightRow->turnOffLights();
    }
  }
}

void CycloneGame::menuLoop() {
  _asyncButtonRow->loop();
  _asyncLightRow->loop();
}

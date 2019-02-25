#include "Arduino.h"
#include "AsyncButtonRow.h"
#include "AsyncLightRow.h"
#include "CycloneGame.h"

CycloneGame::CycloneGame(
    unsigned int firstLight,
    unsigned int lastLast,
    unsigned int firstButton,
    unsigned int lastButton
) {
  _playing = false;
  _asyncButtonRow = new AsyncButtonRow(firstButton, lastButton, _menuSpeed);
  _asyncLightRow = new AsyncLightRow(firstLight, lastLast, _menuSpeed);
  _players = new bool[_asyncButtonRow->buttonCount()];
  _firstLight = firstLight;
  _lastLight = lastLast;
}

void CycloneGame::loop() {
  if (!_playing) {
    _menuLoop();
  } else {
    _gameLoop();
  }
}

void CycloneGame::_menuLoop() {
  bool* buttonStates = _asyncButtonRow->loop();
  _asyncLightRow->loop();
  int buttonCount = _asyncButtonRow->buttonCount();
  for (int i = 0; i < buttonCount; i++) {
    _players[i] = buttonStates[i];
  }
  _numPlayers = 0;
  if (_players[0] && _players[1]) {
    _playing = true;
    _numPlayers = 2;
    _startAndEnd = new int[_numPlayers];
    _startAndEnd[0] = _firstLight;
    _startAndEnd[1] = _lastLight;
    _score = new int[2];
  } else if (_players[0]) {
    _playing = true;
    _numPlayers = 1;
    _startAndEnd = new int[_numPlayers];
    _score = new int[_numPlayers];
    _startAndEnd[0] = _lastLight;
  } else if (_players[1]) {
    _numPlayers = 1;
    _playing = true;
    _startAndEnd = new int[_numPlayers];
    _score = new int[_numPlayers];
    _startAndEnd[0] = _firstLight;
  }
  if (_playing) {
    _asyncLightRow->stop();
    _asyncLightRow->turnOffLights();
    _asyncLightRow->blinkLights(_startAndEnd, _numPlayers, 3);
    _asyncLightRow->updateSpeed(_gameSpeed);
    _asyncButtonRow->updateSpeed(_gameSpeed);
    _asyncLightRow->startRandom();
  }
}

void CycloneGame::_gameLoop() {
  _asyncLightRow->loop();
  int buttonCount = _asyncButtonRow->buttonCount();
  bool* buttonStates = _asyncButtonRow->loop();
  if (_players[0] && _players[1]) {
    // handle both players
  } else if (_players[0]) {
    if (buttonStates[0]) {
      if (_asyncLightRow->getCurrentLight() == _firstLight) {
        _asyncLightRow->stop();
        _score[0]++;
        _asyncLightRow->turnOffLights();
        _asyncLightRow->updateSpeed(_menuSpeed);
        _asyncLightRow->blinkLights(_startAndEnd, _numPlayers, _score[0]);
        _asyncLightRow->updateSpeed(_gameSpeed);
        _asyncLightRow->startRandom();
        if (_score[0] >= _winningScore) {
          _asyncLightRow->updateSpeed(_menuSpeed);
          _playing = false;
        }
      }
    }
  } else if (_players[1]) {
    if (buttonStates[1]) {
      if (_asyncLightRow->getCurrentLight() == _lastLight) {
        _asyncLightRow->stop();
        _score[0]++;
        _asyncLightRow->turnOffLights();
        _asyncLightRow->updateSpeed(_menuSpeed);
        _asyncLightRow->blinkLights(_startAndEnd, _numPlayers, _score[0]);
        _asyncLightRow->updateSpeed(_gameSpeed);
        _asyncLightRow->startRandom();
        if (_score[0] >= _winningScore) {
          _asyncLightRow->updateSpeed(_menuSpeed);
          _playing = false;
        }
      }
    }
  }
}

#include "Arduino.h"
#include "AsyncLightRow.h"
#include "AsyncButtonRow.h"

#ifndef CycloneGame_h
#define CycloneGame_h

class CycloneGame {
 public:
  CycloneGame(
      unsigned int firstLight,
      unsigned int lastLast,
      unsigned int firstButton,
      unsigned int lastButton
  );
  void loop();
 private:
  int _firstLight;
  int _lastLight;
  unsigned int _gameSpeed = 75;
  unsigned int _menuSpeed = 500;
  int _winningScore = 5;
  bool _playing;
  bool* _players;
  int* _score;
  int _numPlayers;
  AsyncButtonRow* _asyncButtonRow;
  AsyncLightRow* _asyncLightRow;
  void _menuLoop();
  void _gameLoop();
  int* _startAndEnd;
};

#endif
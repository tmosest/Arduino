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
  unsigned int _menuSpeed = 500;
  bool playing;
  bool* players;
  AsyncButtonRow* _asyncButtonRow;
  AsyncLightRow* _asyncLightRow;
  void menuLoop();
};

#endif
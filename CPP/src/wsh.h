#pragma once
#include "builtin.h"

class Wsh {
 public:
  BuiltinFunc builtin;
  void loop();
  int launch(char** const args);
};

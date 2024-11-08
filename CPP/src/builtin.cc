#include "builtin.h"

#include <unistd.h>

#include <cstdio>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

const int NONE_BUILTIN_FUNC = -66666;
BuiltinFunc::BuiltinFunc() {
  builtin_funcs_["help"] =
      std::bind(&BuiltinFunc::help, this, std::placeholders::_1);
  builtin_funcs_["exit"] =
      std::bind(&BuiltinFunc::exit, this, std::placeholders::_1);
}

int BuiltinFunc::help(const std::string &args) {
  std::cout << "Wang's shell:" << std::endl
            << "The follow builtin funcs are useable:" << std::endl;
  for (auto &pair : builtin_funcs_) {
    std::cout << "  " << pair.first << std::endl;
  }
  std::cout << "Glad to use it~" << std::endl;
  return 1;
}

int BuiltinFunc::exit(const std::string &args) {
  std::cout << "Bye~" << std::endl;
  return 0;
}

int BuiltinFunc::parase_and_call(const std::string &args) {
  if (builtin_funcs_.find(args) != builtin_funcs_.end()) {
    return builtin_funcs_[args](args);
  } else {
    return NONE_BUILTIN_FUNC;
  }
}
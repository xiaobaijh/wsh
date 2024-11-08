#pragma once

#include <functional>
#include <string>
#include <unordered_map>

extern const int NONE_BUILTIN_FUNC;
class BuiltinFunc {
 public:
  BuiltinFunc();
  int help(const std::string & args);
  int exit(const std::string & args);
  int parase_and_call(const std::string& args);

 private:
  std::unordered_map<std::string, std::function<int(const std::string&)>> builtin_funcs_;
};
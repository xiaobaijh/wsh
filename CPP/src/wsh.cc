#include "wsh.h"

#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "builtin.h"

char** vectorToCharArray(const std::vector<std::string>& words) {
  char** result = new char*[words.size() + 1];  // +1 for the NULL terminator
  for (size_t i = 0; i < words.size(); ++i) {
    result[i] = new char[words[i].length() + 1];
    strcpy(result[i], words[i].c_str());
  }
  result[words.size()] = nullptr;  // NULL terminator
  return result;
}

void freeCharArray(char** array) {
  for (size_t i = 0; array[i] != nullptr; ++i) {
    delete[] array[i];
  }
  delete[] array;
}

void Wsh::loop() {
  std::string line;
  int status = 1;

  do {
    std::cout << "wsh> ";
    std::getline(std::cin, line);
    std::string word;
    std::vector<std::string> arguments;
    std::istringstream iss(line);
    while (iss >> word) {
      arguments.push_back(word);
    }

    if (arguments[0].empty()) {
      std::cout << "非法字符" << std::endl;
      continue;
    }

    char** args = nullptr;
    try {
      args = vectorToCharArray(arguments);
    } catch (const std::bad_alloc& e) {
      std::cerr << "内存分配失败: " << e.what() << std::endl;
      continue;
    } catch (const std::exception& e) {
      std::cerr << "发生错误: " << e.what() << std::endl;
      if (args != nullptr) {
        freeCharArray(args);
      }
      continue;
    }

    status = builtin.parase_and_call(arguments[0]);
    if (NONE_BUILTIN_FUNC == status) {
      status = launch(args);
    }

    freeCharArray(args);
  } while (status);
}

int Wsh::launch(char** const args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Pid==0 means run child process now,so we can exec what we want
    // The execvp() recevied args as a vector,it will search the args[0] in
    // the PATH and run it
    if (execvp(args[0], args) == -1) {
      perror("wsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("wsh");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
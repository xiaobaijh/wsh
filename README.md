# 简单的 Shell 实现

这是一个用 C 语言和 C++ 实现的简单 shell，基于 [Write Yourself a Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/) 教程。

## 功能

- 支持基本的命令执行
- 支持管道 (`|`)
- 支持输入重定向 (`<`) 和输出重定向 (`>`)

## 文件结构

- `C/`：包含用 C 语言实现的 shell
  - `main.c`：主程序文件，包含 shell 的主要逻辑
  - `builtin.c`：包含内建命令的实现
  - `builtin.h`：内建命令的头文件
  - `Makefile`：用于编译 C 语言实现的 shell 的 Makefile
- `CPP/`：包含用 C++ 实现的 shell
  - `main.cpp`：主程序文件，包含 shell 的主要逻辑
  - `builtin.cpp`：包含内建命令的实现
  - `builtin.h`：内建命令的头文件
  - `CMakeLists`：用于编译 C++ 实现的 shell 的 CMakeLists 文件

## 编译和运行

### 编译 C 语言实现

1. 克隆或下载此项目到本地
2. 在项目根目录下运行以下命令编译 C 语言实现：

    ```sh
    cd C
    make
    ```

3. 编译完成后，运行生成的可执行文件：

    ```sh
    ./build/wsh
    ```

### 编译 C++ 实现

1. 克隆或下载此项目到本地
2. 在项目根目录下运行以下命令编译 C++ 实现：

    ```sh
    cd CPP
    mkdir build
    cd build
    cmake ..
    make
    ```

3. 编译完成后，运行生成的可执行文件：

    ```sh
    ./build/wsh
    ```

## 使用示例

启动 shell 后，你可以输入以下命令：

```sh
$ ls -l
$ pwd
$ echo "Hello, World!"
$ cat file.txt | grep "pattern"
$ sort < unsorted.txt > sorted.txt
```
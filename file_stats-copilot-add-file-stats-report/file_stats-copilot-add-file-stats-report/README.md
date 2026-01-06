# 📊 文件统计工具 (File Stats)

一个简单而实用的文本文件统计工具，用于分析文件的行数、单词数和字符数。

---

## 📖 项目简介

`file_stats` 是一个基于 C++11 开发的命令行工具，可以快速统计任何文本文件的基本信息。这个项目非常适合 C++ 初学者学习文件操作、错误处理和命令行程序开发。

### ✨ 核心功能

- 📝 **行数统计** - 精确计算文件中的行数
- 🔤 **单词统计** - 智能识别并统计单词数量
- 🔢 **字符统计** - 统计文件中的所有字符（包括空白字符）
- ⚠️ **完善的错误处理** - 友好的中文错误提示
- 🎯 **简单易用** - 一条命令即可完成统计

---

## 🚀 快速开始

### 📋 前置要求

- **CMake** 3.10 或更高版本
- **C++11** 兼容的编译器（GCC 4.8+, Clang 3.3+, MSVC 2015+）
- **Ninja** 构建工具（推荐）或其他构建系统

### 💾 构建步骤

**方法一：使用 Ninja（推荐）**

```bash
# 1. 创建构建目录
mkdir build
cd build

# 2. 配置项目
cmake -G Ninja ..

# 3. 编译
ninja

# 4. 运行
./file_stats ../test_input.txt
```

**方法二：使用 Make**

```bash
mkdir build
cd build
cmake ..
make
./file_stats ../test_input.txt
```

**方法三：使用 Visual Studio**

1. 直接在 Visual Studio 中打开项目文件夹。
2. 等待 CMake 配置完成。
3. 按 `F5` 直接运行（已配置好 `launch.vs.json`）。

---

## 📚 使用说明

### 基本用法

```bash
file_stats <文件名>
```

### 使用示例

**示例 1：统计测试文件**

```bash
./file_stats test_input.txt
```

**输出结果：**

```text
====================
文件统计报告
====================
File: test_input.txt
Lines: 7
Words: 23
Characters: 142
====================
```

> 📸 *(此处演示程序运行截图)*

**示例 2：错误处理**

```bash
./file_stats nonexistent.txt
```

**输出结果：**

```text
Error: 无法打开文件 'nonexistent.txt'
请检查文件是否存在以及您是否有权限读取它
```

---

## 🔧 技术实现详解

### 技术栈

- **语言标准**：C++11
- **构建系统**：CMake 3.10+
- **标准库应用**：
  - `<fstream>`：用于文件的读取操作
  - `<cctype>`：用于 `std::isspace` 字符判断
  - `<iostream>`：用于标准的输入输出

### 核心算法：状态机单词统计

程序使用一个简单的**有限状态机 (Finite State Machine)** 来统计单词，这种方法比简单的空格分割更准确且无需额外的内存开销。

**算法逻辑：**

1. 维护一个布尔标志 `inWord`，初始为 `false`。
2. 逐个读取字符 `ch`：
   - 如果 `ch` 是空白字符（空格、换行、制表符）：
     - 设置 `inWord = false`（表示当前不在单词内）
   - 如果 `ch` 是非空白字符：
     - 如果当前 `!inWord`（即之前不在单词内）：
       - 说明遇到了新单词的第一个字符
       - **单词计数 +1**
       - 设置 `inWord = true`
     - 如果当前 `inWord`（已经在单词内）：
       - 继续读取，不做操作

```cpp
// 代码片段示意
bool inWord = false;
while (inputFile.get(ch)) {
    if (std::isspace(ch)) {
        inWord = false;
    } else {
        if (!inWord) {
            wordCount++;
            inWord = true;
        }
    }
}
```

### 字符与行数统计

- **字符统计**：每读取一个字节，计数器加一。
- **行数统计**：每遇到换行符 `\n`，行计数器加一。

---

## 🛡️ 错误处理机制

程序实现了三层防御性编程，确保运行稳定：

1. **参数检查**：
   - 验证 `argc` 是否为 2，确保用户输入了文件名。
   - 错误时输出用法提示。

2. **文件打开检查**：
   - 使用 `inputFile.is_open()` 检查文件是否成功打开。
   - 能够捕获文件不存在或权限不足的错误。

3. **读取状态检查**：
   - 在处理结束后检查 `inputFile.bad()`。
   - 捕获磁盘故障或读取过程中的硬件错误。

---

## 🏗️ 项目结构

```text
file_stats/
│
├── main.cpp              # 核心源代码
├── CMakeLists.txt        # CMake 构建脚本
├── test_input.txt        # 默认测试文件
├── README.md             # 本说明文档
└── .vs/
    └── launch.vs.json    # Visual Studio 调试配置
```

---

## 🔨 Visual Studio 调试指南

本项目已包含 `.vs/launch.vs.json` 配置文件，专为 Visual Studio 优化。

- **预设参数**：调试时默认传入 `test_input.txt` 作为参数。
- **工作目录**：自动设置为项目根目录，无需手动拷贝文件。

**如何修改调试参数：**
打开 `.vs/launch.vs.json`，修改 `args` 数组即可测试其他文件。

```json
"args": [ "your_custom_file.txt" ]
```

---

## 🤝 许可证

本项目作为示例代码开源，遵循 MIT 开源许可证。

# 定义编译器
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# 可执行文件名称
TARGET = main

# 源文件
SRCS = json.cpp main.cpp
# 源文件更通配的写法，新增 cpp 文件也不用修改 SRC
# SRCS = $(wildcard *.cpp)

# 默认目标
all: $(TARGET)

# 直接编译并链接
# $^ 是 $(SRCS), $@ 是 $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 清理生成的可执行文件
clean:
	rm -f $(TARGET)

# 防止人为创建的同名 clean 文件带来的干扰
.PHONY: all clean

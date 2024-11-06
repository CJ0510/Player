SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include


TARGET := $(BUILD_DIR)/app
CC := $(CROSS_COMPILE)gcc

# 找到所有的.c文件
SRCS_FILES := $(wildcard $(SRC_DIR)/*.c)

# 找到所有的.o文件
OBJS_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_FILES))

# 编译选项
CFLAGS := -I$(INCLUDE_DIR) -Wall -O2

# 生成目标文件
$(TARGET): $(OBJS_FILES)
	$(CC) $(OBJS_FILES) -o $@

# 生成.o文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 创建 build 目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 清理文件
clean:
	rm -rf $(BUILD_DIR)/*
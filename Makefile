CLIENT_EXE_NAME=client_x86_64

CC=gcc
CC_FLAGS=-c         \
			-g		\
			-W         \
			-Wall      \
			-ansi      \
			-pedantic
LD_FLAGS = -lm

SRC_DIR=src
OBJ_DIR=obj
OUT_DIR=build

COMMON_FILES=game_cli_renderer game list utils
CLIENT_FILES=client $(COMMON_FILES)
CLIENT_OBJ_FILES=$(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(CLIENT_FILES)))
OUT_FILE=$(OUT_DIR)/$(CLIENT_EXE_NAME)


client: build_dir obj_dir $(OUT_FILE)

$(OUT_FILE): $(CLIENT_OBJ_FILES)
	$(CC) $(LD_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $< $(CC_FLAGS) -o $@

obj_dir:
	@ mkdir -p obj

build_dir:
	@ mkdir -p build


clean:
	@ rmdir $(OUT_DIR)
	@ rmdir $(OBJ_DIR)

.PHONY: client clean
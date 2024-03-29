NAME = endgame

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = inc

SDL = -F resource/framework -I resource/framework/SDL2.framework/SDL2 -I resource/framework/SDL2_image.framework/SDL2_image \
	-I resource/framework/SDL2_mixer.framework/SDL2_mixer -I resource/framework/SDL2_ttf.framework/SDL2_ttf

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

INC_FILES = $(wildcard $(INC_DIR)/*.h)

CC = clang

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g \

SDL_FLAGS = -rpath resource/framework -framework SDL2 \
		-framework SDL2_image \
		-I resource/framework/SDL2_image.framework/Headers \
		-framework SDL2_mixer \
		-I resource/framework/SDL2_mixer.framework/Headers \
		-framework SDL2_ttf \
		-I resource/framework/SDL2_ttf.framework/Headers \

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME) clean

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(SDL_FLAGS) $(SDL)

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(SDL)

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)

reinstall: uninstall all

.PHONY: all uninstall clean reinstall

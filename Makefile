# SIMPLE ===================================================================================
NAME = gbmu
# ==========================================================================================

# SRCS =====================================================================================
SRCS_DIR = src/

SRCS =	main.cpp \
		GameWindow.cpp \
		LoadRoom.cpp \
		CPU.cpp \
		MemoryMap.cpp
# ==========================================================================================

# INCLUDES =================================================================================
INCS_DIR = inc/
INCLUDE = -I$(INCS_DIR) -I/usr/include/SDL2
# ==========================================================================================

# DEPEDENCIES ==============================================================================
DEPS = $(INCS_DIR)/
# ==========================================================================================

# FLAGS ====================================================================================
DEBUG = -g #-fsanitize=address
FLAGS = $(DEBUG) -Wall -Wextra -Werror $(INCLUDE)
# ==========================================================================================

# LIBS =====================================================================================
LIBS = -lSDL2 -lSDL2_ttf -lGL
# ==========================================================================================

# UTILS ====================================================================================
CC		= c++
RM		= rm -rf
# ==========================================================================================

# OBJS =====================================================================================
OBJS_DIR 	= 	objects/
OBJ 		= 	$(SRCS:.cpp=.o)
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))
# ==========================================================================================

# COLORS  ==================================================================================
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RED 		= 	\e[91m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m
CHECKMARK 	= 	✔
# ==========================================================================================

# COUNT  ===================================================================================
COUNT = 0
TOTAL = $(words $(SRCS))
# ==========================================================================================

# FROM SUBJECT =============================================================================
$(OBJS_DIR)%.o :	$(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	@$(eval COUNT = $(shell echo $$(($(COUNT) + 1))))
	@printf "$(YELLOW)Compiling:$(RESET) [$(GREEN)%3d%%$(RESET)]\r" $$(($(COUNT) * 100 / $(TOTAL)))
	@$(CC) $(FLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	@$(CC)  $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@printf "$(GREEN)$(CHECKMARK)	- Executable ready.\n$(RESET)"

all: $(NAME) desktop_entry

clean:
	@$(RM) $(OBJS_DIR)
	@printf "$(RED)$(CHECKMARK)	- Objects removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)$(CHECKMARK)	- Executable removed.$(RESET)\n"

re: fclean all
# ==========================================================================================

# SUP ======================================================================================
check: $(NAME)
	./$(NAME)
# ==========================================================================================

# .desktop executable ======================================================================
desktop_entry:
	echo "[Desktop Entry]" > $(NAME).desktop
	echo "Type=Application" >> $(NAME).desktop
	echo "Name=$(NAME)" >> $(NAME).desktop
	echo "Exec=./$(NAME)" >> $(NAME).desktop
#	echo "Icon=path/to/icon.png" >> $(NAME).desktop
	echo "Terminal=false" >> $(NAME).desktop
# ==========================================================================================

.PHONY: all clean fclean re
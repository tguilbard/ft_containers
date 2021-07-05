CC =		g++

VECTOR_SRC = test_vector.cpp
STACK_SRC = test_stack.cpp
MAP_SRC = test_map.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++98

# Colors

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

all:			vector stack map

vector: $(VECTOR_SRC) Makefile
		@echo "-----\nCreating Executable $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) -D TEST $(VECTOR_SRC) -o ft_vector
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Creating Executable $(_YELLOW)std_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) $(VECTOR_SRC) -o std_vector
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Execute $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@./ft_vector > ft_res
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Execute $(_YELLOW)std_$@$(_WHITE) ... \c"
		@./std_vector > std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Diff$(_YELLOW)$(_WHITE)"
		@diff ft_res std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"


stack: 	$(STACK_SRC) Makefile
		@echo "-----\nCreating Executable $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) -D TEST $(STACK_SRC) -o ft_stack
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Creating Executable $(_YELLOW)std_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) $(STACK_SRC) -o std_stack
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Execute $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@./ft_stack > ft_res
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Execute $(_YELLOW)std_$@$(_WHITE) ... \c"
		@./std_stack > std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Diff$(_YELLOW)$(_WHITE)"
		@diff ft_res std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"

map: 	$(MAP_SRC) Makefile
		@echo "-----\nCreating Executable $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) -D TEST $(MAP_SRC) -o ft_map
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Creating Executable $(_YELLOW)std_$@$(_WHITE) ... \c"
		@$(CC) $(CFLAGS) $(MAP_SRC) -o std_map
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Execute $(_YELLOW)ft_$@$(_WHITE) ... \c"
		@./ft_map > ft_res
		@echo "$(_GREEN)DONE$(_WHITE)\n"
		@echo "Execute $(_YELLOW)std_$@$(_WHITE) ... \c"
		@./std_map > std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"
		@echo "Diff$(_YELLOW)$(_WHITE)"
		@diff ft_res std_res
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"

re:				clean all

clean:
				@echo "$(_WHITE)Deleting Object $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -f ft_vector std_vector ft_stack std_stack ft_map std_map ft_res std_res
				@echo "$(_GREEN)DONE$(_WHITE)"


.PHONY: all clean re vector stack map

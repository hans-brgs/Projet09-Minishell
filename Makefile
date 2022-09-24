NAME		= minishell

SRCS		= main.c \
			builtin.c \
			builtin_cmd1.c \
			builtin_cmd2.c \
			builtin_cmd_utils.c \
			cmd_list_handler.c \
			environment1.c \
			environment2.c \
			environment3.c \
			error_handling.c \
			execute_cmd.c \
			execute_utils.c \
			expand_utils1.c \
			expand_variable.c \
			heredoc.c \
			lexer_error.c \
			lexer_operator.c \
			lexer_quotes_spaces.c \
			my_getpid.c \
			my_signal.c \
			parser.c \
			parser_cmd.c \
			parser_path.c \
			parser_redir.c \
			pimp_my_minishell.c \
			quotes.c \
			tkn_list_handler.c \

				

OBJ_DIR		= objs
OBJ_FILES	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

INCS		= -Ilibft

GCC			= gcc
RM			= rm -f
RMF			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
CFLAGS_COMP = -lreadline 
CFLAGS_COMP += -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include/

all:		libft $(NAME)

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(OBJ_DIR)
			@$(GCC) $(CFLAGS) -c $< $(INCS) -o $@

$(NAME):	$(OBJS) 
			@$(GCC) $(OBJS) ${INCS} libft/libft.a -o $(NAME) $(CFLAGS_COMP) 
			@printf "\nDone!\n";

libft:
			@make -C ./libft

clean:
			@make -C ./libft clean
			@$(RM) $(OBJS)
			@$(RMF) $(OBJ_DIR)

fclean:		clean
			@make -C ./libft fclean
			@$(RM) $(NAME)

re:			fclean all

#-----------------------------------------#
#				MY TOOLS				  #
#-----------------------------------------#
brew :
			rm -rf $(HOME)/.brew && git clone --depth=1 https://github.com/Homebrew/brew $(HOME)/.brew && echo 'export PATH=$(HOME)/.brew/bin:$(PATH)' >> $(HOME)/.zshrc && source $(HOME)/.zshrc && brew update
			
readline :
			@brew install readline

MSG = ""
git: fclean
	@git add .
	@git commit -am "`date +'%m-%d-%Y %H:%M:%S'` | $(MSG)"
	@git push

leak:		${NAME}
			valgrind --leak-check=full ./$(NAME)

.PHONY:		all clean fclean libft re .c.o norm brew val
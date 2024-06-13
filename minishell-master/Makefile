SRCS =  $(addprefix srcs/libft/, freet.c isaln.c isspace.c isdigit.c putstr_f.c split.c strjoin.c strjoinc.c strlen.c strnstr.c strnstr2.c strndup.c strcmp.c strncmp.c atoi.c itoa.c token_s.c env_len.c) \
		$(addprefix srcs/lex/, handler_1.c handler_2.c lsttoken.c lex.c) \
		$(addprefix srcs/utils/, u1.c u2.c u3.c utils_check.c shell.c signal.c env_init.c) \
		$(addprefix srcs/built/, built_utils.c cd_2.c cd.c echo.c env.c exit.c export.c pwd.c unset.c) \
		$(addprefix srcs/pipeline/, pipecheck.c pipeu1.c pipeu2.c) \
		$(addprefix srcs/parseur/, parseur.c parseur_u.c) \
		$(addprefix srcs/exec/, executeur.c execu1.c) \
		$(addprefix srcs/redirection/, redirection.c rediru1.c hdoc.c) \
		srcs/main.c

NAME = minishell

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

HEADER = -I./includes -I/Users/${USER}/.brew/opt/readline/include
all: $(NAME)

.c.o: $(SRCS)
	@printf "\r\033[KCreating files : <$<> "
	@gcc $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(HEADER) -o $(NAME) $(SRCS) -lreadline -L/Users/${USER}/.brew/opt/readline/lib
	@printf "\r\033[K$(NAME) done\n"

clean:
	@rm -rf $(OBJS) 
	@printf "clean done\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "fclean done\n"

re: fclean all

.PHONY: all clean fclean re

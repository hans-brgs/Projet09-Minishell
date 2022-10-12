/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:59:02 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/22 17:59:02 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "cmdlist.h"
# include "tknlist.h"
# include "libft/includes/libft.h"

# define SPE_CHAR "$\\#=[]!> <|;{}()*?~&+-/\"'°"
# define EXIT_FAIL -1
# define DEFAULT "\001\033[1;93m\002 ➜  \001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define BLUE "\001\033[1;94m\002"

int	g_status;

enum	e_error
{
	PERROR = 0,
	QUOTE = 1,
	PIPEN = 2,
	SUPERR = 3,
	INFERR = 4,
	DSUPERR = 5,
	DINFERR = 6,
	NL = 7,
	NDIR = 8,
	NPERM = 9,
	PIPERR = 10,
	FORKERR = 11,
	NCMD = 12,
	DUPERR = 13,
	OPT = 14,
	HNOSET = 15,
	TOOARGS = 16,
	NUMARGS = 17,
	INVID = 18,
};

typedef struct s_prompt
{
	char		**env;
	char		**argv;
	char		*input;
	char		*pimped_ms;
	int			is_exit;
	pid_t		pid;
}				t_prompt;

/* ----------------------------------------
				   UTILS
------------------------------------------*/
//-----> environment.c :
char	*my_getenv(char *name, char **env, int len);
char	**my_setenv(char *var, char *value, t_prompt *p, int len);
char	*find_last_slash(char *path);
char	**init_env(char **argv, t_prompt *p);
int		check_len_var(char *var);
void	extend_env(t_prompt *p, char *add);
void	drop_env(t_prompt *p, char *drop);

//-----> quotes.c :
char	*skip_quotes(char *str);
char	*skip_quotes_to_end(char *str);

//-----> pimp_my_minishell.c :
char	*pimp_my_minishell(char **env);
void	message(void);

///-----> readline
void	rl_replace_line(const char *text, int clear_undo);

//-----> signal.c :
void	handle_sigint(int sig);
void	handle_fork_sigint(int sig);
void	handle_heredoc(int sig);
void	handle_child(int sig);

//-----> heredoc.c
int		heredoc(char *delim, char **env, pid_t pid);

//-----> my_getpid.c :
int		my_getpid(void);

/* ----------------------------------------
				   LEXER
------------------------------------------*/
//-----> lexer_quotes_spaces.c :
int		lexer_quotes_spaces(t_tknlist **tkn, char *str);

//-----> lexer_operator.c :
int		lexer_operator(t_tknlist **tkn);

//-----> lexer_error.c :
int		check_error(char *str);
int		check_operator(t_tknlist **tkn);

/* ----------------------------------------
				  EXPANDER
------------------------------------------*/
//-----> expand_variable.c :
void	line_expander(t_tknlist *tkn, char **env, pid_t pid);

//-----> expand_utils.c :
int		is_quoted_dollar(char *str, int len);
int		expd_token_length(char *str);
char	*expand_dollar(char *str, char **env, int state, pid_t pid);
int		total_strlst_len(t_tknlist *expd);
char	*fill_array(int len, t_tknlist *expd);

/* ----------------------------------------
				   PARSER
------------------------------------------*/
//-----> parser.c :
int		parse(t_cmdlist **cmd, t_tknlist *tkn, char **env, pid_t pid);

//-----> parser_cmd.c :
char	**fill_cmd(t_tknlist *tkn);
char	*trim_quotes(char *str);

//-----> parser_path.c :
char	*parse_path(t_cmdlist *cmd, char **env);

//-----> parser_redir.c :
int		parse_output(int output, t_tknlist *tkn);
int		parse_input(int input, t_tknlist *tkn, char **env, pid_t pid);

/* ----------------------------------------
				  BUILTIN
------------------------------------------*/
//-----> builtin.c :
int		is_builtin(t_cmdlist *cmd);
int		builtin_parent(t_cmdlist *cmd, t_prompt *p);
int		builtin_child(t_cmdlist *cmd, t_prompt *p);

//-----> builtin_cmd.c :
int		my_export(t_cmdlist *cmd, t_prompt *p);
int		my_cd(t_cmdlist *cmd, t_prompt *p);
int		my_unset(t_cmdlist *cmd, t_prompt *p);
int		my_env(t_cmdlist *cmd, t_prompt *p);
int		my_echo(t_cmdlist *cmd);
int		my_exit(t_cmdlist *cmd, t_prompt *p);
int		my_pwd(t_cmdlist *cmd);

//-----> builtin_cmd_utils.c :
void	cd_to_home(t_cmdlist *cmd, t_prompt *p);
void	update_pwd(t_prompt *p);
int		export_error(char *var);
void	export_var(char *cmd, t_prompt *p);
void	export_print_env(t_prompt *p);
int		unset_error(char *cmd);

/* ----------------------------------------
				  EXECUTOR
------------------------------------------*/
//-----> execute_utils.c :
void	exec_cmd(t_cmdlist *cmd, t_prompt *p);

//-----> execute_cmd.c :
int		execute(t_cmdlist *cmd, t_prompt *p);

/* ----------------------------------------
				  ERROR
------------------------------------------*/
//-----> error_handling.c :
int		ft_error(int err_type, int status_err, char *str1, char *str2);
void	ft_exit(int err_type, int status_err, char *str, t_cmdlist *cmd);
int		ft_heredoc_error(int status_err, char *str);

#endif
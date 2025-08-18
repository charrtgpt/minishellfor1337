/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <mait-ijj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:07:40 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/05/13 04:27:37 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

typedef enum e_rtype
{
	R_OUT = 1,
	APPEND_R_IN,
	R_IN,
	HERDOC
}	t_rtype;

typedef struct s_excr
{
	char	*cmd_path;
	char	**clean;
	int		status;
	pid_t	pid;
}	t_excr;

typedef struct s_main
{
	char	**pars;
	char	***pipelines;
	char	**my_env;
	int		n_pipelines;
}	t_main;

typedef struct s_pipeline
{
	int		n;
	int		(*pipes)[2];
	pid_t	*pids;
	char	***cmds;
	char	**envp;
	int		*exit_status;
}	t_pipeline;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tofree
{
	t_env	**env;
	char	***pipelines;
	pid_t	*pids;
	char	**pars;
	char	**envp;
}	t_tofree;

typedef struct s_child_args
{
	int			prev_fd;
	int			pipefd[2];
	char		**cmd;
	char		**envp;
	t_tofree	*fr;
	int			*exit_status;
}	t_child_args;

char		*get_right_path(char *cmd, char **envp, char **args, t_tofree *fr);
char		*get_command_path(char *cmd, char **envp,
				char **args, t_tofree *fr);
char		*check_path(char *cmd, char **paths);
void		execute_command(char *cmd_p, char **argv,
				char **envp, t_tofree *fr);
void		free_str(char **str);
int			re_direction(char *f_name, int type);
char		**call_f(char *str);
int			w_e_m(char *message, char *add);
size_t		ft_strlen(const char *s);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		free_and_exitp(char **args, pid_t pid, int *status, t_tofree *fr);
void		handle_exit_status(pid_t pid, int *status);
int			if_pipe(char **args);
int			count_pipe_lines(char **args);
char		**dup_pipe_lines(char **args, int start, int end);
char		***split_on_pipes(char **args);
void		free_pipelines(char ***segs);
void		execute_pipeline(char ***cmds, char **envp,
				t_tofree *fr, int *exit_status);
void		execute_command_with_pipe(char **args, char **envp, t_tofree *fr,
				int *exit_status);
char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
char		**list_to_array(t_env *env);
int			list_size(t_env *env);
void		free_list(t_env *env);
t_env		*set_env(char **envp);
void		execute_command_with_redirection(char **args, char **envp,
				int *status, t_tofree *fr);
int			ft_echo(char **args, int status);
int			run_builttins(char **args, int *status, t_tofree *fr);
int			get_b_type(char *cmd);
char		**clean_arguments(char **args);
int			use_redirection(char **args);
int			find_r_type(const char *arg);
int			handle_input(char *input, t_env **env_list, int *exit_status);
void		cleanup(t_tofree *tofree, int i);
bool		*running_instance(void);
void		child_exit(t_tofree *fr, int status, int i);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(void);
void		env_add_or_update(t_env **env, char *arg);
int			ft_export(char **args, t_env **env);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_unset(char **args, t_env **env);
int			ft_env(t_env **env);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_exit(char **args, int last_status, t_tofree *fr);
int			heredoc_to_file(char *content);
int			check_fd(int fd, char *f_name);
int			three_d_len(char ***arr);
void		wait_childs(t_pipeline *p, int n);
int			setup_pipe(int idx, int n, int pipefd[2]);
void		child_execute(t_child_args args);
void		create_file_only(char **args, char **clean, int *status);
void		handle_env_error(char *cmd, char **clean, t_tofree *fr);
void		print_exit_if_interactive(void);
int			convert_digits(const char *s, size_t *i,
				unsigned long long *acc, int sign);
int			get_sign(const char *s, size_t *i);
size_t		skip_spaces(const char *s, size_t i);
void		print_exit_if_interactive(void);
int			norm_status(long long v);
int			ft_isdigit(int c);
int			ft_isspace(int c);

#endif

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
# include <errno.h>

typedef enum e_rtype
{
	R_OUT = 1,
	APPEND_R_IN,
	R_IN
}	t_rtype;

typedef struct s_excr
{
	char	*cmd_path;
	char	**clean;
	int		status;
	pid_t	pid;
}	t_excr;

typedef struct s_pipeline
{
	int		n;
	int		(*pipes)[2];
	pid_t	*pids;
	char	***cmds;
	char	**envp;
	int		status;
}	t_pipeline;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

char		*get_right_path(char *cmd, char **envp, char **args);
char		*get_command_path(char *cmd, char **envp, char **args);
char		*check_path(char *cmd, char **paths);
void		execute_command(char *cmd_p, char **argv, char **envp);
void		free_str(char **str);
int			re_direction(char *f_name, int type);
char		**call_f(char *str);
void		execute_command_with_redirection(char **args,
				char **envp);
int			w_e_m(char *message, char *add);
int			check_redirection_operator(char **args, int *position);
size_t		ft_strlen(const char *s);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		free_and_exitp(char **args, pid_t pid);
void		handle_exit_status(pid_t pid, int *status);
int			if_pipe(char **args);
int			count_pipe_lines(char **args);
char		**dup_pipe_lines(char **args, int start, int end);
char		***split_on_pipes(char **args);
void		free_pipelines(char ***segs);
void		execute_pipeline(char ***cmds, char **envp, int n);
void		execute_command_with_pipe(char **args, char **envp);
char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
char		**list_to_array(t_env *env);
int			list_size(t_env *env);
void		free_list(t_env *env);
t_env		*set_env(char **envp);

#endif

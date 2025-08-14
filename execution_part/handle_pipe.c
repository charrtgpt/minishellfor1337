#include "minishell.h"

static int	spawn_stage(t_pipeline *p, int idx, int prr_fd, int wpipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), -1);
	if (pid == 0)
	{
		if (prr_fd != -1)
		{
			dup2(prr_fd, STDIN_FILENO);
			close(prr_fd);
		}
		if (wpipe[1] != -1)
		{
			dup2(wpipe[1], STDOUT_FILENO);
			close(wpipe[0]);
			close(wpipe[1]);
		}
		execute_command_with_pipe(p->cmds[idx], p->envp);
	}
	if (prr_fd != -1)
		close(prr_fd);
	if (wpipe[1] != -1)
		close(wpipe[1]);
	p->pids[idx] = pid;
	return (0);
}

static void	wait_all_children(t_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n)
	{
		handle_exit_status(p->pids[i], &p->status);
		i++;
	}
}

static int	init_pipeline(t_pipeline *p, char ***cmds, char **envp, int n)
{
	p->n = n;
	p->cmds = cmds;
	p->envp = envp;
	p->status = 0;
	p->pids = malloc(sizeof(pid_t) * n);
	if (!p->pids)
		return (perror("minishell"), -1);
	return (0);
}

static void	cleanup_on_error(t_pipeline *p, int prev_read_fd, int pipefd[2])
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	if (prev_read_fd != -1)
		close(prev_read_fd);
	free(p->pids);
}

static int	run_pipeline_stages(t_pipeline *p, int *prev_read_fd)
{
	int	idx;
	int	pipefd[2];

	idx = 0;
	while (idx < p->n - 1)
	{
		if (pipe(pipefd) == -1)
			return (perror("minishell"), -1);

		if (spawn_stage(p, idx, *prev_read_fd, pipefd) == -1)
		{
			cleanup_on_error(p, *prev_read_fd, pipefd);
			return (-1);
		}

		*prev_read_fd = pipefd[0];
		idx++;
	}
	return (idx);
}

static int	run_last_stage(t_pipeline *p, int prev_read_fd, int idx)
{
	int	write_pipe[2];

	write_pipe[0] = -1;
	write_pipe[1] = -1;

	if (spawn_stage(p, idx, prev_read_fd, write_pipe) == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		free(p->pids);
		return (-1);
	}
	return (0);
}

void	execute_pipeline(char ***cmds, char **envp, int n)
{
	t_pipeline	p;
	int			prev_read_fd;
	int			last_idx;

	if (n <= 0)
		return ;
	if (init_pipeline(&p, cmds, envp, n) == -1)
		return ;
	prev_read_fd = -1;
	last_idx = run_pipeline_stages(&p, &prev_read_fd);
	if (last_idx == -1)
		return ;

	if (run_last_stage(&p, prev_read_fd, last_idx) == -1)
		return ;
	wait_all_children(&p);
	free(p.pids);
}

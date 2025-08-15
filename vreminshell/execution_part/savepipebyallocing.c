
// /* --------- Allocation and Cleanup --------- */

// static int allocate_pipeline(t_pipeline *p)
// {
// 	if (p->n <= 0)
// 		return (-1);
// 	if (p->n > 1)
// 	{
// 		p->pipes = malloc(sizeof(int[2]) * (p->n - 1));
// 		if (!p->pipes)
// 			return (perror("minishell: malloc"), -1);
// 	}
// 	else
// 		p->pipes = NULL;
// 	p->pids = malloc(sizeof(pid_t) * p->n);
// 	if (!p->pids)
// 	{
// 		free(p->pipes);
// 		return (perror("minishell: malloc"), -1);
// 	}
// 	return (0);
// }

// static void free_pipeline(t_pipeline *p)
// {
// 	free(p->pipes);
// 	free(p->pids);
// }

// /* --------- Pipe Operations --------- */

// static void open_all_pipes(t_pipeline *p)
// {
// 	int i = 0;
// 	while (i < p->n - 1)
// 	{
// 		if (pipe(p->pipes[i]) == -1)
// 		{
// 			perror("minishell: pipe");
// 			free_pipeline(p);
// 			exit(1);
// 		}
// 		i++;
// 	}
// }

// static void close_all_pipes(t_pipeline *p)
// {
// 	int i = 0;
// 	while (i < p->n - 1)
// 	{
// 		close(p->pipes[i][0]);
// 		close(p->pipes[i][1]);
// 		i++;
// 	}
// }

// /* --------- Child Execution --------- */

// static void setup_child_pipes(t_pipeline *p, int idx)
// {
// 	if (idx > 0)
// 		dup2(p->pipes[idx - 1][0], STDIN_FILENO);
// 	if (idx < p->n - 1)
// 		dup2(p->pipes[idx][1], STDOUT_FILENO);
// 	close_all_pipes(p);
// }
// /* --------- Forking & Waiting --------- */

// static void fork_pipeline(t_pipeline *p)
// {
// 	int i = 0;
// 	while (i < p->n)
// 	{
// 		p->pids[i] = fork();
// 		if (p->pids[i] < 0)
// 		{
// 			perror("minishell: fork");
// 			free_pipeline(p);
// 			exit(1);
// 		}
// 		if (p->pids[i] == 0)
// 		{
// 			setup_child_pipes(p, i);
// 			execute_command_with_pipe(p->cmds[i], p->envp);
// 		}
// 		i++;
// 	}
// }

// void execute_pipeline(char ***cmds, char **envp, int n)
// {
// 	t_pipeline	p;
// 	int i;

// 	p.n = n;
// 	p.cmds = cmds;
// 	p.envp = envp;
// 	if (allocate_pipeline(&p) < 0)
// 		return ;
// 	if (p.n > 1)
// 		open_all_pipes(&p);
// 	fork_pipeline(&p);
// 	if (p.n > 1)
// 		close_all_pipes(&p);
// 	i = 0;
// 	while(i < p.n)
// 		handle_exit_status(p.pids[i++], &p.status);
// 	free_pipeline(&p);
// }

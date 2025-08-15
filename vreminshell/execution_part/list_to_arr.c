#include "minishell.h"

int	list_size(t_env *env)
{
	int	n;

    n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

char	*node_to_string(t_env *node)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(node->name, "=");
	if (!tmp)
		return (NULL);
	if (node->value)
	{
		str = ft_strjoin(tmp, node->value);
		free(tmp);
		if (!str)
			return (NULL);
		return (str);
	}
	return (tmp);
}

char	**list_to_array(t_env *env)
{
	char	**arr;
	t_env	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (list_size(env) + 1));
	if (!arr)
		return (NULL);

	tmp = env;
	i = 0;
	while (tmp)
	{
		arr[i] = node_to_string(tmp);
		if (!arr[i])
		{
			free_str(arr);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// builtin_export.c

#include "minishell.h"

static void	print_env_export_format(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

static int	is_valid_identifier(const char *name, size_t len)
{
	size_t	i;

	if (len == 0)
		return (0);
	if (!ft_isalpha((unsigned char)name[0]) && name[0] != '_')
		return (0);
	i = 0;
	while (++i < len)
		if (!ft_isalnum((unsigned char)name[i]) && name[i] != '_')
			return (0);
	return (1);
}

static int	check_name(t_data *data, const char *arg)
{
	char	*eq;
	size_t	key_len;

	eq = ft_strchr(arg, '=');
	if (eq)
		key_len = (size_t)(eq - arg);
	else
		key_len = ft_strlen(arg);
	if (!is_valid_identifier(arg, key_len))
	{
		ft_dprintf(STDERR_FILENO, HEADER "export: not a valid identifier\n");
		data->exit_status = 1;
		return (0);
	}
	return (1);
}

static void	process_arg(t_data *data, const char *arg)
{
	char	*eq;
	size_t	key_len;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq == NULL)
		return ;
	key_len = (size_t)(eq - arg);
	key = ft_substr(arg, 0, key_len);
	if (key == NULL)
	{
		data->exit_status = 1;
		return ;
	}
	set_env(&data->env, key, eq + 1);
	free(key);
}

void	builtin_export(t_data *data, char **argv)
{
	int	i;

	data->exit_status = 0;
	if (!argv[1])
	{
		print_env_export_format(data->env);
		return ;
	}
	i = 0;
	while (argv[++i])
		if (check_name(data, argv[i]))
			process_arg(data, argv[i]);
}

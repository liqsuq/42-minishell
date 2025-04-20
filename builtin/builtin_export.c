// builtin_export.c

#include "minishell.h"

static int is_valid_identifier(const char *name)
{
	int i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha((unsigned char)name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum((unsigned char)name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void print_env_export_format(t_env *env)
{
  while (env)
  {
    if (env->value)
      printf("declare -x %s=\"%s\"\n", env->key, env->value);
    else
      printf("declare -x %s=\"\"\n", env->key);
    env = env->next;
  }
}

static void process_arg_val(t_data *data, const char *arg)
{
	char		*eq;
	size_t	key_len;
	char		*key_dup;

	eq = ft_strchr(arg, '=');
	key_len = (size_t)(eq - arg);
	key_dup = ft_substr(arg, 0, key_len);
	if (!key_dup)
		return;
	if (is_valid_identifier(key_dup))
	{
		set_env(&data->env, key_dup, eq + 1);
		data->exit_status = 0;
	}
	free(key_dup);
}

static void process_arg_key(t_data *data, const char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO,
			HEADER "export: not a valid identifier\n");
		data->exit_status = 1;
	}
	else
	{
		set_env(&data->env, (char *)arg, "");
		data->exit_status = 0;
	}
}

void builtin_export(t_data *data, char **argv)
{
	int		i;
	char	*eq;

	if (!argv[1])
	{
		print_env_export_format(data->env);
		data->exit_status = 0;
		return;
	}
	data->exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
			process_arg_val(data, argv[i]);
		else
			process_arg_key(data, argv[i]);
	}
}
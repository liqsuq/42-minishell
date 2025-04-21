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
    env = env->next;
  }
}

static void process_arg_val(t_data *data, const char *arg)
{
	char   *eq;
	size_t key_len;
	char   *key_dup;

	eq = ft_strchr(arg, '=');
	if (eq == NULL)
	{
		ft_dprintf(STDERR_FILENO, HEADER "export: '=' missing\n");
		data->exit_status = 1;
		return;
	}
	key_len = (size_t)(eq - arg);
	key_dup = ft_substr(arg, 0, key_len);
	if (key_dup	== NULL)
	{
		data->exit_status = 1;
		return;
	}
	set_env(&data->env, key_dup, eq + 1);
	free(key_dup);
}

static void check_arg(t_data *data, const char *arg)
{
	char   *eq;
	size_t  key_len;
	char   *key;

	eq = ft_strchr(arg, '=');
	if (eq)
		key_len = (size_t)(eq - arg);
	else
		key_len = ft_strlen(arg);
	key = ft_substr(arg, 0, key_len);
	if (key == NULL)
	{
		data->exit_status = 1;
		return;
	}
	if (!is_valid_identifier(key))
	{
		ft_dprintf(STDERR_FILENO, HEADER "export: not a valid identifier\n");
		data->exit_status = 1;
		free(key);
		return;
	}
	free(key);
	process_arg_val(data, arg);
}

void builtin_export(t_data *data, char **argv)
{
	int i;

	if (!argv[1])
	{
		print_env_export_format(data->env);
		data->exit_status = 0;
		return;
	}
	data->exit_status = 0;
	i = 0;
	while (argv[++i])
		check_arg(data, argv[i]);
}
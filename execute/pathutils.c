// pathutils.c

#include "minishell.h"

char	*resolve_path(t_env *env, char *line)
{
	char	path[PATH_MAX];
	char	*env_value;
	char	*end;

	if (ft_strchr(line, '/'))
		return (ft_strdup(line));
	env_value = get_env(env, "PATH");
	while (line && *line && env_value && *env_value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(env_value, ':');
		if (end != NULL)
			ft_strlcpy(path, env_value, end - env_value + 1);
		else
			ft_strlcpy(path, env_value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, line, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
		if (end == NULL)
			break ;
		env_value = end + 1;
	}
	return (NULL);
}

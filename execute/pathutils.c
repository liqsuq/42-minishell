// pathutils.c

#include "minishell.h"

static int	get_next_dir(const char **env_path, char *buf)
{
	const char	*p;
	size_t		len;

	if (*env_path == NULL || **env_path == '\0')
		return (1);
	p = *env_path;
	while (*p != '\0' && *p != ':')
		p++;
	len = p - *env_path;
	if (len >= PATH_MAX)
		len = PATH_MAX - 1;
	ft_memcpy(buf, *env_path, len);
	buf[len] = '\0';
	*env_path = p;
	if (**env_path == ':')
		(*env_path)++;
	return (0);
}

static void	join_filename(char *dirname, const char *filename)
{
	int	i;
	int	j;

	i = 0;
	while (dirname[i] != '\0' && i < PATH_MAX - 1)
		i++;
	if (i < PATH_MAX - 1)
		dirname[i++] = '/';
	j = 0;
	while (filename[j] && i < PATH_MAX - 1)
		dirname[i++] = filename[j++];
	dirname[i] = '\0';
}

static char	*search_path(const char *filename)
{
	char		dirname[PATH_MAX];
	const char	*env_value;

	env_value = getenv("PATH");
	if (env_value == NULL || *env_value == '\0')
		return (NULL);
	while (1)
	{
		ft_memset(dirname, 0, PATH_MAX);
		if (get_next_dir(&env_value, dirname))
			break ;
		join_filename(dirname, filename);
		if (access(dirname, X_OK) == 0)
			return (ft_strdup(dirname));
	}
	return (NULL);
}

char	*resolve_path(char *line)
{
	char	*path;

	if (line == NULL || *line == '\0')
		return (NULL);
	if (ft_strchr(line, '/'))
		return (ft_strdup(line));
	path = search_path(line);
	if (path == NULL)
		dprintf(STDERR_FILENO, "%s: command not found\n", line);
	return (path);
}

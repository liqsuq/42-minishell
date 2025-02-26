// search_path.c
# include "minishell.h"

static int get_next_dir(const char **env_path, char *buf)
{
	const char *start;
	const char *p;
	size_t len;

	start = *env_path;
	if (!*start)
		return (0);

	p = start;
	while (*p && *p != ':')
		p++;

	len = p - start;
	if (len >= PATH_MAX)
		len = PATH_MAX - 1;

	ft_memcpy(buf, start, len);
	buf[len] = '\0';
	if (*p == ':')
		*env_path = p + 1;
	else
		*env_path = p;

	return (1);
}

static void join_filename(char *dir, const char *filename)
{
	size_t i = 0;
	size_t fn = 0;

	while (dir[i] != '\0' && i < PATH_MAX - 1)
		i++;

	if (i < PATH_MAX - 1)
		dir[i++] = '/';

	while (filename[fn] && i < PATH_MAX - 1) {
		dir[i] = filename[fn];
		i++;
		fn++;
	}
	dir[i] = '\0';
}

char *search_path(const char *filename)
{
	char dir[PATH_MAX];
	const char *env_value;

	env_value = getenv("PATH");
	if (!env_value || !*env_value)
		return (NULL);
	while (1)
	{
		ft_memset(dir, 0, PATH_MAX);
		if (!get_next_dir(&env_value, dir))
			break;
		join_filename(dir, filename);
		if (access(dir, X_OK) == 0)
		{
			char *dup_path;

			dup_path = ft_strdup(dir);
			if (!dup_path)
				fatal_error("strdup");
			return dup_path;
		}
	}
	return NULL;
}

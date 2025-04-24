// builtin_cd.c
#include "minishell.h"

static void	cd_error(t_data *data, const char *arg)
{
	ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n", arg);
	data->exit_status = 1;
}

static void	do_chdir(t_data *data, const char *path, const char *original_arg)
{
	if (chdir(path) < 0)
	{
		cd_error(data, original_arg);
		return;
	}
	// cd 成功
	data->exit_status = 0;
}

static void update_pwd_if_needed(t_data *data)
{
	// もし PWD が unset されていないなら（= NULL でないなら）更新する
	if (get_env(data->env, "PWD") != NULL)
	{
		char	cwd[PATH_MAX];
		char	*oldpwd = get_env(data->env, "PWD");

		// OLDPWD 更新（Bash 互換を意識するなら PWD が unset でも更新するやり方もある）
		if (oldpwd)
			set_env(&data->env, "OLDPWD", oldpwd);

		// 物理パスで PWD を更新する例 (論理パス維持なら getcwd() しない実装もあり)
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "cd: getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return;
		}
		set_env(&data->env, "PWD", cwd);
	}
}

void builtin_cd(t_data *data, char **argv)
{
	char *home;
	char *oldpwd;
	char *pwd;
	char *tmp;

	if (!argv[1])
	{
		// cd の引数が無ければ HOME を使う
		home = get_env(data->env, "HOME");
		if (!home)
		{
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
			data->exit_status = 1;
			return;
		}
		do_chdir(data, home, home);
		if (data->exit_status == 0)
			update_pwd_if_needed(data);
		return;
	}

	if (ft_strcmp(argv[1], "-") == 0)
	{
		oldpwd = get_env(data->env, "OLDPWD");
		if (!oldpwd)
		{
			ft_dprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
			data->exit_status = 1;
			return;
		}
		// do_chdir は「パスを指定して chdir」するだけ
		do_chdir(data, oldpwd, oldpwd);
		if (data->exit_status == 0)
			update_pwd_if_needed(data);
		// Bash 互換にするなら「新しい PWD を表示」も入れる
		// char *pwd = get_env(data->env, "PWD");
		// if (pwd)
		//   ft_putendl_fd(pwd, STDOUT_FILENO);
		return;
	}

	if (argv[1][0] == '/')
	{
		// 絶対パス
		do_chdir(data, argv[1], argv[1]);
		if (data->exit_status == 0)
			update_pwd_if_needed(data);
	}
	else
	{
		// 相対パス
		pwd = get_env(data->env, "PWD");
		if (!pwd)
		{
			// PWD が unset → getcwd() でフォールバック
			char cwd[PATH_MAX];
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				ft_dprintf(STDERR_FILENO, "cd: getcwd: %s\n", strerror(errno));
				data->exit_status = 1;
				return;
			}
			pwd = cwd;
		}
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			fatal_error("malloc");

		char *fullpath = ft_strjoin(tmp, argv[1]);
		free(tmp);
		if (!fullpath)
			fatal_error("malloc");
		do_chdir(data, fullpath, argv[1]);
		free(fullpath);
		if (data->exit_status == 0)
			update_pwd_if_needed(data);
	}
}

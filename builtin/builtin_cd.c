// builtin_cd.c
#include "minishell.h"

/**
 * 相対パスの場合は PWD 環境変数があればそこからの相対パスとして扱う。
 * PWD が無い場合は getcwd() を使う。
 * chdir に成功したら、PWD が unset されていなければ更新する。
 */
static void cd_to_path(t_data *data, const char *path, char *argv)
{
	// まず、現在の PWD を取得
	char *oldpwd = get_env(data->env, "PWD");

	// chdir 実行
	if (chdir(path) < 0)
	{
		ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n", argv);
		data->exit_status = 1;
		return;
	}

	// chdir 成功 → 必要なら OLDPWD を更新
	// Bash 互換を目指すなら、PWD が unset でもここで OLDPWD を更新する
	if (oldpwd != NULL)
		set_env(&data->env, "OLDPWD", oldpwd);

	// さらに、PWD が unset されていなければ getcwd() で新しいディレクトリを設定
	if (get_env(data->env, "PWD") != NULL)
	{
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, HEADER "cd: getcwd: %s\n", strerror(errno));
			data->exit_status = 1;
			return;
		}
		set_env(&data->env, "PWD", cwd);
	}
	data->exit_status = 0;
}

void builtin_cd(t_data *data, char **argv)
{
	if (argv[1] == NULL)
	{
		// 引数がない場合: HOME を使う
		char *home = get_env(data->env, "HOME");
		if (!home)
		{
			ft_dprintf(STDERR_FILENO, HEADER "cd: HOME not set\n");
			data->exit_status = 1;
			return;
		}
		// ユーザ入力 (argv[1]) はNULLだが、一応そのまま渡す
		cd_to_path(data, home, argv[1]);
		return;
	}

	// argv[1] が絶対パスか相対パスかを判定
	if (argv[1][0] == '/')
	{
		// 絶対パス
		// 第3引数にユーザ入力の相対パスを渡す
		cd_to_path(data, argv[1], argv[1]);
	}
	else
	{
		// 相対パスを絶対パスに結合
		char *pwd = get_env(data->env, "PWD");
		if (pwd == NULL)
		{
			char cwd[PATH_MAX];
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				ft_dprintf(STDERR_FILENO, HEADER "cd: getcwd: %s\n", strerror(errno));
				data->exit_status = 1;
				return;
			}
			pwd = cwd;
		}
		char *tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			fatal_error("malloc");
		char *path = ft_strjoin(tmp, argv[1]);
		free(tmp);
		if (!path)
			fatal_error("malloc");

		// 第3引数にユーザ入力 (argv[1]) を渡す
		cd_to_path(data, path, argv[1]);
		free(path);
	}
}

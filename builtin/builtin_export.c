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

/*
 * 1引数の場合:
 *   - KEY=VAL (valid)   => set_env, exit_status=0
 *   - KEY=VAL (invalid) => スキップ, exit_status=0
 *   - KEY (valid)       => 値="", exit_status=0
 *   - KEY (invalid)     => exit_status=1
 *
 * この挙動で "export [invalid]" => exit_status=1 となる。
 *  "export [invalid]=val" => スキップするが exit_status=0
 */
static void process_single_arg(t_data *data, const char *arg)
{
	char *eq;
	char *key_dup;
	size_t key_len;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key_len = eq - arg;
		key_dup = ft_substr(arg, 0, key_len);
		if (!key_dup)
			return; // malloc失敗時とりあえず無視

		if (is_valid_identifier(key_dup))
			set_env(&data->env, key_dup, eq + 1);
		// invalid=Val => 何もせず exit_status=0
		free(key_dup);
		data->exit_status = 0;
	}
	else
	{
		// KEY だけ
		if (!is_valid_identifier(arg))
		{
			// "export [invalid]" => exit_status=1
			data->exit_status = 1;
		}
		else
		{
			set_env(&data->env, (char *)arg, "");
			data->exit_status = 0;
		}
	}
}

/*
 * 複数引数:
 *   無効はスキップ (エラー扱いにしない)
 *   有効は set_env
 *   最終的に exit_status=0
 */
static void process_multi_args(t_data *data, char **argv)
{
	int i;
	char *eq;
	char *key_dup;
	size_t key_len;

	i = 1;
	while (argv[i] != NULL)
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			key_len = (size_t)(eq - argv[i]);
			key_dup = ft_substr(argv[i], 0, key_len);
			if (key_dup)
			{
				if (is_valid_identifier(key_dup))
					set_env(&data->env, key_dup, eq + 1);
				free(key_dup);
			}
		}
		else
		{
			// KEYだけ
			if (is_valid_identifier(argv[i]))
				set_env(&data->env, (char *)argv[i], "");
		}
		i++;
	}
	data->exit_status = 0;
}

/*
 * builtin_export:
 *  - 引数0 => 環境一覧, status=0
 *  - 引数1 => process_single_arg
 *  - 引数複数 => process_multi_args (無効は黙ってスキップ, status=0)
 */
void builtin_export(t_data *data, char **argv)
{
	int arg_count;
	int user_args;

	arg_count = 0;
	while (argv[arg_count] != NULL)
		arg_count++;

	user_args = arg_count - 1; // 実際の引数数( "export" は除く)

	// 引数なし => 一覧表示
	if (user_args == 0)
	{
		print_env_export_format(data->env);
		data->exit_status = 0;
		return;
	}
	// 単一引数
	if (user_args == 1)
	{
		process_single_arg(data, argv[1]);
		return;
	}
	// 複数 => 無効はスキップ, 有効だけ登録, 最終status=0
	process_multi_args(data, argv);
}
// builtin_export.c

#include "minishell.h"

/*
 * [a-zA-Z_][a-zA-Z0-9_]*
 */
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
 * 単一引数を処理するサブ関数
 * - KEY=VAL (valid)   -> set_env して status=0
 * - KEY=VAL (invalid) -> 追加しない, status=0
 * - KEY (valid)       -> 値=""で追加, status=0
 * - KEY (invalid)     -> status=1
 */
static void process_single_arg(t_data *data, char *arg)
{
	char *eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		// KEY=VAL (or invalid=VAL)
		*eq = '\0';
		if (is_valid_identifier(arg))
		{
			// valid -> 追加
			set_env(&data->env, arg, eq + 1);
		}
		// invalid なら何もしない (status=0)
		*eq = '=';
		data->exit_status = 0;
	}
	else
	{
		// KEY だけ
		if (!is_valid_identifier(arg))
		{
			// invalid -> status=1
			data->exit_status = 1;
		}
		else
		{
			// valid -> 値="" で追加
			set_env(&data->env, arg, "");
			data->exit_status = 0;
		}
	}
}

/*
 * 複数引数の中に 1つでも invalid があれば
 *  -> すべて追加しない & status=0
 * 全部 valid なら全部追加 & status=0
 */
static int has_invalid_args(char **argv)
{
	int i = 1;
	while (argv[i])
	{
		char *eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			if (!is_valid_identifier(argv[i]))
			{
				*eq = '=';
				return 1; // invalid発見
			}
			*eq = '=';
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
				return 1; // invalid発見
		}
		i++;
	}
	return 0; // 全部valid
}

/*
 * 全部 valid の場合、改めて追加
 */
static void add_valid_args(t_data *data, char **argv)
{
	int i = 1;
	while (argv[i])
	{
		char *eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			set_env(&data->env, argv[i], eq + 1);
			*eq = '=';
		}
		else
		{
			set_env(&data->env, argv[i], "");
		}
		i++;
	}
	data->exit_status = 0;
}

/*
 * builtin_export:
 *  - 引数なし        -> 環境一覧を表示
 *  - 引数1つ         -> 単一引数のロジック
 *  - 引数複数        -> invalid混在なら無視、validだけ追加
 */
void builtin_export(t_data *data, char **argv)
{
	int arg_count = 0;
	int user_args;

	while (argv[arg_count])
		arg_count++;
	user_args = arg_count - 1; // argv[0]は"export"自身

	if (user_args == 0)
	{
		// 引数なし -> 環境一覧
		print_env_export_format(data->env);
		data->exit_status = 0;
		return;
	}
	if (user_args == 1)
	{
		// 単一引数
		process_single_arg(data, argv[1]);
		return;
	}
	// それ以外 -> 複数引数
	if (has_invalid_args(argv))
	{
		// 無効混入 -> 追加しないがstatus=0
		data->exit_status = 0;
	}
	else
	{
		// 全部valid -> 追加
		add_valid_args(data, argv);
	}
}

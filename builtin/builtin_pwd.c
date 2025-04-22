// builtin_pwd.c
#include "minishell.h"

/**
 * PWD があればそれを出力。
 * なければ getcwd() でカレントディレクトリを取得して出力。
 * 取得に失敗した場合はエラーにする。
 */
void builtin_pwd(t_data *data, char **argv)
{
    (void)argv;  // argv[1] などオプションは今回は単純化し、無視する例

    char *pwd_env = get_env(data->env, "PWD");
    if (pwd_env)
    {
        // unset されていない PWD が存在
        ft_putendl_fd(pwd_env, STDOUT_FILENO);
        data->exit_status = 0;
        return;
    }
    else
    {
        // PWD が無い場合は getcwd()
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            ft_dprintf(STDERR_FILENO, HEADER "pwd: getcwd: %s\n", strerror(errno));
            data->exit_status = 1;
            return;
        }
        ft_putendl_fd(cwd, STDOUT_FILENO);
        data->exit_status = 0;
    }
}

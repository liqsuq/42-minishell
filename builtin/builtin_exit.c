// builtin_exit.c

#include "minishell.h"

static int	is_number(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

static int	is_overflow(const char *nptr, unsigned long long n, int sign)
{
	unsigned long long	cutoff;
	unsigned long long	cutlim;

	if (sign >= 0)
		cutoff = LLONG_MAX;
	else
		cutoff = -(unsigned long long)LLONG_MIN;
	cutlim = cutoff % 10;
	cutoff /= 10;
	if (n > cutoff || (n == cutoff && (unsigned long)(*nptr - '0') > cutlim))
		return (1);
	return (0);
}

static long long	ft_strtoll(const char *nptr)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr) && !is_overflow(nptr, (unsigned long long)n, sign))
		n = n * 10 + *nptr++ - '0';
	if (!is_overflow(nptr, n, sign))
		return (n * sign);
	if (sign > 0)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

void	builtin_exit(t_data *data, char **argv)
{
	int			exit_status;
	long long	num;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (argv[1] == NULL)
		exit_status = data->exit_status;
	else if (argv[2] != NULL)
	{
		ft_dprintf(STDERR_FILENO, HEADER "exit: too many arguments\n");
		exit_status = ERROR_GENERAL;
	}
	else if (!is_number(argv[1]))
	{
		ft_dprintf(STDERR_FILENO, HEADER "exit: numeric argument required\n");
		exit_status = ERROR_SYNTAX;
	}
	else
	{
		num = ft_strtoll(argv[1]);
		exit_status = (int)(unsigned int)(num % 256);
	}
	free_argv(argv);
	exit(exit_status);
}

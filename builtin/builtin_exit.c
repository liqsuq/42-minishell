/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:42:02 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/02 20:41:10 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static long long	ft_strtoll(const char *nptr, char **endptr)
{
	unsigned long long	n;
	int					sign;

	n = 0;
	sign = 1;
	if (endptr != NULL)
		*endptr = (char *)nptr;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr) && !is_overflow(nptr, n, sign))
		n = n * 10 + *nptr++ - '0';
	if (endptr != NULL)
		*endptr = (char *)nptr;
	if (*nptr == '\0')
		return (n * sign);
	if (sign > 0)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

static void	summarize(int *status, const char *msg, int num)
{
	if (msg != NULL)
		ft_dprintf(STDERR, HEADER "%s", msg);
	if (status != NULL)
		*status = num;
}

void	builtin_exit(t_data *data, char **argv)
{
	int			stat;
	long long	num;
	char		*endptr;

	if (isatty(STDIN))
		ft_dprintf(STDERR, "exit\n");
	if (argv[1] == NULL)
		summarize(&stat, NULL, data->exit_status);
	else if (argv[2] != NULL)
		summarize(&stat, "exit: too many arguments\n", EXIT_FAILURE);
	else if (!is_number(argv[1]))
		summarize(&stat, "exit: numeric argument required\n", ERROR_SYNTAX);
	else
	{
		num = ft_strtoll(argv[1], &endptr);
		if (*endptr != '\0')
			summarize(&stat, "exit: numeric argument required\n", ERROR_SYNTAX);
		else
			summarize(&stat, NULL, (int)(unsigned int)(num % 256));
	}
	free_argv(&argv);
	exit_shell(data, stat);
}

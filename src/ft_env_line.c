/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:18 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/01 14:09:38 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_env_line(char **big_env, char *str)
{
	int		j;
	int		i;

	i = 0;
	while (big_env[i])
	{
		j = 0;
		while (big_env[i][j] != '\0' && big_env[i][j] == str[j])
			j++;
		if (str[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

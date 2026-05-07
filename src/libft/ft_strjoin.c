/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:23:50 by jobraga           #+#    #+#             */
/*   Updated: 2025/04/14 19:41:11 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	tamto;
	char	*s_total;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tamto = ft_strlen(s1) + ft_strlen(s2);
	s_total = malloc(sizeof(char) * (tamto + 1));
	if (!s_total)
		return (NULL);
	while (s1[i] != '\0')
	{
		s_total[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s_total[j + i] = s2[j];
		j++;
	}
	s_total[i + j] = '\0';
	return (s_total);
}

// int	main(void)
// {
// 	char str[] = "ALO";
// 	char *str2 = NULL;

// 	printf("Essa frase '%s' junta com essa '%s'. 
// Dá essa frase '%s'.\n", str, str2, ft_strjoin(str, str2));
// 	return (0);
// }

#include "minishell.h"

char	*ft_charjoin_free(char *s1, char s2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = ft_strlen(s1);
	j = 1;
	str = ft_calloc((i + j + 1), sizeof(char));
	if (str != NULL)
	{
		k = 0;
		while (s1[k] != '\0')
		{
			str[k] = s1[k];
			k++;
		}
		str[k] = s2;
		free(s1);
		return (&str[0]);
	}
	return (0);
}
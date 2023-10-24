/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:52:31 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/16 13:44:58 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_line(char *buffer);
char	*ft_buffer(char *buffer);
char	*ft_read(int fd, char *buffer);
size_t	gnl_strlen(const char *s);
size_t	gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif

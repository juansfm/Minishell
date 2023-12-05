/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:34:16 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/09 20:11:26 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*Tests if c is a letter*/
int					ft_isalpha(int c);

/*Tests if c is a digit*/
int					ft_isdigit(int c);

/*Tests if c is a letter or a digit*/
int					ft_isalnum(int c);

/*Tests if c is a ascii character*/
int					ft_isascii(int c);

/*Tests if c is a printable character*/
int					ft_isprint(int c);

/*Returns the length of str*/
size_t				ft_strlen(const char *str);

/*Copies the character c in b len times*/
void				*ft_memset(void *b, int c, size_t len);

/*Copies the character '\0' in s n times*/
void				ft_bzero(void *s, size_t n);

/*Copies in dst n bytes of src*/
void				*ft_memcpy(void *dst, const void *src, size_t n);

/*Copies in dst n bytes of src without overlapping*/
void				*ft_memmove(void *dst, const void *src, size_t len);

/*Copies in dst n characters of src and return the length of src*/
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*Concatenates dstsize characters of dst and src and returns the 
length of src plus the lesser between the length of dest and dstsize*/
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

/*Transforms upper case letters in lower case letters*/
int					ft_tolower(int c);

/*Transforms lower case letters in upper case letters*/
int					ft_toupper(int c);

/*Locates the first ocurrence of c in s*/
char				*ft_strchr(const char *s, int c);

/*Locates the last ocurrence of c in s*/
char				*ft_strrchr(const char *s, int c);

/*Compares n characters of s1 and s2 and returns the difference*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*Locates the byte c in the n bytes of s*/
void				*ft_memchr(const void *s, int c, size_t n);

/*Compares n bytes of s1 and s2 and returns the difference*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*Locates the string needle in haystack in the len characters*/
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/*Transforms a string in integer*/
int					ft_atoi(const char *str);

/*Allocates memory for count objects of size bytes and filles with '\0'*/
void				*ft_calloc(size_t count, size_t size);

/*Allocates memory with the length of s1 and copies s1*/
char				*ft_strdup(const char *s1);

/*Creates a string that starts in the character start of s with length len*/
char				*ft_substr(const char *s, unsigned int start, size_t len);

/*Concatenates s1 and s2*/
char				*ft_strjoin(const char *s1, const char *s2);

/*Eliminates the characters from the start and the end
 of s1 which appears in set*/
char				*ft_strtrim(const char *s1, const char *set);

/*Separates s by the character c*/
char				**ft_split(const char *s, char c);

/*Transforms an integer in string*/
char				*ft_itoa(int n);

/*Applies the function f in the characters of s*/
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/*Applies the function f in the directions of the characters of s*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*Writes the character c in the file fd*/
void				ft_putchar_fd(char c, int fd);

/*Writes the string s in the file fd*/
void				ft_putstr_fd(char *s, int fd);

/*Writes the string s and a newline in the file fd*/
void				ft_putendl_fd(char *s, int fd);

/*Writes the integer n in the file fd*/
void				ft_putnbr_fd(int n, int fd);

/*Frees a matrix*/
void				ft_free(char **matrix, int j);

/*Returns the length of matrix*/
int					ft_mtxrow(char **matrix);

int					ft_strcmp(const char *s1, const char *s2);

long				ft_atol(const char *str);

unsigned int		ft_atou(const char *str);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
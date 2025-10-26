/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:06:59 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/26 19:01:37 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef MAX_FD
#  define MAX_FD 1000
# endif

/* parte 1 */
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
unsigned int		ft_strlcat(char *dest, char *src, unsigned int size);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *str, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

/* parte 2 */
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **split);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strjoin_free(char *s1, char *s2, int free_flag);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/* parte bonus */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
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

/* Printf */
int					ft_printf(const char *s, ...);
int					ft_strlen_pf(char *s);
int					ft_putnbr_pf(int n);
int					ft_putchar_pf(char c);
int					ft_putstr_pf(char *s);
int					ft_void_hexa(void *p);
int					ft_unsigndec(unsigned int n);
int					ft_lowhexa(int n);
int					ft_upphexa(int n);

/* Get_next_line */
char				*get_next_line(int fd);
int					ft_strlen_gnl(char *s);
char				*ft_strchr_gnl(char *s, int c);
char				*ft_strjoin_gnl(char *bff, char *nl);
char				*ft_strdup_gnl(const char *s1);
void				*ft_calloc_gnl(size_t count, size_t size);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				*content;
	struct s_list	*next;

}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

int					ft_atoi(const char *nptr, int *valid);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(char const *s, char c);
char				**ft_split_free(char **arr);
void				ft_putstr_fd(char *str, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *item);
void				ft_lstadd_sorted(t_list **head, void *content,
						int (*f)(void *, void *));
int					ft_lstsize(t_list *lst);
char				*ft_strndup(const char *src, size_t n);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *item);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_printf(const char *format, ...);
int					ft_vprintf(va_list args, const char *format, ...);
char				*ft_strchr(const char *s, int c);
int					ft_putchr(char c);
int					ft_putstr(char *s);
int					ft_putnbr(int n);
int					ft_putunbr(unsigned int n);
int					ft_putnbr_hex(unsigned long num, int uppercase);
int					ft_putptr(void *num);

ssize_t				get_next_line(int fd, char **receiver);
ssize_t				ft_istrchr(const char *s, char c);

#endif

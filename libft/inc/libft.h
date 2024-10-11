/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:32:18 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/16 17:03:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define HEXX "0123456789abcdef"
# define HEX "0123456789ABCDEF"

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# define RED "\033[0;31m"
# define GREEN "\033[0;92m"




# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/types.h>
# include <fcntl.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_intlst
{
	int				value;
	struct s_intlst	*next;
	int				src_pos_cost;
	int				dst_pos_cost;
	unsigned int	cost;
}					t_intlst;

int				ft_atoi(const char *str);

int				ft_abs(int n);

int				ft_digitcount(unsigned long n, int base);

int				ft_max(int a, int b);

void			ft_bzero(void *s, size_t n);

void			*ft_calloc(size_t count, size_t size);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

int				ft_is_samesign(int a, int b);

int				ft_isspace(int c);

int 			ft_ischarset(char c, const char *set);

int				ft_isint(char *string);

int				ft_isline(char *string);

char			*ft_itoa(int n);

void			ft_striteri(char *s, void (*f)(unsigned int, char*));

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memccpy(void *dest, const void *src, int c, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *b, int c, size_t len);

size_t			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *s, int fd);

size_t			ft_putnbr_fd(int nb, int fd);

size_t			ft_putnbr_unsigned(unsigned int n, int fd);

int				ft_printf(char const *str, ...);

size_t 			ft_puthex(unsigned long int num, char const *str);

size_t			ft_putchar_fd(char c, int fd);

size_t			ft_putstr_fd(char *s, int fd);

int				ft_check_format(char const *ptr, size_t len, va_list args);

char			**ft_split(char const *s, char c);

char			*ft_strchr(const char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char const *s1, char const *s2);

size_t			ft_strlcat(char *dst, const char *src, size_t size);

char			*ft_strcat(char *dest, const char *src);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);

size_t			ft_strlen(const char *s);

char			*ft_strmapi(char *s, char (*f)(unsigned int, char));

int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_strcmp(const char *s1, const char *s2);

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_strtrim(char const *s1, char const *set);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

t_list			*ft_lstnew(void *content);

size_t 			ft_lstsize(t_list *lst);

t_list			*ft_lstlast(t_list *lst);

char			*get_next_line(int fd);

void 			ft_lstadd_front(t_list **lst, t_list *new);

void			ft_lstadd_back(t_list **lst, t_list *new);

void			ft_lstadd_back(t_list **lst, t_list *new);

void			ft_lstdelone(t_list *lst, void (*del)(void*));

void			ft_lstclear(t_list **lst, void (*del)(void*));

void			ft_lstiter(t_list *lst, void (*f)(void*));

t_list			*ft_lstmap(t_list *lst, void *(*f)(void*),
				 void (*del)(void *));
				 
t_intlst		*ft_args_to_intlst(int argc, char **argv);

void			ft_intlst_addfront (t_intlst **lst, t_intlst *new);

void 			ft_intlst_addback(t_intlst **lst, t_intlst * new);

t_intlst		*ft_intlst_before_last (t_intlst *lst);

void			ft_intlst_free(t_intlst **lst);

int				ft_intlst_isresorted(t_intlst *lst);

int				ft_intlst_issorted(t_intlst *lst);

int				ft_intlst_isrevsorted(t_intlst *lst);

t_intlst		*ft_intlst_last(t_intlst *lst);

int				ft_intlst_maxval(t_intlst *lst);

int				ft_intlst_minval(t_intlst *lst);

t_intlst		*ft_intlst_new(int value);

void			ft_intlst_print(t_intlst *lst);

size_t			ft_intlst_size(t_intlst *lst);

#endif
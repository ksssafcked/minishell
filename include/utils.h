/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:23:24 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:04:40 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct s_indices
{
	int	left;
	int	right;
}		t_indices;

char	*ft_strchr(const char *str, int c);
int		ft_isalnum(int c);
int		ft_isdigit(int d);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, unsigned int len);
char	*ft_strdup(const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_partition(unsigned char *base, size_t size, int (*cmp)(const void *,
				const void *), int left_right[2]);
void	ft(unsigned char *base, size_t size, int (*cmp)(const void *,
				const void *), t_indices lr);
void	ft_qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *,
				const void *));
int		ft_isspace(int c);
long	ft_strtol(const char *str, char **endptr, int base);
int		char_is_separator(char c, char separator);
int		count_words(char const *str, char c);
char	*allocate_word(char const *str, char c, int *i);
int		write_split(char **split, char const *str, char c);
char	**ft_split(char const *str, char c);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
void	ft_bzero(void *dst, size_t n);
void	ft_swap_bytes(unsigned char *a, unsigned char *b, size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
void	*ft_memcpy(void *dest_str, const void *src_str, size_t n);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_calloc(size_t num, size_t size);

#endif
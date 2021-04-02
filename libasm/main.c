/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:23:09 by lregenar          #+#    #+#             */
/*   Updated: 2020/11/12 14:12:34 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

ssize_t         ft_read(int fd, char *buf, int size);
ssize_t         ft_write(int fd, char *buf, int size);
int             ft_strcmp(char *str1, char *str2);
char            *ft_strcpy(char *dst, char *src);
char            *ft_strdup(char *str);
unsigned long   ft_strlen(char *str);

int             main(void)
{
    char        *empty_str;
    char        *long_str;
    char        buf[100];
    
    empty_str = "";
    long_str = "qwertyuioplkjhgfdsazxcvbnmehrbfkjfdnkjfkjfnjksjkfnkjefnkjfkjsdfjkfdnkjdfnkjdfnkjndfjkndfkjndf";
    printf("=======Test ft_strlen=======\n");
    printf("empty : >%lu<\n", strlen(empty_str));
    printf("empty : >%lu<\n", ft_strlen(empty_str));
    printf("long : >%lu<\n", strlen(long_str));
    printf("long : >%lu<\n", ft_strlen(long_str));
    printf("=======Test ft_strcpy=======\n");
    printf("empty : >%s<\n", strcpy(buf, empty_str));
    printf("empty : >%s<\n", ft_strcpy(buf, empty_str));
    printf("long : >%s<\n", strcpy(buf, long_str));
    printf("long : >%s<\n", ft_strcpy(buf, long_str));
    printf("=======Test ft_strcmp=======\n");
    char *s1 = "hohohohahaza";
    char *s2 = "hohoethahaza";
    printf("2 Empty strings\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(empty_str, empty_str), ft_strcmp(empty_str, empty_str));
    printf("1st empty string\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(empty_str, s1), ft_strcmp(empty_str, s1));
    printf("2nd empty string\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(s1, empty_str), ft_strcmp(s1, empty_str));
    printf("2 strings : s1 & s2\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(s1, s2), ft_strcmp(s1, s2));
    printf("2 strings : s2 & s1\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(s2, s1), ft_strcmp(s2, s1));
    printf("Identical strings\n");
    printf("Not mine: %d Mine: %d\n\n", strcmp(s1, s1), ft_strcmp(s1, s1));
    printf("=======Test ft_write=======\n");
    int fd_my = open("my.txt", O_RDWR| O_CREAT | O_TRUNC, 0666);
    int fd_real = open("real.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    int i_my;
    int i_real;
    char *str = "Hello_I_am_Danny";
    printf("STDOUT\n");
    printf("Real:");
    i_real = write(1, str, strlen(str));
    write(1, "\n", 1);
    printf("Return value:%d\n", i_real);
    printf("My:");
    i_my = ft_write(1, str, strlen(str));
    ft_write(1, "\n", 1);
    printf("Return value:%d\n\n", i_my);
    printf("File\n");
    printf("Real:");
    i_real = write(fd_real, str, strlen(str));
    printf("Return value:%d\n", i_real);
    printf("My:");
    i_my = write(fd_my, str, strlen(str));
    printf("Return value:%d\n", i_my);
    printf("Wrong fd:\n");
    printf("Real:\n");
    errno = 0;
    i_real = write(100, str, strlen(str));
    printf("Return value: %d\n", i_real);
    perror("Errno: ");
    printf("My:\n");
    errno = 0;
    i_my = ft_write(100, str, strlen(str));
    printf("Return value: %d\n", i_my);
    perror("Errno");
    close(fd_my);
    close(fd_real);
    
    printf("=======Test ft_read=======\n");
    fd_my = open("my.txt", O_RDWR);
    fd_real = open("real.txt", O_RDWR);
    char my[1000];
    char real[1000];
    bzero(real, 1000);
    bzero(my, 1000);
    printf("STDIN:\n");
    printf("Real:\n");
    i_real = read(0, real, 1000);
    printf("%s\n", real);
    printf("Return value: %d\n", i_real);
    printf("My:\n");
    i_my = ft_read(0, my, 1000);
    printf("%s\n", my);
    printf("Return value: %d\n\n", i_my);
    printf("File\n");
    bzero(real, 1000);
    bzero(my, 1000);
    printf("Real:\n");
    i_real = read(fd_real, real, 999);
    printf("%s\n", real);
    printf("Return value: %d\n", i_real);
    printf("My:\n");
    i_my = ft_read(fd_my, my, 999);
    printf("%s\n", my);
    printf("Return value: %d\n\n", i_my);
    printf("Wrong fd:\n");
    bzero(real, 1000);
    bzero(my, 1000);
    printf("Real:\n");
    errno = 0;
    i_real = read(100, real, 999);
    printf("Return value: %d\n", i_real);
    perror("Errno: ");
    printf("My:\n");
    errno = 0;
    i_my = ft_read(100, my, 999);
    printf("Return value: %d\n", i_my);
    perror("Errno");
    close(fd_my);
    close(fd_real);
    
    printf("=======Test ft_strdup=======\n");
    printf("empty: >%s<\n", strdup(empty_str));
    printf("empty: >%s<\n", ft_strdup(empty_str));
    printf("long: >%s<\n", strdup(long_str));
    printf("long: >%s<\n", ft_strdup(long_str));
    return (0);
}

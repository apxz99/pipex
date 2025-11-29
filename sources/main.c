/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:22:45 by sarayapa          #+#    #+#             */
/*   Updated: 2025/09/14 16:08:24 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>

//// Helper function for ft_strmapi and ft_striteri
//char test_mapi(unsigned int i, char c)
//{
//    return (c + i % 2); // สลับเพิ่มค่า ascii เล็กน้อย
//}

//void test_iteri(unsigned int i, char *c)
//{
//    if (i % 2 == 0)
//        *c = *c - 1;
//}

//void del(void *content)
//{
//    free(content);
//}

//void test_libc_functions()
//{
//    printf("==== Testing Libc Functions ====\n");
//    printf("ft_isalpha('A') = %d\n", ft_isalpha('A'));
//    printf("ft_isdigit('5') = %d\n", ft_isdigit('5'));
//    printf("ft_isalnum('Z') = %d\n", ft_isalnum('Z'));
//    printf("ft_isascii(128) = %d\n", ft_isascii(128));
//    printf("ft_isprint(32) = %d\n", ft_isprint(32));

//    printf("ft_strlen(\"Hello\") = %zu\n", ft_strlen("Hello"));

//    char buf[20];
//    ft_memset(buf, 'A', 5);
//    buf[5] = '\0';
//    printf("ft_memset = %s\n", buf);

//    ft_bzero(buf, 5);
//    printf("ft_bzero = %s\n", buf);

//    char src[] = "World";
//    char dst[10];
//    ft_memcpy(dst, src, 6);
//    printf("ft_memcpy = %s\n", dst);

//    ft_memmove(dst+1, dst, 5);
//    printf("ft_memmove overlap = %s\n", dst);

//    char copy[10];
//    ft_strlcpy(copy, "Hello", 10);
//    printf("ft_strlcpy = %s\n", copy);

//    char cat[20] = "Hello ";
//    ft_strlcat(cat, "World", 20);
//    printf("ft_strlcat = %s\n", cat);

//    printf("ft_toupper('a') = %c\n", ft_toupper('a'));
//    printf("ft_tolower('A') = %c\n", ft_tolower('A'));
//    printf("ft_strchr(\"Hello\", 'e') = %s\n", ft_strchr("Hello", 'e'));
//    printf("ft_strrchr(\"Hello\", 'l') = %s\n", ft_strrchr("Hello", 'l'));
//    printf("ft_strncmp(\"abc\",\"abd\",3) = %d\n", ft_strncmp("abc","abd",3));
//    printf("ft_memchr(\"abcde\",'c',5) = %s\n", (char*)ft_memchr("abcde",'c',5));
//    printf("ft_memcmp(\"abc\",\"abd\",3) = %d\n", ft_memcmp("abc","abd",3));
//    printf("ft_strnstr(\"Hello World\",\"World\",11) = %s\n", ft_strnstr("Hello World","World",11));
//    printf("ft_atoi(\"-1234\") = %d\n", ft_atoi("-1234"));

//    char *calloc_test = ft_calloc(5, sizeof(int));
//    printf("ft_calloc success? %s\n", calloc_test ? "YES" : "NO");
//    free(calloc_test);

//    char *dup = ft_strdup("Libft");
//    printf("ft_strdup = %s\n", dup);
//    free(dup);
//}

//void test_additional_functions()
//{
//    printf("\n==== Testing Additional Functions ====\n");
//    char *substr = ft_substr("Hello World", 6, 5);
//    printf("ft_substr = %s\n", substr);
//    free(substr);

//    char *join = ft_strjoin("Hello ", "World");
//    printf("ft_strjoin = %s\n", join);
//    free(join);

//    char *trim = ft_strtrim("!!Hello!!", "!");
//    printf("ft_strtrim = %s\n", trim);
//    free(trim);

//    char **split = ft_split("a,b,c", ',');
//    for (int i=0; split[i]; i++)
//        printf("ft_split[%d] = %s\n", i, split[i]);
//    free(split[0]); free(split[1]); free(split[2]); free(split);

//    char *itoa = ft_itoa(-123);
//    printf("ft_itoa = %s\n", itoa);
//    free(itoa);

//    char *mapi = ft_strmapi("abc", test_mapi);
//    printf("ft_strmapi = %s\n", mapi);
//    free(mapi);

//    char striteri[] = "abcd";
//    ft_striteri(striteri, test_iteri);
//    printf("ft_striteri = %s\n", striteri);

//	ft_putstr_fd("ft_putchar_fd: ", 1);
//	ft_putchar_fd('X', 1);
//	write(1,"\n",1);
//	ft_putstr_fd("ft_putstr_fd: ", 1);
//    ft_putstr_fd("ft_putstr_fd: Hello", 1);
//	write(1,"\n",1);
//	ft_putstr_fd("ft_putendl_fd: ", 1);
//    ft_putendl_fd("World", 1);
//	ft_putstr_fd("ft_putnbr_fd: ", 1);
//    ft_putnbr_fd(1234, 1);
//	write(1,"\n",1);
//}

//void test_bonus_functions()
//{
//    printf("\n==== Testing Bonus List Functions ====\n");
//    t_list *lst = ft_lstnew(strdup("First"));
//	ft_lstadd_back(&lst, ft_lstnew(strdup("Second")));
//	ft_lstadd_front(&lst, ft_lstnew(strdup("Zero")));

//	printf("ft_lstsize = %d\n", ft_lstsize(lst));
//	printf("ft_lstlast = %s\n", (char*)ft_lstlast(lst)->content);

//	ft_lstiter(lst, (void (*)(void *))puts);

//	ft_lstclear(&lst, del);
//	printf("After clear, lst = %p\n", (void*)lst);
//}

//int main(void)
//{
//    test_libc_functions();
//    test_additional_functions();
//    test_bonus_functions();
//    return (0);
//}

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	//char *a = ft_substr(NULL, 4, 4);
	ft_putnbr_fd(123, -1);
}
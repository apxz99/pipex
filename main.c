#include <unistd.h>

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, sizeof(str) - 1);
}
int main(void)
{
	char *str = "hello";
	write(1, str, sizeof(str) - 1);
	return 0;
}

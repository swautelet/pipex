# include "src/pipex.h"
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
		i++;
	return (i);
}
int main ()
{
	char buffer[10];
	int	len;

	len = read (0, buffer, 10);
	while (len > 0)
	{
		len = read(0, buffer, 10);
		buffer[len] = '\0';
		write (1, buffer, ft_strlen(buffer));
	}
	write(1, buffer, ft_strlen(buffer));
}
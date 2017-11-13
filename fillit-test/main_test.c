#include "fillit.h"
#include "libft/libft.h"
#include <fcntl.h>

t_list	*display(t_list *elem)
{
	t_tetri	*tetri;

	tetri = (t_tetri*)(elem->content);
	ft_putnbr(tetri->width);
	ft_putchar('x');
	ft_putnbr(tetri->height);
	ft_putstr("\nElement ");
	ft_putchar(tetri->letter);
	ft_putstr(": \n");
	while (*(tetri->minos))
	{
		ft_putstr(*((tetri->minos)++));
		ft_putchar('\n');
	}
	ft_putstr("\n---\n");
	return elem;
}

int main(int argc, const char *argv[])
{
	ft_lstmap(ft_read_fd(open(argv[1], O_RDONLY)), &display);
	//ft_display(ft_solve(ft_read_fd(open("sample4", O_RDONLY))));
	return 0;
}

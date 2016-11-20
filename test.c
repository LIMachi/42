#include <libft.h>

int main()
{
	t_bitmap	*bmp;

	ft_init(NULL);
	bmp = ft_bitmap_file_load("minecraft-font-iso-8859-1.bmp");
	ft_bmp_print_info(bmp);
	ft_free(bmp->bmp);
	ft_free(bmp);
	return (0);
}

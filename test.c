#include "./libft/inc/libft.h"

int main(int argc,  char **argv)
{
	t_bitmap	*bmp;

	if (argc < 2)
		return (0);
	ft_init(NULL);
	bmp = ft_bitmap_file_load(argv[1]);
	ft_bmp_print_info(bmp);
	ft_free(bmp->bmp);
	ft_free(bmp);
	return (0);
}

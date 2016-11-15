#include "../../minilibx_X11/mlx.h"
#include "../../libft/inc/libft.h"
#include <stdio.h>
#include <string.h>

//DISPLAY

void	*protected_mlx_init(const char **env)
{
	void	*mlx;
	int		i;
	int		err;

	err = 0;
	if (*env == NULL && (err = 1))
	{
		ft_log("Bad corrector, 'env -i' is bad, and you should fell bad for ");
		ft_log("doing this :´(\nShuting down gracefully anyway\n");
	}
	i = -1;
	while (env[++i])
		if (env[i] == ft_strstr((char *)env[i], "DISPLAY="))
			break ;
	if ((err == 0) && !env[i] && (err = 1))
	{
		ft_log("Weird, I can't found that damn display... oh, right, 'env -u ");
		ft_log("DISPLAY' must have been here earlier, this filthy stealer. Oh");
		ft_log(" well, no show tonight\n");
	}
	if (err == 0 && (mlx = mlx_init()) == NULL && (err = 1))
		ft_log("mlx_init() failed, and I just don't know what went wrong :(\n");
	if (err == 1)
		ft_global_callback(EXIT, "reason: error on mlx_init()");
	return (mlx);
}

int	main(const int argc, const char **argv, const char **env)
{
	void	*mlx;

	mlx = protected_mlx_init(env);
}

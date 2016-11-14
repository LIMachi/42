clear
make fclean -C fdf
make fclean -C "Fract'ol"
make fclean -C libftx
make fclean -C libft
make fclean -C "./turned in/fdf"
make clean -C "./turned in/fdf/minilibx_X11"
make clean -C minilibx_X11
make clean -C minilibx_macos
find . -name ".DS_Store" -delete
find . -name "~*" -delete
git add *
git status
git commit -m "`date`"

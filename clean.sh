if [ $1 == "" ]
then
	dir=.
else
	dir=$1
fi

find $dir -depth \( -name "\.DS_Store" -o -name "\._*" -o -name "*.~" \) -print -exec rm -rf '{}' \;
find $dir -depth \( -name "log\.txt" -o -name "\.Trash*" -o -name "*\.42_cache_bak_*" -o -name "\$RECYCLE\.BIN" \) -print -ok rm -rf '{}' \;

makefiles="`find $dir -depth -name Makefile`";
for v in $makefiles; do
	t=`echo $v | rev | cut -f2- -d/ | rev`
	make fclean -C $t
	make clean -C $t
done

rm -rf $dir/**/.dep

#!/bin/bash
# ---------------------------------------------------------------------------- #
# casioenv.sh -- v0.2 by CakeIsALie5                                           #
# Simple CASIO developing environment installing script.                       #
# More or less replaces packet management softwares.                           #
# ---------------------------------------------------------------------------- #
# Initialize                                                                   #

IFS='
'
dflt='\e[39m'
blue='\e[34m'
red='\e[31m'

# Checking if required programs are installed                                  #

if ! command -v curl 2>&1 >/dev/null; then
	echo -e "${red}curl is required for this script.${dflt}" >&2
	echo -e "${red}Please install it then re-run this.${dflt}" >&2
	exit 1
fi

if ! command -v git 2>&1 >/dev/null; then
	echo -e "${red}git is required for this script.${dflt}" >&2
	echo -e "${red}Please install it then re-run this.${dflt}" >&2
	exit 1
fi

# Checking if libs are there                                                   #

echo "The following libs are required :"
echo "- mpfr (libmpfr-dev)"
echo "- mpc (libmpc-dev)"
echo "- gmp (libgmp-dev)"
echo "- libpng (libpng12-dev)"
echo "- ppl (libppl-dev)"
echo -n "Have you installed them [yn] ? "
read answer

if ! [ "$answer" = "y" ]; then
	echo -e "${red}Then you know what you have to do before re-running this script.${dflt}" >&2
	exit 1
fi

# Getting path of cross-compiler                                               #

echo "Path of the cross-compiler ?"
echo -n "> "
read XGCCDIR

if [ -e "$XGCCDIR" ]; then
	if [ -d "$XGCCDIR" ]; then
		echo -e "${red}Directory already exists.${dflt}" >&2
	else
		echo -e "${red}Something else already has this filename.${dflt}" >&2
	fi
	echo -e "${red}Have you miswritten the directory path ?${dflt}" >&2
	echo -e "${red}In case you have just created the directory before${dflt}" >&2
	echo -e "${red}executing this script, please delete it then rerun this.${dflt}" >&2
	exit 1
fi

echo -e "${blue}OK, starting the script.${dflt}\n"
export PATH="$PATH:$XGCCDIR/bin"
mkdir -p "/tmp$(realpath $XGCCDIR)"
cd "/tmp$(realpath $XGCCDIR)"

# Downloading all the required stuff                                           #

GCCDL=ftp://gcc.gnu.org/pub/gcc/releases/gcc-6.1.0/gcc-6.1.0.tar.gz
echo -e "${blue}Downloading gcc 6.1.0...${dflt}"
if ! curl -o gcc-6.1.0.tar.gz -# "$GCCDL"; then
	echo "Failed to download gcc. Exiting." >&2
	exit 1
fi

BUTDL=ftp://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.gz
echo -e "${blue}Downloading binutils 2.26...${dflt}"
if ! curl -o binutils-2.26.tar.gz -# "$BUTDL"; then
	echo "Failed to download binutils. Exiting." >&2
	exit 1
fi

WPGD=https://bitbucket.org/Lephenixnoir/add-in-wrapper.git
echo -e "${blue}Cloning lephenixnoir's wrapper...${dflt}"
if ! git clone "$WPGD" wrapper 2>&1 >/dev/null; then
	echo "Failed to clone lephenixnoir's wrapper. Exiting." >&2
	exit 1
fi

UCDL=http://www.planet-casio.com/files/forums/UsbConnector-13656.zip
echo -e "${blue}Downloading UsbConnector...${dflt}"
if ! curl -o usbconnector.zip -# $UCDL; then
	echo "Failed to download UsbConnector. Exiting." >&2
	exit 1
fi

# All 'bout binutils                                                           #

echo -e "${blue}Expanding binutils 2.26...${dflt}"
tar xzf binutils-2.26.tar.gz

mkdir binutils-build && cd binutils-build

echo -e "${blue}Configuring binutils 2.26...${dflt}"
../binutils-2.26/configure --target=sh3eb-elf --prefix="$XGCCDIR" \
	--disable-nls 2>&1 >/dev/null

echo -e "${blue}Making binutils 2.26...${dflt}"
make -s 2>&1 >/dev/null

echo -e "${blue}Installing binutils 2.26...${dflt}"
make -s install 2>&1 >/dev/null

cd ..

# All 'bout gcc and libgcc                                                     #

echo -e "${blue}Expanding gcc 6.1.0...${dflt}"
tar xzf gcc-6.1.0.tar.gz

mkdir gcc-build && cd gcc-build

echo -e "${blue}Configuring gcc 6.1.0...${dflt}"
../gcc-6.1.0/configure --target=sh3eb-elf --prefix="$XGCCDIR" \
	--disable-nls --enable-languages=c,c++ --without-headers 2>&1 >/dev/null

echo -e "${blue}Making gcc 6.1.0...${dflt}"
make -s all-gcc 2>&1 >/dev/null

echo -e "${blue}Installing gcc 6.1.0...${dflt}"
make -s install-gcc 2>&1 >/dev/null

echo -e "${blue}Making gcc 6.1.0's libgcc...${dflt}"
make -s all-target-libgcc 2>&1 >/dev/null

echo -e "${blue}Installing gcc 6.1.0's libgcc...${dflt}"
make -s install-target-libgcc 2>&1 >/dev/null

cd ..

# Make and install lephe's wrapper                                             #

cd wrapper

echo -e "${blue}Making lephenixnoir's wrapper...${dflt}"
make -s all 2>&1 >/dev/null

echo -e "${blue}Installing lephenixnoir's wrapper...${dflt}"
/usr/bin/install -m 755 build/g1a-wrapper "$XGCCDIR/bin/g1a-wrapper"

cd ..

# Make and install UsbConnector                                                #

echo -e "${blue}Expanding UsbConnector...${dflt}"
unzip usbconnector.zip 2>&1 >/dev/null

echo -e "${blue}Installing UsbConnector...${dflt}"
/usr/bin/install -m 755 UsbConnector/UsbConnector "$XGCCDIR/bin/usb-connector"
ln -sf usb-connector "$XGCCDIR/bin/UsbConnector"

# Ending                                                                       #

rm -rf $(pwd)

echo ""
echo "All the required tools have been installed under the following directory:"
echo "> $XGCCDIR"
echo "Don't forget to add \"$XGCCDIR/bin\" to your PATH !"

# The End.                                                                     #

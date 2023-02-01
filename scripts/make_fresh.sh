#!/bin/sh
cd /Users/markoates/Repos

# sync dotfiles
cd .dotfiles
git pull
source ./.zshrc

# make allegro_flare
cd ../blast
git pull
make clean && make programs -j8 && make && make clean && make programs -j8 && make

# make allegro_flare
cd ../allegro_flare
git pull
make clean && make

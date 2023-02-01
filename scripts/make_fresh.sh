#!/bin/sh

while true; do
    read -p "For this script to run effectively, it's important that \"status\" has run clean. This is just a reminder. Do you wish to continue with the script? " yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done

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

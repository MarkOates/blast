#!/bin/sh


#----- core -----


#- dotfiles
#- union
#- blast
#- allegro_flare
#- hexagon
#- me


#----- projects -----


#CubeShooter
#KrampusReturns
#Mania
#CatDetective
#TrackLock
#LightracerMax
#LabyrinthOfLore
#TheWeepingHouse
#DragonWrath
#Krampus21 (FadeToWhite)
#Fullscore
#Golf
#Peri (?)
#Solitare (?)
#Epidemic (?)
#AllegroMembersClub (?)
#Releaser
#Slug3D (slug_3d)
#Dungeon
#Motris
#ChatGPT
#beebot
#AlexPark
#bearys_bash
#oatescodes
#tileo (x)


#install google test

       #git clone https://github.com/google/googletest;
       #cd googletest;
       #mkdir build;
       #cd build;
       #cmake ..;
       #make;
       #make install;
       #cd ..;
       #cd ..;

#install yaml-cpp

       #// TODO

#install allegro5

       #// TODO




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

# sync union
cd ../union
git pull

# make allegro_flare
cd ../blast
git pull
make clean && make programs -j8 && make && make clean && make programs -j8 && make

# make allegro_flare
cd ../allegro_flare
git pull
make clean && make

# make hexagon
cd ../hexagon
git pull
make clean && make


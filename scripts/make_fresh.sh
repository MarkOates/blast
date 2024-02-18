#!/bin/sh


#----- pre-core -----

#- allegro
#- yaml-cpp


# Note: yaml-cpp on MSYS
# git clone git@github.com:jbeder/yaml-cpp.git
# cd yaml-cpp
# mkdir build
# cd build
# cmake -G "MSYS Makefiles" ..
# make




#----- core -----


#- validate git credentials


#- dotfiles
#- union
#- blast
#- allegro_flare
#- hexagon
#- me

# For full list of projects that would require build, see:
# https://docs.google.com/spreadsheets/d/1aGJLjL2t0RKe0W4nwarA7WwtkUTn1KVzs-Vfw0iXvK8/edit#gid=0


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

#install rerun

       #// TODO

#install yaml-cpp

       #// TODO

#install allegro5

       #// TODO




#while true; do
    #read -p "For this script to run effectively, it's important that \"status\" has run clean. This is just a reminder. Do you wish to continue with the script? " yn
    #case $yn in
        #[Yy]* ) break;;
        #[Nn]* ) exit;;
        #* ) echo "Please answer yes or no.";;
    #esac
#done

REPOS_DIRECTORY=/Users/markoates/Repos

cd $REPOS_DIRECTORY

# sync dotfiles
cd $REPOS_DIRECTORY/.dotfiles
git pull
# source .zshrc

# sync me
cd $REPOS_DIRECTORY/me
git pull

# make blast
cd $REPOS_DIRECTORY/blast
git pull
make clean && make programs -j && make

# make allegro_flare
cd $REPOS_DIRECTORY/allegro_flare
git pull
make fast && make programs -j

# make hexagon
cd $REPOS_DIRECTORY/hexagon
git pull
make fast && make programs -j

# make SomePlatformer
cd $REPOS_DIRECTORY/SomePlatformer
git pull
make fast && make programs -j

# run status
/$REPOS_DIRECTORY/blast/bin/programs/status


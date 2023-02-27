#!/bin/sh


## TODO: guard this with check that you are actually on windows


## CRITICAL: validate an arg is present representing the download token

if [ $# -ne 1 ]; then
    echo ""
    echo "!! Error: Incorrect number of arguments provided. You must provide one."
    echo ""
    echo "Example:"
    echo ""
    echo "./scripts/build_win64_release.sh <expected-folder-name-inside-the-zip>"
    echo ""
    echo "Example 2:"
    echo ""
    echo "./scripts/build_win64_release.sh CubeShooter-SourceRelease-230226193517UTC"
    echo ""
    echo "NOTE: Releases can be found at https://storage.googleapis.com/clubcatt-games-bucket/"
    exit 1
fi



# TODO: ping -c 1 google.com

SOURCE_URL="https://storage.googleapis.com/clubcatt-games-bucket/$1.zip";
# SOURCE_URL="https://drive.google.com/uc?export=download&id=$SOURCE_TOKEN";
TEMP_BUILD_DIR="/c/Users/Mark/Desktop/temp_location_for_building/"
FOOBAR="$1.zip"
FOOBAR_WITHOUT_ZIP="$1"
SOURCE_FOLDER_NAME="$1"


# TODO: validate characters in $1


#"Krampus22_test1-SourceRelease-221209225033UTC.zip"
#"https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"


# Note a "share link":
# https://drive.google.com/file/d/1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N/view?usp=share_link
# ... converted into a direct download link:
# "https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"


# Create the necessary temp build folder if it does not exist

mkdir -p $TEMP_BUILD_DIR


# Download the source release

echo "===== Downloading $SOURCE_URL"
curl -L -o $TEMP_BUILD_DIR$FOOBAR $SOURCE_URL


# Go to the temp location, unzip the folder, and make

(cd $TEMP_BUILD_DIR || exit 1)

(cd $TEMP_BUILD_DIR && (unzip $FOOBAR || exit 1))


## TODO: CRITICAL: verify and validate that the expected folder exists in the zip file

(cd $TEMP_BUILD_DIR &&\
if [ -d $SOURCE_FOLDER_NAME ]
then
    echo "Directory $SOURCE_FOLDER_NAME exists."
else
    echo "Error: Directory $SOURCE_FOLDER_NAME does not exist in the unzipped file."
    exit 6
fi
) || exit 6

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && make)


# Cleanup the unnecessary folders / files

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf include/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf programs/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf src/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm Makefile)



#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro-5.2.dll ./allegro-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_acodec-5.2.dll ./allegro_acodec-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_audio-5.2.dll ./allegro_audio-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_color-5.2.dll ./allegro_color-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_dialog-5.2.dll ./allegro_dialog-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_font-5.2.dll ./allegro_font-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_image-5.2.dll ./allegro_image-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_primitives-5.2.dll ./allegro_primitives-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_ttf-5.2.dll ./allegro_ttf-5.2.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libgcc_s_seh-1.dll ./libgcc_s_seh-1.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libdumb.dll ./libdumb.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libFLAC-8.dll ./libFLAC-8.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopusfile-0.dll ./libopusfile-0.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libvorbisfile-3.dll ./libvorbisfile-3.dll)
#(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopenal-1.dll ./libopenal-1.dll)


# Copying necessary DLLs

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_acodec-5.2.dll  ./allegro_acodec-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_audio-5.2.dll   ./allegro_audio-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_color-5.2.dll   ./allegro_color-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_dialog-5.2.dll  ./allegro_dialog-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_font-5.2.dll    ./allegro_font-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_image-5.2.dll   ./allegro_image-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_main-5.2.dll    ./allegro_main-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_memfile-5.2.dll ./allegro_memfile-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_physfs-5.2.dll  ./allegro_physfs-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_primitives-5.2.dll ./allegro_primitives-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_ttf-5.2.dll     ./allegro_ttf-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro_video-5.2.dll   ./allegro_video-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/allegro-5.2.dll         ./allegro-5.2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libbz2-1.dll            ./libbz2-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libdumb.dll             ./libdumb.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libFLAC-8.dll           ./libFLAC-8.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libfreetype-6.dll       ./libfreetype-6.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libgcc_s_seh-1.dll      ./libgcc_s_seh-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libglib-2.0-0.dll       ./libglib-2.0-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libgraphite2.dll        ./libgraphite2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libharfbuzz-0.dll       ./libharfbuzz-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libhogweed-5.dll        ./libhogweed-5.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libiconv-2.dll          ./libiconv-2.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libintl-8.dll           ./libintl-8.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libjpeg-8.dll           ./libjpeg-8.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libogg-0.dll            ./libogg-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopenal-1.dll         ./libopenal-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopus-0.dll           ./libopus-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libopusfile-0.dll       ./libopusfile-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libpcre-1.dll           ./libpcre-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libpng16-16.dll         ./libpng16-16.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libstdc++-6.dll         ./libstdc++-6.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libtheora-0.dll         ./libtheora-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libvorbis-0.dll         ./libvorbis-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libvorbisfile-3.dll     ./libvorbisfile-3.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libwebp-7.dll           ./libwebp-7.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libwinpthread-1.dll     ./libwinpthread-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/zlib1.dll               ./zlib1.dll)

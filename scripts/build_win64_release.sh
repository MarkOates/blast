#!/bin/sh


## TODO: guard this with check that you are actually on windows

command -v zip >/dev/null 2>&1 || { echo >&2 "\"zip\" command not found. Aborting."; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo >&2 "\"unzip\" command not found. Aborting."; exit 1; }
command -v convert >/dev/null 2>&1 || { echo >&2 "\"convert\" command not found. Aborting."; exit 1; }
command -v windres >/dev/null 2>&1 || { echo >&2 "\"windres\" command not found. Aborting."; exit 1; }
# TODO: ping -c 1 google.com



# Note a "share link":
#"Krampus22_test1-SourceRelease-221209225033UTC.zip"
#"https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"

# https://drive.google.com/file/d/1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N/view?usp=share_link
# ... converted into a direct download link:
# "https://drive.google.com/uc?export=download&id=1NyqegdnLt8auGmsZfq9aeIBAbUmv-I6N"



## CRITICAL: validate an arg is present representing the download token

if [ $# -ne 2 ]; then
    echo ""
    echo "!! Error: Incorrect number of arguments provided. You must provide one."
    echo ""
    echo "Example:"
    echo ""
    #echo "    ./scripts/build_win64_release.sh <expected-folder-name-inside-the-zip> <version-number-string> <final-zip-name>"
    echo "    ./scripts/build_win64_release.sh <project-name> <version-number>"
    echo ""
    echo "Example 2:"
    echo ""
    #echo "    ./scripts/build_win64_release.sh CubeShooter-0.1.2-SourceRelease 0.1.2 CubeShooter-0.1.2-win64"
    echo "    ./scripts/build_win64_release.sh CubeShooter 0.1.2"
    echo "    ./scripts/build_win64_release.sh CubeShooter 0.1.2 2>&1 | tee build_terminal_output.txt"
    echo "    ./scripts/build_win64_release.sh CubeShooter 0.1.2 2>&1 | tee \"output_\$(date +'%I-%M-%p-%b-%d').txt\""
    echo ""
    echo ""
    echo "NOTE: Releases can be found at:"
    echo ""
    echo "https://storage.googleapis.com/clubcatt-games-bucket/"
    echo ""
    exit 2
fi


# Verify that the project name contains only letters and numbers
if [[ ! "$1" =~ ^[a-zA-Z0-9]+$ ]]; then
    echo ""
    echo "!! Error: Project name (first argument) contains invalid characters. Only letters and numbers are allowed."
    echo ""
    exit 3
fi

# Verify that the version number contains only numbers and dots
if [[ ! "$2" =~ ^[0-9]+(\.[0-9]+)*$ ]]; then
    echo ""
    echo "!! Error: Version number (second argument) contains invalid characters. Only numbers and dots are allowed."
    echo ""
    exit 4
fi


# Build




#SOURCE_URL="https://storage.googleapis.com/clubcatt-games-bucket/$1.zip";
# SOURCE_URL="https://drive.google.com/uc?export=download&id=$SOURCE_TOKEN";
# TEMP_BUILD_DIR="/c/Users/Mark/Desktop/temp_location_for_building/"
# TEMP_BUILD_DIR="/home/Mark/Releases/"
FINAL_RELEASES_DIR="/home/Mark/Releases/"
# ZIP_FILENAME="$1.zip"
# SOURCE_FOLDER_NAME="$1"
# FINAL_FOLDER_NAME="$3"


SOURCE_FOLDER_NAME="$1-$2-SourceRelease"
ZIP_FILENAME="$SOURCE_FOLDER_NAME.zip"
FINAL_FOLDER_NAME="$1-$2-win64"
SOURCE_URL="https://storage.googleapis.com/clubcatt-games-bucket/$SOURCE_FOLDER_NAME.zip";


TEMP_BUILD_DIR=$(mktemp -d -t $SOURCE_FOLDER_NAME-win64_build-XXXXXX)
@echo $TEMP_BUILD_DIR
if [ ! -d "$TEMP_BUILD_DIR" ]; then
  echo "Failed to create temporary directory"
  exit 1
fi

echo "Temporary directory created at \"$TEMP_BUILD_DIR\""



# Create the necessary temp build folder if it does not exist

# mkdir -p $TEMP_BUILD_DIR || exit 3


# Download the source release

echo "===== Downloading $SOURCE_URL"
curl -L -o $TEMP_BUILD_DIR/$ZIP_FILENAME $SOURCE_URL || exit 4


# Go to the temp location, unzip the folder, and make

cd $TEMP_BUILD_DIR || exit 1


## TODO: Validate unzip
(cd $TEMP_BUILD_DIR && (unzip $ZIP_FILENAME) || exit 2)


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



echo "Building the ico file - STARTING"

SOURCE_ICON_PNG=$(cd "$TEMP_BUILD_DIR" && cd "$SOURCE_FOLDER_NAME" && (~/Repos/blast/scripts/extract_key_from_app_info.sh app_icon_filename || exit 7))
FULL_PATH_TO_ICON_PNG=$TEMP_BUILD_DIR$SOURCE_FOLDER_NAME/$SOURCE_ICON_PNG

echo "SOURCE_ICON_PNG extracted: \"$SOURCE_ICON_PNG\""
echo "FULL_PATH_TO_ICON_PNG: \"$FULL_PATH_TO_ICON_PNG\""

if [ ! -f "$FULL_PATH_TO_ICON_PNG" ]; then
  echo "Error: File $FULL_PATH_TO_ICON_PNG not found."
  exit 3
fi

## TODO: Validate app.ico does not already exist before running this step
cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME
convert $SOURCE_ICON_PNG -resize 256x256 -define icon:auto-resize:256,128,96,64,48,32,16 app.ico || exit 8
echo "Building the executable - DONE"



cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME



echo "Building the resource file for the icon - STARTING"
echo "Building the resource file for the icon - making .rc file"
echo "1 ICON \"app.ico\"" > windows_app_icon_resource.rc || exit 9
echo "Building the resource file for the icon - compiling .rc file to .o"
windres windows_app_icon_resource.rc -O coff -o windows_app_icon_resource.o || exit 10
echo "Building the resource file for the icon - DONE"



echo "Building the executable - STARTING"
make legacy WINDOWS_APP_ICON_RESOURCE_OBJECT_FILE=windows_app_icon_resource.o || exit 11
echo "Building the executable - DONE"


# Cleanup the unnecessary folders / files

echo "Source folders cleared"


# Copying necessary DLLs
echo "Copying necessary DLLs - STARTING"

(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libFLAC.dll             ./libFLAC.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libbrotlidec.dll        ./libbrotlidec.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libpcre2-8-0.dll        ./libpcre2-8-0.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libbrotlicommon.dll     ./libbrotlicommon.dll)

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
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libtheoradec-1.dll      ./libtheoradec-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libvorbisfile-3.dll     ./libvorbisfile-3.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libwebp-7.dll           ./libwebp-7.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/libwinpthread-1.dll     ./libwinpthread-1.dll)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && cp /mingw64/bin/zlib1.dll               ./zlib1.dll)


echo "Copying necessary DLLs - DONE"


echo "Cleaning up - STARTING"
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf include/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf programs/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm -rdf src/)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm Makefile)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm app.info) # Note that this filename could change
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm app.ico)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm windows_app_icon_resource.rc)
(cd $TEMP_BUILD_DIR && cd $SOURCE_FOLDER_NAME && rm windows_app_icon_resource.o)
echo "Cleaning up - DONE"


# TODO: VALIDATE folder names doesn't already exist
echo "Renaming Folder - STARTING"
(cd $TEMP_BUILD_DIR && (mv $SOURCE_FOLDER_NAME $FINAL_FOLDER_NAME) || exit 12)
echo "Renaming Folder - DONE"


# TODO: VALIDATE Final zip doesn't already exist
echo "Compressing ZIP - STARTING"
(cd $TEMP_BUILD_DIR && (zip -r $FINAL_FOLDER_NAME.zip $FINAL_FOLDER_NAME) || exit 13)
echo "Compressing ZIP - DONE"



echo "WIN64 Build successful!"



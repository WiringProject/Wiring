#!/bin/sh

#REVISION=`head -c 4 ../../todo.txt`
REVISION=`head -1 ../../todo.txt | awk '{print $1}'`

if [ $1 ]
then
  RELEASE=$1
  echo Creating Wiring release $RELEASE...
else 
  RELEASE=$REVISION
  echo Creating Wiring distribution for revision $REVISION...
fi

ARCH="i686"
#`uname -m`
if [ $ARCH != "i686" ]
then
  echo At present, the Linux distribution can only be built on i686 \(32-bit\).
  exit
fi

# remove any old boogers
rm -rf wiring
rm -rf wiring*
rm -rf wiring-*
rm -rf work

./make/sh 

mkdir wiring
cp -r ../shared/lib wiring/
#cp -r ../shared/libraries wiring/
cp -r ../shared/tools wiring/
cp ../../IDE/app/lib/antlr.jar wiring/lib/
cp ../../IDE/app/lib/ecj.jar wiring/lib/
cp ../../IDE/app/lib/jna.jar wiring/lib/
cp -r ../../IDE/app/lib/serial wiring/lib/

cp ../shared/revisions.txt wiring/

if [ $1 ]
then
  # write the release version number into the output directory
  echo $1 > wiring/lib/version.txt
fi

echo Extracting examples...
unzip -q -d wiring/ ../shared/examples.zip

echo Extracting reference...
unzip -q -d wiring/ ../shared/reference.zip

# add the libraries folder with source
#cp -r ../../net processing/libraries/
#cp -r ../../opengl processing/libraries/
#cp -r ../../serial processing/libraries/
#cp -r ../../pdf processing/libraries/
#cp -r ../../dxf processing/libraries/

# add java (jre) files
tar --extract --file=jre.tgz --ungzip --directory=wiring

echo Extracting AVR Tools...
cp dist/tools-avr.tar.gz wiring/
cd wiring
gzip -d tools-avr.tar.gz
tar xf tools-avr.tar
rm tools-avr.tar
cd ..

# grab pde.jar and export from the working dir
cp work/lib/pde.jar wiring/lib/
cp work/lib/core.jar wiring/lib/
#cp work/lib/*.o wiring/lib/
#cp work/lib/*.h wiring/lib/
#cp work/lib/*.cpp wiring/lib
#cp work/lib/*.c wiring/lib

cp -r work/cores wiring/
cp -r work/hardware wiring/
cp -r work/libraries wiring/
cp work/lib/serial/librxtxSerial.so wiring/java/lib/i386/

# get platform-specific goodies from the dist dir
install -m 755 dist/wiring wiring/wiring

# make sure notes.txt is unix LFs
# the 2> is because the app is a little chatty
dos2unix wiring/revisions.txt 2> /dev/null
dos2unix wiring/lib/preferences.txt 2> /dev/null

# remove boogers
find wiring -name "*~" -exec rm -f {} ';'
find wiring -name ".DS_Store" -exec rm -f {} ';'
find wiring -name "._*" -exec rm -f {} ';'
find wiring -name "Thumbs.db" -exec rm -f {} ';'

# clean out the cvs entries
find wiring -name "CVS" -exec rm -rf {} ';' 2> /dev/null
find wiring -name ".cvsignore" -exec rm -rf {} ';'
find wiring -name ".svn" -exec rm -rf {} 2> /dev/null ';'

# zip it all up for release
echo Creating tarball and finishing...
P5=wiring-$RELEASE
mv wiring $P5

tar cfz $P5.tgz $P5
# nah, keep the new directory around
#rm -rf $P5

echo Done.

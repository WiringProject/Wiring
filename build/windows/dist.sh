#!/bin/sh

REVISION=`head -1 ../../todo.txt | awk '{print $1}'`

if [ $1 ]
then
RELEASE=$1
echo Creating Wiring release $RELEASE...
else 
RELEASE=$REVISION
echo Creating Wiring distribution for revision $REVISION...
fi

# check to see if the version number in the app is correct
# so that mikkel doesn't kick my ass
VERSIONED=`cat ../../IDE/app/src/processing/app/Base.java | grep $REVISION`
if [ -z "$VERSIONED" ]
then
echo Fix the revision number in Base.java
exit
fi

./make.sh

# remove any old boogers
rm -rf wiring
rm -rf wiring-*

mkdir wiring
cp -r ../shared/lib wiring/
#cp -r ../shared/libraries wiring/
cp -r ../shared/tools wiring/

if [ $1 ]
then
# write the release version number into the output directory
echo $1 > wiring/lib/version.txt
fi

cp ../../IDE/app/lib/antlr.jar wiring/lib/
cp ../../IDE/app/lib/ecj.jar wiring/lib/
cp ../../IDE/app/lib/jna.jar wiring/lib/
cp -r ../../IDE/app/lib/serial wiring/lib/

cp ../shared/revisions.txt wiring/

echo Extracting examples...
unzip -q -d wiring/ ../shared/examples.zip

echo Extracting reference...
unzip -q -d wiring/ ../shared/reference.zip

# add the libraries folder with source
#cp -r ../../net processing/libraries/
#cp -r ../../opengl processing/libraries/
#cp -r ../../serial processing/libraries/
#cp -r ../../video processing/libraries/
#cp -r ../../pdf processing/libraries/
#cp -r ../../dxf processing/libraries/

# add java (jre) files
unzip -q -d wiring jre.zip

# get platform-specific goodies from the dist dir
cp launcher/wiring.exe wiring/
cp ../../IDE/app/lib/serial/rxtxSerial.dll wiring/
cp /bin/cygwin1.dll wiring/
cp /bin/cygiconv-2.dll wiring/
cp /bin/cygz.dll wiring/
cp /bin/cyggcc_s-1.dll wiring/

echo copying drivers to distribution dir...
cp -rp dist/drivers wiring/

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

cp -r work/hardware wiring/
cp -r work/cores wiring/ 
cp -r work/libraries wiring/

# convert revisions.txt to windows LFs
# the 2> is because the app is a little chatty
unix2dos wiring/revisions.txt 2> /dev/null
unix2dos wiring/lib/preferences.txt 2> /dev/null
unix2dos wiring/lib/keywords.txt 2> /dev/null

# remove boogers
find wiring -name "*.bak" -exec rm -f {} ';'
find wiring -name "*~" -exec rm -f {} ';'
find wiring -name ".DS_Store" -exec rm -f {} ';'
find wiring -name "._*" -exec rm -f {} ';'
find wiring -name "Thumbs.db" -exec rm -f {} ';'

# chmod +x the crew
find wiring -name "*.html" -exec chmod +x {} ';'
find wiring -name "*.dll" -exec chmod +x {} ';'
find wiring -name "*.exe" -exec chmod +x {} ';'
find wiring -name "*.html" -exec chmod +x {} ';'

# clean out the cvs entries
find wiring -name "CVS" -exec rm -rf {} ';' 2> /dev/null
find wiring -name ".cvsignore" -exec rm -rf {} ';'
find wiring -name ".svn" -exec rm -rf {} ';' 2> /dev/null

# zip it all up for release
echo Packaging standard release...
echo
P5=wiring-$RELEASE
mv wiring $P5
zip -rq $P5.zip $P5
# nah, keep the new directory around
#rm -rf $P5

# zip up another for experts
#echo Expert release is disabled until further notice.
echo Packaging expert release...
echo
cp -a $P5 $P5-expert
# remove enormous java runtime
rm -rf $P5-expert/java
zip -rq $P5-expert.zip $P5-expert

echo Done.


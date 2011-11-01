#!/bin/sh


### -- SETUP WORK DIR -------------------------------------------

RESOURCES=`pwd`/work/Wiring.app/Contents/Resources/Java
#echo $RESOURCES
#exit

if test -d work
then
  BUILD_PREPROC=false
else
  echo Setting up directories to build under Mac OS X
  BUILD_PREPROC=true

  mkdir work

  # to have a copy of this guy around for messing with
  echo Copying Wiring.app...
  #cp -a dist/Processing.app work/   # #@$(* bsd switches
  #/sw/bin/cp -a dist/Processing.app work/
  cp -pRX dist/Wiring.app work/
  # cvs doesn't seem to want to honor the +x bit 
  chmod +x work/Wiring.app/Contents/MacOS/JavaApplicationStub

#  cp -rX ../shared/hardware "$RESOURCES/"
  cp -rX ../shared/lib "$RESOURCES/"
#  cp -rX ../shared/libraries "$RESOURCES/"
  cp -rX ../shared/tools "$RESOURCES/"

  cp -X ../../IDE/app/lib/antlr.jar "$RESOURCES/"
  cp -X ../../IDE/app/lib/ecj.jar "$RESOURCES/"
  cp -X ../../IDE/app/lib/jna.jar "$RESOURCES/"
  cp -X ../../IDE/app/lib/serial/* "$RESOURCES/"


  echo Extracting examples...
  unzip -q -d "$RESOURCES/" ../shared/examples.zip

  echo Extracting reference...
  unzip -q -d "$RESOURCES/" ../shared/reference.zip

  LIBRARIES=$RESOURCES/libraries/
#  cp -rX ../../lib "$LIBRARIES"

#  cp -rX ../../net "$LIBRARIES"
#  cp -rX ../../opengl "$LIBRARIES"
#  cp -rX ../../serial "$LIBRARIES"
#  cp -rX ../../video "$LIBRARIES"
#  cp -rX ../../pdf "$LIBRARIES"
#  cp -rX ../../dxf "$LIBRARIES"

  echo Extracting AVR Tools...
  tar -xzf dist/tools-avr.tar.gz -C $RESOURCES
#  cp dist/tools-avr.tar.gz work/
#  cd work
#  gzip -d tools-avr.tar.gz
#  tar xf tools-avr.tar
#  rm tools-avr.tar
#  cd ..
   
fi


### -- START BUILDING -------------------------------------------
echo Updating firmware files...
#LIBRARIES=$RESOURCES/libraries/
#rm -rf "$LIBRARIES"
#cp -rX ../../lib "$LIBRARIES"

# move to root 'wiring' directory
cd ../..

### -- BUILD CORE ---------------------------------------------

echo Copying wiring.core...
FIRMWARE=$RESOURCES/firmware/
rm -rf $RESOURCES/cores
rm -rf $RESOURCES/hardware
rm -rf $RESOURCES/libraries
cp -rX firmware/cores "$RESOURCES"
cp -rX firmware/hardware "$RESOURCES"
cp -rX firmware/libraries "$RESOURCES"

#export PATH=$RESOURCES/tools/avr/bin:$PATH
#rm -rf *.o
#make MCU=atmega128
#make clean
#make MCU=atmega1281
#make clean
#make MCU=atmega2561
#make clean

#cp *.h "$RESOURCES/hardware/Wiring/WiringMega"
#cp *.cpp "$RESOURCES/hardware/Wiring/WiringMega"
#cp *.c "$RESOURCES/hardware/Wiring/WiringMega"
#cp makefile "$RESOURCES/hardware/Wiring/WiringMega"

echo Building processing.core...

cd IDE/core

#CLASSPATH=/System/Library/Frameworks/JavaVM.framework/Classes/classes.jar:/System/Library/Frameworks/JavaVM.framework/Classes/ui.jar:/System/Library/Java/Extensions/QTJava.zip
#export CLASSPATH

perl preproc.pl

mkdir -p bin
javac -source 1.5 -target 1.5 -d bin \
  src/processing/core/*.java \
  src/processing/xml/*.java

rm -f "$RESOURCES/core.jar"

cd bin && \
  zip -rq "$RESOURCES/core.jar" \
  processing/core/*.class \
  processing/xml/*.class \
  && cd ..

# head back to "processing/app"
#cd ../app
cd ../../


### -- BUILD PARSER ---------------------------------------------

#BUILD_PREPROC=true

if $BUILD_PREPROC
then
  # build classes/grammar for preprocessor
pwd
  cd IDE/app/src/processing/app/preproc

  # first build the default java goop
  java \
    -cp "$RESOURCES/antlr.jar" antlr.Tool StdCParser.g

  # now build the pde stuff that extends the java classes
  java \
    -cp "$RESOURCES/antlr.jar" antlr.Tool \
    -glib StdCParser.g WParser.g

  java \
    -cp "$RESOURCES/antlr.jar" antlr.Tool WTreeParser.g

  java \
    -cp "$RESOURCES/antlr.jar" antlr.Tool \
    -glib WTreeParser.g WEmitter.g


# back to base processing dir
cd ../../../../../../

fi
pwd
### -- BUILD PDE ------------------------------------------------
cd IDE/app
echo Building the PDE...

# For some reason, javac really wants this folder to exist beforehand.
rm -rf ../../build/macosx/work/classes
mkdir ../../build/macosx/work/classes
# Intentionally keeping this separate from the 'bin' folder
# used by eclipse so that they don't cause conflicts.

javac \
    -Xlint:deprecation \
    -source 1.5 -target 1.5 \
    -classpath "$RESOURCES/core.jar:$RESOURCES/antlr.jar:$RESOURCES/ecj.jar:$RESOURCES/jna.jar":$RESOURCES/RXTXcomm.jar \
    -d ../../build/macosx/work/classes \
    src/processing/app/*.java \
    src/processing/app/debug/*.java \
    src/processing/app/exec/*.java \
    src/processing/app/format/*.java \
    src/processing/app/macosx/*.java \
    src/processing/app/preproc/*.java \
    src/processing/app/syntax/im/*.java \
    src/processing/app/syntax/*.java \
    src/processing/app/tools/*.java \
#    src/antlr/*.java \
#    src/antlr/java/*.java 

cd ../../build/macosx/work/classes
rm -f "$RESOURCES/pde.jar"
zip -0rq "$RESOURCES/pde.jar" .
cd ../..

# get updated core.jar and pde.jar; also antlr.jar and others
#mkdir -p work/Processing.app/Contents/Resources/Java/
#cp work/lib/*.jar work/Processing.app/Contents/Resources/Java/


### -- BUILD LIBRARIES ------------------------------------------------

PLATFORM=macosx


CLASSPATH=$RESOURCES/core.jar
JAVAC="javac -source 1.5 -target 1.5"
LIBRARIES=$RESOURCES/libraries
#pwd
# move to processing/build 
cd ..


# SERIAL LIBRARY
#echo Building serial library...
#cd ../serial
#mkdir -p bin
#$JAVAC \
#    -classpath "library/RXTXcomm.jar:$CLASSPATH" \
#    -d bin src/processing/serial/*.java 
#rm -f library/serial.jar
##find bin -name "*~" -exec rm -f {} ';'
#cd bin && zip -rq ../library/serial.jar processing/serial/*.class && cd ..
#mkdir -p "$LIBRARIES/serial/library/"
#cp library/serial.jar "$LIBRARIES/serial/library/"



echo
echo Done.

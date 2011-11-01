#!/bin/sh


### -- SETUP WORK DIR -------------------------------------------

if test -d work
then
  BUILD_PREPROC=false
else
  echo Setting up directories to build for Linux...
  BUILD_PREPROC=true

  mkdir work
  cp -r ../shared/lib work/
#  cp -r ../shared/libraries work/
  cp -r ../shared/tools work/
#  cp -r ../shared/hardware work/

  cp ../../IDE/app/lib/antlr.jar work/lib/
  cp ../../IDE/app/lib/ecj.jar work/lib/
  cp ../../IDE/app/lib/jna.jar work/lib/
  cp -r ../../IDE/app/lib/serial work/lib/

  echo Extracting examples...
  unzip -q -d work/ ../shared/examples.zip

  echo Extracting reference...
  unzip -q -d work/ ../shared/reference.zip

# This line is really needed?
#  cp -r ../../lib work/libraries/

#  cp -r ../../net work/libraries/
#  cp -r ../../opengl work/libraries/
#  cp -r ../../serial work/libraries/
#  cp -r ../../video work/libraries/
#  cp -r ../../pdf work/libraries/
#  cp -r ../../dxf work/libraries/

  install -m 755 dist/wiring work/wiring

  ARCH="i686"
#`uname -m`
  if [ $ARCH = "i686" ]
  then
    echo Extracting JRE...
    tar --extract --file=jre.tgz --ungzip --directory=work
    cp work/lib/serial/librxtxSerial.so work/java/lib/i386/
    echo Extracting AVR Tools...
    cp dist/tools-avr.tar.gz work/
    cd work
    gzip -d tools-avr.tar.gz
    tar xf tools-avr.tar
    rm tools-avr.tar
    cd ..
  else 
#    echo This is not my beautiful house.
#    if [ $ARCH = "x86_64" ]
#    then 
#      echo You gots the 64.
#    fi
    echo "
The Java bundle that is included with Processing supports only i686 by default.
To build the code, you will need to install the Java 1.5.0_15 JDK (not a JRE,
and not any other version), and create a symlink to the directory where it is
installed. Create the symlink in the \"work\" directory, and named it \"java\":
ln -s /path/to/jdk1.5.0_15 `pwd`/work/java"
    exit
  fi
fi


### -- START BUILDING -------------------------------------------
echo Updating firmware files...
#echo Updating libraries...
#rm -rf work/libraries/
#cp -r ../../lib work/libraries/

echo ------------- Path -----------------------
echo `pwd`
cd ../..
echo `pwd`


### -- BUILD CORE ----------------------------------------------


echo Copying wiring.core...
rm -rf build/linux/work/cores
rm -rf build/linux/work/hardware
rm -rf build/linux/work/libraries
cp -rx firmware/cores build/linux/work/
cp -rx firmware/hardware build/linux/work/
cp -rx firmware/libraries build/linux/work/

#cd core

#CLASSPATH="../build/linux/work/java/lib/rt.jar"
#export CLASSPATH

#export PATH=../build/linux/work/tools/avr/bin:$PATH
#rm -rf *.o
#make MCU=atmega128
#make clean
#make MCU=atmega1281
#make clean
#make MCU=atmega2561
#make clean

#cp *.h ../build/linux/work/hardware/Wiring/WiringMega
#cp *.cpp ../build/linux/work/hardware/Wiring/WiringMega
#cp *.c ../build/linux/work/hardware/Wiring/WiringMega
#cp makefile ../build/linux/work/hardware/Wiring/WiringMega


echo Building processing.core...
cd IDE/core

perl preproc.pl
mkdir -p bin
../../build/linux/work/java/bin/java \
    -cp ../../build/linux/work/java/lib/tools.jar \
    com.sun.tools.javac.Main \
    -d bin -source 1.5 -target 1.5 \
    src/processing/core/*.java src/processing/xml/*.java
#find bin -name "*~" -exec rm -f {} ';'
# remove old core
rm -f ../../build/linux/work/lib/core.jar
cd bin && zip -rq ../../../build/linux/work/lib/core.jar \
  processing/core/*.class processing/xml/*.class && cd ..

# back to base processing dir
cd ../../

echo ----------- path ------------------
echo `pwd`

### -- BUILD PREPROC ------------------------------------------------

echo Building PDE for JDK 1.5...

#cd app

# long path is to avoid requiring java to be in your PATH
  echo Building antlr grammar code...

cd IDE/app/src/processing/app/preproc

# first build the default java goop
../../../../../../build/linux/work/java/bin/java \
    -cp ../../../../../../build/linux/work/lib/antlr.jar antlr.Tool StdCParser.g

# now build the pde stuff that extends the java classes
../../../../../../build/linux/work/java/bin/java \
    -cp ../../../../../../build/linux/work/lib/antlr.jar antlr.Tool \
    -glib StdCParser.g WParser.g

../../../../../../build/linux/work/java/bin/java \
    -cp ../../../../../../build/linux/work/lib/antlr.jar antlr.Tool WTreeParser.g

../../../../../../build/linux/work/java/bin/java \
    -cp ../../../../../../build/linux/work/lib/antlr.jar antlr.Tool \
    -glib WTreeParser.g WEmitter.g


# back to base processing dir
cd ../../../../../../


### -- BUILD PDE ------------------------------------------------

cd IDE/app
echo Building the PDE...

rm -rf ../../build/linux/work/classes
mkdir ../../build/linux/work/classes

../../build/linux/work/java/bin/java \
    -cp ../../build/linux/work/java/lib/tools.jar \
    com.sun.tools.javac.Main \
    -source 1.5 -target 1.5 \
    -classpath ../../build/linux/work/lib/core.jar:../../build/linux/work/lib/antlr.jar:../../build/linux/work/lib/ecj.jar:../../build/linux/work/lib/jna.jar:../../build/linux/work/java/lib/tools.jar:../../build/linux/work/lib/serial/RXTXcomm.jar \
    -d ../../build/linux/work/classes \
    src/processing/app/*.java \
    src/processing/app/debug/*.java \
    src/processing/app/exec/*.java \
    src/processing/app/format/*.java \
    src/processing/app/linux/*.java \
    src/processing/app/preproc/*.java \
    src/processing/app/syntax/im/*.java \
    src/processing/app/syntax/*.java \
    src/processing/app/tools/*.java \
#    src/antlr/*.java \
#    src/antlr/java/*.java 

cd ../../build/linux/work/classes
rm -f ../lib/pde.jar
zip -0rq ../lib/pde.jar .
cd ../../../../


### -- BUILD LIBRARIES ------------------------------------------------


echo
echo Done.

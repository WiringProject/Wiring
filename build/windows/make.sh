#!/bin/sh

########################################
# Notes:
#
# ./make.sh [clean|all|processing|pde|firmware]
#
# clean - remove work folder
# all - creates work folder (if it doesn't already exist),
#       builds Processing IDE,
#       builds pde.jar,
#       and copies firmware components
# processing - builds Processing IDE
# pde - builds pde.jar
# examples - extracts example sketch archive to work folder
# reference - extracts help/reference archive to work folder
# firmware - copies firmware components to work folder
#
# If the work folder doesn't exist, it will automatically be created.
# All essential components will be copied into the work folder before
# any command will be undertaken.
#
# (if "debug" - without quotes - is provided as a second parameter,
# each stage will be followed by a keyboard entry pause)
#
# (NOTE: launch4j needs to have a tmpdir set - but for the life of me, I
# can't figure out where to set the property.  So my solution was to
# just remove the "USERPROFILE" environment variable - not certain where
# launch4j creates temp files now, but at least it works.)
#
# http://launch4j.sourceforge.net/docs.html
#
# More notes on Windows ugliness:
# all expansions have been assuming the source folder is not within
# a folder which has spaces in its name.  This will require escaping all
# folders with quotes.

# **** start of lack-of-launch4j-understanding yuckiness ****
#unset USERPROFILE
# **** end of lack-of-launch4j-understanding yuckiness ****

if [ -n "$2" -a "$2" = "debug" ]
then
  DEBUG=true
  echo "Debugging on."
else
  DEBUG=false
fi

function debug_pause() {
  if $DEBUG
  then
    read -p "Press Enter to continue"
  fi
}


MAKETYPE=$1

PLATFORM=windows
BUILD_PREPROC=false

PLATFORM_FOLDER=`pwd`
WORK_FOLDER=$PLATFORM_FOLDER/work
JAVA=$WORK_FOLDER/java/bin/java
RESOURCES=$WORK_FOLDER/lib

WIRING_BASE=`pwd`/../..
BUILD_FOLDER=$WIRING_BASE/build
# PLATFORM_FOLDER=$WIRING_BASE/build/$PLATFORM
IDE_FOLDER=$WIRING_BASE/IDE
FIRMWARE_FOLDER=$WIRING_BASE/firmware


if [ ! -e make.sh ]
then
  echo
  echo "You must be in the $PLATFORM build folder before starting make.sh."
  echo
  echo "e.g."
  echo "  cd /wiring/build/$PLATFORM"
  echo "  ./make.sh"
  exit
fi

debug_pause

if [ -z $MAKETYPE ]
then
  MAKETYPE=all
fi

if [ $MAKETYPE = clean ]
then
  if [ -d work ]
  then
    echo "Removing work folder..."
    rm -rf work
    echo "Done."
  else
    echo "Nothing to do."
  fi
  
  exit
fi

echo "Making $MAKETYPE"


### Setup Work folder, if it doesn't exist

if [ ! -d work ]
then
  echo "Setting up directories to build Wiring..."
  BUILD_PREPROC=true

  mkdir work
  echo "Copying shared tools/lib..."
  cp -r $BUILD_FOLDER/shared/lib work/
  cp -r $BUILD_FOLDER/shared/tools work/
  # cp -r $BUILD_FOLDER/shared/hardware work/

  echo "Copying app components..."
  cp $IDE_FOLDER/app/lib/antlr.jar work/lib/
  cp $IDE_FOLDER/app/lib/ecj.jar work/lib/
  cp $IDE_FOLDER/app/lib/jna.jar work/lib/
  cp -r $IDE_FOLDER/app/lib/serial work/lib/
  cp $IDE_FOLDER/app/lib/serial/rxtxSerial.dll work/

  echo "Extracting enormous JRE..."
  unzip -q -d work jre.zip

  # build the export launcher
  echo "Building launcher..."
  cd export
  make
  cd ..

  # build the processing.exe bundle
  # there are a few hacks in the source to launch4j-3.0.1
  # to build them, use the following:
  # cd head_src/gui_head && make -f Makefile.win
  cd launcher
  ./launch4j/launch4jc.exe config.xml
  cp wiring.exe ../work/
  cd ..

  echo "Copying Cygwin libraries..."
  cp /bin/cygwin1.dll work/
  cp /bin/cygiconv-2.dll work/
  cp /bin/cygz.dll work/
  cp /bin/cyggcc_s-1.dll work/
  chmod +x work/cygwin1.dll
  chmod +x work/cygiconv-2.dll
  chmod +x work/cygz.dll
  chmod +x work/cyggcc_s-1.dll

  echo "Extracting AVR 8 Bit tools..."
  tar -C work -zxf $PLATFORM_FOLDER/dist/tools-avr.tar.gz

  # chmod +x the crew
  # cygwin requires this because of unknown weirdness
  # it was not formerly this anal retentive
  # with the html, it's necessary on windows for launching reference 
  # from shell/command prompt, which is done internally to view reference
  echo "Windows/Cygwin chmod..."
  find work -name "*.html" -exec chmod +x {} ';'
  find work -name "*.dll" -exec chmod +x {} ';'
  find work -name "*.exe" -exec chmod +x {} ';'
  find work -name "*.html" -exec chmod +x {} ';'

  echo "Done setting up work folder."
  debug_pause
fi
### -- END Work folder setup


### -- BUILD processing.core
if [ $MAKETYPE = processing ] || [ $MAKETYPE = all ]
then
  echo "Building Processing core..."

  cd $IDE_FOLDER/core

#CLASSPATH="..\\build\\windows\\work\\java\\lib\\rt.jar;..\\build\\windows\\work\\java\\lib\\tools.jar"
#CLASSPATH="..\\build\\windows\\work\\java\\lib\\tools.jar"
#export CLASSPATH

  perl preproc.pl

  mkdir -p bin
  $JAVA \
      -classpath "..\\..\\build\\windows\\work\\java\\lib\\tools.jar" \
      com.sun.tools.javac.Main \
      -source 1.5 -target 1.5 -d bin \
      src/processing/core/*.java src/processing/xml/*.java

  #rm -f ../../build/windows/work/lib/core.jar
  rm -f $RESOURCES/core.jar

  # package this folder into core.jar
  cd bin
#  zip -rq ../../../build/windows/work/lib/core.jar \
#      processing/core/*.class processing/xml/*.class
  zip -rq $RESOURCES/core.jar \
      processing/core/*.class processing/xml/*.class

#  cd ..

  # back to base processing dir
#  cd ../../build/windows

  cd $PLATFORM_FOLDER

  echo "Done building Processing core."
  debug_pause
fi
### -- END core.processing BUILD


### -- BUILD PREPROC
if $BUILD_PREPROC
then
  #echo "Building PDE for JDK 1.5"
  echo "Pre-building PDE components..."

  cd $IDE_FOLDER/app/src/processing/app/preproc

  # first build the default java goop
  $JAVA \
      -cp "..\\..\\..\\..\\..\\..\\build\\windows\\work\\lib\\antlr.jar" antlr.Tool StdCParser.g

  # now build the pde stuff that extends the java classes
  $JAVA \
      -cp "..\\..\\..\\..\\..\\..\\build\\windows\\work\\lib\\antlr.jar" antlr.Tool \
      -glib StdCParser.g WParser.g

  $JAVA \
      -cp "..\\..\\..\\..\\..\\..\\build\\windows\\work\\lib\\antlr.jar" antlr.Tool WTreeParser.g

  $JAVA \
      -cp "..\\..\\..\\..\\..\\..\\build\\windows\\work\\lib\\antlr.jar" antlr.Tool \
      -glib WTreeParser.g WEmitter.g


  # back to base processing dir
  # cd ../../../../../../build/windows
  cd $PLATFORM_FOLDER

  echo "Done pre-building PDE components."
  debug_pause
fi
### -- END PREPROC BUILD


### -- BUILD PDE ------------------------------------------------

if [ $MAKETYPE = pde ] || [ $MAKETYPE = all ]
then
  echo "Building PDE jar..."

  cd $IDE_FOLDER/app

  # has to be present, otherwise javac will complain of file writing errors
  #rm -rf ../../build/windows/work/classes
  rm -rf $WORK_FOLDER/classes
  #mkdir ../../build/windows/work/classes
  mkdir $WORK_FOLDER/classes

  $JAVA \
      -classpath "..\\..\\build\\windows\\work\\java\\lib\\tools.jar" \
      com.sun.tools.javac.Main \
      -source 1.5 -target 1.5 \
      -classpath "..\\..\\build\\windows\\work\\lib\\core.jar;..\\..\\build\\windows\\work\\lib\antlr.jar;..\\..\\build\\windows\\work\\lib\\ecj.jar;..\\..\\build\\windows\\work\\lib\\jna.jar;..\\..\\build\\windows\\work\\java\\lib\\tools.jar;..\\..\\build\\windows\\work\\lib\\serial\\RXTXcomm.jar" \
      -d ..\\..\\build\\windows\\work\\classes \
      src/processing/app/*.java \
      src/processing/app/debug/*.java \
      src/processing/app/exec/*.java \
      src/processing/app/format/*.java \
      src/processing/app/syntax/im/*.java \
      src/processing/app/syntax/*.java \
      src/processing/app/preproc/*.java \
      src/processing/app/tools/*.java \
      src/processing/app/windows/*.java 
#      src/antlr/*.java \
#      src/antlr/java/*.java 

  #cd ../../build/windows/work/classes
  #rm -f ../lib/pde.jar
  #zip -rq ../lib/pde.jar .
  rm -f $RESOURCES/pde.jar
  cd $WORK_FOLDER/classes
  zip -rq $RESOURCES/pde.jar .

  # back to base processing dir
  #cd ../..
  
  cd $PLATFORM_FOLDER

  echo "Done building PDE jar."
  debug_pause
fi

if [ $MAKETYPE = examples ] || [ $MAKETYPE = all ]
then
  echo "Removing old examples..."
  rm -rf $WORK_FOLDER/examples
  echo "Extracting examples..."
  unzip -q -d work/ $BUILD_FOLDER/shared/examples.zip
fi

if [ $MAKETYPE = reference ] || [ $MAKETYPE = all ]
then
  echo "Removing old reference..."
  rm -rf $WORK_FOLDER/reference
  echo "Extracting reference..."
  unzip -q -d work/ $BUILD_FOLDER/shared/reference.zip
fi

### -- COPY firmware components
if [ $MAKETYPE = firmware ] || [ $MAKETYPE = all ]
then
  echo "Updating firmware components..."
  echo "removing old cores..."
  rm -rf $WORK_FOLDER/cores
  echo "removing old hardware..."
  rm -rf $WORK_FOLDER/hardware
  echo "removing old libraries..."
  rm -rf $WORK_FOLDER/libraries
  echo "copying new cores..."
  cp -r $FIRMWARE_FOLDER/cores $WORK_FOLDER
  echo "copying new hardware..."
  cp -r $FIRMWARE_FOLDER/hardware $WORK_FOLDER
  echo "copying new libraries..."
  cp -r $FIRMWARE_FOLDER/libraries $WORK_FOLDER

  echo "Done updating firmware components."
fi
### -- END COPY firmware components

echo
echo "All Done."

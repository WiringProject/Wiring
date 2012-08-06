HOW TO BUILD WIRING ON YOUR FAVORITE PLATFORM

These instructions apply to the Wiring distribution available on
GitHub. If you're trying to build an older version of Wiring (obtained
from e.g. Subversion), you'll need to use the instructions from that
older version instead.


////////////////////////////////////////////////////////////////////

//// Steps for First Time Setup 


1. INSTALL DEVELOPMENT TOOLS

At a minimum, you will need the following things to build Wiring:

+ A Java Development Kit (JDK). Any Oracle JDK compatible with Java
  1.5+ should work. (We make use of some com.sun.* APIs that may
  render other JDKs inoperable).

+ Apache Ant. Last we checked, OS X includes this by default with its
  JDK install. Linux users will likely find Ant in their
  distribution's package manager. Windows users can download and
  install Ant from its Apache page:

      http://ant.apache.org/

Depending on your platform, you will also need some other stuff:

1a. Windows:

    - Launch4j: You need this to build wiring.exe. After you download and
      install it, make sure that launch4jc.exe is on your PATH.

      http://launch4j.sourceforge.net/

1b. Mac OS X

    - Apple's developer tools (XCode).

1c. On Linux:

    - tar: We test with GNU tar. This is almost certainly already
      installed on your system.

2. GRAB THE CODE FROM GITHUB

That means you'll also need Git. If you're reading this, you've
probably already got that ;). If you don't, the following GitHub guide
should help you install Git:

      http://help.github.com/set-up-git-redirect

Once that's installed, get the code with:

     $ git clone git://github.com/WiringProject/Wiring.git

3. BUILD IT

From the top-level Wiring directory, run

    $ ant

To build the Wiring IDE.

The first time you run this, Ant will automatically download and
extract bunch of other things you need, so it may take a while. After
the first time, though, builds will go much faster.


////////////////////////////////////////////////////////////////////

//// Updating to the Latest Version


4a. Each time you want to update to latest version, run

    $ git pull

    From within the Wiring directory (you may also use a Git GUI to do
    this, but that depends on your platform).

4b. If you're getting strange errors when you try to build, especially
    if significant changes have been made to the Wiring repository,
    you can clean up with:

    $ ant clean

    If you want to nuke _everything_ (compiled IDE, downloaded
    dependencies, etc.), then use:

    $ ant clean.all

    Be aware, though, that using clean.all means your next build will
    require an internet connection, as Wiring's dependencies will have
    to be re-downloaded.


////////////////////////////////////////////////////////////////////

//// The Frequently Asked Question

- What about Eclipse? Command line sucks.

  The command line stuff isn't as scary as it might initially
  seem. Hopefully it's just a matter of following the instructions
  above (and being patient).

  However, there are plenty of GUIs out there for Git etc., and
  Eclipse has good Ant integration. Wiring should build using Ant
  within Eclipse, and we're moving development over to it. However,
  we're not documenting it until the dust has settled, so for now,
  you're on your own.


////////////////////////////////////////////////////////////////////


Original author: Hernando Barragan
Current build system maintainer: Marti Bolivar <mbolivar@leaflabs.com>

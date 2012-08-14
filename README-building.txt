HOW TO BUILD WIRING ON YOUR FAVORITE PLATFORM

These instructions apply to the Wiring distribution available on
GitHub:

    https://github.com/WiringProject/Wiring


////////////////////////////////////////////////////////////////////

//// Steps for First Time Setup


1. INSTALL DEVELOPMENT TOOLS

At a minimum, you will need the following things to build Wiring:

+ A Java Development Kit (JDK). Any Oracle JDK compatible with Java
  1.5+ should work. (We make use of some com.sun.* APIs that may
  render other JDKs inoperable).

  - Windows: after installing the JDK, you'll need to:

    1. Set the environment variable JAVA_HOME to point to the JDK
    directory (by default, this goes into C:\Program
    Files\Java\jdk-VERSION\).

    2. Add the JDK's bin\ directory to your PATH (check this by
    running javac at the command prompt).

  - OS X: use Apple's. (We haven't tested with Oracle's; feedback is
    welcome).

  - Linux: you're on your own. Your distribution's package manager
    likely provides many choices.

+ Apache Ant.

  - Windows: download and install Ant from its Apache page:

      http://ant.apache.org/

    Pay attention to the Windows install instructions (setting
    JAVA_HOME, ANT_HOME, and updating your PATH) here:

      http://ant.apache.org/manual/install.html

    However, the recommendations that page makes about *how* to set
    environment variables are bogus; to make the settings permanent,
    you'll need to go through the usual environment variables dialog
    dance in the System control panel.

  - OS X: last we checked, Ant is included by default with the JDK.

  - Linux: you'll likely find Ant in your distribution's package
    manager (e.g. on Debian or Ubuntu: sudo apt-get install ant).

Depending on your platform, you will also need some other stuff:

1a. Windows:

    - Launch4j: You need this to build wiring.exe. After you download
      and install it, make sure that launch4jc.exe (which is in the
      top-level Launch4j folder under Program Files) is on your PATH.

      http://launch4j.sourceforge.net/

1b. Mac OS X

    - Apple's developer tools (XCode). You may be able to get by with
      just the free command line tools.

1c. Linux:

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

To build the Wiring IDE for your system. (This is the same thing as
running $ ant make).

NOTE: the first time you run ant, some external dependencies will be
automatically downloaded and extracted, so it may take a while. After
the first time, though, builds will go much faster.

Once it's built, use

    $ ant run

to run the Wiring IDE.

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

    IMPORTANT: Using clean.all means your next build will require an
    internet connection, as the external dependencies will have to be
    re-downloaded. You have been warned.


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

#!/bin/sh
CYGWIN=nodosfilewarning
export CYGWIN

CLASSPATH=lib\\pde.jar\;lib\\core.jar\;lib\\jna.jar\;lib\\ecj.jar\;lib\\antlr.jar\;lib\\oro.jar\;lib\\serial\\RXTXcomm.jar\;lib\\serial\\*\;java\\lib\\tools.jar
export CLASSPATH

cd work && ./java/bin/java processing.app.Base

# Set XPARAM_CLASSPATH for csh

if ( ${?XPARAM_CLASSPATH} ) then
   exit
endif

setenv XPARAM_CLASSPATH /usr/lib/xparam-plugins


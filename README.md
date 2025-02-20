# sp209api-test-minimal
 
The aim of this project is to demonstrate the usage of SP209 logic analyzer API. Only 64bit system is supported.

More info about the API can be found here: https://docs.ikalogic.com/la-api/la_home

The example Qt projects takes care of correctly linking the libraries.

# Installation
First, please download and install ScanaStudio for your platform. While ScanaStudio is not needed, this will ensure drivers are isntalled in windows, and correct UDEV rules are set for UNIX. 

## Windows
Compile against the sp1000g_api library in `dependencies/win` folder.

## Linux
Compile against the sp1000g_api library in `dependencies/linux` folder.

## Mac
Compile against the sp1000g_api library in `dependencies/mac` folder.

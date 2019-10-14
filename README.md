# sp209api-test-minimal
 
The aim of this project is to demonstrate the usage of SP209 logic analyzer API

# Installation
First, please download ScanaStudio for your platform. While ScanaStudio is not needed, this will ensure drivers are isntalled in windows, and correct UDEV rules are set for UNIX. 

## Windows
Nothing need to be done to get it running under windows, provided you use a recent (Qt5) environment.

## Linux
Under linux, it *may* be necessary to manually copy and rename the `*.so.rename` files  from the `dependencies` folder of this repo to `/usr/local/lib` and ensure that 
`LD_LIBRARY_PATH=/usr/local/lib`
Then run `export LD_LIBRARY_PATH` before launching the compiled file.

## Mac
currently untested under mac OS.

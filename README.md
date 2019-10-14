# sp209api-test-minimal
 
The aim of this project is to demonstrate the usage of SP209 logic analyzer API

## Windows
Nothing need to be done to get it running under windows, provided you use a recent (Qt5) environment.

## Linux
Under linux, it *may* be necessary to manually copy the `*.so` files in  `/usr/local/lib` and ensure that 
`LD_LIBRARY_PATH=/usr/local/lib`
Then run `export LD_LIBRARY_PATH` before launching the compiled file.

## Mac
currently untested under mac OS.

# Build & Run
We will use cmake to build the executable for running this project. At first, create the build directory and then `cd` into the directory from the terminal.

```shell
mkdir build
cd build
```

After that we need to run `cmake` command to generate the cmake files and the `make` command to generate the executable.

Since we are into the `/build` directory and we need to run cmake on the source directory, we have to run the following commands to generate the cmake files and the executable file.
``` shell
cmake ..
make
```

This will create an executable with the name defined in the `CMakeFiles.txt` file, here that will be `web_server`. To run this executable we just need to run the following command:
```shell
./web_server
```

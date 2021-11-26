Tevian Client
===

A program for recognizing faces on images using the Tevian API.

![Tevian](https://i.imgur.com/zbbVRtL.png)

Features
------
- The client is implemented as a GUI and CLI application
- Processing multiple images and folders
- Display of processing progress

Installation
------
    gitclone https://github.com/leeroyka/TevianClient.git
    cd TevianClient
    mkdir build && cd build
    cmake .. && cmake --build .
    make install
	
Compilation
------	
- The code can be compiled with the provided cmake file using the standard make command.
- If compiling the code manually and you want to use the CLI version, include the following flags:
```
ENABLE_CLI_APPLICATION **ON**
```

Requirements
------
- **Qt5**
- **OpenSSL** 2.0 or newest
- **C++11** or newest
- **Cmake** 2.8 or newest

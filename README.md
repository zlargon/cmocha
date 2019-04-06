# cmocha

[![Build Status](https://travis-ci.com/zlargon/cmocha.svg?branch=master)](https://travis-ci.com/zlargon/cmocha)

C testing tool with mocha style

## Support Platform

- Mac
- Linux
- Windows

## Example

```c
#include "mocha.h"

int test1() {
    assert(1 == 1);     // pass
    return 0;           // return 0 to tell mocha this test pass
}

int test2() {
    assert(1 == 0);     // fail. automatically return -1 to tell mocha this test fail
    return 0;           // this line won't be executed
}

int main() {
    // if there is any test failed, 'describe' will return -1, and then test result fail
    // otherwise, 'describe' will return 0, and test pass
    return describe(
        "Test Example",
        test1,      // pass
        test2       // fail
    );
}
```

## Build Example with CMake

- install [cmake](https://cmake.org/) build tool

```bash
cd example

mkdir build             # create your build folder
cd build

cmake ..                # generate build project
cmake --build .         # build code

./example               # run example
./Debug/example.exe     # run example (on windows)
```

## Windows

`Font Color` and `Check Symbol` can display fine with [Windows Git Bash](https://gitforwindows.org/) but break with `cmd` and `PowerShell`

![windows git bash](https://user-images.githubusercontent.com/2791834/55674356-a4c65e80-5881-11e9-91d8-7c8471320209.PNG)

## Demo

[![asciicast](https://asciinema.org/a/239276.svg)](https://asciinema.org/a/239276)

## License

MIT

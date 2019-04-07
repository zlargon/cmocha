# cmocha

[![Build Status](https://travis-ci.com/zlargon/cmocha.svg?branch=master)](https://travis-ci.com/zlargon/cmocha)

C testing tool with mocha style

## Support Platform

- Mac
- Linux
- Windows

![screenshot](https://user-images.githubusercontent.com/2791834/55678160-ecb9a580-58c2-11e9-8e82-2ad2608e3e73.PNG)

## Example

```c
#include "mocha.h"

int test1() {
    expect(1 == 1);     // pass
    return 0;           // return 0 to tell mocha this test pass
}

int test2() {
    expect(1 == 0);     // fail. automatically return -1 to tell mocha this test fail
    return 0;           // this line won't be executed
}

int main() {
    // if there is any test failed, 'describe' will return -1, and then test result fail
    // otherwise, 'describe' will return 0, and test pass
    return describe(
        "Test Example",
        test1,          // pass
        test2           // fail
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

## Demo

[![asciicast](https://asciinema.org/a/239276.svg)](https://asciinema.org/a/239276)

## License

MIT

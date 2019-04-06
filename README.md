# cmocha
C testing tool in mocha style

```c
#include "mocha.h"

int test1() {
    // void assert(expression);
    assert(1 == 1);

    // return 0 to tell mocha this test pass
    return 0;
}

int test2() {
    // automatically return -1 to tell mocha this test fail
    assert(1 == 0);

    // this won't be excuted
    return 0;
}

int main() {
    /**
     *  int describe(
     *      const char * description,
     *      int (* testCase)(), ...
     *  );
     */
    describe(
        "Test Example",
        test1,
        test2
    );

    return 0;
}
```

# Build Example with CMake

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

Windows:
`Font Color` and `Check Symbol` can display fine with [Windows Git Bash](https://gitforwindows.org/) but break with `cmd` and `PowerShell`

![windows git bash](https://user-images.githubusercontent.com/2791834/55674356-a4c65e80-5881-11e9-91d8-7c8471320209.PNG)

# Demo

[![asciicast](https://asciinema.org/a/239276.svg)](https://asciinema.org/a/239276)

# License

MIT

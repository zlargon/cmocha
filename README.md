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

# Run Example

1. install [cmake](https://cmake.org/)

```
cd example          # go to example folder

mkdir build         # create 'build' folder
cd build

cmake ..            # generate build project
cmake --build .     # build code

./example           # run example
```

![test](https://user-images.githubusercontent.com/2791834/55655665-cc0a2680-57c2-11e9-9b82-e26f1336a894.png)

# License

MIT

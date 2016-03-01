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
     *  void describe(
     *      const char * description,
     *      int (* testCase)(), ...
     *  );
     */
    describe(
        "Test Example",
        test1,
        test2
    );

    /* if there is any test failed, `abort()` will be called */
    return 0;
}
```

![test](https://cloud.githubusercontent.com/assets/2791834/13429801/d87ca15e-dffc-11e5-8c87-a9ce2d3b81ec.png)

# License

MIT

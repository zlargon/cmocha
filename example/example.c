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

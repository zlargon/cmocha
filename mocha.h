#ifndef __MOCHA_H
#define __MOCHA_H

/**
 * int describe(const char * description, int (* testCase)(), ...);
 *
 * @param description
 * @param testCase      function => int testCase();
 * @return 0            all pass
 *         -1           at least one failed
 */
#define describe(description, ...) __describe(description, #__VA_ARGS__, __VA_ARGS__)

/**
 * void assert(expression);
 *
 * @param expression
 */
#define assert(expression)                                          \
    if (!(expression)) {                                            \
        __assert_fail(#expression, __FILE__, __LINE__, __func__);   \
        return -1;                                                  \
    }

/* internal function */
int __describe(const char * description, const char * testCaseNames, int (* testCaseList)(), ...);
void __assert_fail(const char * expression, const char * file, int line, const char * func);

#endif

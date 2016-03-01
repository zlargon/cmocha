#ifndef __MOCHA_H
#define __MOCHA_H

/**
 * void describe(const char * description, int (* testCase)(), ...);
 *
 * @param description
 * @param testCase      function => int testCase();
 */
#define describe(description, testCase...) __describe(description, #testCase, testCase)

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
void __describe(const char * description, const char * testCaseNames, int (* testCaseList)(), ...);
void __assert_fail(const char * expression, const char * file, int line, const char * func);

#endif

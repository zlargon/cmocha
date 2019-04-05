#include <stdio.h>      // fprintf, stdout
#include <stdlib.h>     // calloc, free
#include <string.h>     // strlen, strcmp, memcpy, strtok_r
#include <stdarg.h>     // va_start, va_end, va_list
#include "mocha.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>   // gettimeofday
#endif

// color
#define COLOR_DARK_GRAY "\033[1;30m"
#define COLOR_RED       "\033[0;31m"
#define COLOR_GREEN     "\033[0;32m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_BLUE      "\033[0;34m"
#define COLOR_MAGENTA   "\033[0;35m"
#define COLOR_CYAN      "\033[0;36m"
#define COLOR_GRAY      "\033[0;37m"
#define COLOR_RESET     "\033[0m\n"

// TestCase
typedef int (* TestCase)();

// currentTime
// https://stackoverflow.com/a/728092/
static unsigned long long currentTime() {
#ifdef _WIN32
    SYSTEMTIME systime;
    FILETIME filetime;

    GetSystemTime(&systime);
    if (!SystemTimeToFileTime(&systime, &filetime)) {
        return 0;
    }

    unsigned long long ns_since_1601;
    ULARGE_INTEGER * ptr = (ULARGE_INTEGER*)&ns_since_1601;

    // copy the result into the ULARGE_INTEGER; this is actually
    // copying the result into the ns_since_1601 unsigned long long.
    ptr->u.LowPart = filetime.dwLowDateTime;
    ptr->u.HighPart = filetime.dwHighDateTime;

    // Compute the number of milliseconds since 1601; we have to
    // divide by 10,000, since the current value is the number of 100ns
    // intervals since 1601, not ms.
    return (ns_since_1601 / 10000);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((unsigned long long)tv.tv_sec) * 1000 + ((unsigned long long)tv.tv_usec) / 1000);
#endif
}

// __describe
void __describe(const char * description, const char * testCaseNames, TestCase testCaseList, ...) {
    int pass = 0, fail = 0;
    long long describeStart = currentTime();
    printf("\n  \033[4m%s" COLOR_RESET, description);

    size_t len = strlen(testCaseNames);
    char * names = (char *) calloc(len + 1, sizeof(char));
    memcpy(names, testCaseNames, len);

    va_list ap;
    va_start(ap, testCaseList);
    TestCase testCase = testCaseList;

    char * testName = strtok(names, ", ");
    while (testName != NULL) {

        // replace '_' to ' '
        size_t i;
        for (i = 0; testName[i] != '\0'; i++) {
            if (testName[i] == '_') testName[i] = ' ';
        }

        long long testStart = currentTime();
        int result = testCase();

        // Report
        if (result == 0) {
            // pass: ✓ xxxx (100 ms)
            printf(
                COLOR_GREEN     "    ✓"
                COLOR_DARK_GRAY " %s"
                COLOR_YELLOW    " (%lldms)" COLOR_RESET,
                testName,
                currentTime() - testStart
            );
            pass++;
        } else {
            // fail: ✘ xxxx
            printf(COLOR_RED "    ✘ %s" COLOR_RESET, testName);
            fail++;
        }

        testName = strtok(NULL, ", ");
        testCase = va_arg(ap, TestCase);
    }
    free(names);

    // Final Report
    printf(COLOR_GREEN "\n\n  %d passing " COLOR_DARK_GRAY "(%lldms)" COLOR_RESET, pass, currentTime() - describeStart);
    if (fail > 0) {
        printf(COLOR_RED "  %d failing\n" COLOR_RESET, fail);
        abort();
    }
    puts("");
}

// __assert_fail
void __assert_fail(const char * expression, const char * file, int line, const char * func) {
    printf(
        COLOR_RED
        "      Assertion Failed: %s, %s (%s:%d)" COLOR_RESET,
        expression, func, file, line
    );
}

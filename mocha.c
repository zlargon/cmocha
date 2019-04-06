#include <stdio.h>      // printf, putchar
#include <stdarg.h>     // va_start, va_end, va_list
#include "mocha.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>   // gettimeofday
#endif

// color
#define UNDERSCORE      "\033[4m"
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

// printTestName
static int printTestName(const char * str, int startIndex) {
    int i;
    for (i = startIndex; ; i++) {
        char c = str[i];
        switch (c) {
            case ',':   continue;
            case ' ':   return i + 1;
            case '\0':  return -1;
            default:    putchar(c == '_' ? ' ' : c);    // replace '_' to ' '
        }
    }
}

// __describe
int __describe(const char * description, const char * testCaseNames, TestCase testCaseList, ...) {
    unsigned long long describeStart = currentTime();
    printf(
        "\n  "
        UNDERSCORE "%s"     // description
        COLOR_RESET,
        description
    );

    va_list ap;
    va_start(ap, testCaseList);

    int pass = 0, fail = 0, index = 0;
    TestCase testCase;
    for (testCase = testCaseList; index != -1; testCase = va_arg(ap, TestCase)) {

        // execute the test case and calulate the duration time
        unsigned long long startTime = currentTime();
        int result = testCase();
        unsigned long long duration = currentTime() - startTime;

        // Report
        if (result == 0) {
            // pass: ✓ xxxx (100 ms)
            pass++;

            printf(
                COLOR_GREEN "    ✓ "
                COLOR_DARK_GRAY
            );
            index = printTestName(testCaseNames, index);
            printf(
                COLOR_YELLOW " (%lldms)" // duration
                COLOR_RESET,
                duration
            );
        } else {
            // fail: ✘ xxxx
            fail++;

            printf(COLOR_RED "    ✘ ");
            index = printTestName(testCaseNames, index);
            printf(COLOR_RESET);
        }
    }

    va_end(ap);

    // Final Report
    int result = fail > 0 ? -1 : 0;
    // pass report
    printf(
        COLOR_GREEN     "\n\n  %d passing " // pass
        COLOR_DARK_GRAY "(%lldms)"          // duration
        COLOR_RESET,
        pass,
        currentTime() - describeStart
    );

    // fail report
    if (result == -1) {
        printf(
            COLOR_RED "  %d failing"        // fail
            COLOR_RESET,
            fail
        );
    }

    puts("");
    return result;
}

// __assert_fail
void __assert_fail(const char * expression, const char * file, int line, const char * func) {
    printf(
        COLOR_RED
        "      Assertion Failed: %s, %s (%s:%d)" COLOR_RESET,
        expression, func, file, line
    );
}

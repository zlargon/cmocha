#include <stdbool.h>    // bool, true, false
#include <stdio.h>      // printf, putchar
#include <stdarg.h>     // va_start, va_end, va_list
#include "mocha.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>   // gettimeofday
#endif

// TestCase
typedef int (* TestCase)();

// setFontStyle
#ifdef _WIN32
    // https://docs.microsoft.com/en-us/windows/console/console-screen-buffers
    // https://stackoverflow.com/a/9203489
    // https://stackoverflow.com/a/17125539
    #define RESET       DEFAULT_STYLE
    #define UNDERLINE   (FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | COMMON_LVB_UNDERSCORE)
    #define DARK_GRAY   FOREGROUND_INTENSITY
    #define RED         (FOREGROUND_INTENSITY | FOREGROUND_RED)
    #define GREEN       FOREGROUND_GREEN
    #define YELLOW      (FOREGROUND_RED | FOREGROUND_GREEN)
    #define setFontStyle(style) SetConsoleTextAttribute(hConsole, DEFAULT_BACKGROUND | style);

    static HANDLE hConsole;
    static WORD DEFAULT_STYLE;
    static WORD DEFAULT_BACKGROUND;
    static void initStyle() {
        static isInit = false;
        if (isInit) return;
        isInit = true;

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        DEFAULT_STYLE = consoleInfo.wAttributes;
        DEFAULT_BACKGROUND = DEFAULT_STYLE & 0b1111111111110000;
    }
#else
    #define RESET       "\033[0m"
    #define UNDERLINE   "\033[4m"
    #define DARK_GRAY   "\033[1;30m"
    #define RED         "\033[0;31m"
    #define GREEN       "\033[0;32m"
    #define YELLOW      "\033[0;33m"
    #define setFontStyle(style) printf(style);
#endif

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
#ifdef _WIN32
    initStyle();
#endif
    unsigned long long describeStart = currentTime();

    printf("\n  ");
    setFontStyle(UNDERLINE);
    printf("%s\n", description);
    setFontStyle(RESET);

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
            // pass: v xxxx (100 ms)
            pass++;

            setFontStyle(GREEN);
            printf("    v ");
            setFontStyle(DARK_GRAY);
            index = printTestName(testCaseNames, index);
            setFontStyle(YELLOW);
            printf(" (%lldms)\n", duration);
            setFontStyle(RESET);
        } else {
            // fail: 1) xxxx
            fail++;

            setFontStyle(RED);
            printf("    %d) ", fail);
            index = printTestName(testCaseNames, index);
            puts("");
            setFontStyle(RESET);
        }
    }

    va_end(ap);

    // Final Report
    int result = fail > 0 ? -1 : 0;
    // pass report
    setFontStyle(GREEN);
    printf("\n\n  %d passing", pass);
    setFontStyle(DARK_GRAY);
    printf(" (%lldms)\n", currentTime() - describeStart);
    setFontStyle(RESET);

    // fail report
    if (result == -1) {
        setFontStyle(RED);
        printf("  %d failing\n", fail);
        setFontStyle(RESET);
    }

    puts("");
    return result;
}

// __assert_fail
void __assert_fail(const char * expression, const char * file, int line, const char * func) {
#ifdef _WIN32
    initStyle();
#endif
    setFontStyle(RED);
    printf("      Assertion Failed: %s, %s (%s:%d)\n", expression, func, file, line);
    setFontStyle(RESET);
}

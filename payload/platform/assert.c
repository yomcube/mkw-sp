// Implements __assert_func

#include <revolution.h>

__attribute__((noreturn)) void __assert_func(const char *filename, int line, const char *assertFunc,
        const char *expr) {
    (void)filename;
    (void)line;
    (void)assertFunc;
    OSFatal(GXCOLOR_WHITE, GXCOLOR_BLACK, expr);
}

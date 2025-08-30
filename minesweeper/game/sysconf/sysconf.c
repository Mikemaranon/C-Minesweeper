#include "sysconf.h"

// --- Set terminal in raw mode ---
void set_raw_mode(int enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);   // save actual state
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // deactivate line buffer and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore
    }
}

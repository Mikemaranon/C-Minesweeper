#ifndef SYSCONF_H
#define SYSCONF_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

// public function declarations
void set_raw_mode(int enable);

#endif
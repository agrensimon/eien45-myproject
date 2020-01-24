#include "serialport.h"



main() {
    int fd = serial_init("/dev/ttyS0",0);
    serial_cleanup(fd);
}
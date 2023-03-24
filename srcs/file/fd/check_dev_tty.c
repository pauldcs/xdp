#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

bool check_dev_tty(void) {
    int   tty_fd;
    char  *tty;

    tty_fd = open("/dev/tty", O_RDWR | O_NONBLOCK);

    if (tty_fd == -1) {
        tty = (char *)ttyname(STDIN_FILENO);
        if (!tty) {
            return (false);
        }
        tty_fd = open(tty, O_RDWR | O_NONBLOCK);
        if (tty_fd == -1) {
            return (false);
        }
    }
    close(tty_fd);
    return (true);
}
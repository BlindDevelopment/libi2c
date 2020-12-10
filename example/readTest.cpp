#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "i2c.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int fd;
    I2CDevice device;
	size_t len = 50;
    char *data = new char[len];

    /* First open i2c bus */
    if ((fd = i2c_open("/dev/i2c-1")) == -1) {

        perror("Open i2c bus error");
        return -1;
    }

    /* Fill i2c device struct */
    device.bus = fd;
    device.addr = 0x08;
    device.tenbit = 0;
    device.delay = 10;
    device.flags = 0;
    device.page_bytes = 8;
    device.iaddr_bytes = 0; /* Set this to zero, and using i2c_ioctl_xxxx API will ignore chip internal address */

    /* Read data from i2c */
	ssize_t nRead = i2c_ioctl_read(&device, 0x00, data, len);
	cout << data << endl;

    i2c_close(fd);
	delete[] data;
    return 0;

}


## MIK32 example

This example demonstrates reading values from OV7670 and sending them send via UART using MIK32 microcontroller.

## How to build
To build this example you need to download linux [package](https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz) for architecture-specific compilers:
```bash
$ wget --no-check-certificate https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz && \
    tar -xvzf xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz && \
    rm -rf xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz
```

Then you need to export environment variable for toolchain:
```bash
$ export MIK32_TOOLCHAIN_DIR=<directory where you extracted the package>/xpack-riscv-none-elf-gcc-14.2.0-3/bin
```

Now run
```bash
$ make
```
this will create *build/* directory and *mik32_firmware.\** files.
By default baudrate is set to 115200, but you can override it by
```bash
$ make SERIAL_BAUDRATE=<any-number-you-want>
```

To cleanup build files run
```bash
$ make clean
```

To flash your device just run
```bash
$ make flash
```
this will build the project and flash the device.

You can set appropriate file for your microcontroller device file in Makefile by changing SERIAL_PORT variable or overriding it. This is how to check messages, sent by your MIK32:
```bash
$ make monitor SERIAL_PORT=/path/to/your/device
```


# Zephyr BGM220P (EFR32BG22) LED Blink, Hello World & Bluetooth – Developer Guide

This README is tailored for developers working in a native **Zephyr environment** (not using Docker) on a Linux system like Ubuntu. It outlines the steps to build and flash applications on the **Silicon Labs BGM220P** module or **SLTB010A** evaluation board using **Zephyr RTOS**, **SEGGER J-Link**, and **Bluetooth LE** features.

---

## 🔧 Environment Setup

### ✅ Requirements

* Ubuntu 20.04+ (Native OS, not Docker)
* Zephyr SDK ≥ 0.16.5
* Zephyr Project initialized with `west`
* SEGGER J-Link software installed and connected
* USB access rules and `plugdev` permissions set

### 🛠 Steps

```bash
# Create Python virtual environment for Zephyr
python3.10 -m venv zephyr-venv
source zephyr-venv/bin/activate

# Clone Zephyr and set up workspace
west init ~/zephyrproject
cd ~/zephyrproject
west update
west zephyr-export

# Install Zephyr SDK and set environment variables
export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk-0.16.5
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
```

### 🔌 Install SEGGER J-Link

```bash
wget https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb
sudo dpkg -i JLink_Linux_x86_64.deb
sudo apt-get install -f
```

---

## 💡 Build and Flash Blinky

### 🔨 Build the sample

```bash
west build -b sltb010a -s zephyr/samples/basic/blinky -d build_bg22 --pristine
```

### ⚡ Flash to SLTB010A

```bash
west flash
```

> ✅ The on-board LED will blink once per second.

---

## 🧪 Custom Hello World on Button Press

### 📁 App Structure

```
hello_app/
├── CMakeLists.txt
├── prj.conf
└── src/
    └── main.c
```

### 📜 Files

**CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_app)
target_sources(app PRIVATE src/main.c)
```

**prj.conf**

```conf
CONFIG_CONSOLE=y
CONFIG_UART_CONSOLE=y
CONFIG_GPIO=y
```

**src/main.c**

```c
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED_NODE DT_ALIAS(led0)
#define BTN_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BTN_NODE, gpios);

void main(void)
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&btn, GPIO_INPUT | GPIO_PULL_UP);

    int last = 1;
    while (1) {
        int state = gpio_pin_get_dt(&btn);
        if (!state && last) {
            printk("Hello World! %s\n", CONFIG_BOARD);
            gpio_pin_toggle_dt(&led);
        }
        last = state;
        k_msleep(10);
    }
}
```

### 🏗 Build & Flash


west build -b sltb010a --pristine

west flash 

<img width="1920" height="1080" alt="Screenshot from 2025-07-15 17-31-32" src="https://github.com/user-attachments/assets/75dd0596-5727-44d9-ad76-6bb761655b51" />


✅ On pressing BTN0: LED toggles and "Hello World! sltb010a" prints via UART.

## 📶 Enable and Test Bluetooth on BGM220P

The BGM220P (EFR32BG22) module supports **Bluetooth Low Energy (BLE)** out of the box.

### 🔨 Build the HCI UART Bluetooth Sample

```bash
west build -b sltb010a -s zephyr/samples/bluetooth/hci_uart -d build_bt --pristine


### ⚡ Flash Bluetooth Sample

```bash
west flash 
```

> This configures the BGM220P to act as a Bluetooth Controller. You can then connect it to a host stack like **Zephyr’s bt-host**, **BlueZ**, or **nRF Connect mobile app** to test advertisements and GATT services.

### 🔧 Optional: Add to prj.conf

```conf
CONFIG_BT=y
CONFIG_BT_DEBUG_LOG=y
CONFIG_BT_HCI_RAW=y
CONFIG_UART_INTERRUPT_DRIVEN=y
```

### 📡 Debug & Monitor

Use `minicom` or `screen` to observe UART traffic:

```bash
sudo screen /dev/ttyACM0 115200
```

You may also connect the board to an external BLE scanner or mobile app to see the broadcast.

---

## 🐞 Common Issues & Solutions

| Issue                           | Solution                                                            |
| ------------------------------- | ------------------------------------------------------------------- |
| `west flash` fails              | Use `--runner jlink`, not `openocd`                                 |
| Permission denied on USB device | Add user to `plugdev` and reload udev rules                         |
| Unknown device in JLinkExe      | Use exact part: `EFR32BG22C224F512IM40`                             |
| UART output unreadable          | Confirm baud = 115200 and correct `/dev/ttyACM0` or equivalent port |
| BLE not visible on phone        | Make sure the device advertises; check your build configs           |

---

## ✅ Summary

This guide helps you:

* Set up a native Zephyr environment on Ubuntu
* Build and flash LED blink and GPIO apps
* Enable and test BLE controller functionality
* Use SEGGER J-Link tools for programming/debugging

You can extend this further with GATT profiles, sensors, and custom BLE services.

Happy Hacking 🎯


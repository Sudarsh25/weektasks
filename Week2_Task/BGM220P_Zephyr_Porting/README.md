# 🚀 Zephyr RTOS Porting – Silicon Labs BGM220P

This repository contains a full **custom board port of the BGM220P (EFR32BG22 SoC)** to the Zephyr RTOS ecosystem. It includes board files, SoC configurations, application examples, device tree overlays, and documentation.

---

## 📖 Objective

Enable Zephyr RTOS support on **BGM220P** for embedded development, allowing firmware engineers to:
- Compile and run `my_app` and other demos
- Use `west` to build firmware
- Integrate peripherals like GPIO, UART, and I2C

---

## 🧩 Project Structure
BGM220P_Zephyr_Porting/
├── boards/
│ └── arm/bgm220p/
│ ├── bgm220p.dts
│ ├── bgm220p.dtsi
│ ├── pinctrl.dtsi
│ ├── bgm220p_defconfig
│ ├── bgm220p.yaml
│ ├── Kconfig
│ ├── board.cmake
│ ├── CMakeLists.txt
│ └── Kconfig.bgm220p
├── dtsi_files/
│ ├── bgm220p.dtsi
│ ├── efm32gg11b.dtsi
│ ├── efr32_series1_common.dtsi
│ └── efr32_series1_common_pinctrl.dtsi
├── my_app/
│ ├── prj.conf
│ ├── CMakeLists.txt
│ └── src/
│ └── main.c
├── docs/
│ ├── BGM220p.pdf
│ ├── week2ble.pdf
│ └── week2process.pdf


---

## 🔨 Build Instructions

### 📦 Environment Setup

bash
# Ensure Zephyr SDK is installed and sourced
export ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-0.17.2
source zephyr/zephyr-env.sh

## 🛠️ Build Application

cd my_app/
west build -b bgm220p . --pristine

💡 Toolchain Notes
Make sure the following is correctly set in toolchain.cmake:
set(CC gcc)
set(CROSS_COMPILE ${ZEPHYR_SDK_INSTALL_DIR}/arm-zephyr-eabi/bin/arm-zephyr-eabi-)

Check toolchain installation:
echo $ZEPHYR_SDK_INSTALL_DIR
#Expected: /opt/toolchains/zephyr-sdk-0.17.2

# 🧯Common Issues & Fixes

• Issue: Circular Kconfig error
– Cause: Using select on SoC symbols created recursive dependency loops
– Fix: Avoid using select on SoC-related symbols; instead use depends on and default in       Kconfig files

 Issue: Symbol has no prompt
– Cause: CONFIG_SOC_SERIES_* was manually set in defconfig, but it’s a hidden symbol
– Fix: Only set CONFIG_SOC_PART_NUMBER_EFR32BG22C224F512IM40=y
  This will automatically select the appropriate SoC series

 Issue: -gcc not found during build
– Cause: The CC or CROSS_COMPILE variable was not set correctly in toolchain.cmake
– Fix: Ensure your toolchain.cmake includes:
   
    set(CC gcc)
    set(CROSS_COMPILE ${ZEPHYR_SDK_INSTALL_DIR}/arm-zephyr-eabi/bin/arm-zephyr-eabi-)

Issue: DTSI parsing failure
– Cause: Incorrect or missing #include paths in .dts or .dtsi files
– Fix: Verify that all included DTSI files are present and properly referenced.
  Example:

    #include <silabs/efr32bg22.dtsi>
    #include "pinctrl.dtsi"


# 🧪 Application: my_app (Blinky)

A simple LED blinking app built using:

    Zephyr GPIO APIs

    Main loop with k_sleep

    GPIO control of on-board LED 

File: my_app/src/main.c

# 📚 Documents

Documentation related to this porting effort is located in the docs/ directory:

 📄 BGM220p.pdf — Board design and integration notes
 📄 week2ble.pdf — BLE stack and configuration details
 📄 week2process.pdf — Porting and build process summary

📄 License

Licensed under the Apache 2.0 License.

# 🙋 Maintainer

Sreesudarshan R V
Email : sreesudarshanrv@gmail.com
Github : https://github.com/Sudarsh25/weektasks




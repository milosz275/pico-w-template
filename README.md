# Pico W Template

This is a template for a Pico W project. It includes a basic project structure and a simple example of a Pico W application in C using pico-sdk and pico-extras. Feel free to use it if CMake is is challenging for you or you just want to get started quickly.

To use this template click "Use this template" and create a new repository or open the template in a codespaces [or use this template here](https://github.com/new?template_name=pico-w-template&template_owner=milosz275).

## Getting Started

### Prerequisites

It might be necessary to install additional dependencies to build the project. The following commands install the required dependencies on Ubuntu:

```bash
sudo apt-get install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential ninja-build
```

This project uses git submodules to include the Pico SDK and Pico Extras. To clone the repository with submodules use the following command:

```bash
git clone --recurse-submodules https://github.com/milosz275/pico-w-template.git
```

If you have already cloned the repository without submodules you can initialize them using the following commands:

```bash
git submodule init
git submodule update
```

If any issues occur during the build, you may wanted to update the submodules inside `pico-sdk`:

```bash
cd pico-sdk
git submodule update --init
```

### Configuration

Please create a `cmake` directory with a `credentials.cmake` file inside it. The file should contain the following lines:

```cmake
set(WIFI_SSID "<YOUR_SSID>" CACHE INTERNAL "WiFi SSID")
set(WIFI_PASSWORD "<YOUR_PASS>" CACHE INTERNAL "WiFi password")
```


### Building

To build the project, run the following commands:

```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```

## Acknowledgements

- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- [Pico Extras](https://github.com/raspberrypi/pico-extras)
- [Pico Template](https://github.com/modmuss50/pico-template)
- [Pico W Webserver Example](https://github.com/krzmaz/pico-w-webserver-example)
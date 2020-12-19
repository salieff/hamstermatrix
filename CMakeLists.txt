cmake_minimum_required(VERSION 3.5)

project(hamstermatrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hamstermatrix
    main.cpp
    src/button.cpp
    src/triggers.cpp
    src/voltage.cpp)

add_compile_definitions(
    ESP_PLATFORM
    MBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"
    HAVE_CONFIG_H
    GCC_NOT_5_2_0=0
    WITH_POSIX
    F_CPU=240000000L
    ARDUINO=10813
    ARDUINO_ESP32_DEV
    ARDUINO_ARCH_ESP32
    ARDUINO_BOARD=\"ESP32_DEV\"
    ARDUINO_VARIANT=\"esp32\"
    ESP32
    CORE_DEBUG_LEVEL=0
    ARDUINO_LIB_DISCOVERY_PHASE)

include_directories(
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/config"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/app_trace"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/app_update"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/asio"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/bootloader_support"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/bt"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/coap"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/console"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/driver"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-tls"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp32"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_adc_cal"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_event"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_http_client"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_http_server"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_https_ota"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp_ringbuf"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/ethernet"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/expat"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/fatfs"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/freemodbus"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/freertos"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/heap"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/idf_test"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/jsmn"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/json"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/libsodium"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/log"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/lwip"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mbedtls"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mdns"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/micro-ecc"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/mqtt"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/newlib"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/nghttp"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/nvs_flash"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/openssl"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/protobuf-c"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/protocomm"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/pthread"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/sdmmc"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/smartconfig_ack"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/soc"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/spi_flash"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/spiffs"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/tcp_transport"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/tcpip_adapter"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/ulp"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/vfs"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wear_levelling"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wifi_provisioning"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/wpa_supplicant"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/xtensa-debug-module"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-face"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp32-camera"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/esp-face"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/tools/sdk/include/fb_gfx"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/cores/esp32"
    "/home/salieff/.arduino15/packages/esp32/hardware/esp32/1.0.4/variants/esp32"
    "./src")

add_compile_options(
    -std=gnu++11
    -Os
    -g3
    -Wpointer-arith
    -fexceptions
    -fstack-protector
    -ffunction-sections
    -fdata-sections
    -fstrict-volatile-bitfields
    -mlongcalls
    -nostdlib
    -fno-rtti)

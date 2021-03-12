cmake_minimum_required(VERSION 3.5)

project(hamstermatrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hamstermatrix
    main.cpp
    hamstermatrix/button.cpp
    hamstermatrix/triggers.cpp
    hamstermatrix/voltage.cpp)

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

set(ESP32_DIR "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/1.0.5")
set(ESP32_SDK_INCLUDE "${ESP32_DIR}/tools/sdk/include")

include_directories(
    "${ESP32_SDK_INCLUDE}/config"
    "${ESP32_SDK_INCLUDE}/app_trace"
    "${ESP32_SDK_INCLUDE}/app_update"
    "${ESP32_SDK_INCLUDE}/asio"
    "${ESP32_SDK_INCLUDE}/bootloader_support"
    "${ESP32_SDK_INCLUDE}/bt"
    "${ESP32_SDK_INCLUDE}/coap"
    "${ESP32_SDK_INCLUDE}/console"
    "${ESP32_SDK_INCLUDE}/driver"
    "${ESP32_SDK_INCLUDE}/esp-tls"
    "${ESP32_SDK_INCLUDE}/esp32"
    "${ESP32_SDK_INCLUDE}/esp_adc_cal"
    "${ESP32_SDK_INCLUDE}/esp_event"
    "${ESP32_SDK_INCLUDE}/esp_http_client"
    "${ESP32_SDK_INCLUDE}/esp_http_server"
    "${ESP32_SDK_INCLUDE}/esp_https_ota"
    "${ESP32_SDK_INCLUDE}/esp_ringbuf"
    "${ESP32_SDK_INCLUDE}/ethernet"
    "${ESP32_SDK_INCLUDE}/expat"
    "${ESP32_SDK_INCLUDE}/fatfs"
    "${ESP32_SDK_INCLUDE}/freemodbus"
    "${ESP32_SDK_INCLUDE}/freertos"
    "${ESP32_SDK_INCLUDE}/heap"
    "${ESP32_SDK_INCLUDE}/idf_test"
    "${ESP32_SDK_INCLUDE}/jsmn"
    "${ESP32_SDK_INCLUDE}/json"
    "${ESP32_SDK_INCLUDE}/libsodium"
    "${ESP32_SDK_INCLUDE}/log"
    "${ESP32_SDK_INCLUDE}/lwip"
    "${ESP32_SDK_INCLUDE}/mbedtls"
    "${ESP32_SDK_INCLUDE}/mdns"
    "${ESP32_SDK_INCLUDE}/micro-ecc"
    "${ESP32_SDK_INCLUDE}/mqtt"
    "${ESP32_SDK_INCLUDE}/newlib"
    "${ESP32_SDK_INCLUDE}/nghttp"
    "${ESP32_SDK_INCLUDE}/nvs_flash"
    "${ESP32_SDK_INCLUDE}/openssl"
    "${ESP32_SDK_INCLUDE}/protobuf-c"
    "${ESP32_SDK_INCLUDE}/protocomm"
    "${ESP32_SDK_INCLUDE}/pthread"
    "${ESP32_SDK_INCLUDE}/sdmmc"
    "${ESP32_SDK_INCLUDE}/smartconfig_ack"
    "${ESP32_SDK_INCLUDE}/soc"
    "${ESP32_SDK_INCLUDE}/spi_flash"
    "${ESP32_SDK_INCLUDE}/spiffs"
    "${ESP32_SDK_INCLUDE}/tcp_transport"
    "${ESP32_SDK_INCLUDE}/tcpip_adapter"
    "${ESP32_SDK_INCLUDE}/ulp"
    "${ESP32_SDK_INCLUDE}/vfs"
    "${ESP32_SDK_INCLUDE}/wear_levelling"
    "${ESP32_SDK_INCLUDE}/wifi_provisioning"
    "${ESP32_SDK_INCLUDE}/wpa_supplicant"
    "${ESP32_SDK_INCLUDE}/xtensa-debug-module"
    "${ESP32_SDK_INCLUDE}/esp-face"
    "${ESP32_SDK_INCLUDE}/esp32-camera"
    "${ESP32_SDK_INCLUDE}/esp-face"
    "${ESP32_SDK_INCLUDE}/fb_gfx"
    "${ESP32_DIR}/cores/esp32"
    "${ESP32_DIR}/variants/esp32"
    "./hamstermatrix")

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

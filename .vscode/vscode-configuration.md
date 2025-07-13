# vscode configuration

Configuration for cmake and vcpkg are done in the *.vscode\settings.json* file.

## Windows configuration

Here a sample of a windows configuration:

`{
    "cmake.configureArgs": [
        "-DVCPKG_APPLOCAL_DEPS=ON",
        "-DX_VCPKG_APPLOCAL_DEPS_INSTALL=ON",
        "-DVCPKG_MANIFEST_MODE=ON",
        "-DVCPKG_TARGET_TRIPLET=x64-windows"
    ],
    "vcpkg.general.enable": true,
    "vcpkg.target.hostTriplet": "x64-windows",
    "vcpkg.target.defaultTriplet": "x64-windows",
    "vcpkg.target.useStaticLib": false,
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    }
}`

## Linux configuration

Here a sample of a linux configuration:

`{
    "cmake.configureArgs": [
        "-DVCPKG_APPLOCAL_DEPS=ON",
        "-DX_VCPKG_APPLOCAL_DEPS_INSTALL=ON",
        "-DVCPKG_MANIFEST_MODE=ON",
        "-DVCPKG_TARGET_TRIPLET=x64-linux"
    ],
    "vcpkg.general.enable": true,
    "vcpkg.target.hostTriplet": "x64-linux",
    "vcpkg.target.defaultTriplet": "x64-linux",
    "vcpkg.target.useStaticLib": false,
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "/home/kesitem/.local/share/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
}`
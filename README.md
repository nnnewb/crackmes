# crackmes

simple CrackMes.

1. console, hard coded serial, no protection.
2. console, simple generated serial, no protection.
3. GUI, time based one time password (TOTP), hard coded secret, no protection.
4. **WIP** GUI, hard coded secret, hand write simple compress packer protected.

## requirements

download [LIEF](https://lief-project.github.io/download/) win32 version.

## build

`vcpkg` required.

```shell
vcpkg intall wxWidgets OpenSSL GTest
mkdir build
cmake .. -A Win32 -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg repo]/scripts/buildsystems/vcpkg.cmake" -DLIEF_DIR="[path to LIEF-0.11.5-win32]"
cmake --build . --config Release
```

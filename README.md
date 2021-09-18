# crackmes

simple CrackMes.

1. console, hard coded serial, no protection
2. console, simple generated serial, no protection
3. GUI, time based one time password (TOTP), hard coded secret, no protection

## build

`vcpkg` required.

```shell
vcpkg intall wxWidgets OpenSSL GTest
mkdir build
cmake .. -A Win32 -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg repo]/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

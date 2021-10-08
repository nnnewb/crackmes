# crackmes

simple CrackMes.

1. console, hard coded serial, no protection.
2. console, simple generated serial, no protection.
3. GUI, time based one time password (TOTP), hard coded secret, no protection.
4. **WIP** GUI, hard coded secret, hand write simple compress packer protected.

## requirements

download [LIEF](https://lief-project.github.io/download/) win32 version.

## build

debug variant for example.  `vcpkg` is required. see [vcpkg.io](https://vcpkg.io).

```shell
vcpkg install wxWidgets OpenSSL GTest
```

build LIEF from source.

```shell
git clone https://github.com/lief-project/LIEF.git
cd LIEF
mkdir build
cmake .. -G "Visual Studio 2019" -A Win32 -DCMAKE_BUILD_TYPE=Debug -DLIEF_PYTHON_API=off -DLIEF_USE_CRT_DEBUG=MDd
cmake --build . --config Debug --target LIB_LIEF
cmake --install . --config Debug --prefix LIEF-debug
mv LIEF-debug ../../ # crackmes/LIEF-debug
```

build crackmes

```shell
cd crackmes
mkdir build
cmake .. -A Win32 \
    -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg repo]/scripts/buildsystems/vcpkg.cmake" \
    -DLIEF_DIR="[absolute path to your LIEF build.]"

# eg.
#
# cmake .. \
#     -G "Visual Studio 2019" \
#     -A Win32 \
#     -DCMAKE_TOOLCHAIN_FILE="D:\vcpkg\scripts\buildsystems\vcpkg.cmake" \
#     -DLIEF_DIR="D:\crackmes\LIEF-debug"
#

cmake --build . --config Release
```

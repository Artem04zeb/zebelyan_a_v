cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/Users/artem/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
cmake --install build --prefix D:/Desktop/Flag_Connection

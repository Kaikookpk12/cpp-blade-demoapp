Commands to build locally (linux example)
```
git submodule update --init
cmake --preset linux-x64-debug
cmake --build --preset linux-x64-debug 
cp build/linux-x64-debug/_deps/hedera-sdk-cpp-build/openssl/lib64/*.a build/linux-x64-debug/_deps/hedera-sdk-cpp-build/openssl/lib
cmake --build --preset linux-x64-debug 
cd build/linux-x64-debug/Debug/
./demo-application
```
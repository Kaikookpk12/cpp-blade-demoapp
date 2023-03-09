
```
git submodule update --init
cmake --preset linux-x64-debug
cmake --build --preset linux-x64-debug 
build/linux-x64-debug/Debug/
./demo-application
```

`cmake --preset linux-x64-debug && cmake --build --preset linux-x64-debug && cd build/linux-x64-debug/Debug/ && ./demo-application`



cd vcpkg
git chechout 680071397677bb123b2f2b0ebe73905feae4a955
./bootstrap-vcpkg.sh

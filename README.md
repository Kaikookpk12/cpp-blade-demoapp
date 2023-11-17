# Blade-cpp SDK demo app

[<img src="./docs/demo.gif" width="70%">](https://www.youtube.com/watch?v=RIiEelrwWCA "Demo video")

## Disclaimer

As Blade-cpp SDK using https://github.com/hashgraph/hedera-sdk-cpp, which still in development there are limited functionality now. 

Cureently, please use ECDSA keys only

## Commands to build locally (macos example)

```
git submodule update --init
cmake --preset macos-arm64-release
cmake --build --preset macos-arm64-release
cd package/bin && ./demo-application
```

## main.cpp

In demo app used TerminalUI lib: https://github.com/ArthurSonzogni/FTXUI

In this app used basic components from FTXUI. 
App contains three tabs, menu, buttons and inputs.
Some demodata present to demonstrate some functions quickly. 
At the bottom of UI there is Output section, with execution time in ms an serialized output.
Also at the end of main() there are some more examples commented out, please check 

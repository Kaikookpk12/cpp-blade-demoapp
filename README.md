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
cd package/bin
./demo-application
```

# Examples exists in main(), please uncomment and check

# Execution output example

```
Demo application using BladeSDK
init: {dAppCode: "unitysdktest", network: "TESTNET", apiKey: Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE, visitorId: ad7257731c78437cd6abf9400e7ca15d2bbbd45df6a4892fa55cbd66fdebd2eb, sdkEnvironment: "CI", sdkVersion: Unity@0.6.4}
getAccountInfo: {accountId: "0.0.346533", evmAddress: "0x11f8d856ff2af6700ccda4999845b2ed4502d8fb", publicKey: "029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30"}
```
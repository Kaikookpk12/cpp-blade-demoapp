# Blade-cpp SDK demo app

## Disclaimer

As Blade-cpp SDK using https://github.com/hashgraph/hedera-sdk-cpp, which still in development there are limited functionality now. 

Cureently, please use ED25519 keys only

## Commands to build locally (linux example)

```
sudo apt-get install libgtest-dev
git submodule update --init
cmake --preset linux-x64-debug
cmake --build --preset linux-x64-debug 
cp build/linux-x64-debug/_deps/hedera-sdk-cpp-build/openssl/lib64/*.a build/linux-x64-debug/_deps/hedera-sdk-cpp-build/openssl/lib
cmake --build --preset linux-x64-debug 
cd build/linux-x64-debug/Debug/
./demo-application
```

# Execution output example

```
Demo application using BladeSDK
BladeSDK::init

BladeSDK::createAccount
Account Id: 0.0.3704198
SeedPhrase: sugar cake depend inflict squirrel trumpet guess pledge egg transfer chicken uncle
PrivateKey: B87B710E3D382E5AD334CC1920EC4A3206AB2C5C6F016958EB130CCFA8F1C466
Public key: 037A65073F864EB0D1373885864E8E34DA62DC9820FD00A05C42F92F01A9746D31

BladeSDK::transferHbars

BladeSDK::transferToken

BladeSDK::importAccount
Account Id: 0.0.3657386
SeedPhrase: bone govern tent wrong arrive miracle hurt bracket tomorrow urge pioneer gate
PrivateKey: 5AF278182C8646A09ACD8FD9A3131B8A83EFEC31B87B63CFD53E46794081614F
Public key: 021B55E5B276C53AFF49F5330F550CB6A48EE95D19E455E649811F56B4D1B36419

BladeSDK::signMessage
Signature (hex): 9826d46846ccb1f3024b716412a5e2dde9c0cae9959d71a7ef9d6b6c684f1918474fa555d26a09b00592790f678301042a56bd7c3bcfcaa08b0c65409059110a

BladeSDK::verifyMessage
On valid signature. Valid: 1
On invalid signature. Valid: 0
```
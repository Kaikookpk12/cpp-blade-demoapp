#include <iostream>
#include <BladeSDK.h>

int main(int argc, char *argv[])
{
    std::cout << "Demo application using BladeSDK" << std::endl;

    std::cout << "BladeSDK::init" << std::endl;
    BladeSDK::init("api-key", "TESTNET", "dAppCode", "6C9781BF-6B49-4182-B584-08F5EF28B224");
    std::cout << std::endl;

    std::cout << "BladeSDK::createAccount" << std::endl;
    BladeSDK::AccountData accountData = BladeSDK::createAccount("0.0.8298", "f38f262dbbb197a0b3aaff0cf76ea573a1185b5fe8e1cfe13c41efdc280b5073");
    BladeSDK::printAccount(accountData);
    std::cout << std::endl;

    std::cout << "BladeSDK::transferHbars" << std::endl;    
    // sender https://hashscan.io/testnet/account/0.0.8230
    // receiver https://hashscan.io/testnet/account/0.0.8299
    
    // // ecdsa (currenly have problems)
    // // BladeSDK::transferHbars("0.0.8235", "ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "0.0.8299", 1);
    
    // ED25519 Private key
    BladeSDK::transferHbars("0.0.8230", "1c1fc6ab4f5937bf9261cd3d1f1609cb5f30838d018207b476ff50d97ef8e2a5", "0.0.8299", 1);
    std::cout << std::endl;

    std::cout << "BladeSDK::transferToken" << std::endl;
    // JTT token https://hashscan.io/testnet/token/0.0.8323
    // sender https://hashscan.io/testnet/account/0.0.8235
    // receiver https://hashscan.io/testnet/account/0.0.8299
    BladeSDK::transferTokens("0.0.8323", "0.0.8230", "1c1fc6ab4f5937bf9261cd3d1f1609cb5f30838d018207b476ff50d97ef8e2a5", "0.0.8235", 1, false);
    std::cout << std::endl;


    // // std::cout << "BladeSDK::createAccountBlade" << std::endl;
    // // BladeSDK::printAccount(BladeSDK::createAccountBlade());


    std::cout << "BladeSDK::importAccount" << std::endl;
    BladeSDK::printAccount(BladeSDK::importAccount("bone govern tent wrong arrive miracle hurt bracket tomorrow urge pioneer gate"));
    std::cout << std::endl;

    std::cout << "BladeSDK::signMessage" << std::endl;
    // ED25519 Private key
    std::string signatureHex = BladeSDK::vectorToHex(BladeSDK::signMessage("test", "1c1fc6ab4f5937bf9261cd3d1f1609cb5f30838d018207b476ff50d97ef8e2a5"));
    std::cout << "Signature (hex): " << signatureHex << std::endl;
    std::cout << std::endl;

    std::cout << "BladeSDK::verifyMessage" << std::endl;
    // ED25519 Public key of previous private 
    bool valid = BladeSDK::verifyMessage("test", signatureHex, "90fcc00614bcd3a45cbcf4e02368bb0ecc99861111deb0799d0de63a1d4c734f");
    std::cout << "On valid signature. Valid: " << std::to_string(valid) << std::endl;

    valid = BladeSDK::verifyMessage("test", "DEADBEEF", "90fcc00614bcd3a45cbcf4e02368bb0ecc99861111deb0799d0de63a1d4c734f");
    std::cout << "On invalid signature. Valid: " << std::to_string(valid) << std::endl;          
}
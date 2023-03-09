#include <iostream>
#include <garydu.h>
#include <BladeSDK.h>

int main(int argc, char *argv[])
{
    std::cout << "Demo application using BladeSDK" << std::endl;
    
    Gary::Du::sayHello();

    std::cout << "BladeSDK::init" << std::endl;
    BladeSDK::init("api-key", "TESTNET", "dAppCode", "6C9781BF-6B49-4182-B584-08F5EF28B224");

    std::cout << "BladeSDK::createAccount" << std::endl;
    BladeSDK::AccountData accountData = BladeSDK::createAccount("0.0.8298", "f38f262dbbb197a0b3aaff0cf76ea573a1185b5fe8e1cfe13c41efdc280b5073");
    BladeSDK::printAccount(accountData);

    // std::cout << "BladeSDK::createAccountBlade" << std::endl;
    // BladeSDK::printAccount(BladeSDK::createAccountBlade());

    std::cout << "BladeSDK::importAccount" << std::endl;
    BladeSDK::printAccount(BladeSDK::importAccount("bone govern tent wrong arrive miracle hurt bracket tomorrow urge pioneer gate"));

    // std::cout << "BladeSDK::signMessage" << std::endl;
    // std::string signatureHex = BladeSDK::vectorToHex(BladeSDK::signMessage("test", "4A4935857096E9D97955800946A66F87DE35DA54EC9A91B7F316B20D2B334B3F"));
    // std::cout << "Signature (hex): " << signatureHex << std::endl;

    // std::cout << "BladeSDK::verifyMessage" << std::endl;
    // bool valid = BladeSDK::verifyMessage("test", "eee555e99410caa406d73ebf192dd88bee5623e14b77a0932cfdd517c0ff5d895a42508f54e10093ed378728c4f7a6ee2012193451a0a37b3df221ff8eb3d26b", "03D01617265176DCAD9EF9993A2B364D372E901530CAD667F25DA1E37F45CFAB77");
    // std::cout << "Valid signature: " << std::to_string(valid) << std::endl;          
}
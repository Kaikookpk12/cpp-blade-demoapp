#include <iostream>
#include <BladeSDK.h>

int main(int argc, char *argv[]) {
    try {
        std::string accountId = "0.0.346533";
        std::string accountId2 = "0.0.346530";
        std::string contractId = "0.0.416245";
        std::string tokenId = "0.0.433870";
        std::string privateKeyHex = "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b";
        std::string publicKeyHex = "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30";
        std::string dAppCode = "unitysdktest";
        std::string apiKey = "Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE";
        BladeSDK::SdkEnvironment sdkEnvironment = BladeSDK::SdkEnvironment::CI;
        BladeSDK::Network network = BladeSDK::Network::Testnet;

        std::cout << "Demo application using BladeSDK" << std::endl;

        BladeSDK::Blade blade = BladeSDK::Blade(apiKey, network, dAppCode, sdkEnvironment);
        std::cout << "init: " << blade << std::endl;
        

        // std::cout << "createAccountBlade: " << blade.createAccountBlade() << std::endl;
        
        std::cout << "getAccountInfo: " << blade.getAccountInfo(accountId) << std::endl;

        // std::cout << "getBalance: " << blade.getBalance(accountId) << std::endl;

        // std::cout << "importAccount: " << blade.importAccount("best soccer little verify love ladder else kick depth mesh silly desert", true) << std::endl; // ECDSA, 0.0.2018696

        // std::cout << "transferHbars: " << blade.transferHbars(accountId, privateKeyHex, accountId2, "15", "cpp-sdk-test") << std::endl;

        // std::cout << "transferTokens (paid): " <<  blade.transferTokens(tokenId, accountId, privateKeyHex, accountId2, "1", "cpp-sdk-paid-token-transfer", false) << std::endl;

        // std::cout << "transferTokens (blade pay): " <<  blade.transferTokens(tokenId, accountId, privateKeyHex, accountId2, "1", "cpp-sdk-blade-pay-token-transfer", true) << std::endl;
        
        // // sign + verify
        // std::string message = "hello";
        // std::string messageBase64 = BladeSDK::UtilService::stringToBase64(message);
        // std::string messageHex = BladeSDK::UtilService::vectorToHex(BladeSDK::UtilService::stringToVector(message));

        // BladeSDK::SignMessageData signature = blade.sign(message, privateKeyHex, "string");
        // std::cout << "Sign str (" << message << "): " << signature << std::endl;
        // std::cout << "Valid?: " << blade.signVerify(message, signature.signedMessage, publicKeyHex, "string") << std::endl;  

        // signature = blade.sign(messageBase64, privateKeyHex, "base64");
        // std::cout << "Sign base64 (" << messageBase64 << "): " << signature << std::endl;
        // std::cout << "Valid?: " << blade.signVerify(messageBase64, signature.signedMessage, publicKeyHex, "base64") << std::endl;

        // signature = blade.sign(messageHex, privateKeyHex, "hex");
        // std::cout << "Sign hex (" << messageHex << "): " << signature << std::endl;
        // std::cout << "Valid?: " << blade.signVerify(messageHex, signature.signedMessage, publicKeyHex, "hex") << std::endl;


        // contract call [paid]
        // ContractFunctionParameters params = ContractFunctionParameters().addString("cpp-sdk-test [self pay]");
        // std::cout << "Contract call: " << blade.contractCallFunction(contractId, "set_message", params, accountId, privateKeyHex, 150000, false) << std::endl;

        // contract call [Blade pay]
        // ContractFunctionParameters params = ContractFunctionParameters().addString("cpp-sdk-test [Blade pay]");
        // std::cout << "Contract call: " << blade.contractCallFunction(contractId, "set_message", params, accountId, privateKeyHex, 150000, true) << std::endl;


        // WIP
        // contract call query (self pay)
        // ContractFunctionParameters params = ContractFunctionParameters();
        // std::cout << "Contract call query: " << blade.contractCallQueryFunction(contractId, "get_message", params, accountId, privateKeyHex, 1500000, {"string", "int32"}) << std::endl;


        // delete account
        // BladeSDK::AccountData accountOperator = BladeSDK::AccountData {.accountId = accountId, .privateKey = privateKeyHex};
        // BladeSDK::AccountData accountToDelete = BladeSDK::AccountData {.accountId = "0.0.2577306", .privateKey = "3030020100300706052B8104000A04220420AF9B9915BE6A3B4BED77C127679939B5339A20B042196F870DB4191C4C472AF4"};
        // std::cout << "deleteAccount: " << blade.deleteAccount(accountToDelete.accountId, accountToDelete.privateKey, accountOperator.accountId, accountOperator.accountId, accountOperator.privateKey) << std::endl;
        
        
        // get C14 url
        // std::cout << "c14 url: " << blade.getC14url("karate", "0.0.123456", "1234") << std::endl;


        //get transaction history
        // BladeSDK::TransactionsHistoryData history = blade.getTransactions(accountId, "CRYPTOTRANSFER", "/api/v1/transactions?account.id=0.0.346533&limit=25&timestamp=lt:1695395474.219548003", 5);
        // std::cout << "getTransactions (CRYPTOTRANSFER)[" << history.transactions.size() << "]: " << history << std::endl;

        // BladeSDK::TransactionsHistoryData history = blade.getTransactions(accountId, "CRYPTOCREATEACCOUNT", "", 5);
        // std::cout << "getTransactions (CRYPTOCREATEACCOUNT)[" << history.transactions.size() << "]: " << history << std::endl;

        // BladeSDK::TransactionsHistoryData history = blade.getTransactions(accountId, "CRYPTODELETE", "", 2);
        // std::cout << "getTransactions (CRYPTODELETE)[" << history.transactions.size() << "]: " << history << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 0;
    } 
    return 0;
}
#include <iostream>
#include <chrono>
#include <BladeSDK.h>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

using namespace ftxui;
using namespace std::literals;

std::string statusTitle = "Output:";
std::string statusText = "[empty]";
long long startOperation = 0;


Component Text(const std::string& t) {
  return Renderer([t] { return text(t) | borderEmpty; });
}

void Output(std::string text) {
    statusTitle = "Output:";
    if (text == "") {
        statusText = "L O A D I N G . . .";
        startOperation = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    } else {
        if (statusText == "L O A D I N G . . .") {
            long long elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count() - startOperation;

            statusTitle = "Output (" + std::to_string(elapsedTime) + "ms):";
        }
        statusText = text;
    }
    
}

int main(int argc, char *argv[]) {    
    std::string accountId = "0.0.346533";
    std::string accountId2 = "0.0.346530";
    std::string contractId = "0.0.416245";
    std::string tokenId = "0.0.433870";
    std::string privateKeyHex = "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b";
    std::string publicKeyHex = "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30";
    std::string dAppCode = "unitysdktest";
    std::string apiKey = "GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv";
    BladeSDK::SdkEnvironment sdkEnvironment = BladeSDK::SdkEnvironment::CI;
    BladeSDK::Network network = BladeSDK::Network::Testnet;
    std::unique_ptr<BladeSDK::Blade> bladePtr;
    int shift = 0;    

    std::vector<std::string> tabTitles{"Init", "Examples", "..."};
    int tabSelected = 0;
    auto option = MenuOption::HorizontalAnimated();
    option.underline.follower_delay = 250ms;
    auto tabs = Menu(&tabTitles, &tabSelected, option);

    
    //////////////////////////////////
    //////////// INIT TAB ////////////
    //////////////////////////////////
    Component input_dAppCode = Input(&dAppCode, "dAppCode");
    Component input_apiKey = Input(&apiKey, "apiKey");

    std::vector<std::string> networkEntries = {"Testnet", "Mainnet"};
    int networkSelected = 0;
    Component dropdown_network = Dropdown(&networkEntries, &networkSelected) | borderEmpty;

    std::vector<std::string> bladeEnvEntries = {"CI", "Prod"};
    int bladeEnvSelected = 0;
    Component dropdown_bladeEnv = Dropdown(&bladeEnvEntries, &bladeEnvSelected);

    Component input_accountId = Input(&accountId, "0.0.12345");
    Component input_privateKey = Input(&privateKeyHex, "3030020100300706052b...");
    Component input_contractId = Input(&contractId, "0.0.12345");
    Component input_tokenId = Input(&tokenId, "0.0.12345");

    auto btn_initBlade = Button("Init", [&] { 
        Output("");

        if (!bladePtr) {
            // Initialize the bladePtr if not already done

            if (networkSelected == 0) {
                network = BladeSDK::Network::Testnet;
            } else {
                network = BladeSDK::Network::Mainnet;
            }

            if (bladeEnvSelected == 0) {
                sdkEnvironment = BladeSDK::SdkEnvironment::CI;
            } else {
                sdkEnvironment = BladeSDK::SdkEnvironment::Prod;
            }

            try {
                bladePtr = std::make_unique<BladeSDK::Blade>(apiKey, network, dAppCode, sdkEnvironment);

                std::ostringstream os;    
                os << bladePtr->getInfo();
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade already initialized");
        }
    }, ButtonOption::Animated(Color::Green));
    
    auto btn_stopBlade = Button("Stop", [&] { 
        Output("");
        bladePtr = nullptr;
        Output("Blade stopped");
    }, ButtonOption::Animated(Color::Red));


    auto component_init = Container::Vertical({
        input_dAppCode,
        input_apiKey,
        dropdown_network,
        dropdown_bladeEnv,
        input_accountId,
        input_privateKey,
        input_contractId,
        input_tokenId,
        Container::Horizontal({
            btn_initBlade,
            btn_stopBlade
        }),
    });

    auto initTabRenderer = Renderer(component_init, [&] {
        return vbox({
            hbox(text(" dAppCode   : "), input_dAppCode->Render()),
            hbox(text(" ApiKey     : "), input_apiKey->Render()),
            hbox(text(" Network    : "), dropdown_network->Render()),
            hbox(text(" Blade env  : "), dropdown_bladeEnv->Render()),
            separator(),
            hbox(text(" accountId  : "), input_accountId->Render()),
            hbox(text(" privateKey : "), input_privateKey->Render()),
            hbox(text(" contractId : "), input_contractId->Render()),
            hbox(text(" tokenId    : "), input_tokenId->Render()),
            separator(),
            hbox({
                btn_initBlade->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_stopBlade->Render() | xflex_grow,
            }),
            separator(),
            //    text("Hello " + dAppCode + " " + apiKey),
            window(text(statusTitle), paragraphAlignLeft(statusText)),
        });
    });


    //////////////////////////////////
    ////////// EXAMPLES TAB //////////
    //////////////////////////////////

    std::string amount = "5";
    std::string mnemonicMessageSignature = "target waste stamp attend toss elephant cause citizen detail public click baby";

    Component input_accountIdEx = Input(&accountId, "0.0.12345");
    Component input_mnemonicMessageSignature = Input(&mnemonicMessageSignature, "Mnemonic / Message / Signature");
    Component input_receiverId = Input(&accountId2, "0.0.12345");
    Component input_amount = Input(&amount, "5");
    BladeSDK::AccountData createdAccount;



    auto btn_getBalance = Button("Get balance", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;    
                os << bladePtr->getBalance(accountId);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_getTransactions = Button("Get transactions", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;    
                os << bladePtr->getTransactions(accountId, "CRYPTOTRANSFER", "", 5);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_createAccount = Button("Create account", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                createdAccount = bladePtr->createAccountBlade();
                os << createdAccount;
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_deleteAccount = Button("Delete account", [&] { 
        Output("");
        if (bladePtr) {
            if (createdAccount.accountId != "") {
                try {
                    std::ostringstream os;  
                    os << bladePtr->deleteAccount(createdAccount.accountId, createdAccount.privateKey, accountId, accountId, privateKeyHex);
                    createdAccount = {};
                    Output(os.str());
                } catch (const std::exception& e) {
                    Output(e.what());
                } 
            } else {
                Output("Account not created");
            }
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Red));

    auto btn_fromMnemonic = Button("From mnemonic", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                os << bladePtr->importAccount(mnemonicMessageSignature, true);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_sign = Button("Sign", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                BladeSDK::SignMessageData signature = bladePtr->sign(mnemonicMessageSignature, privateKeyHex, "string");
                mnemonicMessageSignature = signature.signedMessage;
                os << signature;
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_verify = Button("Verify", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                os << bladePtr->signVerify("hello", mnemonicMessageSignature, publicKeyHex, "string");
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_contractCall = Button("Contract call", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                ContractFunctionParameters params = ContractFunctionParameters().addString(mnemonicMessageSignature);
                os << bladePtr->contractCallFunction(contractId, "set_message", params, accountId, privateKeyHex, 150000, false);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_contractQuery = Button("Contract query", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                ContractFunctionParameters params = ContractFunctionParameters();
                ContractFunctionResult res = bladePtr->contractCallQueryFunction(contractId, "get_message", params, accountId, privateKeyHex, 50000, 1.5, {"string", "int32"});
                os << "Contract call query. string: " << res.getString(0) << ", int32: " << std::to_string(res.getInt32(1)) << std::endl;;
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_sendHbars = Button("Send HBARs", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                os << bladePtr->transferHbars(accountId, privateKeyHex, accountId2, amount, mnemonicMessageSignature);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));

    auto btn_sendTokens = Button("Send tokens", [&] { 
        Output("");
        if (bladePtr) {
            try {
                std::ostringstream os;  
                os << bladePtr->transferTokens(tokenId, accountId, privateKeyHex, accountId2, amount, mnemonicMessageSignature, false);
                Output(os.str());
            } catch (const std::exception& e) {
                Output(e.what());
            } 
        } else {
            Output("Blade not initialized");
        }
    }, ButtonOption::Animated(Color::Green));




    auto component_examples = Container::Vertical({
        Container::Horizontal({
            input_accountIdEx,
            btn_getBalance,
            btn_getTransactions
        }),
        Container::Horizontal({
            btn_createAccount,
            btn_deleteAccount
        }),
        input_mnemonicMessageSignature,
        Container::Horizontal({
            btn_fromMnemonic,
            btn_sign,
            btn_verify
        }),
        Container::Horizontal({
            btn_contractCall,   
            btn_contractQuery
        }),
        Container::Horizontal({
            input_receiverId,
            input_amount,
            btn_sendHbars,   
            btn_sendTokens
        }),
    });

    auto exampleTabRenderer = Renderer(component_examples, [&] {
        return vbox({ 
            hbox({
                window(text("Account id:"), input_accountIdEx->Render()) | xflex_grow,
                btn_getBalance->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_getTransactions->Render() | xflex_grow
            }),
            separator(),
            hbox({
                btn_createAccount->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_deleteAccount->Render() | xflex_grow
            }),
            window(text("Mnemonic / message / signature:"), input_mnemonicMessageSignature->Render()),
            hbox({
                btn_fromMnemonic->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_sign->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_verify->Render() | xflex_grow
            }),
            separator(),
            hbox({
                btn_contractCall->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_contractQuery->Render() | xflex_grow
            }),
            separator(),
            hbox({
                window(text("Receiver id:"), input_receiverId->Render()) | xflex_grow,
                window(text("Amount:"), input_amount->Render()) | xflex_grow,
                btn_sendHbars->Render() | xflex_grow,
                separator() | borderEmpty,
                btn_sendTokens->Render() | xflex_grow
            }),
            separator(),
            window(text(statusTitle), paragraphAlignLeft(statusText)),
        });  
    });


    //////////////////////////////////
    /////////// OTHER TAB ////////////
    //////////////////////////////////    

    auto spinner_tab_renderer = Renderer([&] {
        Elements entries;
        entries.push_back(spinner(21, shift) | bold | border | center);
        return hbox(std::move(entries)) | center | size(WIDTH, GREATER_THAN, 80) | size(HEIGHT, GREATER_THAN, 200);
    });



    //////////////////////////////////
    ////////////// APP ///////////////
    //////////////////////////////////    

    auto tabsContainer = Container::Tab({
        initTabRenderer,
        exampleTabRenderer,
        spinner_tab_renderer,
    }, &tabSelected);


    auto components = CatchEvent(Container::Vertical({ tabs, tabsContainer }), [&](const Event &e) {
        if (e.is_character()) { /* app.on_key_up(); */ }
        return false;
    });

    auto appRenderer = Renderer(components, [&] {
        return vbox({ center(text("C++ Blade SDK demo")) ,
            separator(),
            tabs->Render(),
            tabsContainer->Render(),
        }) | border;
    });

    auto screen = ScreenInteractive::Fullscreen();
    std::atomic<bool> refresh_ui_continue = true;
    std::thread refresh_ui([&] {
        while (refresh_ui_continue) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1.0s / 10.0);// NOLINT magic numbers
            shift++;
            screen.PostEvent(Event::Custom);
        }
    });
    screen.Loop(appRenderer);
    refresh_ui_continue = false;
    refresh_ui.join();


    // std::cout << "Other examples" << std::endl;

    // BladeSDK::Blade blade = BladeSDK::Blade(apiKey, network, dAppCode, sdkEnvironment);
    // std::cout << "init: " << blade << std::endl;
    
    // std::cout << "createAccountBlade: " << blade.createAccountBlade() << std::endl;
    
    // std::cout << "getAccountInfo: " << blade.getAccountInfo(accountId) << std::endl;

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

    // contract call query (self pay)
    // ContractFunctionParameters params = ContractFunctionParameters();
    // ContractFunctionResult res = blade.contractCallQueryFunction(contractId, "get_message", params, accountId, privateKeyHex, 50000, 1.5, {"string", "int32"});
    // std::cout << "Contract call query. string: " << res.getString(0) << ", int32: " << std::to_string(res.getInt32(1)) << std::endl;


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



    return 0;
}

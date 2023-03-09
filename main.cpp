#include <iostream>
#include <garydu.h>
#include <main.h>

int main(int argc, char *argv[])
{
    std::cout << "base application message" << std::endl;
    Gary::Du::sayHello();

    BladeSDK::init("api-key", "TESTNET", "dAppCode", "6C9781BF-6B49-4182-B584-08F5EF28B224");
    BladeSDK::printAccount(BladeSDK::createAccount("0.0.8298", "f38f262dbbb197a0b3aaff0cf76ea573a1185b5fe8e1cfe13c41efdc280b5073"));
          
}
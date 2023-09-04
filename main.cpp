#include <iostream>
#include <garydu.h>
#include <visitorId.h>

int main(int argc, char *argv[])
{
    Gary::Du::sayHello();

    Gary::VisitorId visitorId("finger print public key");
   
    std::cout << "Get fingerprint demo: " << visitorId.getVisitorId() << std::endl;
}
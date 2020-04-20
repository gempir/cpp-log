#include <iostream>
#include <cpr/cpr.h>
#include "gempir.h"

int main() {
    std::cout << GEMPIR << std::endl;

    auto r = cpr::Get(cpr::Url{"https://gist.githubusercontent.com/fourtf/eb2c086f7639bb9f5a740dc7c2c40753/raw/cada2f7e1c56fc73439be2a7656d03203800d224/.txt"});
    // r.status_code;
    // r.headers["content-type"];

    std::cout << "CURL result: " << r.text;

    return 0;
}
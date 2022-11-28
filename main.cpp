#include <iostream>
#include "ump.h"

int main() {
    auto msg = showSms("114514");
    std::cout << "短信：" << msg << std::endl;
    int ret = sendCode("13533353653", "114514");
    return ret;
}

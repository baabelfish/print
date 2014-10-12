#include "../print.hpp"
#include <vector>

using namespace pr;

int main() {
    std::unordered_multiset<int> a{1,2,3};
    print(1, 2, 3);
    print(1, 2, a);
    print(1, 2, Bg::Red, 3, Ansi::Reset, Fg::Green, "terve");
    log("morjens");
    logWarning("morjens");
    logError("morjens");
    logFatal("morjens");
    LOG("morjens");
    LOGWarning("morjens");
    LOGFatal("morjens");
    return 0;
}

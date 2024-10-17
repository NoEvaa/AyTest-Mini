#include <aytestm.hpp>
#include <iostream>

#define AA(macro, ...) 
#define CHECK(...)

// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890


int main()
{
    auto ei = AYTTM_EXPRINFO(1 < 2);
    std::cout << ei.expression() << std::endl;

    std::cout << ei() << std::endl;

    auto sl = AYTTM_SRC_LOC;
    std::cout << sl.file_name() << std::endl;
    std::cout << sl.line() << std::endl;
    std::cout << 0 << std::endl;
    return 0;
}


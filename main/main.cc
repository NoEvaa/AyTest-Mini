#include <aytestm.hpp>
#include <iostream>

#define AA(macro, ...) 
#define CHECK(...)

#define AYTTM_SRC_LOC std::source_location().current()

int main()
{
    auto sl = AYTTM_SRC_LOC;
    std::cout << sl.file_name() << std::endl;
    std::cout << sl.line() << std::endl;
    std::cout << 0 << std::endl;
    return 0;
}


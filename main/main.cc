#include <aytestm.hpp>
#include <iostream>


// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890



TEST_CASE("case 1") {

}

int main()
{
    using namespace aytest_mini;
    auto AYTTM_BUILTIN(expr) = TestExpr(AYTTM_EXPRINFO_BOOL(1 < 2))
            .bindEval(EvalInfo(nullptr, "THROW"))
            .bindHandler(EvalInfo(nullptr, "CHECK"));
    std::cout << AYTTM_BUILTIN(expr) << std::endl;

    TestContext::run();
    return 0;
}


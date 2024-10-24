#include <aytestm.hpp>
#include <iostream>


// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

namespace aytest_mini {
}

class AYTTM_BUILTIN(TestCase1) : public aytest_mini::TestCase {
public:
    void AYTTM_BUILTIN(runImpl)() override;
};
namespace {
static int AYTTM_BUILTIN(s_i_TestCase1) =
    aytest_mini::initTestCase<AYTTM_BUILTIN(TestCase1)>("case 1", AYTTM_SRC_LOC);
}
void AYTTM_BUILTIN(TestCase1)::AYTTM_BUILTIN(runImpl)() {
    this->AYTTM_BUILTIN(invokeExpr)(
        aytest_mini::TestExpr(AYTTM_EXPRINFO_BOOL(1 < 2))
            .bindEval(aytest_mini::EvalInfo(nullptr))
            .bindHandler(aytest_mini::EvalInfo(nullptr)),
        AYTTM_SRC_LOC
    );
}



int main()
{
    using namespace aytest_mini;
    auto AYTTM_BUILTIN(expr) = TestExpr(AYTTM_EXPRINFO_BOOL(1 < 2))
            .bindEval(EvalInfo(nullptr, "THROW"))
            .bindHandler(EvalInfo(nullptr, "CHECK"));
    std::cout << AYTTM_BUILTIN(expr) << std::endl;

    AYTTM_BUILTIN(TestCase1) tcase;
    tcase.__A_Y_T_E_S_T_M__builtin__setName("case 1");
    tcase.__A_Y_T_E_S_T_M__builtin__setSrcLoc(AYTTM_SRC_LOC);
    std::cout << tcase << std::endl;

    return 0;
}


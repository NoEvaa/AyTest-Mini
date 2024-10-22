#include <aytestm.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <source_location>

#include <algorithm>

// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

namespace aytest_mini {
class TestGroup {
public:
    void run() {
        for (auto & tcase : m_cases) {
            try {
                tcase->AYTTM_BUILTIN(run)();
            } catch (...) {

            }
        }
    }

    void appendCase(std::shared_ptr<TestCase> p_tc) {
        assert(p_tc);
        m_cases.push_back(p_tc);
    }
private:
    TestCases m_cases;
};


class TestContext {
public:
    //static void run();

    static TestGroup & getGroup() {
        static TestGroup s_group;
        return s_group;
    }
private:
    std::ostream * m_p_ost = nullptr;
};


class AYTTM_BUILTIN(TestCase1) : public TestCase {
public:
    void AYTTM_BUILTIN(run)() override;
};

namespace detail {
template <typename T>
int initTestCase(char const * p_name, std::source_location const & src_loc) {
    auto p_tcase = std::make_shared<T>();
    p_tcase->AYTTM_BUILTIN(setName)(p_name);
    p_tcase->AYTTM_BUILTIN(setSrcLoc)(src_loc);
    TestContext::getGroup().appendCase(std::static_pointer_cast<TestCase>(p_tcase));
    return 0;
}
}

namespace {
static int AYTTM_BUILTIN(s_i_TestCase1) =
    aytest_mini::detail::initTestCase<AYTTM_BUILTIN(TestCase1)>("case 1", AYTTM_SRC_LOC);
}
void AYTTM_BUILTIN(TestCase1)::AYTTM_BUILTIN(run)() {
    [&](){
        using namespace aytest_mini;
        auto AYTTM_BUILTIN(src_loc) = AYTTM_SRC_LOC;
        auto AYTTM_BUILTIN(expr) = TestExpr(AYTTM_EXPRINFO_BOOL(1 < 2))
            .bindEval(EvalInfo{nullptr})
            .bindHandler(HandlerInfo{nullptr});
        //auto & AYTTM_BUILTIN(ost)= this->getStream();
        try {
            if (!AYTTM_BUILTIN(expr).run()) {

            }
        } catch (TestTermination const & e) {
        } catch (std::exception const & e) {
        }
    }();
}


}

int main()
{
    using namespace aytest_mini;
    auto AYTTM_BUILTIN(expr) = TestExpr(AYTTM_EXPRINFO_BOOL(1 < 2))
            .bindEval(EvalInfo{nullptr, "THROW"})
            .bindHandler(HandlerInfo{nullptr, "CHECK"});
    AYTTM_BUILTIN(expr).outputToStream(std::cout) << std::endl;

    auto sl = AYTTM_SRC_LOC;
    std::cout << sl.file_name() << std::endl;
    std::cout << sl.line() << std::endl;
    std::cout << 0 << std::endl;
    return 0;
}


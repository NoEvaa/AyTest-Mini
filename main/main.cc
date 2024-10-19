#include <aytestm.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <source_location>

#include <algorithm>

#define AA(macro, ...) 
#define CHECK(...)

// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

namespace aytest_mini {
class TestContext;
bool testNoThrow(ExprInfo const & einfo) {
    try {
        einfo();
    } catch (TestException const & e) {
        return false;
    } catch (...) {
        return false;
    }
    return true;
}


class TestCase {
public:
    virtual ~TestCase() = default;

    void setSrcLoc(std::source_location const & src_loc) {
        m_src_loc = src_loc;
    }
    
    void bindStream(std::ostream & ost) {
        m_p_ost = &ost;
    }
    void unbindStream() {
        m_p_ost = nullptr;
    }
    std::ostream & getStream() {
        assert(m_p_ost);
        return *m_p_ost;
    }

    virtual void run() = 0;

private:
    std::ostream * m_p_ost;

    std::source_location m_src_loc;
};

using TestCases = std::vector<std::shared_ptr<TestCase>>;

TestCases &  getTestCases() {
    static TestCases s_test_cases;
    return s_test_cases;
}

class __aytestm__builtin__TestCase1 : public TestCase {
public:
    void run() override;
};
namespace {
static int __aytestm__builtin__i__TestCase1 = [](){
    auto p_tcase = std::make_shared<__aytestm__builtin__TestCase1>();
    p_tcase->setSrcLoc(AYTTM_SRC_LOC);
    getTestCases().push_back(std::static_pointer_cast<TestCase>(p_tcase));
    return 0;
}();
}
void __aytestm__builtin__TestCase1::run() {
    [&](){
        using namespace aytest_mini;
        auto __aytestm__builtin__src_loc = AYTTM_SRC_LOC;
        auto __aytestm__builtin__expr = TestExpr(AYTTM_EXPRINFO(1 < 2))
            .bindEval(EvalInfo{nullptr})
            .bindHandler(HandlerInfo{nullptr});
        auto & __aytestm__builtin__ost = this->getStream();
        try {
            if (!__aytestm__builtin__expr.run()) {
            }
        } catch (TestTermination const & e) {
        } catch (std::exception const & e) {
            e.what();
        }
    }();
}
}

int main()
{

    auto ei = AYTTM_EXPRINFO(1 < 2);
    std::cout << ei.info() << std::endl;

    std::cout << ei() << std::endl;

    auto sl = AYTTM_SRC_LOC;
    std::cout << sl.file_name() << std::endl;
    std::cout << sl.line() << std::endl;
    std::cout << 0 << std::endl;
    return 0;
}


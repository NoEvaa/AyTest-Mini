#include <aytestm.hpp>
#include <functional>
#include <iostream>
#include <source_location>

#include <algorithm>

#define AA(macro, ...) 
#define CHECK(...)

// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

namespace aytest_mini {
class TestContext;
class TestCase {
public:
    void bindStream(std::ostream & ost) {
        m_p_ost = &ost;
    }

    std::ostream & getStream() {
        assert(m_p_ost);
        return *m_p_ost;
    }

void run() {

    [&](){
        using namespace aytest_mini;
        auto src_loc = AYTTM_SRC_LOC;
        auto expr = TestExpr(AYTTM_EXPRINFO(1 < 2))
            .bindEval(EvalInfo{nullptr})
            .bindHandler(HandlerInfo{nullptr});
        auto & ost = this->getStream();
        try {
            expr.run();
        } catch (TestFailure const & e) {
            e.what();
        } catch (std::exception const & e) {
            e.what();
        }
    }();


    }
private:
    std::ostream * m_p_ost;
};

bool testNoThrow(ExprInfo const & einfo) {
    try {
        einfo();
    } catch (TestFailure const & e) {
        return false;
    } catch (...) {
        return false;
    }
    return true;
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


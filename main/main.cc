#include <aytestm.hpp>
#include <stdexcept>

TEST_CASE("check true") {
    CHECK(true);
}
TEST_CASE("check false") {
    CHECK(false);
}
TEST_CASE("check") {
    CHECK(0 < 1);
    CHECK(0 > 1);
}
TEST_CASE("require true") {
    REQUIRE(true);
}
TEST_CASE("require false") {
    REQUIRE(false);
}
TEST_CASE("require") {
    REQUIRE(0 < 1);
    REQUIRE(0 > 1);
    CHECK(false);
}
namespace {
inline void throwTest() {
    throw std::runtime_error{"throw test"};
}
inline void nothrowTest() {}
}
TEST_CASE("check throw") {
    CHECK_THROW(throwTest());
    CHECK_THROW(nothrowTest());
}
TEST_CASE("require throw") {
    REQUIRE_THROW(throwTest());
    REQUIRE_THROW(nothrowTest());
    CHECK(false);
}
TEST_CASE("check nothrow") {
    CHECK_NOTHROW(nothrowTest());
    CHECK_NOTHROW(throwTest());
}
TEST_CASE("require nothrow") {
    REQUIRE_NOTHROW(nothrowTest());
    REQUIRE_NOTHROW(throwTest());
    CHECK(false);
}
TEST_CASE("check throw as") {
    CHECK_THROW_AS(std::string, throwTest());
    CHECK_THROW_AS(std::runtime_error, throwTest());
}
TEST_CASE("require throw as") {
    REQUIRE_THROW_AS(std::runtime_error, throwTest());
    REQUIRE_THROW_AS(std::string, throwTest());
    CHECK(false);
}

int main()
{
    aytest_mini::detail::Locksmith ls;
    int mn = 3;
    do {
        for (int i = 0;i<mn;++i){
            std::cout << ls.unlocking() << std::endl;
        }
        std::cout << std::endl;
    } while (ls.nextKey());
    //aytest_mini::TestContext::run();
    return 0;
}


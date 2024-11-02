# Ayin Test - Mini

AyTest-Mini 是一个轻量的、现代的、仅头文件的单元测试框架，可用于C++20以及更高版本。
它仅包含了实现单元测试所需的最少代码。

该框架目前已经完全完成，无计划加入其他新功能。
如果您希望获取更多功能，请考虑使用[其他测试框架](#友情链接)。

## 适用场景

- 中小型模块单元测试

- 教学目的

## 快速开始

要想使用该模块，您仅需下载最新版本的头文件并将其包含到您的源码文件中（或者直接将该仓库作为您项目的一个子模块）。

### 一个简单例子

假设我们有一个函数`pow2`需要被测试：

```c++
#define AYTESTM_CONFIG_MAIN
#include "aytestm.hpp"

int pow2(int x) { return x * x; }

TEST_CASE("case 1") {
    CHECK(pow2(1) == 1);
    CHECK(pow2(2) == 4);
    CHECK(pow2(10) == 100);
    CHECK(pow2(1) + 1 == 3);
    CHECK_THROWS(pow2(0));
}
```

这段代码会编译为一个完整的可执行程序。
如果运行它，它将执行所有测试用例（在本例中，只有一个），
然后报告任何失败以及通过和失败的测试数量。
在编译和运行后能够看到两个测试失败项。
输出结果如下所示：

```
AyTest-Mini v1.0.0

--------------------------------------------------------------------------------
../../../tests/main.test.cc(6):
TEST CASE: case 1 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

../../../tests/main.cc(10): FAILED:
    CHECK( pow2(1) + 1 == 3 )

../../../tests/main.cc(11): FAILED:
    CHECK_THROWS( pow2(0) )
No exception thrown.

================================================================================
test cases:     1 |    1 failed 
assertions:     4 |    3 passed |    1 failed
```

## 教程

### 测试用例宏

- **TEST_CASE( case name, ... )**

任何断言表达式必须被定义在一个测试用例中。
在一个可执行程序中可以有任意数量的测试用例。

```c++
TEST_CASE("case 1") {
    assertion expression
    assertion expression
    assertion expression
}
```

- **SECTION( ... )**

一个测试用例每次运行时只会执行其中的一个`section`，
测试用例会被重复运行直至所有有效的`section`被执行。

请注意本模块中的`section`不能够被嵌套或处于循环内！

```c++
TEST_CASE("") {
    assertion expression
    SECTION("S1") {
        assertion expression
        assertion expression
    }
    SECTION("S2") {
        assertion expression
        assertion expression
    }
    assertion expression
}
```

### 断言宏

`REQUIRE`系列宏会对表达式进行测试，在表达式断言失败后会中断测试用例。

`CHECK`系列宏同样测试表达式，但即使断言失败，测试用例仍将继续运行。

- **CHECK( expression )**
- **REQUIRE( expression )**

执行表达式并检查结果是否为真。
如果一个异常被抛出，它将会被捕获、报告并计为失败。

请注意表达式应该返回一个布尔值。

```c++
CHECK( 1 + 1 == 2 );
REQUIRE( 1 + 1 != 0 );
```

- **CHECK_NOTHROW( expression )**
- **REQUIRE_NOTHROW( expression )**

预期表达式在执行期间不会抛出异常。

```c++
CHECK_NOTHROW( [](){}() );
REQUIRE_NOTHROW( [](){}() );
```

- **CHECK_THROWS( expression )**
- **REQUIRE_THROWS( expression )**

预期表达式在执行期间会抛出（任何类型）异常。

```c++
CHECK_THROWS( [](){ throw int{0}; }()) );
REQUIRE_THROWS( [](){ throw int{0}; }()) );
```

- **CHECK_THROWS_AS( exception type, expression )**
- **REQUIRE_THROWS_AS( exception type, expression )**

预期表达式在执行期间会抛出指定类型的异常。

```c++
CHECK_THROWS_AS( int, [](){ throw int{0}; }() );
REQUIRE_THROWS_AS( int, [](){ throw int{0}; }()) );
```

### 编译时配置

配置宏需要定义在引入头文件前。

- 生成默认主函数

该选项能用于自动生成一个主函数。

```c++
#define AYTESTM_CONFIG_MAIN
```

- 禁用 ANSI 颜色码

该选项能用于禁用 ANSI 颜色码的输出。

```c++
#define AYTESTM_DISABLE_ANSI_COLOR
```

- 禁用测试宏

该选项能用于禁用测试宏。

```c++
#define AYTESTM_DISABLE_TEST_MACRO
```

### 更多

或许你可以去阅读[Catch2文档](https://catch2-temp.readthedocs.io/en/latest/index.html)。

## 友情链接

- [AyTest](https://github.com/NoEvaa/AyTest)

- [Catch2](https://github.com/catchorg/Catch2)

- [doctest](https://github.com/doctest/doctest)

- [googletest](https://github.com/google/googletest)

## 作者

- [@NoEvaa](https://github.com/NoEvaa)

## 许可证

[MIT](LICENSE)


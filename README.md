# Ayin Test - Mini

AyTest-Mini is a lightest modern header-only unit testing framework for C++20 and later.
It only contains the minimum code quantity required to implement unit testing.

This framework is now fully completed and no further features will be added.
If you need more features, please consider using other testing frameworks.

## Quick Start

To get started, all you need is to download the latest version which is just a single header 
and include it in your source files (or add this repository as a git submodule).

### A simple example

Suppose we have a `pow2` function that we want to test:

```c++
#define AYTESTM_CONFIG_MAIN
#include "aytestm.hpp"

int pow2(int x) { return x * x; }

TEST_CASE("case 1") {
    CHECK(pow2(1) == 1);
    CHECK(pow2(2) == 4);
    CHECK(pow2(10) == 100);
}
```

## Tutorial

### Testing Case Macros

- **TEST_CASE( case name, ... )**

```c++
TEST_CASE("case 1") {
    assertion expression
    assertion expression
    assertion expression
}
```

- **SECTION(...)**

```c++
TEST_CASE("") {
    SECTION("S1") {
        assertion expression
        assertion expression
    }
    SECTION("S2") {
        assertion expression
        assertion expression
    }
}
```

### Assertion Macros

The `REQUIRE` family of macros tests an expression and aborts the test case if it fails.
The `CHECK` family are equivalent but execution continues in the same test case even if the assertion fails.

- **CHECK( expression )**
- **REQUIRE( expression )**

Evaluates the expression and check if the result is true.
If an exception is thrown, it is caught, reported, and counted as a failure.

Note that the expression should return a boolean value.

```c++
CHECK( 1 + 1 == 2 );
REQUIRE( 1 + 1 != 0 );
```

- **CHECK_NOTHROW( expression )**
- **REQUIRE_NOTHROW( expression )**

Expects that no exception is thrown during evaluation of the expression.

```c++
CHECK_NOTHROW( [](){}() );
REQUIRE_NOTHROW( [](){}() );
```

- **CHECK_THROWS( expression )**
- **REQUIRE_THROWS( expression )**

Expects that an exception (of any type) is be thrown during evaluation of the expression.

```c++
CHECK_THROWS( [](){}( throw int{0}; ) );
REQUIRE_THROWS( [](){}( throw int{0}; ) );
```

- **CHECK_THROWS_AS( exception type, expression )**
- **REQUIRE_THROWS_AS( exception type, expression )**

Expects that an exception of the specified type is thrown during evaluation of the expression.

```c++
CHECK_THROWS_AS( int, [](){}( throw int{0}; ) );
REQUIRE_THROWS_AS( int, [](){}( throw int{0}; ) );
```

### Compile-time Configuration

Macros need to be defined before including the header file.

#### Generating default main function

This option can be used to generate a main function automatically.

```c++
#define AYTESTM_CONFIG_MAIN
```

#### Disabling ANSI color

This option can be used to disable the output of ANSI color code.

```c++
#define AYTESTM_DISABLE_ANSI_COLOR
```

#### Disabling testing macros 

This option can be used to disable the testing macros.

```c++
#define AYTESTM_DISABLE_TEST_MACRO
```

### More

Maybe you can read [Catch2 documentation](https://catch2-temp.readthedocs.io/en/latest/index.html) instead.

## Friendship Link

- [AyTest](https://github.com/NoEvaa/AyTest)

- [catch2](https://github.com/catchorg/Catch2)

- [doctest](https://github.com/doctest/doctest)

- [googletest](https://github.com/google/googletest)

## Authors

- [@NoEvaa](https://github.com/NoEvaa)

## License

[MIT](LICENSE)


#ifndef COMMON_H
#define COMMON_H
#include <memory>

class Base
{
public:
    Base() {
        exist = true;
    }
    ~Base() {
        exist = false;
    }
    static bool exist;// init in autoptr.cpp
    int value = 0;
};

class User
{
public:
#if __cplusplus <= 201402L// 仅在 c++14 版本之前 使用auto_ptr
    void funcPassAutoPtr(std::auto_ptr<Base> basep) {
    }
#endif
    void funcPassUniquePtr(std::unique_ptr<Base> &basep) {
    }
    void funcPassSharedPtrValue(std::shared_ptr<Base> basep) {
    }
    void funcPassSharedPtrRef(std::shared_ptr<Base> &basep) {
    }
};

#endif//CPP_TEST_COMMON_H

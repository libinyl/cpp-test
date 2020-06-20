#include <gtest/gtest.h>
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
    static bool exist;
};

bool Base::exist = false;

// 当auto_ptr对象生命周期结束时，其析构函数会将auto_ptr对象拥有的动态内存自动释放
TEST(AUTOPTR_TEST, test1) {

    ASSERT_FALSE(Base::exist);
    {
        std::auto_ptr<Base> autostr(new Base);
        ASSERT_TRUE(Base::exist);
    }
    ASSERT_FALSE(Base::exist);// 超过定义域后自动释放
}
#include "common.h"
#include <gtest/gtest.h>

// shared_ptr 拷贝和赋值; 使用移动语义转移所有权.

// 当shared_ptr对象生命周期结束时，其析构函数会将shared_ptr对象拥有的动态内存自动释放
TEST(SHAREDPTR_TEST, get_destruct) {
    std::shared_ptr<Base> initp;
    ASSERT_EQ(initp.get(), nullptr);// 初始化内部指针值为 null

    ASSERT_FALSE(Base::exist);
    {
        std::shared_ptr<Base> basep(new Base);
        ASSERT_TRUE(Base::exist);
        // get 返回原始指针
        Base *rawp = basep.get();
        rawp->value = 1;
        ASSERT_EQ(basep->value, 1);
    }
    ASSERT_FALSE(Base::exist);// 超过定义域后自动释放
};

TEST(SHAREDPTR_TEST, reset) {
    std::shared_ptr<Base> basep1(new Base);
    basep1.reset();// 调用 reset 来释放对象
    ASSERT_FALSE(Base::exist);

    std::shared_ptr<Base> basep2(new Base);
    basep2->value = 1;
    ASSERT_EQ(basep2->value, 1);
    basep2.reset(new Base);// 调用 reset 来指向新对象
    ASSERT_EQ(basep2->value, 0);
}

// 调用拷贝构造或赋值后, 均可操作对象
TEST(SHAREDPTR_TEST, copy_and_ref) {
    std::shared_ptr<Base> basep(new Base);
    User u;
    u.funcPassSharedPtrValue(basep);// 可以传值, 可以传引用
    u.funcPassSharedPtrRef(basep);
}

// 引用计数
TEST(SHAREDPTR_TEST, assign_count) {
    std::shared_ptr<Base> basep1(new Base);
    std::shared_ptr<Base> basep2 = basep1;
    basep2->value = 4;
    ASSERT_EQ(basep2->value, 4);
    ASSERT_EQ(basep2.use_count(), 2);
}


#if __cplusplus >= 201703L
TEST(SHAREDPTR_TEST, make) {
    std::shared_ptr<Base> basep = std::make_shared<Base>();// c++17 支持 make_shared
}
#endif

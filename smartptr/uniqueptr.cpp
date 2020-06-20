#include "common.h"
#include <gtest/gtest.h>


// unique_ptr 相对于 auto_ptr, 禁止了拷贝和赋值; 使用移动语义转移所有权.

// 当auto_ptr对象生命周期结束时，其析构函数会将auto_ptr对象拥有的动态内存自动释放
TEST(UNIQUEPTR_TEST, get_destruct) {
    std::unique_ptr<Base> initp;
    ASSERT_EQ(initp.get(), nullptr);// 初始化内部指针值为 null

    ASSERT_FALSE(Base::exist);
    {
        std::unique_ptr<Base> basep(new Base);
        ASSERT_TRUE(Base::exist);
        // get 返回原始指针
        Base *rawp = basep.get();
        rawp->value = 1;
        ASSERT_EQ(basep->value, 1);
    }
    ASSERT_FALSE(Base::exist);// 超过定义域后自动释放
};

TEST(UNIQUEPTR_TEST, release) {
    std::unique_ptr<Base> basep(new Base);
    Base *rawp = basep.release();
    ASSERT_TRUE(Base::exist);
    ASSERT_EQ(basep.get(), nullptr);// release 后 auto_ptr 值为 null
    delete rawp;                    // 必须手动释放内存
}

TEST(UNIQUEPTR_TEST, reset) {
    std::unique_ptr<Base> basep(new Base);
    basep->value = 2;
    basep.reset(new Base);
    ASSERT_EQ(basep->value, 0);
}

#if __cplusplus >= 201402L
TEST(UNIQUEPTR_TEST, make) {
    std::unique_ptr<Base> basep = std::make_unique<Base>();// c++14 支持 make_unique
}
#endif

TEST(UNIQUEPTR_TEST, move) {
    std::unique_ptr<Base> basep1(new Base);
    basep1->value = 2;
    std::unique_ptr<Base> basep2;
    basep2 = std::move(basep1);      // 通过 move 转移所有权. 原型是 unique_ptr& operator= (unique_ptr&& x) noexcept;
    ASSERT_EQ(basep1.get(), nullptr);// 转移后原指针为 null
    ASSERT_EQ(basep2->value, 2);
}

// 调用拷贝构造或赋值后, 原有指针被置为 null
TEST(UNIQUEPTR_TEST, cannot_copy) {
    std::unique_ptr<Base> basep(new Base);
    //std::unique_ptr<Base> basep2(basep); //无法拷贝  unique_ptr& operator= (const unique_ptr&) = delete;
    User u;
    u.funcPassUniquePtr(basep);     // 只能传引用
    ASSERT_NE(basep.get(), nullptr);// 拷贝后原指针不会为 null.
}

TEST(UNIQUEPTR_TEST, cannot_assign) {
    std::unique_ptr<Base> basep1(new Base);
    //std::unique_ptr<Base> basep2 = basep1; 无法赋值
}
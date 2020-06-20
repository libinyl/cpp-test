#include "common.h"
#include <gtest/gtest.h>

// auto_ptr 表达唯一所有权. 当拷贝或赋值后, 原指针被置为 null. 已被弃用.
// auto_ptr采用copy语义来转移指针资源，转移指针资源的所有权的同时将原指针置为NULL，这跟通常理解的copy行为是不一致的(不会修改原数据)，而这样的行为在有些场合下不是我们希望看到的.
// boost::scoped_ptr 相对于 auto_ptr, 禁止了拷贝和赋值.
// unique_ptr 相对于 auto_ptr, 禁止了拷贝和赋值; 使用移动语义转移所有权.


// 当auto_ptr对象生命周期结束时，其析构函数会将auto_ptr对象拥有的动态内存自动释放
TEST(AUTOPTR_TEST, auto_destruct) {
    std::auto_ptr<Base> bp1;
    ASSERT_EQ(bp1.get(), nullptr);// 初始化内部指针为 null

    ASSERT_FALSE(Base::exist);
    {
        std::auto_ptr<Base> autostr(new Base);
        ASSERT_TRUE(Base::exist);
    }
    ASSERT_FALSE(Base::exist);// 超过定义域后自动释放
}


TEST(AUTOPTR_TEST, release) {
    std::auto_ptr<Base> basep(new Base);
    Base *rawp = basep.release();
    ASSERT_TRUE(Base::exist);
    ASSERT_EQ(basep.get(), nullptr);// release 后 auto_ptr 值为 null
    delete rawp;                    // 必须手动释放内存
}

TEST(AUTOPTR_TEST, reset) {
    std::auto_ptr<Base> basep(new Base);
    basep->value = 2;
    basep.reset(new Base);
    ASSERT_EQ(basep->value, 0);
}

// 调用拷贝构造或赋值后, 原有指针被置为 null
TEST(AUTOPTR_TEST, danger_null_after_copy) {
    std::auto_ptr<Base> basep(new Base);
    User u;
    u.funcPassAutoPtr(basep);
    ASSERT_EQ(basep.get(), nullptr);// 拷贝后原指针变为 null.
}

TEST(AUTOPTR_TEST, danger_null_after_assign) {
    std::auto_ptr<Base> basep1(new Base);
    std::auto_ptr<Base> basep2 = basep1;
    ASSERT_EQ(basep1.get(), nullptr);// 赋值后原指针变为 null.
}
template<typename T>
struct Func_ {
    using type = T;
};

template<>
struct Func_<int> {
    using type = unsigned int;
};

Func_<int>::type h = 3;
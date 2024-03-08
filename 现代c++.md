# 移动语义std::move
这里是一个C++11的std::move的示例实现。它并不完全满足标准细则，但是它已经非常接近了。
```cpp
template<typename T>                            // 在 std命名空间
typename remove_reference<T>::type&&
move(T&& param)
{
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}
```
分析：std::move接受一个对象的引用（准确的说，一个通用引用)，返回一个指向同对象的引用。
类型T是一个左值引用，那么T&&将会成为一个左值引用【引用折叠推导】，
此时 std::remove_reference 可以把 param 的 引用属性去除，
这样才能使得 static_cast<ReturnType>(param) 类型转换为右值 成功。

所以，std::move不移动任何东西，只是一个类型转换，它跟 (Type&&) 强制转换 没有区别

# 完美转发 std::forward<type> 【引用折叠是 std::forward 的支持基础】
forward<>(T&& param) 函数，实际上没有转发任何东西。
此函数的形参 是一个 右值引用&&, 
如果传入的实参是 左值，那么 & + && = &
如果传入的实参是 右值，那么 && + && = &&
这就实现了左值是左值、右值是右值的效果

# 总结： std::move 和 std::forward 只是一种强制类型转换

# 转发引用与右值引用的区别
带右值引用符号不一定就是右值引用，这种不确定类型的引用称为转发引用
```cpp
template <typename T>
void f(T&&) {}  // T&&不一定是右值引用

int a = 1;
f(a);  // T 推断为 int&，T&& 是 int& &&，折叠为 int&，是左值引用
f(1);  // T 推断为 int，T&& 是 int&&，右值引用
auto&& b = a;  // int& b = a，左值引用
auto&& c = 1;  // int&& c = 1，右值引用
```

转发引用必须严格按 T&& 的形式涉及类型推断
```cpp
template <typename T>
void f(std::vector<T>&&) {}  // 右值引用而非转发引用

std::vector<int> v;
f(v);  // 错误

template <typename T>
void g(const T&&) {}  // 右值引用而非转发引用

int i = 1;
g(i);  // 错误
```

auto&& 都是转发引用，因为一定涉及类型推断。完美转发中，如果想在转发前修改要转发的值，可以用 auto&& 存储结果，修改后再转发
```cpp
template <typename T>
void f(T x) {
    auto&& res = do_something(x);
    do_something_else(res);
    set(std::forward<decltype(res)>(res));
}
```

T&& 在模板中也可能不涉及类型推断
```cpp
template <class T, class Allocator = allocator<T>>
class vector {
 public:
  void push_back(T&& x);  // 右值引用

  template <class... Args>
  void emplace_back(Args&&... args);  // 转发引用
};

std::vector<A> v;  // 实例化指定了 T, 不涉及类型推断

// 对应的实例化为
class vector<A, allocator<A>> {
 public:
  void push_back(A&& x);  // 不涉及类型推断，右值引用

  template <class... Args>
  void emplace_back(Args&&... args);  // 转发引用
};
```

# 避免重载使用转发引用的函数
转发引用几乎可以匹配任何类型，因此应该避免对其重载。
```cpp
std::vector<std::string> v;

template <typename T>
void f(T&& s) {
    v.emplace_back(std::forward<T>(s));
}
void f(int n) { v.emplace_back(make_string(n)); }
std::string make_string(int n) { return std::string("hi"); }

int main() {
    f(1);  // 调用重载版本
    // 但对于非 int（即使能转换到 int）参数就会出现问题
    int i = 1;
    /*
    * 转发引用是比 int 更精确的匹配
    * 为 std::vector<std::string> 传入 short
    * 用 short 构造 std::string 导致错误
    */
    f(i);
}
```

# 引用折叠
引用折叠会出现在四种语境中：模板实例化、auto 类型推断、decltype 类型推断、typedef 或 using 别名声明。
```cpp
template <typename T>
void f(T&&);

int i = 1;
f(i);  // T 为 int&，T& && 变成了引用的引用，于是需要引用折叠的机制
```
为了使实例化成功，编译器生成引用的引用时，将使用引用折叠的机制，规则如下
& + & → &
& + && → &
&& + & → &
&& + && → &&

## 引用折叠是 std::forward 的支持基础【看上面的 std::forward 】

# 移动不比拷贝快的情况
在如下场景中，C++11 的移动语义没有优势
1. 无移动操作：待移动对象不提供移动操作，移动请求将变为拷贝请求
2. 移动不比拷贝快：待移动对象虽然有移动操作，但不比拷贝操作快
3. 移动不可用：本可以移动时，要求移动操作不能抛异常，但未加上 noexcept 声明
4. 还有一些特殊场景无需使用移动语义，比如 RVO 返回优化【直接避免了 拷贝、移动的行为】
5. std::array 实际是带 STL 接口的内置数组。不同于其他容器的是，其他容器把元素存放于堆上，自身只持有一个指向堆内存的指针，移动容器时只需要移动指针，在常数时间内即可完成移动。std::array 自身存储了内容，没有这样的指针，移动或拷贝对元素逐个执行，需要线性时间复杂度，所以移动并不比拷贝快多少
6. std::string 的一种实现是使用 SSO（small string optimization），在字符串很小时（一般是15字节）存储在自身内部，而不使用堆上分配的内存，因此对小型字符串的移动并不比拷贝快


# lambda默认捕获模式的问题
默认按引用捕获 [&](param)
```cpp
int computeDivisor(int a, int b) { return a; }
using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;
void thisFunEndAndLambdaRefWillDie() {
    int divisor = computeDivisor(1, 2); // 假设 divisor 是一个 运行期才可知的数字 
    filters.emplace_back([&](int x) {return x % divisor == 0; });
    // thisFunEndAndLambdaRefWillDie 函数离开作用域,  divisor死亡, 
    // 但是lambda已经被添加到 vector 里面！divisor就是一个悬空引用
}
```

默认按值捕获 [=](param)
假设在一个 Widget 类，可以实现向过滤器的容器添加条目
```cpp
using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;
class Widget {
    int divisor;
public:
    void addFilter() const {
        filters.emplace_back([=](int value) { return value % divisor == 0; });
    }
};
filters.back()(10); // 运行报错, divisor 为空！// 但是lambda已经被添加到 vector 里面！divisor就是一个悬空引用

分析
上面的  filters.emplace_back([=](int value) { return value % divisor == 0; });
等价于  filters.emplace_back([=this](int value) { return value % this->divisor == 0; });
```

实际上 默认值捕获，捕获的是 this指针，结果运行时期 this对象已经被析构
如果不使用 [=] 而是使用 [] 的话，代码无法编译，因为没有捕获this，怎么能使用this->divisor

这种问题的解决方法:
```cpp
using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;
class Widget {
    int divisor;
public:
    void addFilter() const {
        int j = divisor; // 直接临时变量值拷贝
        filters.emplace_back([j](int value) { return value % j == 0; });
    }
};
```
lambda函数只能捕获 非static的局部变量、形参
```cpp
void addDivisorFilter()
{
    static auto calc1 = computeSomeValue1();    //现在是static
    static auto calc2 = computeSomeValue2();    //现在是static
    static auto divisor = computeDivisor(calc1, calc2);  //现在是static

    filters.emplace_back(
        [=](int value)                          //什么也没捕获到！
        { return value % divisor == 0; }        //引用上面的static
    );
    ++divisor;  //改变static变量在lambda下次调用时可能带来让人困惑的效果
}
```

# 用初始化捕获将对象移入闭包
move-only 类型对象不支持拷贝，只能采用引用捕获
```cpp
auto p = std::make_unique<int>(42);
auto f = [&p]() { std::cout << *p; };
```
初始化捕获则支持把 move-only 类型对象移动进 lambda 中
```cpp
auto p = std::make_unique<int>(42);
auto f = [p = std::move(p)]() { std::cout << *p; };
assert(p == nullptr);
```

# 用 decltype 获取 auto&& 参数类型以 std::forward
对于泛型 lambda： auto f = [](auto x) { return g(x); };

```cpp
// 传入参数是 auto，类型未知，std::forward 的模板参数应该是什么？
auto f = [](auto&& x) { return g(std::forward <???> (x)); };
```
此时可以用 decltype 判断传入的实参是左值还是右值
如果传递给 auto&& 的实参是左值，则x为左值引用类型，decltype(x) 为左值引用类型
如果传递给 auto&& 的实参是右值，则x为右值引用类型，decltype(x) 为右值引用类型
```cpp
auto f = [](auto&& x) { return g(std::forward<decltype(x)>(x)); };
```
转发任意数量的实参
```cpp
auto f = [](auto&&... args) {
    return g(std::forward<decltype(args)>(args)...);
};
```


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

# 完美转发 std::forward<type> 
forward<>(T&& param) 函数，实际上没有转发任何东西。
此函数的形参 是一个 右值引用&&, 
如果传入的实参是 左值，那么 & + && = &
如果传入的实参是 右值，那么 && + && = &&
这就实现了左值是左值、右值是右值的效果

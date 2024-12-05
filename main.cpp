// 项目使用 makefile 构建
// make 命令编译
// make clean 清理可执行文件
// 项目代码实现逻辑
// 1.实现构造函数
// 2.实现隐式类型转换
// 3.Json数组的加入与基本类型之间的转换
// 4.Json对象的赋值
// 5.内容返回
// 6.内容拷贝、内存释放和数组遍历
// 7.类型判断
// 8.显式类型转换
// 9.判断数组索引或对象键值是否存在
// 10.根据索引删除数组元素或键值删除对象值
#include<iostream>
#include "json.h"

using namespace std;
using namespace yazi::json;

int main(){
    /*
    Json v1;
    Json v2 = true;
    Json v3 = 123;
    Json v4 = 1.23;
    Json v5 = "hello world";

    // 基本类型的运算符重载
    bool b = v2;
    int i = v3;
    double f = v4;
    const string& s = v5;

    cout << b << endl;
    cout << i << endl;
    cout << f << endl;
    cout << s << endl;

    Json arr; // Json对象的数组
    arr[0] = true;
    arr[1] = 123;

    arr.append(1.23);
    arr.append("hello world");

    cout << arr.str() << endl;

    bool b = arr[0];
    int i = arr[1];
    double f = arr[2];
    const string& s = arr[3];
    
    
    Json obj;
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["str"] = "hello world";

    cout << obj.str() << endl;
    */

    Json arr; // Json对象的数组
    arr[0] = true;
    arr[1] = 123;
    arr[2] = 1.23;
    arr[3] = "hello world";

    for(auto it = arr.begin(); it != arr.end(); ++it){
        cout << (*it).str() << endl;
    }

    cout << arr.has(0) << endl;
    cout << arr.has(4) << endl;

    arr.remove(0);
    cout << arr.str() << endl;

    Json obj; // 对象
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["str"] = "hello world";
    obj["arr"] = arr;

    cout << obj.str() << endl;

    cout << obj.has("str") << endl;
    cout << obj.has("str123") << endl;

    obj.remove("str");
    cout << obj.str() << endl;

    obj.clear(); // 释放一次，统一由 obj 释放

    cout << obj.str() << endl;

    return 0;
}
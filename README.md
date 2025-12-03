# Json 解析器

## 知识点

- 面向对象程序设计
- C++基本语法
- 标准模板库
- 内存管理

## 项目流程

### Json 类的成员

有两级命名空间，yazi::json，里面声明一个类 Json。
JSON 数据格式有类型：null, bool, int, double, string, array, object。
使用联合体 union 存放值，因为联合体是共用内存空间的，联合体的大小为所占内存空间最大的成员变量大小。其中，string 类型的值由指向 string 对象的指针构成，array 类型的值由指向 vector\<Json> 对象的指针构成，object 类型的值由指向 map\<string, Json> 对象的指针构成。具体实现如下所示：

```cpp
enum Type{
    json_null = 0,
    json_bool,
    json_int,
    json_double,
    json_string,
    json_array,
    json_object,
};

union Value{
    bool m_bool;
    int m_int;
    double m_double;
    std::string* m_string;
    std::vector<Json>* m_array;
    std::map<string, Json>* m_object;
};
```

对类 Json 来说，它主要包括两个数据成员：类型 `Type m_type` 和值 `Value m_value`，其中的 `Type` 和 `Value` 分别是枚举类和联合体。

### 基本类型赋值给 Json 对象

首先，我们要实现下面形式的调用， 即基本类型赋值给 Json 对象的操作：

```cpp
Json v1;
Json v2 = true;
Json v3 = 123;
Json v4 = 1.23;
Json v5 = "hello world";
```

需要实现构造函数。如下：

```cpp
// 构造函数
Json();
Json(bool value);
Json(int value);
Json(double value);
Json(const char* value);
Json(const string& value);
Json(Type type);
// 拷贝构造函数
Json(const Json& other);
```

### Json 对象赋值给基本类型

接着，我们需要实现 Json 对象转化为基本变量类型，如下：

```cpp
bool b = v2;
int i = v3;
double f = v4;
const string& s = v5;
```

通过基本类型的运算符重载实现这一功能。

```cpp
operator bool();
operator int();
operator double();
operator string();
```

### Json 数组相关功能

接着，我们实现 Json 数组相关的功能，如索引添加元素、append 函数添加元素和数组元素转化为基本类型，最后结果如下：

```cpp
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
```

通过重载操作符实现，如下：

```cpp
// Json 数组的赋值：重载中括号 []
Json & operator [](int index);
void append(const Json & other);

// 返回 Json 内容
string str() const;
```

### json_object 相关的操作

然后，我们实现 json_object 相关的操作，如下：

```cpp
Json obj;
obj["bool"] = true;
obj["int"] = 123;
obj["double"] = 1.23;
obj["str"] = "hello world";

cout << obj.str() << endl;
```

为了实现上面的功能，我们需要重载中括号 []，如下：

```cpp
// Json 对象的赋值：重载中括号 []，区别在于参数不同
Json & operator [](const char* key);
Json & operator [](const string& key);

void operator = (const Json & other);

void copy(const Json& other);
void clear();
```

### Json 数组的遍历操作

接着，我们实现 json_array 的遍历操作，如下：

```cpp
Json arr; // Json对象的数组
arr[0] = true;
arr[1] = 123;
arr[2] = 1.23;
arr[3] = "hello world";

for(auto it = arr.begin(); it != arr.end(); ++it){
    cout << (*it).str() << endl;
}
```

为此，我们需要实现以下接口：

```cpp
typedef vector<Json>::iterator iterator;
iterator begin(){
    return (m_value.m_array)->begin();
}
iterator end(){
    return (m_value.m_array)->end();
}
```

### Json 对象的比较

之后，我们实现判断对象相等与不相等的接口，如下：

```cpp
bool operator == (const Json & other);
bool operator != (const Json & other);
```

### 其它接口

接着，我们再加上 Json 对象的类型判断和显式类型转换，以及判断数组索引（对象键）和根据索引删除数组元素（键删除对象值），如下：

```cpp
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
```

为此，我们需要实现如下接口：

```cpp
// 判断类型
bool isNull() const { return m_type == json_null; }
bool isBool() const { return m_type == json_bool; }
bool isInt() const { return m_type == json_int; }
bool isDouble() const { return m_type == json_double; }
bool isString() const { return m_type == json_string; }
bool isArray() const { return m_type == json_array; }
bool isObject() const { return m_type == json_object; }

// 显式转换
bool asBool() const;
int asInt() const;
double asDouble() const;
string asString() const;

// 判断数组索引
bool has(int index);
bool has(const char* key);
bool has(const string& key);

// 根据索引删除数组元素或键删除对象值
void remove(int index);
void remove(const char* key);
void remove(const string& key);

void parse(const string& str);
```

### 实现解析器

#### 类的数据成员

Parser 类有两个数据成员：用于解析的字符串 m_str 和 索引 m_idx。

```cpp
string m_str;
int m_idx;
```

#### 构造函数和数据加载

需要实现如下接口：

```cpp
Parser();
void load(const string& str);
```

#### 各种数据类型的解析

需要实现如下接口：

```cpp
Json parse();

void skip_white_space();
char get_next_token();

Json parse_null();
Json parse_bool();
Json parse_number();
string parse_string();
Json parse_array();
Json parse_object();
```

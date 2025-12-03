#pragma once

#include<string>
#include<vector>
#include<map>
using namespace std; 

// 嵌套命名空间：yazi::json
namespace yazi{
    namespace json{
        class Json{
        public:
            enum Type{
                json_null = 0,
                json_bool,
                json_int,
                json_double,
                json_string,
                json_array,
                json_object,
            };

            // 构造函数
            Json();
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const char* value);
            Json(const string& value);
            Json(Type type);
            Json(const Json& other);

            // 隐式转换
            operator bool();
            operator int();
            operator double();
            operator string();

            // Json 数组的赋值：重载中括号 []
            Json & operator [](int index);
            void append(const Json & other);

            // Json 对象的赋值：重载中括号 []，区别在于参数不同
            Json & operator [](const char* key);
            Json & operator [](const string& key);

            void operator = (const Json & other);
            bool operator == (const Json & other);
            bool operator != (const Json & other);

            // 返回 Json 内容
            string str() const;

            void copy(const Json& other);
            void clear();

            typedef vector<Json>::iterator iterator;
            iterator begin(){
                return (m_value.m_array)->begin();
            }
            iterator end(){
                return (m_value.m_array)->end();
            }

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

            // 根据索引删除数组元素或键值删除对象值
            void remove(int index);
            void remove(const char* key);
            void remove(const string& key);

            void parse(const string& str);


        private:
            // 联合能够节省内存，因为联合体内变量是共用
            // 内存空间的，以最大变量大小为联合体大小
            union Value{
                bool m_bool;
                int m_int;
                double m_double;
                std::string* m_string;
                std::vector<Json>* m_array;
                std::map<string, Json>* m_object;
            };

            Type m_type; // 枚举类型
            Value m_value;

        }; // Json

    }// namespace json
} // namespace yazi
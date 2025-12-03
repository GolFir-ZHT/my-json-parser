#pragma once

#include "json.h"
#include<string>
using namespace std;

namespace yazi{
    namespace json{
        class Parser{
            public:
                Parser();
                void load(const string& str);

                Json parse();

            private:
                string m_str;
                int m_idx;

                void skip_white_space();
                char get_next_token();
                
                Json parse_null();
                Json parse_bool();
                Json parse_number();
                string parse_string();
                Json parse_array();
                Json parse_object();
        };
    }
}
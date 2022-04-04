#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft {

template <typename T1, typename T2>
class pair
{
    public:
        typedef T1  key_type;
        typedef T2  value_type;

        pair(void): _key(0), _value(0) {}
        pair(const key_type &key, const value_type &value): _key(key), _value(value) {}
        pair(const pair &rhs) { *this = rhs; }
        ~pair(void) {}

        pair &operator=( const pair& rhs ) {
            if (this != &rhs) {
                this->_key = rhs._key;
                this->_value = rhs._value;
            }
            return *this;
        }

        // key_type getKey() const { return this->_key;}
        // value_type getValue() const { return this->_value;}
        // void setKey(const key_type &val) { this->_key = val ;}
        // void setValue(const value_type &val) { this->_value = val;}

    // private:
        key_type    _key;
        value_type  _value;
};
}


#endif
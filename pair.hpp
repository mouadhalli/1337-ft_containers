#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft {

    template <typename T1, typename T2>
    struct pair
    {
        public:
            typedef T1  key_type;
            typedef T2  value_type;

            pair(void): _key(), _value() {}
            pair(const key_type &key, const value_type &value): _key(key), _value(value) {}
            template<class key, class value>
            pair ( const pair<key, value>& pr ) : _key(pr._key), _value(pr._value) {}
            ~pair(void) {}

            pair &operator=( const pair& rhs ) {
                if (this != &rhs) {
                    _key = rhs._key;
                    _value = rhs._value;
                }
                return *this;
            }

            key_type    _key;
            value_type  _value;
    };

    template <typename T1, typename T2>
    ft::pair<T1, T2>    make_pair(T1 x, T2 y) {
        return (ft::pair<T1, T2>(x, y));
    }
}

#endif
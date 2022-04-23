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

            pair(void): first(), second() {}
            pair(const key_type &key, const value_type &value): first(key), second(value) {}
            template<class key, class value>
            pair ( const pair<key, value>& pr ) : first(pr.first), second(pr.second) {}
            ~pair(void) {}

            pair &operator=( const pair& rhs ) {
                if (this != &rhs) {
                    first = rhs.first;
                    second = rhs.second;
                }
                return *this;
            }

            key_type    first;
            value_type  second;
    };

    template <typename T1, typename T2>
    ft::pair<T1, T2>    make_pair(T1 x, T2 y) {
        return (ft::pair<T1, T2>(x, y));
    }

    template<typename T1, typename T2>
    bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
    template<typename T1, typename T2>
    bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }
    template<typename T1, typename T2>
    bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first < rhs.first || lhs.second < rhs.second); }
    template<typename T1, typename T2>
    bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return rhs < lhs; }
    template<typename T1, typename T2>
    bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || lhs < rhs); }
    template<typename T1, typename T2>
    bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs == rhs || rhs < lhs); }
}

#endif
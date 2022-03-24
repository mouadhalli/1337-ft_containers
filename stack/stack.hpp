#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft{

    template<class T,class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef	T		            value_type;
            typedef Container	        container_type;
            typedef	size_t		        size_type;

            explicit stack( const container_type& ctnr = container_type() ): _c(ctnr) {}
            ~stack( void ) {}

            bool empty() const { return _c.empty(); }
            size_type size() const { return _c.size(); }
            value_type& top() { return _c.back(); }
            value_type const& top() const { return _c.back(); }
            void push( const value_type &val ) { _c.push_back(val); }
            void pop() { _c.pop_back();}

            friend bool operator==( const stack &lhs, const stack &rhs ) { return lhs._c == rhs._c; }
            friend bool operator!=( const stack &lhs, const stack &rhs ) { return lhs._c != rhs._c; }
            friend bool operator< ( const stack &lhs, const stack &rhs ) { return lhs._c < rhs.c_; }
            friend bool operator<=( const stack &lhs, const stack &rhs ) { return lhs._c <= rhs._c; }
            friend bool operator> ( const stack &lhs, const stack &rhs ) { return lhs._c > rhs.c_; }
            friend bool operator>=( const stack &lhs, const stack &rhs ) { return lhs._c >= rhs._c; }

        private:
            container_type		_c;
    };
}

#endif
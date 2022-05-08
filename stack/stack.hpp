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

            

            explicit stack( const container_type& ctnr = container_type() ): c(ctnr) {}
            ~stack( void ) {}

            bool empty() const { return c.empty(); }
            size_type size() const { return c.size(); }
            value_type& top() { return c.back(); }
            value_type const& top() const { return c.back(); }
            void push( const value_type &val ) { c.push_back(val); }
            void pop() { c.pop_back();}

            friend bool operator==( const stack &lhs, const stack &rhs ) { return lhs.c == rhs.c; }
            friend bool operator!=( const stack &lhs, const stack &rhs ) { return lhs.c != rhs.c; }
            friend bool operator< ( const stack &lhs, const stack &rhs ) { return lhs.c < rhs.c; }
            friend bool operator<=( const stack &lhs, const stack &rhs ) { return lhs.c <= rhs.c; }
            friend bool operator> ( const stack &lhs, const stack &rhs ) { return lhs.c > rhs.c; }
            friend bool operator>=( const stack &lhs, const stack &rhs ) { return lhs.c >= rhs.c; }

        protected:
            container_type		c;
    };
}

#endif
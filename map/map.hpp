#ifndef MAP_HPP
#define MAP_HPP
#include "AVL.hpp"
#include "../pair.hpp"

namespace ft {

    template < class Key,                                           // map::key_type
               class T,                                             // map::mapped_type
               class Compare = std::less<Key>,                      // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > // map::allocator_type
               >
    class map
    {
        public:
            typedef Key 										key_type;
            typedef T 											mapped_type;
            typedef ft::pair<const key_type, mapped_type> 		value_type;
            typedef Compare 									key_compare;
            // typedef value_compare	Nested function class to compare elements	see value_comp
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference 			reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer			pointer; 
            typedef typename allocator_type::const_pointer		const_pointer;
            typedef AVL<value_type, key_compare, allocator_type> tree_type;
			typedef	size_t										size_type;
            typedef typename tree_type::iterator				iterator;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _Tree(), _Comp(comp), _Allocator(alloc) {}
			
			// template <class InputIterator>
  			// map (InputIterator first, InputIterator last,
       		// const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			//    	_Tree(first, last),
			// 	_Comp(comp),
			// 	_Allocator(alloc) {}
			
			map (const map& x) { *this = x; };
			~map ( void ) {};

			map	&operator=( const map &rhs ) {
            	this->_Tree = rhs._Tree;
                return *this;
            }

			iterator begin( void ) {return _Tree.begin();}
			iterator end( void ) {return _Tree.end();}
			// const_iterator begin() const;

            void	insert(const value_type& val) {   //modify function return later
                _Tree.insert(val);
            }

			size_type	erase(const key_type& key) {
				if (_Tree.erase(key))
					return (1);
				return (0);
			}

            void clear( void ) {_Tree.clear();}

            bool empty() const {return _Tree.IsEmpty();}

			size_type count (const key_type& k) const {return _Tree.count(k);}

            void	printTree() {_Tree.print();}

		private:
			tree_type		_Tree;
        	key_compare		_Comp;
        	allocator_type	_Allocator;

    };
}

#endif
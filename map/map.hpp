#ifndef MAP_HPP
#define MAP_HPP
#include "AVL.hpp"
#include "../pair.hpp"
#include "../utils.hpp"
#include "../vector/vector.hpp"

namespace ft {

    template < class Key,
               class T,
               class Compare = std::less<Key>,
               class Alloc = std::allocator<ft::pair<const Key,T> >
               >
    class map
    {
        public:
            typedef Key 										key_type;
            typedef T 											mapped_type;
            typedef ft::pair<const key_type, mapped_type> 		value_type;
            typedef Compare 									key_compare;
            typedef Alloc										allocator_type;
            typedef typename allocator_type::reference 			reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer			pointer; 
            typedef typename allocator_type::const_pointer		const_pointer;
            typedef AVL<value_type, key_compare, allocator_type> tree_type;
			typedef	size_t										size_type;
            typedef typename tree_type::iterator				iterator;
            typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
            typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _Tree(), _Comp(comp), _Allocator(alloc) {}
			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				_Comp = comp;
				_Allocator = alloc;
				for (; first != last; first++)
					_Tree.insert(*first);
			}
			
			map (const map& x) { *this = x; };

			~map ( void ) {};

			map	&operator=( const map &rhs ) {
				if (this != &rhs)
				{
            		_Tree = rhs._Tree;
            		_Comp = rhs._Comp;
            		_Allocator = rhs._Allocator;
				}
                return *this;
            }

			mapped_type& operator[] (const key_type& k) {
				return (this->insert(ft::make_pair(k, mapped_type())).first->second);
			}
			
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
			    protected:
					key_compare comp;
					value_compare(key_compare __c) : comp(__c) { }

			    public:
					bool operator()(const value_type& __x, const value_type& __y) const
						{ return comp(__x.first, __y.first); }
			};

			value_compare value_comp() const { return value_compare(_Comp); }


			iterator 				begin( void ) {return _Tree.begin();}
			const_iterator			begin( void ) const {return _Tree.begin();}

			iterator 				end( void ) {return _Tree.end();}
			const_iterator			end( void ) const {return _Tree.end();}

			reverse_iterator 		rbegin( void ) {return _Tree.rbegin();}
			const_reverse_iterator	rbegin( void ) const {return _Tree.rbegin();}

			reverse_iterator 		rend( void ) {return _Tree.rend();}
			const_reverse_iterator	rend( void ) const {return _Tree.rend();}

            ft::pair<iterator, bool>	insert(const value_type& val) {
                bool status = _Tree.insert(val);
				return (ft::make_pair(this->find(val.first), status));
            }

			iterator insert(iterator position, const value_type& val) {
				(void)position;
                _Tree.insert(val);
				return (iterator(_Tree.find(_Tree.getRoot(), val.first), &_Tree));
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last) {
				for (; first != last; first++)
					_Tree.insert(*first);
			}

			size_type	erase(const key_type& key) {
				if (_Tree.erase(key))
					return (1);
				return (0);
			}

			void erase (iterator position) {
                _Tree.erase(position->first);
			}

			void erase (iterator first, iterator last) {
				ft::vector<key_type>KeysVector;
				for (;first != last; first++)
					KeysVector.push_back(first->first);
				for(typename ft::vector<key_type>::iterator it = KeysVector.begin();it != KeysVector.end(); it++)
                        erase(*it);
			}

            void clear( void ) {_Tree.clear();}

            bool empty() const {return _Tree.IsEmpty();}

			size_type count (const key_type& k) const {return _Tree.count(k);}

			iterator find(const key_type& k) {
				return (iterator(_Tree.find(_Tree.getRoot(), k), &_Tree));
			}

			const_iterator find(const key_type& k) const {
				return (const_iterator(_Tree.find(_Tree.getRoot(), k), &_Tree));
			}

			size_type size() const { return _Tree.size();}
			size_type max_size() const { return _Tree.max_size();}

			allocator_type get_allocator() const {return _Allocator;}
			key_compare key_comp() const {return _Comp;}

			iterator lower_bound (const key_type& k) {
				iterator bound = this->find(k);
				if (bound == this->end())
					return (iterator(_Tree.find_Succesor(k), &_Tree));
				return bound;
			}

			const_iterator lower_bound (const key_type& k) const {
				const_iterator bound = this->find(k);
				if (bound == this->end())
					return (const_iterator(_Tree.find_Succesor(k), &_Tree));
				return bound;
			}

			iterator upper_bound (const key_type& k) {
				return (iterator(_Tree.find_Succesor(k), &_Tree));
			}
			const_iterator upper_bound (const key_type& k) const {
				return (iterator(_Tree.find_Succesor(k), &_Tree));
			}

			ft::pair<iterator,iterator>	equal_range (const key_type& k) {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			void swap (map& x) {
				_Tree.swap(x._Tree);
				std::swap(_Comp, x._Comp);
				std::swap(_Allocator, x._Allocator);
			}

		private:
			tree_type		_Tree;
        	key_compare		_Comp;
        	allocator_type	_Allocator;

    };

	template <class Key, class T, class Compare, class Alloc>
  		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); }

	template< class Key, class T, class Compare, class Alloc >
        bool operator==( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) {
            if (lhs.size() != rhs.size())
                return (lhs.size() == rhs.size());
            return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }

    template< class Key, class T, class Compare, class Alloc >
        bool operator!=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator==(lhs, rhs)); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator<( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator<=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator>(lhs, rhs)); }
    template< class Key, class T, class Compare, class Alloc >
        bool operator>( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (operator<(rhs, lhs)); }	
    template< class Key, class T, class Compare, class Alloc >
        bool operator>=( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (!operator<(lhs, rhs)); }
}

#endif
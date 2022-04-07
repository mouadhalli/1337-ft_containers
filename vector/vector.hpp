#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

namespace ft{

template < class T, class Alloc = std::allocator<T> >
class vector
{
    public:
/*    						{{.. Memeber Types ..}}														*/
        typedef	T											value_type;
        typedef	Alloc										allocator_type;
        typedef	typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef random_access_iterator<value_type>      		iterator;
    	typedef random_access_iterator<const value_type>		const_iterator;

    	typedef reverse_iterator<const_iterator>   			const_reverse_iterator;
    	typedef reverse_iterator<iterator>         			reverse_iterator;
        typedef	ptrdiff_t									difference_type;
        typedef	size_t   									size_type;

/*    						{{.. Memeber Funcitons ..}}:													*/

		//Constructors && destructor:

						//---- Default Constructor ----//
		vector (const allocator_type& alloc = allocator_type()):
			_Arr(0),
			_alloc(alloc),
			_size(0),
			_Capacity(0)
		{};

						//---- Fill Constructor ----//
		vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()):
			_alloc(alloc),
			_size(n),
			_Capacity(n)
		{
			_Arr = _alloc.allocate(_Capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_Arr[i], val);
		};

						//---- Range Constructor ----//
		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
        		const allocator_type& alloc = allocator_type(),
				typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			difference_type AllocSize = std::abs(std::distance(first, last));
			_size = AllocSize;
			_alloc = alloc;
			_Capacity = AllocSize;
			_Arr = _alloc.allocate(_Capacity);

			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_Arr[i], *first++);
		};

						//---- Copy Constructor ----//
		vector (const vector& x):
			_Arr(0),
			_size(0),
			_Capacity(0)
		{ *this = x; };

		//Destructor:
		~vector( void )
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_Arr[i]);
			_alloc.deallocate(_Arr, _Capacity);
        };

allocator_type get_allocator() const { return _alloc; }

		//Operators Overload:

						//---- Assignement Operator= ----//
		vector&	operator=(const vector& x)
		{
			if (this != &x)
			{
				if (_size)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_Arr[i]);
					_alloc.deallocate(_Arr, _Capacity);
				}
				_size = x._size;
				_Capacity = x._Capacity;
				_Arr = _alloc.allocate(_Capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&_Arr[i], x._Arr[i]);
				}
			}
			return (*this);
		};

						//---- Iterator Functions----//
		iterator	begin() {return iterator(&_Arr[0]);} 
		iterator	end() {return iterator(&_Arr[_size]);}

		const_iterator begin() const {return iterator(&_Arr[0]);}
		const_iterator end() const {return iterator(&_Arr[_size]);}

		reverse_iterator rbegin() {return reverse_iterator(this->end());}
		reverse_iterator rend() {return  reverse_iterator(this->begin());}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(this->end());}
		const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}

						//---- Iterator Functions----//
		size_type	size( void ) const {return _size;}
		size_type	max_size( void ) const { return _alloc.max_size();}

		void resize (size_type n, value_type val = value_type()) {
			if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_Arr[i]);
				_size = n;	
			}
			else if (n > _Capacity)
			{
				n > _Capacity * 2 ? reserve(n) : reserve(_Capacity * 2);
				while (_size < n)
					_alloc.construct(&_Arr[_size++], val);
			}
			else if (n > _size)
			{
				while (_size < n)
					_alloc.construct(&_Arr[_size++], val);
			}
		};

		size_type	capacity( void ) const {return _Capacity;}
		bool		empty( void ) const {return _size ? false : true;}

		void 		reserve (size_type n) {
            if (n > max_size()) {
                throw std::length_error("ft::vector: new capacity exceeds ram max length");
            } else if (n > _Capacity)
			{
				value_type *tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&tmp[i], _Arr[i]);
					_alloc.destroy(&_Arr[i]);
				}
				_alloc.deallocate(_Arr, _Capacity);
				_Arr = tmp;
				_Capacity = n;
			}
		}

						//---- Element access ----//
		reference		operator[](size_type n) {return _Arr[n];}
		const reference	operator[](size_type n) const {return _Arr[n];}
		reference at (size_type n) {if (n >= _size) throw std::out_of_range("vector: element's out of bounds"); return _Arr[n];}
		const_reference at (size_type n) const {if (n >= _size) throw std::out_of_range("vector: element's out of bounds"); return _Arr[n];}
		reference front() {return _Arr[0];}
		const_reference front() const {return _Arr[0];}
		reference back() {return _Arr[_size - 1];}
		const_reference back() const {return _Arr[_size - 1];}

						//---- Modifiers ----//
		void	assign(size_type n, const value_type& val) {
			if (n > _Capacity)
				reserve(n);
			for(size_type i = 0; i < _size; i++)
					_alloc.destroy(&_Arr[i]);
			for(size_type i = 0; i < n; i++)
					_alloc.construct(&_Arr[i], val);
			_size = n;
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
		typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()){
			difference_type range = std::distance(first, last);
			if ((size_type)range > _Capacity)
				reserve(range);
			for(size_type i = 0; i < _size; i++)
				_alloc.destroy(&_Arr[i]);
			for(difference_type i = 0; i < range; i++)
				_alloc.construct(&_Arr[i], *first++);
			_size = range;
		}

		void push_back (const value_type& val) {
			if (!_Capacity)
				reserve(1);
            if (_size + 1 > _Capacity)
				reserve(_Capacity * 2);
            _Arr[_size++] = val;
		}

		void pop_back( void ) {if (_size && _Capacity)_alloc.destroy(&_Arr[--_size]);}

		iterator insert (iterator position, const value_type& val){
			difference_type pos = std::distance(begin(), position);
			if (!_Capacity)
				reserve(1);
			else if (_size + 1 > _Capacity)
				reserve(_Capacity * 2);
			for(difference_type i = _size - 1; i > pos; i--)
				_alloc.construct(&_Arr[i + 1], _Arr[0]);
			_alloc.construct(&_Arr[pos], val);	
			_size += 1;
			return iterator(&_Arr[pos]);
		}

		 void insert (iterator position, size_type n, const value_type& val){
			difference_type pos = std::distance(begin(), position);
			if (_size + n > _Capacity)	
			{
				int a = ((_Capacity * 2) > (_Capacity + n) ? (_Capacity * 2)  : (_Capacity + n) );
				reserve(a);
			}
			for(difference_type i = (_size - 1) + n; i > pos; i--)
			{
				if (i >= pos + (difference_type)n) 
					_alloc.construct(&_Arr[i], _Arr[0]);
				else
					_alloc.construct(&_Arr[i], val);
			}
			_alloc.construct(&_Arr[pos], val);
			_size += n;
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last,
			typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()){
			difference_type pos = std::distance(begin(), position);
			difference_type range = std::distance(first, last);
			if (_size + range > _Capacity)
			{
				int a = ((_Capacity * 2) > (_Capacity + range) ? (_Capacity * 2)  : (_Capacity + range) );
				reserve(a);
			}
			for(difference_type i = (_size - 1) + range; i > pos; i--)
			{
				if (i >= pos + range) 
					_alloc.construct(&_Arr[i], _Arr[0]);
				else
					_alloc.construct(&_Arr[i], *first++);
			}
			_alloc.construct(&_Arr[pos], *first);
			_size += range;
		}

		iterator erase (iterator position){
			difference_type pos = std::distance(begin(), position);
			_alloc.destroy(&_Arr[pos]);
			for (size_type i = pos; i < _size; i++)
				_alloc.construct(&_Arr[i], _Arr[i + 1]);
			_size--;
			return (&_Arr[pos]);
		}
 
		iterator erase (iterator first, iterator last){
			difference_type pos = std::distance(begin(), first);
			difference_type range = std::distance(first, last);
			for (size_type i = pos + range; i < _size; i++)
			{
				_alloc.destroy(&_Arr[i - range]);
				_alloc.construct(&_Arr[i - range], _Arr[i]);
			}
			_size -= range;
			return (&_Arr[pos]);
		}

		void swap (vector& x){
			value_type	*tmpArr = this->_Arr;
			size_type	tmpSize = this->_size;
			size_type	tmpCapacity = this->_Capacity;

			this->_Arr = x._Arr;
			this->_size = x._size;
			this->_Capacity = x._Capacity;

			x._size = tmpSize;
			x._Capacity = tmpCapacity;			
			x._Arr = tmpArr;
		}

		void clear( void ){
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_Arr[i]);
			_size = 0;
		}

/*    						{{..Memeber Variables..}}													*/
	private:
		value_type		*_Arr;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_Capacity;
};

template < class T, class Alloc>
	bool operator== (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2)
			return true;
        if (*first2 < *first1)
			return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template < class T, class Alloc>
	bool operator!= (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { return (!operator==(lhs, rhs)); }
template < class T, class Alloc>
	bool operator<  (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
template < class T, class Alloc>
	bool operator>  (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { return (operator<(rhs, lhs)); }
template < class T, class Alloc>
	bool operator<=  (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { return (!operator<(rhs, lhs)); }
template < class T, class Alloc>
	bool operator>=  (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { return (!operator<(lhs, rhs)); }

template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}

}
#endif

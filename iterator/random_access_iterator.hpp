#include "iterator_traits.hpp"

namespace ft{

template <class Iterator>
class random_access_iterator
{
	private:
		typedef	random_access_iterator<const Iterator>						const_iterator;
	public:
        typedef iterator_traits< iterator<std::random_access_iterator_tag, Iterator> > iterator_traits;
		typedef Iterator													iterator_type;
		typedef typename iterator_traits::iterator_category	iterator_category;
		typedef typename iterator_traits::value_type			value_type;
		typedef typename iterator_traits::difference_type	difference_type;
		typedef typename iterator_traits::pointer			pointer;
		typedef typename iterator_traits::reference			reference;

		operator const_iterator() const{
			return  const_iterator(this->_Ptr);
		}
		random_access_iterator( void ): _Ptr(nullptr) {}
		random_access_iterator( value_type *element ): _Ptr(element) {}
		random_access_iterator( const random_access_iterator &rhs ): _Ptr(rhs._Ptr) {}
		~random_access_iterator( void ) {}

		random_access_iterator &operator=( const random_access_iterator &rhs ) {
			if (this != &rhs)
				_Ptr = rhs._Ptr;
			return (*this);
		}

		pointer	operator->( void ) { return _Ptr; }
		reference operator*( void ) const { return *_Ptr; }

		reference operator[](difference_type rhs) const { return _Ptr[rhs]; }

		random_access_iterator	&operator+=(difference_type rhs) { _Ptr += rhs; return *this; }
		random_access_iterator	&operator-=(difference_type rhs) { _Ptr -= rhs; return *this; }

		random_access_iterator	&operator++() {++_Ptr; return *this;}
		random_access_iterator	&operator--() {--_Ptr; return *this;}
		random_access_iterator	operator++( int ) {
			random_access_iterator tmp(*this);
			++_Ptr;
			return tmp;
		};
		random_access_iterator	operator--( int ) {
			random_access_iterator tmp(*this);
			--_Ptr;
			return tmp;
		}

		//a + a | a - a
		difference_type operator+( const random_access_iterator &rhs) const {return _Ptr + rhs._Ptr;}
		difference_type operator-( const random_access_iterator &rhs) const {return _Ptr - rhs._Ptr;}

		//a + m | a - m 
		random_access_iterator operator+( difference_type rhs ) const {return random_access_iterator(_Ptr + rhs);}
		random_access_iterator operator-( difference_type rhs ) const {return random_access_iterator(_Ptr - rhs);}

		pointer	getData( void ) const {return _Ptr;}

	private:
		pointer	_Ptr;

};

//m + a
template < class T >
random_access_iterator<T> operator+(ptrdiff_t lhs, const random_access_iterator<T>& rhs) { return (rhs + lhs); }

template < class T >
bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.getData() == rhs.getData(); }

template < class T >
bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator==(lhs, rhs); }

template < class T >
bool operator<(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.getData() < rhs.getData(); }

template < class T >
bool operator>(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return operator<(rhs, lhs); }

template < class T >
bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator<(rhs, lhs); }

template < class T >
bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return !operator<=(lhs, rhs); }

}
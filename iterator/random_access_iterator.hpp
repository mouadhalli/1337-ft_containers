#include "iterator_traits.hpp"

template <class _Iter>
class random_access_iterator
{
	public:
		typedef _Iter														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

		random_access_iterator( void ): _Data(nullptr) {};
		random_access_iterator( value_type *element ): _Data(element) {};
		random_access_iterator( const random_access_iterator &rhs ): _Data(rhs._Data) {};
		~random_access_iterator( void ) {};

		random_access_iterator &operator=( const random_access_iterator &rhs ) { _Data = rhs._Data; return *this; };

		pointer	operator->( void ) { return _Data; };
		reference operator*( void ) { return *_Data; };

		reference operator[](difference_type rhs) const { return _Data[rhs]; };

		random_access_iterator	&operator+=(difference_type rhs) { _Data += rhs; return *this; };
		random_access_iterator	&operator-=(difference_type rhs) { _Data -= rhs; return *this; };

		random_access_iterator	&operator++() {++_Data; return *this;};
		random_access_iterator	&operator--() {--_Data; return *this;};
		random_access_iterator	operator++( int ) {
			random_access_iterator tmp(*this);
			++_Data;
			return *this;
		};
		random_access_iterator	operator--( int ) {
			random_access_iterator tmp(*this);
			--_Data;
			return *this;
		};

		//a + a | a - a
		difference_type operator+( const random_access_iterator &rhs) const {return _Data + rhs._Data;};
		difference_type operator-( const random_access_iterator &rhs) const {return _Data - rhs._Data;};

		//a + m | a - m 
		random_access_iterator operator+( difference_type rhs ) const {return random_access_iterator(_Data + rhs);};
		random_access_iterator operator-( difference_type rhs ) const {return random_access_iterator(_Data - rhs);};

		pointer	getData( void ) const {return _Data;};

	private:
		pointer	_Data;

};

//m + a
template < class T >
random_access_iterator<T> operator+(ptrdiff_t lhs, const random_access_iterator<T>& rhs) {return (rhs + lhs);}

template < class T >
bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.getData() == rhs.getData();}

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


#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

namespace ft{

template <class Iter>
class reverse_iterator
{
	public:
		typedef Iter                                       				iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type        value_type;
		typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
		typedef typename iterator_traits<iterator_type>::pointer           pointer;
		typedef typename iterator_traits<iterator_type>::reference         reference;

		reverse_iterator( void ): _Ptr() {};

		reverse_iterator (iterator_type it): _Ptr(--it) {}

		template <class U>
  		reverse_iterator (const reverse_iterator<U>& rev_it) {this->_Ptr = --rev_it.base();}


		~reverse_iterator( void ) {};

		iterator_type base() const {
			iterator_type tmp = _Ptr;
			++tmp;
			return tmp;
		}

		reference operator*() const {return *_Ptr;}
		pointer operator->() const {return &(*_Ptr);}

		reverse_iterator operator+ (difference_type n) const {return reverse_iterator(base() - n);}

		reverse_iterator& operator++() {
            --_Ptr;
            return (*this);
        }
        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

		reverse_iterator& operator+= (difference_type n) {
			_Ptr -= n;
			return (*this);
		};

		reverse_iterator operator- (difference_type n) const {return reverse_iterator(base() + n);}

		reverse_iterator& operator--() {
            ++_Ptr;
            return (*this);
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

		reverse_iterator& operator-= (difference_type n) {
			_Ptr += n;
			return (*this);
		};

        reference operator[] (difference_type n) const { return _Ptr[-n]; }

	private:
		iterator_type	_Ptr;

};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() == lhs.base();}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() != lhs.base();}

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() < lhs.base();}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() <= lhs.base();}

template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() > lhs.base();}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() >= lhs.base();}

template <class Iterator>
reverse_iterator<Iterator> operator+ (
	typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {return rev_it + n;}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
    const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return rhs.base() - lhs.base();}
	
}
#endif
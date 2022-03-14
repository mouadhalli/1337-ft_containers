
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

		reverse_iterator( void ): _Ptr(0) {};
		reverse_iterator( value_type *element ): _Ptr(element) {};
		reverse_iterator(const reverse_iterator &rhs): _Ptr(rhs._Ptr) {};
		~reverse_iterator( void ) {};

		reverse_iterator &operator=(const reverse_iterator &rhs) { _Ptr = rhs._Ptr; return *this; };

	private:
		pointer	_Ptr;

};

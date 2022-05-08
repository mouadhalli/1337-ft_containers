#ifndef UTILS_H
#define UTILS_H

namespace ft {

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

    template<class InputIt, class rhit>
	bool equal(InputIt first1, InputIt last1, rhit first2)
	{
		while (first1 != last1) {
		  if (!(*first1 == *first2))
		    return false;
		  ++first1; ++first2;
		}
		return true;
	}


	template<bool,typename T>
	struct enable_if{};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <bool is_integral, typename T>
	struct is_integral_base {
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_t : public is_integral_base<false, bool> {};

	template <>
		struct is_integral_t<bool> : public is_integral_base<true, bool> {};

	template <>
		struct is_integral_t<char> : public is_integral_base<true, char> {};

	template <>
		struct is_integral_t<signed char> : public is_integral_base<true, signed char> {};

	template <>
		struct is_integral_t<short int> : public is_integral_base<true, short int> {};
		
	template <>
		struct is_integral_t<int> : public is_integral_base<true, int> {};

	template <>
		struct is_integral_t<long int> : public is_integral_base<true, long int> {};

	template <>
		struct is_integral_t<long long int> : public is_integral_base<true, long long int> {};

	template <>
		struct is_integral_t<unsigned char> : public is_integral_base<true, unsigned char> {};

	template <>
		struct is_integral_t<unsigned short int> : public is_integral_base<true, unsigned short int> {};

	template <>
		struct is_integral_t<unsigned int> : public is_integral_base<true, unsigned int> {};

	template <>
		struct is_integral_t<unsigned long int> : public is_integral_base<true, unsigned long int> {};
		
	template <>
		struct is_integral_t<unsigned long long int> : public is_integral_base<true, unsigned long long int> {};

	template <typename T>
		struct is_integral : public is_integral_t<T> {};

}
#endif
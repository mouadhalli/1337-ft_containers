#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>

namespace ft {

	template <typename T>
	struct node {
	    T		data;
	    node	*left;
	    node	*right;
	    node	*parent;
		int		 height;
		int		 balanceFactor;
	};

	template <typename T, typename Compare = std::less<typename T::key_type>, typename Alloc = std::allocator<T> >
	class AVL {

		public:
			typedef T					value_type;
			typedef node<value_type>	node_type;
			typedef Alloc				allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other	rebind_type;
            typedef Compare 			key_compare;

			AVL(const allocator_type& alloc = allocator_type(), const key_compare &compare = key_compare())
				: _root(nullptr), _allocator(alloc), _Comp(compare) {}
			~AVL( void ) {}

			// AVL &operator=(AVL const &rhs){
			// 	if (this != &rhs) {
			// 		_root = rhs._root;
			// 	}
			// 	return *this;
			// }

			size_t	max(size_t a, size_t b) { return (a > b ? a : b); }
			size_t	height(node_type *node) { if (node == NULL) return 0; return node->height; }
			int		BalanceFactor(node_type *node) { return height(node->right) - height(node->left); }

			node_type	*new_Node(const value_type &val) {
				node_type	*newNode = _rebindAlloc.allocate(1);
				newNode->data = _allocator.allocate(1);
				_allocator.construct(newNode->data, val);
				newNode->parent = nullptr;
				newNode->left = nullptr;
				newNode->right = nullptr;
				newNode->height = 1;
				newNode->balanceFactor = 0;
				return newNode;
			}

			node_type	*insert(node_type *node, const value_type &val) {
				if (!node)
					return (new_Node(val));
				else if (_Comp(node->data->first, val.first)) // right insert
				{
					node->right = insert_value(node->right, value); // keep searching
					node->right->parent = node;
				}
				else // left insert
				{
					node->right = insert_value(node->right, value); // keep searching
					node->right->parent = node;
				}
				//update height
				node->height = 1 + max(height(node->right), height(node->left));
				node->balanceFactor = balanceFactor(node);
				//balance
				if (node->balanceFactor == -2)	// means its left heavy
				{
					if (node->left->balanceFactor <= 0) 
						// left left case
					else
						// left right case
				}
				else if (node->balanceFactor == 2)	// means its right heavy
				{
					if (node->right->balanceFactor >= 0)
						//right right case
					else
						//right left case
				}
				return node
			}

		private:
			node_type		*_root;
			allocator_type	_allocator;
			allocator_type	_rebindAlloc;
			key_compare		_Comp;

	};
};
#endif
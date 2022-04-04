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
			/*

					   z                               y
					 /  \                            /   \ 
					T1   y     Left Rotate(z)       z      x
					    /  \   - - - - - - - ->    / \    / \
					   T2   x                     T1  T2 T3  T4
					       / \
					     T3  T4
			*/

			node_type	*leftRotate(node_type *z) {
				node_type *y = z->right;
				node_type *T2 = y->left;
				y->left = z;
				z->right = T2;
				z->height = max(height(z->left),
				        height(z->right)) + 1;
				y->height = max(height(y->left),
				        height(y->right)) + 1;
				return y;
			}

			/*
			         z                                      y 
			        / \                                   /   \
			       y   T4      Right Rotate (z)          x      z
			      / \          - - - - - - - - ->      /  \    /  \ 
			     x   T3                               T1  T2  T3  T4
			    / \
			  T1   T2
			*/

			node_type	*rightRotate(node_type *z) {
				node_type *y = z->left;
				node_type *T3 = y->right;
				y->right = z;
				z->left = T3;
				z->height = max(height(z->left),
				        height(z->right)) + 1;
				y->height = max(height(y->left),
				        height(y->right)) + 1;
				return y;
			}

			node_type	*insert(node_type *node, const value_type &val) {
				if (!node)
					return (new_Node(val));
				else if (_Comp(node->data->first, val.first)) // right insert
				{
					node->right = insert_value(node->right, val); // keep searching
					node->right->parent = node;
				}
				else // left insert
				{
					node->right = insert_value(node->right, val); // keep searching
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
						node = rightRotate(node);
					else
					{
						// left right case
						node->left = leftRotate(node->left);
						node = rightRotate(node);
					}
				}
				else if (node->balanceFactor == 2)	// means its right heavy
				{
					if (node->right->balanceFactor >= 0)
						//right right case
						node = leftRotate(node);
					else
						//right left case
						node->right = rightRotate(node->right);
						node = leftRotate(node);
				}
				return node;
			}

		private:
			node_type		*_root;
			allocator_type	_allocator;
			allocator_type	_rebindAlloc;
			key_compare		_Comp;

	};
};
#endif
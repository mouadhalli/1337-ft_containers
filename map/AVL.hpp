#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "../iterator/bidirectional_iterator.hpp"

namespace ft {

	template <typename T>
	struct node {
	    T		*data;
	    node	*left;
	    node	*right;
	    node	*parent;
		int		 height;
		int		 balanceFactor;
	};

	template <typename T, typename Compare = std::less<typename T::key_type>, typename Alloc = std::allocator<T> >
	class AVL {

		public:
			typedef T																		value_type;
			typedef node<value_type>														node_type;
			typedef	typename value_type::key_type											key_type;
			typedef Alloc																	allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other				rebind_type;
            typedef Compare 																key_compare;
			typedef ft::bidirectional_iterator< value_type, node_type, AVL >				iterator;

			AVL( void )
				: _root(nullptr), _size(0) {}
			~AVL( void ) {}

			// AVL &operator=(AVL const &rhs){
			// 	if (this != &rhs) {
			// 		_root = rhs._root;
			// 	}
			// 	return *this;
			// }

			size_t	max(size_t a, size_t b) { return (a > b ? a : b); }
			size_t	height(node_type *node) {
				if (node == NULL)
					return 0;
				return node->height;
			}


			node_type	*new_Node(const value_type &val) {
				node_type	*newNode = _rebindAlloc.allocate(1);
				newNode->data = _Alloc.allocate(1);
				_Alloc.construct(newNode->data, val);
				newNode->parent = nullptr;
				newNode->left = nullptr;
				newNode->right = nullptr;
				newNode->height = 1;
				newNode->balanceFactor = 0;
				return newNode;
			}

			void	FreeNode(node_type *node)
			{
				_Alloc.destroy(node->data);
				_Alloc.deallocate(node->data, 1);
				_rebindAlloc.deallocate(node, 1);
			}

			void	deleteTree(node_type *node) {
				if (node)
				{
					deleteTree(node->left);
					deleteTree(node->right);
					FreeNode(node);
				}
			}

			void	clear(void) {deleteTree(_root); _root = nullptr;}

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
				y->parent = z->parent;
				z->parent = y;
				z->height = max(height(z->right),
				        height(z->left)) + 1;
				y->height = max(height(y->right),
				        height(y->left)) + 1;
				z->balanceFactor = height(z->right) - height(z->left);
				y->balanceFactor = height(y->right) - height(y->left);

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
				y->parent = z->parent;
				z->parent = y;
				z->height = max(height(z->right),
				        height(z->left)) + 1;
				y->height = max(height(y->right),
				        height(y->left)) + 1;
				z->balanceFactor = height(z->right) - height(z->left);
				y->balanceFactor = height(y->right) - height(y->left);
				return y;
			}

			node_type	*Balance(node_type *node) {
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
					{
						//right left case
						node->right = rightRotate(node->right);
						node = leftRotate(node);
					}
				}
				return node;
			}

			node_type	*insert_val(node_type *node, const value_type &val) {
				if (!node)
					return (new_Node(val));
				else if (_Comp(node->data->_key, val._key)) // left insert
				{
					node->right = insert_val(node->right, val); // keep searching
					node->right->parent = node;
				}
				else // right insert
				{
					node->left = insert_val(node->left, val); // keep searching
					node->left->parent = node;
				}
				//update node
				node->height = 1 + max(height(node->right), height(node->left));
				node->balanceFactor = height(node->right) - height(node->left);
				return (Balance(node));
			}

			bool	exist(node_type *node, const key_type &key) const {
				if (node)
				{
					if (!_Comp(node->data->_key, key) && !_Comp(key, node->data->_key))
						return true;
					else if (_Comp(node->data->_key, key))
						return exist(node->right, key);
					else if (!_Comp(node->data->_key, key))
						return exist(node->left, key);
				}
				return false;
			}

			node_type	*find(node_type *node, const key_type &key) {
				if (node)
				{
					if (!_Comp(node->data->_key, key) && !_Comp(key, node->data->_key))
						return node;
					else if (_Comp(node->data->_key, key))
						return exist(node->right, key);
					else if (!_Comp(node->data->_key, key))
						return exist(node->left, key);
				}
				return nullptr;
			}

			bool	insert(const value_type &val) {
				if (!exist(_root, val._key))
				{
					_root = insert_val(_root, val);
					_root->parent = nullptr;
					_size++;
					return (true);
				}
				return (false);
			}

			node_type	*maxValueNode(node_type	*node)
			{
			    node_type	*current = node;
			    while (current->right != NULL)
			        current = current->right;

			    return current;
			}

			node_type	*minValueNode(node_type	*node)
			{
			    node_type	*current = node;
			    while (current->left != NULL)
			        current = current->left;

			    return current;
			}

			node_type	*inorderSuccessor(node_type *currentNode) {

				node_type *ParentNode = nullptr;

				if (currentNode)
				{
					if (currentNode->right)
						return minValueNode(currentNode->right);
					else
					{
						ParentNode = currentNode->parent;
						while (ParentNode && currentNode == ParentNode->right)
						{
							currentNode = ParentNode;
							ParentNode = ParentNode->parent;
						}
					}
				}
				return (ParentNode);
			}

			node_type	*inorderPredecessor(node_type *currentNode) {

				node_type *ParentNode = nullptr;

				if (currentNode)
				{
					if (currentNode->left)
						return maxValueNode(currentNode->left);
					else
					{
						ParentNode = currentNode->parent;
						while (ParentNode && currentNode == ParentNode->left)
						{
							currentNode = ParentNode;
							ParentNode = ParentNode->parent;
						}
					}
				}
				return (ParentNode);
			}

			node_type	*getRoot( void ) {return _root;}

		/*
			       y 
			     /   \
			    x      z
			  /  \    /  \ 
			 T1  T2  T3  T4
		*/

			/*delete node with a given key
				- check if the node exist
				- check for the deletion case:
					- node with no childs
					- node with 1 child
					- node with 2 childs:
		*/

			node_type	*RemoveNode(node_type *node, key_type &key)
			{
				if (!node)
					return nullptr;
				if (_Comp(node->data->_key, key))
					node->right = RemoveNode(node->right, key);
				else if (_Comp(key, node->data->_key))
					node->left = RemoveNode(node->left, key);
				else
				{
					if (!node->right)
						return node->left;
					else if (!node->left)
						return node->right;
					else
					{
                        node_type	*successorVal = maxValueNode(node->left);
                        node->data = successorVal->data;
                        node->left = RemoveNode(node->left, successorVal->data->_key);
                    }
				}
				node->height = 1 + max(height(node->right), height(node->left));
				node->balanceFactor = height(node->right) - height(node->left);
				return Balance(node);
			}

			bool	erase(const key_type &key)
			{
				if (exist(_root, key))
				{
					_root = RemoveNode(_root, key);
					_size--;
					return (true);
				}
				return (false);
			}

			bool	IsEmpty( void ) const {
				if (!_size)
					return true;
				return false;
			}

			bool	count(const key_type &key) const { return exist(_root, key);}

			iterator	begin( void ) {return iterator(minValueNode(_root), this);}
			iterator	end( void ) {return iterator(nullptr, this);}


	struct Trunk
	{
	    Trunk *prev;
	    std::string str;
	
	    Trunk(Trunk *prev, std::string str)
	    {
	        this->prev = prev;
	        this->str = str;
	    }
	};
 
	// Helper function to print branches of the binary tree
	void showTrunks(Trunk *p)
	{
	    if (p == nullptr) {
	        return;
	    }
	
	    showTrunks(p->prev);
	    std::cout << p->str;
	}
	
	void printTree(node_type* root, Trunk *prev, bool isLeft)
	{
	    if (root == nullptr) {
	        return;
	    }
	
	    std::string prev_str = "    ";
	    Trunk *trunk = new Trunk(prev, prev_str);
	
	    printTree(root->right, trunk, true);
	
	    if (!prev) {
	        trunk->str = "———";
	    }
	    else if (isLeft)
	    {
	        trunk->str = ".———";
	        prev_str = "   |";
	    }
	    else {
	        trunk->str = "`———";
	        prev->str = prev_str;
	    }
	
	    showTrunks(trunk);
	    std::cout << " " << root->data->_key << std::endl;
	
	    if (prev) {
	        prev->str = prev_str;
	    }
	    trunk->str = "   |";
	
	    printTree(root->left, trunk, false);
	}

	void	print() {printTree(_root, nullptr, false);}
	
		void __print(node_type *root, int space) {
			if (root == NULL)
				return;
			space += 8;
			__print(root->right, space);
			std::cout << std::endl;
			for (int i = 10; i < space; i++)
				std::cout << " ";
			std::cout << root->data->_key << std::endl;
			__print(root->left, space);
			// std::cout << "Node Key => " << root->data->_key << " BF => " << root->balanceFactor << std::endl;
		}
	// void	print() {__print(_root, 0);}

		private:
			node_type		*_root;
			allocator_type	_Alloc;
			rebind_type		_rebindAlloc;
			key_compare		_Comp;
			size_t			_size;

	};
};
#endif
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "../iterator/bidirectional_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

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
			typedef ft::bidirectional_iterator<const value_type, const node_type, AVL >		const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

			AVL( void ) : _root(nullptr), _size(0) {}
			~AVL( void ) {}

			AVL &operator=(AVL const &rhs){
				if (this != &rhs) {
					deleteTree(_root);
					_root = nullptr;
					insertTree(rhs._root);
					_Alloc	= rhs._Alloc;
					_rebindAlloc = rhs._rebindAlloc;
					_Comp = rhs._Comp;
					_size = rhs._size;
				}
				return *this;
			}

			void 	insertTree(node_type *node) {
				if (node)
				{
					insert(*node->data);
					insertTree(node->right);
					insertTree(node->left);
				}
				return;
			}

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
				if (node)
				{
					node->parent = nullptr;
					_Alloc.destroy(node->data);
					_Alloc.deallocate(node->data, 1);
					_rebindAlloc.deallocate(node, 1);
					node = nullptr;
				}
				return;
			}

			void	deleteTree(node_type *node) {
				if (node)
				{
					deleteTree(node->left);
					deleteTree(node->right);
					FreeNode(node);
				}
				return;
			}

			void	clear(void) {
				deleteTree(_root);
				_root = nullptr;
				_size = 0;
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
				y->parent = z->parent;
				z->parent = y;
				y->left = z;
				z->right = T2;
				if (T2)
				{
					T2->parent = z;
					T2->height = max(height(T2->right),
				        height(T2->left)) + 1;
					T2->balanceFactor = height(T2->right) - height(T2->left);

				}
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
				y->parent = z->parent;
				y->right = z;
				z->parent = y;

				z->left = T3;
				if (T3)
				{
					T3->parent = z;
					T3->height = max(height(T3->right),
				        height(T3->left)) + 1;
					T3->balanceFactor = height(T3->right) - height(T3->left);
				}
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

			bool	exist(node_type *node, const key_type &key) const {
				if (node)
				{
					if (!_Comp(node->data->first, key) && !_Comp(key, node->data->first))
						return true;
					else if (_Comp(node->data->first, key))
						return exist(node->right, key);
					else if (!_Comp(node->data->first, key))
						return exist(node->left, key);
				}
				return false;
			}

			node_type	*find(node_type *node, const key_type &key) {
				if (node)
				{
					if (!_Comp(node->data->first, key) && !_Comp(key, node->data->first))
						return node;
					else if (_Comp(node->data->first, key))
						return find(node->right, key);
					else if (!_Comp(node->data->first, key))
						return find(node->left, key);
				}
				return nullptr;
			}

			node_type	*find(node_type *node, const key_type &key) const {
				if (node)
				{
					if (!_Comp(node->data->first, key) && !_Comp(key, node->data->first))
						return node;
					else if (_Comp(node->data->first, key))
						return find(node->right, key);
					else if (!_Comp(node->data->first, key))
						return find(node->left, key);
				}
				return nullptr;
			}

			node_type	*find_Succesor(const key_type &key)
			{
				node_type	*current = _root;
				node_type	*succesor = nullptr;

				while (current != nullptr)
				{
					if (_Comp(key, current->data->first))
					{
						succesor = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return (succesor);
			}

			node_type	*find_Succesor(const key_type &key) const
			{
				node_type	*current = _root;
				node_type	*succesor = nullptr;

				while (current != nullptr)
				{
					if (_Comp(key, current->data->first))
					{
						succesor = current;
						current = current->left;
					}
					else
						current = current->right;
				}
				return (succesor);
			}

			node_type	*insert_val(node_type *node, const value_type &val) {
				if (!node)
					return (new_Node(val));
				else if (_Comp(node->data->first, val.first)) // left insert
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

			bool	insert(const value_type &val) {
				if (!exist(_root, val.first))
				{
					_root = insert_val(_root, val);
					_root->parent = nullptr;
					_size++;
					return (true);
				}
				return (false);
			}

			node_type	*maxValueNode( node_type	*node)
			{
				if (node)
				{
			    	while (node->right != NULL)
			    	    node = node->right;
				}
			    return node;
			}

			node_type	*minValueNode( node_type	*node)
			{
				if (node)
				{
			    	while (node->left != NULL)
			    	    node = node->left;
				}
			    return node;
			}

			node_type	*maxValueNode( node_type	*node) const
			{
				if (node)
				{
			    	while (node->right != NULL)
			    	    node = node->right;
				}
			    return node;
			}

			node_type	*minValueNode( node_type	*node) const
			{
				if (node)
				{
			    	while (node->left != NULL)
			    	    node = node->left;
				}
			    return node;
			}

			node_type	*inorderSuccessor(const node_type *currentNode) {

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

			node_type	*inorderSuccessor(const node_type *currentNode) const {

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

			node_type	*inorderPredecessor(const node_type *currentNode) {

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

			node_type	*inorderPredecessor(const node_type *currentNode) const {

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

			node_type	*getRoot( void ) const {return _root;}

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
				node_type *tmp = nullptr;
				if (!node)
					return nullptr;
				if (_Comp(node->data->first, key))
				{
					node->right = RemoveNode(node->right, key);
					if (node->right)
						node->right->parent = node;
				}
				else if (_Comp(key, node->data->first))
				{
					node->left = RemoveNode(node->left, key);
					if (node->left)
						node->left->parent = node;
				}
				else
				{
					if (!node->right)
					{
						tmp = node->left;
						FreeNode(node);
						return tmp;
					}
					else if (!node->left)
					{
						tmp = node->right;
						FreeNode(node);
						return tmp;
					}
					else
					{
                        node_type	*successorVal = minValueNode(node->right);
						_Alloc.construct(node->data, *successorVal->data);
                        node->right = RemoveNode(node->right, successorVal->data->first);
						if (node->right)
							node->right->parent = node;
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
					if (_root)
						_root->parent = nullptr;
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

			size_t size() const {return _size;}
			size_t max_size() const { return _Alloc.max_size();}

			bool	count(const key_type &key) const { return exist(_root, key);}

			iterator		begin( void ) {return iterator(minValueNode(_root), this);}
			const_iterator	begin() const {
				const node_type *tmp = reinterpret_cast< const node_type *>(minValueNode(_root));
				// const node_type *tmp = nullptr;


				return const_iterator(tmp, this);
			}

			iterator		end( void ) {return iterator(nullptr, this);}
			const_iterator	end() const {return const_iterator(nullptr, this);}

			reverse_iterator rbegin() {return reverse_iterator(this->end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(this->end());}

			reverse_iterator rend() {return  reverse_iterator(this->begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}

			void swap (AVL& x) {
				std::swap(_root, x._root);
				std::swap(_Alloc, x._Alloc);
				std::swap(_rebindAlloc, x._rebindAlloc);
				std::swap(_Comp, x._Comp);
				std::swap(_size, x._size);
			}


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
	    std::cout << " " << root->data->first << std::endl;
	    // std::cout << " " << root->data->first << "|" << root->parent->data->first << std::endl;
	
	    if (prev) {
	        prev->str = prev_str;
	    }
	    trunk->str = "   |";
	
	    printTree(root->left, trunk, false);
	}

	void	print() {
		if (_root)
			printTree(_root, nullptr, false);
	}

		private:
			node_type		*_root;
			allocator_type	_Alloc;
			rebind_type		_rebindAlloc;
			key_compare		_Comp;
			size_t			_size;

	};
};
#endif
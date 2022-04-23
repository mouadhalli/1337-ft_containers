#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

    template < typename T, typename NodeType, typename TreeType >
    class bidirectional_iterator {
        public:
			typedef T	iterator_type;		
            typedef	iterator_traits< iterator<std::bidirectional_iterator_tag, iterator_type> > iterator_traits;
			typedef typename iterator_traits::iterator_category	iterator_category;
			typedef typename iterator_traits::value_type		value_type;
			typedef typename iterator_traits::difference_type	difference_type;
			typedef typename iterator_traits::pointer			pointer;
			typedef typename iterator_traits::reference			reference;

			bidirectional_iterator() : _Node(), _Tree() {}
			bidirectional_iterator(NodeType *node, const TreeType *tree) : _Node(node), _Tree(tree) {}
			bidirectional_iterator( const bidirectional_iterator &rhs ) {*this = rhs;}
			~bidirectional_iterator( void ) {};

			bidirectional_iterator &operator=( const bidirectional_iterator &rhs ) {
				if (this != &rhs)
				{
					_Node = rhs._Node;
					_Tree = rhs._Tree;
				}
				return (*this);
			}

            pointer   operator->() const { return _Node->data; }
            reference operator*() const { return *_Node->data; }

			operator bidirectional_iterator<const value_type, const NodeType, TreeType>() const {
				return bidirectional_iterator<const value_type, const NodeType, TreeType>(_Node, _Tree);
			}
/*
	increment iterator:
		- iterator should be pointing to a node so we can find the next one
			- next node => currentNode < nextNode : (first node that is greater than the current one)
				this means that we should find its inorder successor (Inorder Successor of an input node can also be defined
				as the node with the smallest key greater than the key of the input node)
					- to find the innordesuccesor node there is two cases:
						1 - if currentNode have a right subtree then its inordesuccesor is the min key traveling from there
						2 - if currentNode doesn't have a right subtree then the innordesuccesor is one of its incestors
							we should travel up and find a node which its left subtree is our currentNode node
							T1 = currentNode     | x = currentNode
							x = innordersuccesor | T2 = innordersuccesor
										       y 
										     /   \
										    x     z
										  /  \    /  \ 
										 T1  T2  T3  T4
*/
			bidirectional_iterator	&operator++() {
				if (_Tree)
				{
					if (!_Node)
						_Node = _Tree->minValueNode(_Tree->getRoot());
					else
						_Node = _Tree->inorderSuccessor(_Node);	
				}
				return (*this);
			}

			bidirectional_iterator	&operator--() {
				if (_Tree)
				{
					if (!_Node)
						_Node = _Tree->maxValueNode(_Tree->getRoot());
					else
						_Node = _Tree->inorderPredecessor(_Node);	
				}
				return (*this);
			}

            bidirectional_iterator operator++(int) {
				bidirectional_iterator tmpIter(*this); 
				++(*this);
				return (tmpIter);
			}
            bidirectional_iterator operator--(int) {
				bidirectional_iterator tmpIter(*this);
				--(*this);
				return (tmpIter);
			}

			NodeType	*getNode( void ) const { return _Node; }

		private:
			NodeType	*_Node;
			TreeType const *_Tree;
    };

	template < typename T, typename NodeType, typename TreeType >
	bool	operator==(const bidirectional_iterator<T, NodeType, TreeType> &lhs, const bidirectional_iterator<T, NodeType, TreeType> &rhs){
		return lhs.getNode() == rhs.getNode();
	}

	template < typename T, typename NodeType, typename TreeType >
	bool	operator!=(const bidirectional_iterator<T, NodeType, TreeType> &lhs, const bidirectional_iterator<T, NodeType, TreeType> &rhs){
		return lhs.getNode() != rhs.getNode();
	}

}

#endif
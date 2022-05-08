#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

namespace ft {

    template < typename T, typename NodeType, typename TreeType >
    class bidirectional_iterator {

        public:
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef	T											value_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type*									pointer;
			typedef value_type&									reference;

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
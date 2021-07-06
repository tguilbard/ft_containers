/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 11:02:13 by user42            #+#    #+#             */
/*   Updated: 2021/07/06 17:03:14 by tguilbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include <memory>
# include <functional>
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{

template <typename T, class Compare >
class BT_iterator : public Iterator_Trait
{
	public :
		typedef typename T::value_type	value_type;
		typedef value_type				*pointer;
		typedef value_type&				reference;

		BT_iterator(const Compare& comp = Compare())
		: _node(), _last_node(), _comp(comp)
		{}

		BT_iterator(T * node_p, T * last_node, const Compare& comp = Compare())
		: _node(node_p), _last_node(last_node), _comp(comp)
		{}

		BT_iterator(const BT_iterator& bst_it)
		: _node(bst_it._node), _last_node(bst_it._last_node), _comp()
		{}

		virtual ~BT_iterator()
		{}

		BT_iterator &operator=(const BT_iterator& bst_it)
		{
			if (*this == bst_it)
				return (*this);
			_node = bst_it._node;
			_last_node = bst_it._last_node;
			_comp = bst_it._comp;
			return (*this);
		}

		bool operator==(const BT_iterator& bst_it)
		{return _node == bst_it._node;}

		bool operator!=(const BT_iterator& bst_it)
		{return _node != bst_it._node;}

		reference operator*() const
		{return _node->data;}

		pointer operator->() const
		{return &_node->data;}

		BT_iterator& operator++(void)
		{
			T* cursor = _node;

			if (_node->right == _last_node)
			{
				cursor = _node->parent;
				while (cursor != _last_node && _comp(cursor->data.first, _node->data.first))
					cursor = cursor->parent;
				_node = cursor;
			}
			else if (cursor == _last_node)
				_node = _last_node->right;
			else
			{
				cursor = _node->right;
				if (cursor == _last_node->parent
					&& cursor->right == _last_node)
					_node = cursor;
				else
				{
					while (cursor->left != _last_node)
						cursor = cursor->left;
				}
				_node = cursor;
			}
			return (*this);
		}

		BT_iterator operator++(int)
		{
			BT_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		BT_iterator& operator--(void)
		{
			T* cursor = _node;

			if (_node->left == _last_node)
			{
				cursor = _node->parent;
				while (cursor != _last_node
					&& !_comp(cursor->data.first, _node->data.first))
					cursor = cursor->parent;
				_node = cursor;
			}
			else if (cursor == _last_node)
				_node = _last_node->right;
			else
			{
				cursor = _node->left;
				if (cursor == _last_node->parent
					&& cursor->left == _last_node)
					_node = cursor;
				else
				{
					while (cursor->right != _last_node)
						cursor = cursor->right;
				}
				_node = cursor;
			}
			return (*this);
		}

		BT_iterator operator--(int)
		{
			BT_iterator tmp(*this);
			operator--();
			return (tmp);
		}            

		T *			_node;
		T *			_last_node;
		Compare     _comp;
};

template<typename T>
struct tree_node
{
	typedef T	value_type;

	T			data;
	tree_node	*parent;
	tree_node	*left;
	tree_node	*right;

	tree_node (tree_node* parent = 0, tree_node* left = 0, tree_node* right =0)
	: data(), parent(parent), left(left), right(right)
	{}

	tree_node (const T& data, tree_node* parent = 0, tree_node* left = 0, tree_node* right =0)
	: data(data), parent(parent), left(left), right(right)
	{}
};

template <class T, class Compare = std::less<T>, class Node = tree_node<T>,
class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
class binary_tree
{
	public :
		typedef binary_tree					self;
		typedef self&								self_reference;
		typedef T									value_type;
		typedef Node								node_type;
		typedef Node *								node_pointer;
		typedef Node_Alloc							node_alloc;
		typedef BT_iterator<Node, Compare>			iterator;
		typedef BT_iterator<Node, Compare>	const_iterator;
		typedef typename Type_Alloc::size_type		size_type;

		binary_tree (const node_alloc& node_alloc_init = node_alloc())
		: _node_alloc(node_alloc_init), _size(0)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
		}

		~binary_tree ()
		{
			_node_alloc.destroy(_last_node);
			_node_alloc.deallocate(_last_node, 1);	
		}

		ft::pair<iterator, bool> insertPair(value_type to_insert)
		{
			Node * new_node = _node_alloc.allocate(1);
			Node * prev_node = _last_node;
			Node * start_node = _last_node->parent;

			bool side = true;

			while (start_node != _last_node)
			{
				typename value_type::first_type curkey = start_node->data.first;
				if (curkey == to_insert.first)
					return (ft::pair<iterator, bool>(iterator(start_node, _last_node), false));
				prev_node = start_node;
				if (to_insert.first > curkey)
				{
					side = true;
					start_node = start_node->right;
				}
				else
				{
					side = false;
					start_node = start_node->left;
				}
			}
			_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));

			if (prev_node == _last_node)
				_last_node->parent = new_node;
			else if (side == true)
				prev_node->right = new_node;
			else
				prev_node->left = new_node;

			_last_node->left = _BT_get_lower_node(_last_node->parent);
			_last_node->right = _BT_get_higher_node(_last_node->parent);
			_size += 1;
			return (ft::pair<iterator, bool>(iterator(new_node, _last_node), true));
		}

		void removeByKey(value_type to_remove)
		{_removeByKey(_last_node->parent, to_remove);}

		node_pointer searchByKey(value_type to_remove)
		{
			node_pointer node = _last_node->parent;

			while (node != _last_node)
			{
				if (node->data.first > to_remove.first)
					node = node->left;
				else if  (node->data.first < to_remove.first)
					node = node->right;
				else
					return (node);
			}
			return (node);
		}

		void swap(self& x)
		{
			if (&x == this)
				return ;

			node_pointer save = this->_last_node;
			this->_last_node = x._last_node;
			x._last_node = save;
		}

		size_type max_size() const
		{ return (node_alloc().max_size()); }

		node_pointer    _last_node;
		node_alloc      _node_alloc;
		size_type		_size;

	private :

		node_pointer _BT_get_lower_node(node_pointer root)
		{
			while (root != _last_node && root->left != _last_node)
				root = root->left;
			return (root);
		}

		node_pointer _BT_get_higher_node(node_pointer root)
		{
			while (root != _last_node && root->right != _last_node)
				root = root->right;
			return (root);
		}

		void _replaceNodeInParent(node_pointer node, node_pointer new_node)
		{
			if (node->parent != _last_node)
			{
				if (_last_node->parent == node)
					_last_node->parent = new_node;

				if (node == node->parent->left)
					node->parent->left = new_node;
				else
					node->parent->right = new_node;
			}
			else
				_last_node->parent = new_node;

			_last_node->left = _BT_get_lower_node(_last_node->parent);
			_last_node->right = _BT_get_higher_node(_last_node->parent);
			_size -= 1;

			if (new_node != _last_node)
				new_node->parent = node->parent;

			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}

		void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)
		{
			if (new_node->parent != _last_node)
			{
				if (new_node->parent != to_remove)
					new_node->parent->left = new_node->right;
			}
			
			new_node->parent = to_remove->parent;
			if (to_remove->left != new_node)
				new_node->left = to_remove->left;
			if (to_remove->right != new_node)
				new_node->right = to_remove->right;

			if (to_remove->parent != _last_node)
			{
				if (to_remove->parent->left == to_remove)
					to_remove->parent->left = new_node;
				else if (to_remove->parent->right == to_remove)
					to_remove->parent->right = new_node;
			}
			else
				_last_node->parent = new_node;
				
			if (to_remove->left != _last_node && to_remove->left != new_node)
				to_remove->left->parent = new_node;
			if (to_remove->right != _last_node && to_remove->right != new_node)
				to_remove->right->parent = new_node;

			if (to_remove->parent != _last_node)
			{
				to_remove->left = _last_node;
				to_remove->right = _last_node;
				to_remove->parent = new_node;
			}

			_last_node->left = _BT_get_lower_node(_last_node->parent);
			_last_node->right = _BT_get_higher_node(_last_node->parent);
			_size -= 1;

			_node_alloc.destroy(to_remove);
			_node_alloc.deallocate(to_remove, 1);
		}

		void _removeByKey(node_pointer node, value_type to_remove)
		{
			if (to_remove.first < node->data.first)
			{
				_removeByKey(node->left, to_remove);
				return ;
			}

			if (to_remove.first > node->data.first)
			{
				_removeByKey(node->right, to_remove);
				return ;
			}
			
			if (node->left != _last_node && node->right != _last_node)
			{
				node_pointer successor = _BT_get_lower_node(node->right);
				_replaceDoubleChildren(node, successor);
				return ;
			}
			else if (node->left != _last_node)
				_replaceNodeInParent(node, node->left);
			else if (node->right != _last_node)
				_replaceNodeInParent(node, node->right);
			else
				_replaceNodeInParent(node, _last_node);
		}
};

}

#endif

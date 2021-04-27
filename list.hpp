/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:02:47 by user42            #+#    #+#             */
/*   Updated: 2021/04/27 17:55:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "utils.hpp"

template<typename T>
struct node
{
	T data;
	struct node *next;
	struct node *previous;
};

template<typename T, class allocator =std::allocator<T> >
class list;

template<typename T>
class list_iterator
{
	public :
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T &reference;
		typedef const T& const_reference;
		typedef typename std::ptrdiff_t difference_type;

	private :
		typedef list_iterator<T> self;
		node<T>* _node;

	public :
		list_iterator() : _node(0) {}
		list_iterator(node<T>* ptr) : _node(ptr) {}
		list_iterator(const self &to_copy) : _node(to_copy._node) {}
		self &operator=(const self &to_copy) {_node = to_copy._node; return *this;}
		~list_iterator() {}
		self &operator++() {_node = _node->next; return *this;}
		self &operator++(int) {_node = _node->next; return *this;}
		self &operator--() {_node = _node->previous; return *this;}
		self &operator--(int) {_node = _node->previous; return *this;}
		reference operator*() {return _node->data;}
		const_reference operator*() const {return _node;}
		node<T> *operator->() {return _node;}
		node<const T> *operator->() const {return _node;}

		bool operator==(const list_iterator &to_comp)
		{return _node == to_comp._node;}
		bool operator!=(const list_iterator &to_comp)
		{return _node != to_comp._node;}

};

template<typename T>
class const_list_iterator : public list_iterator<T>
{
	public :
		const_list_iterator() : list_iterator<T>() {}
		const_list_iterator(node<T>* ptr) : list_iterator<T>(ptr) {}
		const_list_iterator(const list_iterator<T> &to_copy) : list_iterator<T>(to_copy) {}
		~const_list_iterator() {}
};

# include "revers.hpp"

template<typename T, class allocator>
class list
{
	public:
		typedef T 									value_type;
		typedef allocator							allocator_type;
 		typedef typename allocator::reference		reference;
		typedef typename allocator::const_reference	const_reference;
		typedef typename allocator::pointer			pointer;
		typedef typename allocator::const_pointer	const_pointer;
		typedef list_iterator<value_type>			iterator;
		typedef const_list_iterator<value_type>		const_iterator;
		typedef reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef reverse_iterator<iterator>			reverse_iterator;
		typedef typename std::ptrdiff_t				difference_type;
		typedef typename allocator::size_type		size_type;
	
	private :
		typedef list<T> self;
		typedef node<T> node;
	
		node* _node;
		size_type _len;
		allocator_type _alloc;

	public :

		explicit  list(const allocator_type& alloc = allocator_type())
		: _node(0), _len(0), _alloc(alloc)
		{_node = new node; _node->data = value_type(); _node->previous = _node; _node->next = _node;}

		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _node(0), _len(0), _alloc(alloc)
		{
			_node = new node; _node->data = value_type(); _node->previous = _node; _node->next = _node;
			insert(begin(), n, val);
		}

		template<class it_type>
		list(it_type first, it_type last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<it_type>::value, it_type>::type* = 0)
		: _node(0), _len(0), _alloc(alloc)
		{
			_node = new node; _node->data = value_type(); _node->previous = _node; _node->next = _node;
			insert(begin(), first, last);
		}

		list(const self& to_copy)
		: _node(0), _len(0), _alloc(to_copy._alloc)
		{
			_node = new node; _node->data = value_type(); _node->previous = _node; _node->next = _node;
			insert(begin(), to_copy.begin(), to_copy.end());
		}

		~list()
		{
			clear();
			delete _node;
		}

		self& operator=(const self &to_copy)
		{
			clear();
			insert(begin(), to_copy.begin(), to_copy.end());
			return *this;
		}

		iterator begin()
		{return _node->next;}
		const_iterator begin() const
		{return _node->next;}
		iterator end()
		{return _node;}
		const_iterator end() const
		{return _node;}
		reverse_iterator rbegin()
		{return iterator(_node->previous);};
		const_reverse_iterator rbegin() const
		{return const_iterator(_node->previous);};
		reverse_iterator rend()
		{return iterator(_node);}
		const_reverse_iterator rend() const
		{return const_iterator(_node);}

		bool empty() const
		{return _len;}
		size_type size() const
		{return _len;}
		size_type max_size() const
		{return allocator_type().max_size();}

		reference front()
		{return begin()->data;}
		const reference front() const
		{return begin()->data;}

		reference back()
		{return rbegin()->data;}
		const reference back() const
		{return rbegin()->data;}

		template<class it_type>
		void assign(it_type first, it_type last, typename ft::enable_if<!ft::is_integral<it_type>::value, it_type>::type* = 0)
		{
			clear();
			insert(begin(), first, last);
		}
		void assign(size_type n, const value_type& val)
		{
			clear();
			insert(begin(), n, val);
		}

		void pop_front()
		{
			node *tmp = _node->next;

			_node->next = _node->next->next;
			_node->next->previous = _node;
			_alloc.destroy(&(tmp->data));
			delete tmp;
			_len--;
		}

		void push_front(const value_type& val)
		{
			node *new_node = new node;

			new_node->data = val;
			new_node->next =  _node->next;
			_node->next->previous = new_node;
			new_node->previous = _node;
			_node->next = new_node;
			_len++;
		}

		void push_back(const value_type& val)
		{
			node *new_node = new node;

			new_node->data = val;
			new_node->previous = _node->previous;
			_node->previous->next = new_node;
			new_node->next = _node;
			_node->previous = new_node;
			_len++;			
		}

		void pop_back()
		{
			node *tmp = _node->previous;
			_node->previous = tmp->previous;
			tmp->previous->next = _node;
			_alloc.destroy(&(tmp->data));
			delete tmp;
			_len--;
		}

		iterator insert(iterator position, const value_type& val)
		{
			node *new_node = new node;

			new_node->data = val;
			new_node->previous = position->previous;
			new_node->previous->next = new_node;
			new_node->next = position->next->previous;
			new_node->next->previous = new_node;
			_len++;
			return new_node;
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			node *new_node = new node;

			new_node->data = val;
			new_node->previous = position->previous;
			new_node->previous->next = new_node;
			for (size_type i = 1; i < n; i++)
			{
				node *tmp = new node;
				tmp->data = val;
				tmp->previous = new_node;
				new_node->next = tmp;
				new_node = tmp;
			}
			new_node->next = position->next->previous;
			position->previous = new_node;
			_len += n;
		}

		template<class it_type>
		void insert(iterator position, it_type first, it_type last, typename ft::enable_if<!ft::is_integral<it_type>::value, it_type>::type* = 0)
		{
			if (first == last)
				return ;
			node *new_node = new node;

			new_node->data = *first;
			new_node->previous = position->previous;
			new_node->previous->next = new_node;
			first++;
			_len++;
			while (first != last)
			{
				node *tmp = new node;
				tmp->data = *first;
				tmp->previous = new_node;
				new_node->next = tmp;
				new_node = tmp;
				first++;
				_len++;
			}
			new_node->next = position->next->previous;
			position->previous = new_node;
		}

		iterator erase(iterator position)
		{
			iterator tmp = position->next;
			position->previous->next = position->next;
			position->next->previous = position->previous;
			delete &(*position);
			_len--;
			return tmp;
		}

		iterator erase(iterator first, iterator last)
		{
			first->previous->next = last->next->previous;
			last->previous = first->previous;
			while(first != last)
			{
				iterator tmp = first->next;
				delete &(*first);
				first = tmp;
				_len--;
			}
			return last;
		}

		void swap(list& x)
		{
			if( x == *this)
				return;

			node *tmp_node = x._node;
			size_type tmp_len = x._len;
			allocator_type tmp_alloc = x._alloc;

			x._node = _node;
			x._len = _len;
			x._alloc = _alloc;

			_node = tmp_node;
			_len = tmp_len;
			_alloc = tmp_alloc;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _len)
			{
				iterator index = begin();
				for (size_type i = 0; i < n; i++)
					index++;
				erase(index, end());
			}
			if (n > _len)
				insert(end(), n - size(), val);
		}

		void clear()
		{
			iterator index = begin();
			while (index != end())
			{
				iterator tmp = index->next;
				delete &(*index);
				index = tmp;
			}
			_len = 0;
			_node->next = _node;
			_node->previous = _node;
		}

		void splice(iterator position, list& x)
		{
			x.begin()->previous = position->previous;
			x.begin()->previous->next = x._node->next;
			position->previous = x._node->previous;
			x.rbegin()->next = position->next->previous;
			_len += x.size();
			x._len = 0;
			x._node->next = x._node;
			x._node->previous = x._node;
		}

		void splice(iterator position, list& x, iterator i)
		{
			node *adr = i->next->previous;
			i->next->previous = i->previous;
			i->previous->next = i->next;
			x._len--;
			i->previous = position->previous;
			i->previous->next = adr;
			i->next = position->next->previous;
			i->next->previous = adr;
			_len++;
		}

		void splice(iterator position, list& x, iterator first, iterator last)
		{
			if (first == last)
				return ;
			first->previous->next = last->next->previous;
			last->previous = first->previous;
			first->previous = position->previous;
			first->previous->next = first->next->previous;
			while (first->next != last->next->previous)
			{
				first++;
				_len++;
				x._len--;
			}
			first->next = position->next->previous;
			position->previous = first->previous->next;
		}

		void remove(const value_type& val)
		{
			iterator index = begin();
			while(index != end())
			{
				if (*index == val)
					index = erase(index);
				else
					index++;
			}
		}

		template<class predicate>
		void remove_if(predicate pred)
		{
			iterator index = begin();
			while (index != end())
			{
				if (pred(*index))
					index = erase(index);
				else
					index++;
			}
		}

		void unique()
		{
			iterator index = begin();
			iterator tmp;
			while (index != rbegin())
			{
				tmp = index->next;
				if (*index == *tmp)
					erase(tmp);
				else
					index++;
			}
		}

		template<class BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			iterator index = begin();
			iterator tmp;
			while (index != rbegin())
			{
				tmp = index->next;
				if (binary_pred(*index, *tmp))
					erase(tmp);
				else
					index++;
			}
		}

		void merge(list& x)
		{
			iterator index = begin();
			iterator index_x = x.begin();
			iterator tmp;
			while (index != end())
			{
				if (*index_x < *index && index_x != x.end())
				{
					tmp = index_x;
					index_x++;
					splice(index, x, tmp);
				}
				else
					index++;
			}
			while (index_x != x.end() && index == end())
			{
				tmp = index_x;
				index_x++;
				splice(index, x, tmp);
			}
		}

		template<class Compare>
		void merge(list& x, Compare comp)
		{
			iterator index = begin();
			iterator index_x = x.begin();
			iterator tmp;
			while (index != end())
			{
				if (comp(*index_x, *index) && index_x != x.end())
				{
					tmp = index_x;
					index_x++;
					splice(index, x, tmp);
				}
				else
					index++;
			}
			while (index_x != x.end() && index == end())
			{	
				tmp = index_x;
				index_x++;
				splice(index, x, tmp);
			}
		
		}

		void sort()
		{
			iterator index = begin();
			node *tmp;
			while (index != rbegin())
			{
				if (index->data > index->next->data)
				{
					tmp = index->next;
					index->previous->next = tmp;
					index->next = tmp->next;
					tmp->next->previous = tmp->previous;
					tmp->next = tmp->previous;
					tmp->previous = index->previous;
					index->previous = tmp;
					index = begin();
				}
				else
					index++;
			}
		}

		template<class Compare>
		void sort(Compare comp)
		{
			iterator index = begin();
			node *tmp;
			while (index != rbegin())
			{
				if (!comp(index->data, index->next->data))
				{
					tmp = index->next;
					index->previous->next = tmp;
					index->next = tmp->next;
					tmp->next->previous = tmp->previous;
					tmp->next = tmp->previous;
					tmp->previous = index->previous;
					index->previous = tmp;
					index = begin();
				}
				else
					index++;
			}
		}

		void reverse()
		{
			iterator index = begin();
			node *tmp;

			while (index != end())
			{
				tmp = index->next;
				index->next = index->previous;
				index->previous = tmp;
				index = tmp;
			}
			tmp = index->next;
			index->next = index->previous;
			index->previous = tmp;
		}

};

template<class T, class alloc>
bool operator==(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename list<T>::iterator index_l = lhs.begin();
	typename list<T>::iterator index_r = rhs.begin();
	while(*index_l == *index_r && index_l != lhs.rbegin())
	{
		index_l++;
		index_r++;
	}
	if (*index_l != *index_r )
		return false;
	return true;
}

template<class T, class alloc>
bool operator!=(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class T, class alloc>
bool operator<(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	typename list<T>::iterator index_l = lhs.begin();
	typename list<T>::iterator index_r = rhs.begin();
	while(*index_l == *index_r && index_l != lhs.rbegin() && index_r != rhs.rbegin())
	{
		index_l++;
		index_r++;
	}
	if (*index_l < *index_r)
		return true;
	if (*index_l == *index_r && lhs.size() < rhs.size())
		return true;
	return false;
}

template<class T, class alloc>
bool operator>(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	return rhs < lhs;
}


template<class T, class alloc>
bool operator<=(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	return !(rhs < lhs);
}

template<class T, class alloc>
bool operator>=(const list<T, alloc>& lhs, const list<T, alloc>& rhs)
{
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(list<T,Alloc>& x, list<T,Alloc>& y)
{
	x.swap(y);
}

#endif

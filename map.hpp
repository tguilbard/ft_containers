/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 08:00:02 by user42            #+#    #+#             */
/*   Updated: 2021/07/05 12:26:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"
# include "binary_tree.hpp"
# include "iterator.hpp"

namespace ft
{
	
template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	public :
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<const Key, T>										value_type;
		typedef Compare														key_compare;

		class value_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;
			
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
				
			public:
				bool operator() (const value_type& x, const value_type& y) const
				{return comp(x.first, y.first);}
		};

		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename binary_tree<value_type, key_compare>::iterator	iterator;
		typedef typename binary_tree<value_type, key_compare>::const_iterator const_iterator;
		typedef rvrs_iterator<const_iterator>							const_reverse_iterator;
		typedef rvrs_iterator<iterator>									reverse_iterator;
		typedef typename std::ptrdiff_t										difference_type; 
		typedef typename allocator_type::size_type							size_type;

	private :
		allocator_type						_alloc;
		Compare								_comp;
		binary_tree<value_type, Compare>	_bt;

	public :
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:_alloc(alloc), _comp(comp), _bt()
		{}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		:_alloc(alloc), _comp(comp), _bt()
		{insert(first, last);}

		map(const map& x)
		:_alloc(x._alloc), _comp(x._comp), _bt()
		{insert(x.begin(), x.end());}

		~map()
		{clear();}

		map& operator= (const map& x)
		{
			if (&x == this)
				return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}

		iterator begin()
		{return iterator(_bt._last_node->left, _bt._last_node);}
		const_iterator begin() const
		{return const_iterator(_bt._last_node->left, _bt._last_node);}
		iterator end()
		{return iterator(_bt._last_node, _bt._last_node);}
		const_iterator end() const
		{return const_iterator(_bt._last_node, _bt._last_node);}
		reverse_iterator rbegin()
		{return reverse_iterator(++end());}
		const_reverse_iterator rbegin() const
		{return const_reverse_iterator(++end());}
		reverse_iterator rend()
		{return reverse_iterator(--begin());}
		const_reverse_iterator rend() const
		{return const_reverse_iterator(--begin());}

		bool empty() const
		{return _bt._last_node->parent == _bt._last_node;}
		size_type size() const
		{return _bt._size;}
		size_type max_size() const
		{return _bt.max_size();}

		mapped_type& operator[] (const key_type& k)
		{
			iterator tmp = find(k);
			if (tmp == end())
				insert(ft::pair<key_type, mapped_type>(k, mapped_type()));
			tmp = find(k);
			return tmp->second;
		} 

		ft::pair<iterator,bool> insert (const value_type& val)
		{
			iterator node = find(val.first);
			if (node != end())
				return (ft::make_pair(node, false));
			return _bt.insertPair(val);
		}
		
		iterator insert (iterator position, const value_type& val)
		{(void)position; return (_bt.insertPair(val).first);}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{while (first != last) insert(*(first++));}

		void erase (iterator position)
		{erase(position->first);}
		
		size_type erase (const key_type& k)
		{
			if (find(k) == end())
				return (0);
			_bt.removeByKey(ft::pair<key_type, mapped_type>(k, mapped_type()));
			return (1);
		}
		void erase (iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap (map& x)
		{_bt.swap(x._bt);}

		void clear()
		{erase(begin(), end());}

		key_compare key_comp() const
		{return key_compare();}
		value_compare value_comp() const
		{return value_compare(key_compare());}

		iterator find (const key_type& k)
		{return iterator(_bt.searchByKey(ft::pair<key_type, mapped_type>(k, mapped_type())), _bt._last_node);}
		const_iterator find (const key_type& k) const
		{return const_iterator(_bt.searchByKey(ft::pair<key_type, mapped_type>(k, mapped_type())), _bt._last_node);}

		size_type count (const key_type& k) const
		{
			const_iterator beg = begin();
			const_iterator end = this->end();
			while (beg != end)
				if ((*(beg++)).first == k)
					return (1);
			return (0);
		}

		iterator lower_bound (const key_type& k)
		{
			iterator beg = begin();
			iterator end = this->end();
			while (beg != end)
			{
				if (_comp((*beg).first, k) == false)
					break;
				beg++;
			}
			return (beg);
		}
		const_iterator lower_bound (const key_type& k) const
		{return const_iterator(lower_bound(k));}

		iterator upper_bound (const key_type& k)
		{
			iterator beg = begin();
			iterator end = this->end();
			while (beg != end)
			{
				if (_comp(k, (*beg).first))
					break;
				beg++;
			}
			return (beg);
		}
		const_iterator upper_bound (const key_type& k) const
		{return const_iterator(upper_bound(k));}

		ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
		{return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}
		ft::pair<iterator, iterator> equal_range (const key_type& k)
		{return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}

		allocator_type get_allocator() const
		{return _alloc;}
};

}

#endif

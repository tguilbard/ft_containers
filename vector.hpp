/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 07:55:20 by user42            #+#    #+#             */
/*   Updated: 2021/04/22 10:49:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdio>
# include <memory>
# include "utils.hpp"

# if ((ULONG_MAX) == (UINT_MAX))
#  define nativePointerBitWidth 32
# else
#  define nativePointerBitWidth 64
# endif

template<typename T, class allocator =std::allocator<T> >
class vector;

template<typename T>
class vector_iterator
{
	public :
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T &reference;
		typedef const T& const_reference;
		typedef typename std::ptrdiff_t difference_type;

	private :
		typedef vector_iterator<T> self;
		pointer _data;

	public :
		vector_iterator() : _data(0) {}
		vector_iterator(pointer ptr) : _data(ptr) {}
		vector_iterator(const self &to_copy) : _data(to_copy._data) {}
		self &operator=(const self &to_copy) {_data = to_copy._data; return *this;}
		~vector_iterator() {}
		self &operator++() {++_data; return *this;}
		self &operator++(int) {++_data; return *this;}
		self &operator--() {--_data; return *this;}
		self &operator--(int) {--_data; return *this;}
		reference operator*() {return *_data;}
		const_reference operator*() const {return *_data;}
		pointer operator->() {return _data;}
		const_pointer operator->() const {return _data;}
		reference operator[](difference_type idx) {return *(_data + idx);}
		const_reference operator[](difference_type idx) const {return *(_data + idx);}
		self &operator+=(difference_type add) {_data += add; return *this;}
		self &operator-=(difference_type sub) {_data -= sub; return *this;}

		bool operator==(const vector_iterator &to_comp)
		{return _data == to_comp._data;}
		bool operator!=(const vector_iterator &to_comp)
		{return _data != to_comp._data;}
		bool operator>(const vector_iterator<T> &to_comp)
		{return _data > to_comp._data;}
		bool operator<(const vector_iterator<T> &to_comp)
		{return _data < to_comp._data;}
		bool operator>=(const vector_iterator<T> &to_comp)
		{return _data >= to_comp._data;}
		bool operator<=(const vector_iterator<T> &to_comp)
		{return _data <= to_comp._data;}

		vector_iterator operator+(difference_type add)
		{return (vector_iterator(_data + add));}
		difference_type operator+(vector_iterator obj)
		{return _data + obj._data;}
		vector_iterator operator-(difference_type sub)
		{return (vector_iterator(_data - sub));}
		difference_type operator-(vector_iterator obj)
		{return _data - obj._data;}

		static const bool input_iter = true;

};

#include "revers.hpp"

template<typename T, class allocator>
class vector
{
	public:
		typedef T 									value_type;
		typedef allocator							allocator_type;
 		typedef typename allocator::reference		reference;
		typedef typename allocator::const_reference	const_reference;
		typedef typename allocator::pointer			pointer;
		typedef typename allocator::const_pointer	const_pointer;
		typedef vector_iterator<value_type>			iterator;
		typedef vector_iterator<const value_type>	const_iterator;
		typedef reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef reverse_iterator<iterator>			reverse_iterator;
		typedef typename std::ptrdiff_t				difference_type;
		typedef typename allocator::size_type		size_type;
	
	private :
		typedef vector<T> self;

		allocator_type _alloc;
		pointer			_arr;
		size_type		_len;
		size_type		_cap;

	public :
		explicit vector(const allocator &alloc = allocator()) : _alloc(alloc), _arr(0), _len(0), _cap(0) {}

		explicit vector(size_type count, const value_type &val = value_type(), const allocator &alloc = allocator())
			: _alloc(alloc), _arr(0), _len(0), _cap(0)
		{insert(begin(), count, val);}

		template<class it_type>
		vector(it_type first, it_type last, const allocator &alloc = allocator())
			: _alloc(alloc), _arr(0), _len(0), _cap(0)
		{insert(begin(), first, last);}

		vector(const self &to_copy)
			: _alloc(to_copy._alloc), _arr(0), _len(0), _cap(0)
		{insert(begin(), to_copy.begin(), to_copy.end());}
		
		~vector()
		{	
			clear();
			if (_cap)
				delete [] _arr;
		}

		self &operator=(const self& to_copy)
		{
			clear();
			insert(begin(), to_copy.begin(), to_copy.end());
			return *this;
		}

		iterator begin()
		{return _arr;}

		const_iterator begin() const
		{return _arr;}
		
		iterator end()
		{return _arr + _len;}

		const_iterator end() const
		{return _arr + _len;}

		reverse_iterator rbegin()
		{return _arr + _len - 1;}

		const_reverse_iterator rbegin() const
		{return _arr + _len - 1;}
		
		reverse_iterator rend()
		{return _arr - 1;}

		const_reverse_iterator rend() const
		{return _arr - 1;}

		size_type size() const
		{return _len;}

		size_type max_size() const
		{return (2^nativePointerBitWidth)/sizeof(value_type) - 1;}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _len)
				erase(begin() += n , end());
			if (n > _len)
				insert(end(), n - _len, val);
		}

		size_type capacity() const
		{return _cap;}

		bool empty() const
		{return (_len) ? false:true;}

		void reserve(size_type n)
		{
			if (_cap < n)
			{
				if (_cap == 0)
				{
					_cap = 1;
					while (_cap < n)
						_cap *= 2;
					_arr = new value_type[_cap];
				}
				else
				{
					while (_cap < n)
						_cap *= 2;
					pointer tmp;
					tmp = new value_type[_cap];
					for(int i = 0; i < _len; i++)
						tmp[i] = _arr[i];
					delete [] _arr;
					_arr = tmp;
				}
			}
		}

		reference operator[](size_type n)
		{return *(_arr + n);}
	
		const_reference operator[](size_type n) const
		{return *(_arr + n);}

		reference at(size_type n)
		{
			if (n < _len)
				return *(_arr + n);
		}

		const_reference at(size_type n) const
		{
			if (n < _len)
				return *(_arr + n);
		}

		reference front()
		{return *_arr;}

		const_reference front() const
		{return *_arr;}

		reference back()
		{return *(_arr + _len - 1);}

		const_reference back() const
		{return *(_arr + _len - 1);}

		template<class it_type>
		void assign(it_type first, it_type last)
		{
			_cap = (_cap == 0) ? 1 : _cap;
			while(last - first > _cap)
				_cap *= 2;
			~vector();
			_arr = new value_type[_cap];
			_len = last - first;
			for(int i = 0; i < _len; i++)
				_arr[i] = *(first + i);
		}

		void assign(size_type n, const value_type& val)
		{
			_cap = (_cap == 0) ? 1 : _cap;
			while(n > _cap)
				_cap *= 2;
			~vector();
			_arr = new value_type[_cap];
			_len = n;
			for(int i = 0; i < _len; i++)
				_arr[i] = val;
		}

		void push_back(const value_type &val)
		{
			if (_len >= _cap)
			{
				_cap = (_cap == 0) ? 1 : _cap * 2;
				pointer tmp;
				tmp = new value_type[_cap];
				for(size_type i = 0; i < _len; i++)
					tmp[i] = _arr[i];
				delete [] _arr;
				_arr = tmp;
			}
			_arr[_len] = val; 
			_len++;
		}

		void pop_back()
		{
			if (_len)
			{
				_len--;
				_alloc.destroy(_arr + _len);
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			iterator it;

			if (_len >= _cap)
			{
				_cap = (_cap == 0) ? 1 : _cap * 2;
				pointer tmp;
				tmp = new value_type[_cap];
				it = begin();
				int i = 0;
				while(it != position)
					tmp[i++] = *(it++);
				tmp[i++] = val;
				while(it != end())
					tmp[i++] = *(it++);
				delete [] _arr;
				_arr = tmp;
			}
			else
			{
				it = end() - 1;
				while(it != position)
				{
					*(it + 1) = *it;
					it--;
				}
				*(it + 1) = *it;
				*it = val;
			}
			_len++;
			return (position);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			iterator it;
			size_type i;

			if (_len + n > _cap)
			{
				_cap = (_cap == 0) ? 1 : _cap * 2;
				while (_len + n > _cap)
					_cap *= 2;
				pointer tmp;
				tmp = new value_type[_cap];
				it = begin();
				i = 0;
				while(it != position)
					tmp[i++] = *(it++);
				for(size_type j = 0; j < n; j++)
					tmp[i++] = val;
				while(it != end())
					tmp[i++] = *(it++);
				delete [] _arr;
				_arr = tmp;
			}
			else
			{
				it = end() - 1;
				while(it != position)
				{
					*(it + n) = *it;
					it--;
				}
				*(it + n) = *it;
				for(i = 0; i < n; i++)
					*(it + i) = val;
			}
			_len += n;
		}

		template<class it_type>
		void insert(iterator position, it_type first, it_type last)
		{
			iterator it;
			if (last - first + _len > _cap)
			{
				_cap = (_cap == 0) ? 1 : _cap * 2;
				while (last - first + _len > _cap)
					_cap *= 2;
				pointer tmp;
				tmp = new value_type[_cap];
				it = begin();
				int i = 0;
				while(it != position)
					tmp[i++] = *(it++);
				for(; first != last; first++)
					tmp[i++] = *first;
				while(it != end())
					tmp[i++] = *(it++);
				delete [] _arr;
				_arr = tmp;
				_len = i;
			}
			else if (last - first != 0)
			{
				_len += last - first;
				it = end() - 1;
				while(it != position)
				{
					*(it + (last - first)) = *it;
					it--;
				}
				*(it + (last - first)) = *it;
				for(; first != last; first++)
					*(it++) = *first;
			}
		}

		iterator erase(iterator position)
		{
			iterator tmp = position;

			_alloc.destroy(&(*position));
			while(tmp != end())
			{
				tmp = tmp + 1;
				tmp++;
			}
			_len--;
			return (position);
		}

		iterator erase(iterator first, iterator last)
		{
			iterator tmp = first;

			while(tmp != last)
				_alloc.destroy(&(*(tmp++)));
			tmp  = first;
			while(tmp != end())
			{
				tmp = tmp + (last - first);
				tmp++;
			}
			_len -= (last - first);
			return (first);
		}

		void swap(vector& x)
		{
			vector tmp(*this);
			*this(x);
			x(tmp);
		}

		void clear()
		{
			for(iterator it = begin(); it != end(); it++)
				_alloc.destroy(&(*it));
			_len = 0;
		}
};

template<class T, class alloc>
bool operator==(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	size_t i;

	if (lhs.size() != rhs.size())
		return false;
	i = 0;
	while(lhs[i] == rhs[i] && i < lhs.size())
		i++;
	if (lhs[i] != rhs[i])
		return false;
	return true;
}

template<class T, class alloc>
bool operator!=(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class T, class alloc>
bool operator<(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	size_t i;

	i = 0;
	while(lhs[i] == rhs[i] && i < lhs.size() && i < rhs.size())
		i++;
	if (lhs[i] < rhs[i])
		return true;
	if (lhs[i] == rhs[i] && lhs.size() < rhs.size())
		return true;
	return false;
}

template<class T, class alloc>
bool operator>(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	return rhs < lhs;
}


template<class T, class alloc>
bool operator<=(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	return !(rhs < lhs);
}

template<class T, class alloc>
bool operator>=(const vector<T, alloc>& lhs, const vector<T, alloc>& rhs)
{
	return !(lhs < rhs);
}

#endif

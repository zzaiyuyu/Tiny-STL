#pragma once
#include <iostream>
/*
ͨ���º��������ƣ�ͨ��ģ��������޹أ�ͨ��������ʵ�ֺ������޹أ�
�����Ƿ����㷨
*/
/*************�º���*****************/
template <typename T>
struct Display {
	void operator() (const T& x){
		std::cout << x << ' ';
	}
};

/***************������ȡ****************/
/*��Ƕ���ͣ���������ͨ���������ݣ�typedef value_type ��ʹ��ʱҲ���в������ݣ�����֧��ԭ��ָ�� */
/*������ģ��ƫ�ػ����Բ��ֲ������н�һ������*/
template<class I>
struct IteratorTraits {
	//Ƕ�״������ͱ���Ҫָ��������һ�����͡�
	typedef typename I::value_type value_type;
};

template<class T>
struct IteratorTraits<T*> {
	typedef T value_type;
};

template<class T>
struct IteratorTraits<const T*> {
	typedef T value_type;
};

/******************�㷨********************/
template <class Iterator, class T>
Iterator Find(Iterator begin, Iterator end, const T& value) {
	while (begin != end && value != *begin) {
		++begin;
	}
	return begin;
}

template <class InputIterator, class Function>
Function ForEach(InputIterator begin, InputIterator end, Function f) {
	while (begin != end) {
		f(*begin);
		++begin;
	}
	return f;
}

//��������ֻ֧��������ʵĵ�����
template <class Iterator>
void InsertionSort(Iterator first, Iterator last) {
	for (Iterator tmp= first+1; tmp != last; tmp++) {
		//��Ҫ֪����������ָ���ͣ�����ƫ�ػ���ȡ
		_InsertionSort(first, tmp);//[first, tmp)
	}
}
template<class Iterator>
void _InsertionSort(Iterator first, Iterator last) {
	//�м���Ż�
	typedef typename IteratorTraits<Iterator>::value_type value_type;
	value_type value = *last;
	if (*last < *first) {
		while (last != first) {
			*last = *(last - 1);
			last--;
		}
		*first = value;
	}
	else {
		_UnguardedIns(last, value);
	}
}
template<class Iterator, class T>
void _UnguardedIns(Iterator last, T value) {
	last--;
	while (*last > value) {
		*(last + 1) = *(last);
		last--;
	}
	*(last + 1) = value;
}


/****************����*********************/
/*����ȡ�а�����Ż���nlogn����ֵ���Ƶݹ������unguarded�Ż�*/
template<class Iterator>
inline Iterator Median(Iterator a, Iterator b, Iterator c){
	if (*a > *b) {
		if (*b > *c) {
			return b;
		}
		if (*a > *c) {
			return c;
		}
		return a;
	}
	else if (*a > *c) {
		return a;
	}
	else if (*b > *c) {
		return c;
	}
	else {
		return b;
	}
}

template<class Iterator>
Iterator Partition(Iterator first, Iterator last) {
	Iterator piv = Median(first, first + (last - first) / 2, last - 1);
	swap(*piv, *(last - 1));
	Iterator pp = first - 1;
	for(; first < last-1; ++first){
		if (*first > *(last-1)) {
			continue;
		}
		else {
			++pp;
			if (pp != first) {
				swap(*pp, *first);
			}
		}
	}
	++pp;
	swap(*pp, *(last - 1));
	return pp;
}

const int THRESHOLD = 16;
template<class Iterator>
inline void Sort(Iterator first, Iterator last) {
	if (first != last) {
		_QuickSortLoop(first, last);
		InsertionSort(first, last);
	}
}

template<class Iterator>
inline void _QuickSortLoop(Iterator first, Iterator last) {
	if (last - first > THRESHOLD) {
		Iterator mid = Partition(first, last);
		_QuickSortLoop(first, mid);
		_QuickSortLoop(mid+1, last);
	}
}

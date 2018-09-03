#pragma once
#include <iostream>
#include <assert.h>

/*������ȡ���жϵ�ǰ�����Ƿ����Զ�������*/
/*ԭ�����ñ��������ڱ����ڼ��ж�T�����ͣ������ػ��б�������ʹ���ػ���ģ����*/
struct TrueType {
	static bool Get()
	{
		return true;
	}
};

struct FalseType {
	static bool Get()
	{
		return false;
	}
};
//���û���ػ��������Զ�������
template<class T>
struct TypeTraits {
	typedef FalseType PODTYPE;
};
template <>
struct TypeTraits<int> {
	typedef TrueType PODTYPE;
};
template <>
struct TypeTraits<double> {
	typedef TrueType PODTYPE;
};

/**********************vector*****************************/
/*erase����resize�����ܼ�Сvector�ռ䣬��ΪΪ�˱�֤��������Ч�����ݱ����������洢�ġ��������ÿ�������һ��tmp��Ȼ�󽻻�*/

template<class T>
class Vector {
public:
	//�����ռ䣬ָ����ȫʤ�ε�����
	typedef T* Iterator;
	Vector() 
		:_start(0),_finish(0),_end(0)
	{
	}
	//��size���������
	Vector(int size, T data = T()) {
		T* pTmp = new T[size * sizeof(T)];
		for (int i = 0; i < size; i++) {
			pTmp[i] = data;
		}
		_start = pTmp;
		_finish = pTmp+size;
		_end = pTmp + size;
	}
	//[first, last)��������
	Vector(const T* first, const T* last) {
		int size = last - first;
		T* pTmp = new T[size * sizeof(T)];
		for (; first != last; first++) {
			pTmp[i] = *first;
		}
		_start = pTmp;
		_finish = pTmp + size;
		_end = pTmp + size;
	}

	Vector(const Vector<T>& v) {
		T* pTmp = new T[sizeof(T) * v.Capacity()];
		for (int i = 0; i < v.Size(); i++) {
			pTmp[i] = v._start[i];
		}
		_start = pTmp;
		_finish = pTmp + v.Size();
		_end = pTmp + v.Capacity();
	}

	Vector<T>& operator=(const Vector<T>& v)
	{
		if (*this != v) {
			T* pNew = new T[sizeof(T)*Size()];
			memcpy(pNew, v._start, Size());
			delete[] _start;
			_start = pNew;
			_finish = pNew + v.Size();
			_end = pNew + v.Capacity();
		}
		return *this;
	}
	~Vector() {
		if (_start) {
			delete[] _start;
		}
	}

	size_t Size()const {
		return _finish - _start;
	}
	size_t Capacity()const {
		return _end - _start;
	}
	bool Empty()const {
		return _start == _finish;
	}

	void Resize(size_t newSize, const T& data = T()) {
		size_t old = Size();
		if (newSize <= old) {
			_finish = _start + newSize;
		}
		else {
			size_t capacity = Capacity();
			if (newSize < capacity) {
				//���ﲹ
				while (newSize != old) {
					*_finish = data;
					++_finish;
					--newSize;
				}
			}
			else {
				//1.�����¿ռ�
				T* pTmp = new T[newSize];
				if (_start) {
					//2����Ԫ��
					for (size_t i = 0; i < old; i++) {
						pTmp[i] = _start[i];
					}
					for (size_t i = old; i < newSize; i++) {
						pTmp[i] = data;
					}
					delete[] _start;
				}
				//3�ͷžɿռ�
			
				_start = pTmp;
				_finish = _start + newSize;
				_end = _finish;
			}

		}
	}
	//Ԥ���ռ�
	void Reserve(size_t n) {
		if (n > Capacity()) {
			//1.�����¿ռ�
			size_t size = Size();
			T* pTmp = new T[n];
			if (_start) {
				//2����Ԫ��
				for (size_t i = 0; i < old; i++) {
					pTmp[i] = _start[i];
				}
				for (size_t i = oldSize; i < newSize; i++) {
					pTmp[i] = data;
				}
				//3�ͷžɿռ�
				delete[] _start;
			}
			_start = pTmp;
			_finish = _start + size;
			_end = _start + n;

		}
	}

	void PushBack(const T& data);
	void PopBack();
	void Erase(size_t pos);
	void Insert(size_t pos, const T& data);

	T& operator[](size_t index) {
		assert(index < Size());
		return _start[index];
	}
	const T& operator[](size_t index) const {
		assert(index < Size());
		return _start[index];
	}
	T& Front() {
		return *_start;
	}
	T& Back() {
		return *(_finish - 1);
	}

	void Clear() {
		_finish = _start;
	}
	void Swap(Vector<T>& v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_end, v._end);
	}

	Iterator Begin() {
		return _start;
	}
	Iterator End() {
		return _finish;
	}

private:
	void _CheckCapacity() {
		if (_finish == _end) {
			size_t newSize = Size() * 2 + 3;
			T* pTmp = new T[newSize];
			size_t size = Size();
			if (_start) {
				//����������memcpy���죬������ȡ
				if (TypeTraits<T>::PODTYPE::Get()) {
					memcpy(pTmp, _start, sizeof(T)*size);
				}
				else {
					//�Զ��������������丳ֵ�����
					for (size_t i = 0; i < size; i++) {
						pTmp[i] = _start[i];
					}
				}
				delete[] _start;
			}
			_start = pTmp;
			_finish = _start + size;
			_end = _start + newSize;
		}
	}

private:
	Iterator _start;	//��̬���ٿռ���ʼ
	Iterator _finish;	//��ǰδ��Ԫ�ص���ʼ�ռ�
	Iterator _end;	//��̬���ٿռ�ĩβstatic void TestVector()
};

//������Ҫ��T�ĵط�����Ҫ����template˵��T
template<class T>
void Vector<T>::PushBack(const T& data) {
	_CheckCapacity();
	*_finish = data;
	++_finish;
}

template<class T>
void Vector<T>::PopBack() {
	if (_start != _finish) {
		--_finish;
	}
}
template<class T>
void Vector<T>::Insert(size_t pos, const T& data)
{
	//pos��1��ʼ
	_CheckCapacity();
	//�и��ӣ�size_t���޷�����
	int index = (int)Size()-1;
	while (index>=0 && index >= pos-1) {
		_start[index+1] = _start[index];
		index--;
	}
	_start[++index] = data;
	_finish++;
}

template<class T>
void Vector<T>::Erase(size_t pos)
{
	size_t end = Size();
	--pos;//λ��תΪ�±�
	while (pos < end) {
		_start[pos] = _start[pos + 1];
		pos++;
	}
	--_finish;
}


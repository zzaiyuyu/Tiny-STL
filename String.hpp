#ifndef STRING_H
#define STRING_H
#include <iostream>
class String {
public:
	friend std::ostream & operator<<(std::ostream& cout, String& s);
	String(const char* str = "")
	{
		if (NULL == str) {
			str = "";
		}
		_pStr = new char[strlen(str) + 1];
		strcpy(_pStr, str);
	}
	//�������
	String(const String& s)
		:_pStr(new char[strlen(s._pStr) + 1])
	{
		strcpy(_pStr, s._pStr);
	}

	String& operator=(String s) {
		std::swap(_pStr, s._pStr);
		return *this;
	}
	//�Ĳ���ֵ�汾
	//String& operator=(const String& s)
	//{
	//  if (this != &s) {
	//      char* pStr = new char[strlen(s._pStr) + 1];
	//      strcpy(pStr, s._pStr);
	//      delete[] _pStr;
	//      _pStr = pStr;
	//  }
	//  return *this;
	//}
	~String()
	{
		if (_pStr) {
			delete[] _pStr;
		}
	}

	String operator+(String s) {
		int len = size() + s.size() + 1;
		char* tmp = new char[len];
		strcpy(tmp, _pStr);
		strcat(tmp, s._pStr);
		std::swap(tmp, s._pStr);
		delete[] tmp;
		return s;
	}
	bool operator==(const String &str)const
	{
		if (strcmp(_pStr, str._pStr) == 0) {
			return true;
		}
		return false;
	}

	size_t size() const
	{
		return strlen(_pStr);
	}

	const char* c_str() const
	{
		return _pStr;
	}
	//ȡ��position��ָλ������ȡlen���ַ�����Ӵ�����  
	String& sub_str(int position, int len) {
		if (position<0 || position >= size() || len<0 || len >size()) //������������ȡ�Ӵ�  
		{
		}
		else
		{
			if (position + len - 1 >= size())            //�ַ���������  
				len = size() - position;
			for (int i = 0, j = position; i<len; i++, j++)
				_pStr[i] = _pStr[j];
			_pStr[len] = '\0';
		}
		return *this;
	}
private:
	char* _pStr;
};

std::ostream & operator<<(std::ostream& cout, String& s)
{
	cout << s._pStr;
	return cout;
}

#endif
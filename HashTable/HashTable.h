#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<assert.h>
//const size_t EXIT = 0;
enum Statue
{
	EMPTY,
	DELETE,
	EXIST
};

template <class K,class V>
struct HashNode
{
	K _key;
	V _value;
	Statue _statue;

	HashNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_statue(EMPTY)	
	{}
};

template<class K>
struct __HashFunc//char
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct __HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while(*str)
		{
			hash = hash * 131 + *str;
			++str;
		}
		return hash;
	}

	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

template<class K,class V,class HashFunc = __HashFunc<K> >
class HashTable
{
	typedef HashNode<K,V> Node;
public:
	HashTable(size_t size)
		:_size(0)
	{
		assert(size>0);
	//	_table.resize(size);
		_table.resize(_GetPrimeSize());
	}
	
	~HashTable()
	{
		_Clear();
	}

	pair<Node*,bool> Insert(const K& key,const V& value)//返回值为了方便重载（）
	{
		_CheckCapacity();
		//插满了
		//if(_size == _table.size())
		//{
		//	_table.resize(_size);
		//	return make_pair((Node*)NULL,false);
		//}
				
		//未满 线性探测
		//看status=EXIST 存下一位
		//剩下状态直接插入 
		int index = _HashFunc(key);//除留余数
		int first = index;
		size_t i = 0;
		while(_table[index]._statue == EXIST)
		{
			if(_table[index]._key == key)//不支持重复插入
				return make_pair(&_table[index],false);
			////线性探测
			//index++;
			//if(index == _table.size())
			//{
			//	index = 0;
			//}

			//二次线性探测
			i++;
			index = first + i*i;
			index %= _table.size();
		}	
		_table[index]._statue = EXIST;
		_table[index]._key = key;
		_table[index]._value = value;
		_size++;
		return make_pair(&_table[index],true);
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		while(_table[index]._statue != EMPTY)
		{	
			if(_table[index]._key == key && _table[index]._statue == EXIST)
			{
				return &_table[index];
			}
			else
			{
			   //status = DELETE时  的要跳过
			   index++;
			   if(index == _table.size())
			   {
					index = 0;
			   }
			}
		}
		cout<<"没有插入这个值"<<endl;
		return (Node*)NULL;
	}

	bool Remote(const K& key)
	{
		if(_table.empty())
			return false;

		Node* pos = Find(key);
		if(pos)
		{
			pos->_statue = DELETE;
			_size--;
			return true;
		}
		return false;
	}
	
protected:	

	size_t _GetPrimeSize()
	{
		const int _PrimeSize= 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul,         97ul,         193ul,		 389ul,		  769ul,
			1543ul,       3079ul,       6151ul,		 12289ul,	  24593ul,
			49157ul,      98317ul,      196613ul,	 393241ul,	  786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
	;	// 10 < 53 return 53  
		//  54 < 53 ++ 54 < 97 return 97
		for(size_t i = 0; i<_PrimeSize; ++i)
		{
			if(_table.size() <  _PrimeList[i])
			{
				return _PrimeList[i];
			}
		}
		return 0;
		
	}
	void Swap(HashTable<K,V,HashFunc> t)
	{
		_table.swap(t._table);//vector里重载了swap		 void swap ( vector<T,Allocator>& vec );
		swap(_size,t._size);//交换两个值，调库里的swap	 void swap ( string& lhs, string& rhs);
	}
	size_t _HashFunc(const K& key)
	{
		HashFunc ht;
		return ht(key) % _table.size();
	}
	void _CheckCapacity()
	{
		if(_table.empty())
		{
			_table.resize(7);
			return;
		}
		//载荷因子 < 0.7
		//现代写法
		if(_size*10 / _table.size() >= 7)
		{
			//size_t newSize = _table.size() * 2;
			size_t newSize = _GetPrimeSize();

			HashTable<K,V,HashFunc> tmp(newSize);
			for(size_t i = 0; i<_table.size(); ++i)
			{
				if(_table[i]._statue == EXIST)
				{
					tmp.Insert(_table[i]._key,_table[i]._value);
				}
			}
			this->Swap(tmp);
		}
		
	}
protected:
	vector<Node> _table;
	size_t _size;
};

void Test()
{
	HashTable<int,int> ht(10);
	ht.Insert(89,0);
	ht.Insert(18,0);
	ht.Insert(49,0);
	ht.Insert(58,0);
	ht.Insert(9,0);

	cout<<ht.Find(9)->_key<<endl;;
	//ht.Find(9);
	ht.Remote(58);

	cout<<ht.Find(9)->_key<<endl;;
	
	
	HashTable<string,string> ht1(10);
	ht1.Insert("left","左");
	ht1.Insert("right","右");
	cout<<ht1.Find("left")->_key<<" "<<ht1.Find("left")->_value<<endl;
	
}

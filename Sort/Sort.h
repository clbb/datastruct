#pragma once
#include<assert.h>
#include<iostream>
using namespace std;

void Print(int a[],size_t size)
{
	for(size_t i = 0; i<size; ++i)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

template <class T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l<r;
	}
};
template <class T>
struct Greater
{
	bool operator()(const T& l,const T& r)
	{
		return l>r;
	}
};
//template<class T,class Compare = Less<T> >
template<class T, template<class> class Compare = Less >
void InsertSort(T a[],size_t size)
{
	assert(a);

	for(size_t i = 1; i<size; ++i)
	{
		int end = i-1;
		T tmp = a[i];
		while(end >= 0)
		{
			if(Compare<T>()(tmp,a[end]))//升序 
			{
				a[end+1] = a[end];
				end--;
			}
			else
				break;
		}
		a[end+1] = tmp;
	}
}

void Test1()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	InsertSort(a,10);
	Print(a,10);
}

void ShellSort(int *a,size_t size)
{
	assert(a);

	int gap = size;
	while(gap > 1)
	{
		gap = gap / 3 + 1; 
		for(size_t i = gap; i<size; ++i)
		{
			int end = i-gap;
			int tmp = a[i];
			while(end >= 0)
			{
				if(a[end] > tmp)
				{
					a[end+gap] = a[end];
					end-=gap;
				}
				else
					break;
			}
			a[end+gap] = tmp;
		}
	}
	
}

void Test2()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	ShellSort(a,10);
	Print(a,10);
}


void AdjustDown(int* a,size_t n,int parent)
{
	int child = 2*parent+1;
	while(child < n)
	{
		if(child+1 < n && a[child+1] > a[child])
			child++;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
			break;
	}
}


void HeapSort(int *a,size_t size)
{	
	assert(a);

	for(int i = (size-1-1)/2; i>=0; --i)
	{
		AdjustDown(a,size,i);
	}

	int end = size-1;
	while(end > 0)
	{
		swap(a[end],a[0]);
		AdjustDown(a,end,0);
		--end;
	}
}

void Test3()
{
	int a[] = {9,5,4,9,3,6,8,7,1,0};
//	int a[] = {5,2,7,1,3,8,4,9,0,6};
	HeapSort(a,10);
	Print(a,10);
}

int Partion(int *a,int left,int right)
{
	int key = right;
	while(left < right)
	{
		while(left < right && a[left] <= a[key])//
		{
			++left;
		}
		while(left < right && a[right] >= a[key])
		{
			right--;
		}
		swap(a[left],a[right]);
	}
//	a[left] = a[key];
	swap(a[left],a[key]);
	return left;
}


void QuickSort(int *a,int left,int right)
{
	assert(a);

	if(left < right)
	{
		int div = Partion(a,left,right);
		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}
}

void Test4()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	QuickSort(a,0,sizeof(a)/sizeof(a[0])-1);
	Print(a,sizeof(a)/sizeof(a[0]));
}

void SelectSort(int* a,size_t n)
{
	assert(a);
	int begin = 0;
	int minIndex;
	while(begin < n)
	{
		minIndex = begin;
		for(int i = begin+1; i<n; ++i)
		{
			if(a[minIndex] > a[i])//找最小的
				minIndex = i;
		}
		if(minIndex != begin)
			swap(a[minIndex],a[begin]);
		begin++;
	}
	
}
void SelectSortOP(int* a,size_t n)
{
	assert(a);

	int left = 0;
	int right = n-1;
	int minIndex;
	int maxIndex;
	while(left < right)
	{
		minIndex = left;
		maxIndex = left;
		for(int i = left; i <= right; ++i)
		{
			if(a[minIndex] > a[i])
				minIndex = i;
			if(a[maxIndex] < a[i])
				maxIndex = i;
		}
		swap(a[minIndex],a[left]);
		if(maxIndex == left)
			maxIndex = minIndex;
		swap(a[maxIndex],a[right]);
		++left;
		--right;
	}	
	
}

void Test5()
{
	int a[] = {5,2,7,1,3,8,4,9,0,6};
	SelectSort(a,sizeof(a)/sizeof(a[0]));
	Print(a,sizeof(a)/sizeof(a[0]));
}

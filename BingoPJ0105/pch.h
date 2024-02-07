// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#endif //PCH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <array>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <set>
#include <sstream>
#include <bitset>

using namespace std;

//template <typename T>
//class BingoBoard {
//private:
//	T data;
//	bool isCheck;
//	pair<T, bool> bingoNode;
//	vector<pair> bingoBoard;
//public:
//	BingoBoard();
//	BoardPushBack(const T& _data);
//
//};
//
//template<typename T>
//inline BingoBoard<T>::BingoBoard()
//{
//}

// =========================== 가변배열

template <typename T>
class CVector {
private:
	T* pArr; // 가변 배열의 시작주소
	int iCount; // current size
	int iMaxCount; // max size
public:
	CVector();
	void push_back(const T& data);
	void reallocate(const int resizeCount);
	int& operator [](int idx);

	class iterator;
	iterator begin();
	iterator end();
	//iterator erase(const iterator& iter);

	class iterator {
	private:
		CVector<T>* cV;
		T* iterArr;
	public:
		iterator() : cV(nullptr), iterArr(nullptr) {};
		iterator(const CVector<T>& cv, const T& arr) {
			cV = cv;
			iterArr = arr;
		};
		friend class CVector;
	};
};

template<typename T>
inline CVector<T>::CVector()
{
	pArr = new T[2]; // 1로 초기화
	iCount = 0;
	iMaxCount = 2;
}

template<typename T>
inline void CVector<T>::push_back(const T& data)
{
	if (iCount >= iMaxCount) {
		reallocate(++iMaxCount);
	}
	pArr[iCount] = data;

	iCount++;
}

template<typename T>
inline void CVector<T>::reallocate(const int resizeCount)
{
	if (resizeCount > iMaxCount) {
		T* newArr = new T[resizeCount];
		for (int i = 0; i < iMaxCount; i++) {
			newArr[i] = pArr[i];
		}
		delete[] pArr;
		pArr = newArr;
	}
	else return;

	iMaxCount = resizeCount;
}

template<typename T>
inline int& CVector<T>::operator[](int idx)
{
	return pArr[idx];
}

template<typename T>
inline typename CVector<T>::iterator CVector<T>::begin()
{
	return iterator(this,pArr[0]);
}

template<typename T>
inline typename CVector<T>::iterator CVector<T>::end()
{
	return iterator(this,pArr[iMaxCount-1]);
}

// ================================= 연결리스트

template <typename T>
struct LLNode {
	T data;
	LLNode* prevNode;
	LLNode* nextNode;
	LLNode() : data(nullptr), prevNode(nullptr), nextNode(nullptr) {};
	LLNode(const T& d) : data(d), prevNode(nullptr), nextNode(nullptr) {};
};

template <typename T>
class CList {
private:
	LLNode<T>* headNode;
	LLNode<T>* tailNode;
	int iCount;

public:
	CList() : headNode(nullptr), tailNode(nullptr), iCount(0) {};
	void push_back(const T& data);

	class iterator;
	iterator begin();
	iterator end();
	iterator insert(const iterator& iter , const T& data);
	iterator erase(const iterator& iter);
	
	class iterator {
	private:
		CList<T>* cList;
		LLNode<T>* pNode;
	public:
		iterator() { cList = nullptr; pNode = nullptr; };
		iterator(CList* pList, LLNode<T>* pNode) {
			this->cList = pList;
			this->pNode = pNode;
		};
		T& operator *() { return pNode->data; }

		friend class CList;
	};
};

template<typename T>
inline void CList<T>::push_back(const T& data)
{
	LLNode<T>* newNode = new LLNode<T>(data);

	if (nullptr == headNode) {
		headNode = newNode;
		tailNode = newNode;
	}
	else {
		tailNode->nextNode = newNode;
		newNode->prevNode = tailNode;
		tailNode = newNode;
	}

	iCount++;
}

template<typename T>
inline typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this, headNode);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::insert(const iterator& iter, const T& data)
{
	LLNode<T>* newNode = new LLNode<T>(data);

	if (iter.pNode == headNode) {
		iter.pNode->prevNode = newNode;
		newNode->nextNode = iter.pNode;
		headNode = newNode;
	}
	else {
		iter.pNode->prevNode = newNode;
		iter.pNode->prevNode->nextNode = newNode;
		newNode->nextNode = iter.pNode;
		newNode->prevNode = iter.pNode->prevNode;
	}
	++iCount;
	return iterator(this,newNode);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::erase(const iterator& iter)
{
	LLNode<T>* returnNode = iter.pNode->nextNode;
	if (iter.pNode == headNode) {
		headNode = iter.pNode->nextNode;
		headNode->prevNode = nullptr;
	}
	else {
		iter.pNode->prevNode->nextNode = iter.pNode->nextNode;
		iter.pNode->nextNode->prevNode = iter.pNode->prevNode;
	}
	delete(iter.pNode);

	return iterator(this, returnNode);
}

// =========================== heap

enum class NodeState {
	ROOT = 1,
	LEFT = 2,
	RIGHT = 3
};

class CHeap {
private:
	int* hArr;//배열
	int cnt; // 갯수
public:
	CHeap() {
		hArr = new int[255];
		cnt = 0;
	}
	void push(const int data);
	void Heapify(); // 인덱스,탐색범위
	void pop();
	void GetSize() { cout << cnt << endl; }
	int& operator [](int idx) {
		return hArr[idx];
	}
};

inline void CHeap::push(const int data)
{
	int i = cnt+1;
	hArr[i] = data;

	while (i > 1) {
		if (hArr[i] > hArr[i / 2]) {
			swap(hArr[i], hArr[i/2]);
			i /= 2;
		}
		else break;
	}

	cnt++;
}

inline void CHeap::Heapify()
{
	int root = 1;
	int left = 2;
	int right = 3;
	int curr = cnt; // 1번 인덱스부터 채워져있으므로

	while (curr > 2) {
		swap(hArr[root], hArr[curr]);
		if (hArr[root] < hArr[left]) {
			if (hArr[left] > hArr[right]) swap(hArr[root], hArr[left]);
		}
		if (hArr[root] < hArr[right] && curr > 3) swap(hArr[root], hArr[right]);

		curr--;
	}
	swap(hArr[root], hArr[left]);
}

inline void CHeap::pop()
{
	int i = 1;
	hArr[i] = 0;
	while (i <= cnt) {
		if (hArr[2 * i] > hArr[2 * i + 1]) {
			hArr[i] = hArr[2 * i];
			hArr[2 * i] = 0;
			i *= 2;
		}
		else {
			hArr[i] = hArr[2 * i + 1];
			hArr[2 * i + 1] = 0;
			i *= 2+1;
		}
	}
	
	cnt--;
}

// ==================== Hash Table

class HashNode {
private:
	string hKey;
	int hValue;
	HashNode* nextNode;
public:
	HashNode() : hKey(""), hValue(0), nextNode(nullptr) {};
	HashNode(const string key, const int val) :
		hKey(key), hValue(val), nextNode(nullptr) {};
	HashNode* getNext() { return nextNode; }
	void setNext(HashNode* node) { nextNode = node; }
	const string& getKey() const { return hKey; }
	int getValue() const { return hValue; }
};

class HashBucket { // 해쉬 노드를 담을 연결리스트 버킷
private: 
	int iCount;
	HashNode* headNode;
public:
	HashBucket() : iCount(0), headNode(nullptr) { headNode = new HashNode; };
	~HashBucket();
	const bool& isEmpty() const { return iCount == 0; }
	void push(HashNode* pNode);
	HashNode* FindNode(const string& key) const;
	void DeleteNode(const string& key);
	void Display();
};

class HashMap {
private:
	int bucketSize;
	int iCount;
	HashBucket* bucket;
private:
	int HashFunc(const string& key);
public:
	HashMap();
	HashMap(int bucketSize);
	~HashMap();
	void Insert(const string& key, int val);
	void Delete(const string& key);
	int Find(const string& key);
	int operator [](const string& key);
	void Display();
};
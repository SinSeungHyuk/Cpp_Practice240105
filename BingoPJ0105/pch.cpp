// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

HashBucket::~HashBucket()
{
	HashNode* nextNode = headNode;
	HashNode* deleteNode = nullptr;
	while (deleteNode != nullptr) {
		deleteNode = nextNode->getNext();
		delete nextNode;
		nextNode = deleteNode;
	}
}

void HashBucket::push(HashNode* pNode)
{
	HashNode* newNode = headNode;
	HashNode* nextNode = headNode->getNext();
	newNode->setNext(pNode);
	pNode->setNext(nextNode);
	++iCount;
}

HashNode* HashBucket::FindNode(const string& key) const
{
	HashNode* pNode = headNode;

	while (pNode != nullptr) {
		if (key == pNode->getKey()) {
			break;
		}
		pNode = pNode->getNext();
	}
	return pNode;
}

void HashBucket::DeleteNode(const string& key)
{
	HashNode* pNode = headNode;
	HashNode* prevNode = nullptr;

	while (pNode != nullptr) {
		if (pNode->getKey() == key) {
			if (prevNode) prevNode->setNext(pNode->getNext());
			else headNode->setNext(pNode->getNext());
			delete pNode;
			--iCount;
			return;
		}
		prevNode = pNode;
		pNode = pNode->getNext();
	}
}

void HashBucket::Display()
{
	HashNode* pNode = headNode->getNext();
	while (nullptr != pNode) {
		cout << pNode->getValue() << " ";
		pNode = pNode->getNext();
	}
}
// ------------------- 해시테이블
int HashMap::HashFunc(const string& key) // 해시함수
{
	int hash = 401;
	int c;

	for (int i = 0; i < key.length(); i++) {
		hash = ((hash << 4) + static_cast<int>(key[i])) % bucketSize;
	}
	return hash;
}

HashMap::HashMap()
{
	bucketSize = 16;
	iCount = 0;
	bucket = new HashBucket[16];
}

HashMap::HashMap(int bucketSize)
{
	this->bucketSize = bucketSize;
	iCount = 0;
	bucket = new HashBucket[bucketSize];
}

HashMap::~HashMap()
{
	delete[] bucket;
}

void HashMap::Insert(const string& key, int val)
{
	int hash = HashFunc(key); // key를 주소로 변환

	// 중복 키값 찾기
	HashNode* overlap = bucket[hash].FindNode(key);

	if (nullptr != overlap) return;

	bucket[hash].push(new HashNode(key, val));
	iCount++;
}

void HashMap::Delete(const string& key)
{
	int hash = HashFunc(key);

	bucket[hash].DeleteNode(key);
	iCount--;
}

int HashMap::Find(const string& key)
{
	int hash = HashFunc(key);

	HashNode* find = bucket[hash].FindNode(key);

	if (nullptr == find) {
		cout << "Find Fail\n";
		return -1; // find fail
	}

	return find->getValue();
}

int HashMap::operator[](const string& key)
{
	int hash = HashFunc(key);

	HashNode* find = bucket[hash].FindNode(key);

	if (nullptr == find) return -1; // find fail

	return find->getValue();
}

void HashMap::Display()
{
	for (int i = 0; i < iCount; ++i)
		bucket[i].Display();

	cout << "\n";
}

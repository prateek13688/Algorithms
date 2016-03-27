#include <iostream>
#include <hash_map>
using namespace std;
template<class K, class T>
struct cacheEntry{
	K Key;
	T data;
	cacheEntry *prev;
	cacheEntry *next;
};
template<class K, class T>
class LRUCache
{
public:
	hash_map<K, cacheEntry<K, T>> maps;
	cacheEntry<K, T>* head;
	cacheEntry<K, T>* tail;
	int elementCount;
	int maxSize;
	LRUCache(int size){
		maps = new hash_map<K, cacheEntry<K, T>>(size);
		head = NULL;
		tail = NULL;
		elementCount = 0;
		maxSize = size;
	}
	T get(K value){
		cacheEntry<K, T> * node = maps.find(value);
		if (node != NULL){
			updateList(node);
			T data = node->data;
			return data;
		}
		else return NULL;
	}
	void updateList(cacheEntry<K, T> * node){
		cacheEntry<K, T> * temp1 = node->prev;
		cacheEntry<K, T> * temp2 = node->next;
		temp1->next = temp2;
		if (temp2 != NULL)
			temp2->prev = temp1;
		cacheEntry<K, T> * temp3 = head;
		temp3->prev = node;
		node->next = head;
		node->prev = NULL;
		head = node;
	}
	void put(K key, T value){
		cacheEntry<K, T> * node = maps.find(key);
		if (node != NULL){
			node->data = value;
			updateList(node);
		}
		else{
			insertintoList(key, value);
		}
	}
	void insertintoList(K key, T value){
		cacheEntry<K, T>* node = new cacheEntry();
		node->Key = key;
		node->data = value;
		node->next = NULL;
		node->prev = NULL;
		if (head == NULL){
			head = node
				count++;
		}
		else{
			if (count >= maxSize){
				cacheEntry<K, T> * tail = gettail(head);
				cacheEntry<K, T> * tmp = tail->prev;
				temp->next = NULL;
				count--;
				free(tail);
				K key = node->Key;
				T data = node->data;
				delete node;
				insertintoList(key, value);
			}
			else{
				node->next = head;
				head->prev = node;
				head = node;
			}
		}
		maps[key] = value;
	}
	cacheEntry<K, T>* gettail(cacheEntry<K, T>* head){
		cacheEntry<K, T>* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		return temp;
	}
};


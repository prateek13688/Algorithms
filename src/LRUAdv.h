#pragma once
#include<iostream>
#include <list>
#include<unordered_map>
using namespace std;
struct cacheEntry{
	int Key;
	int data;
	cacheEntry *prev;
	cacheEntry *next;
	cacheEntry(int k, int v) : Key(k), data(v), prev(NULL), next(NULL){}
};
class LRUAdv{
public:
public:
	unordered_map<int, cacheEntry*> maps;
	cacheEntry* head;
	cacheEntry* tail;
	int count;
	int maxSize;
	LRUAdv(int size){
		head = new cacheEntry(-1, -1);
		tail = new cacheEntry(-1, -1);
		count = 0;
		head->next = tail;
		head->prev = NULL;
		tail->prev = head;
		tail->next = NULL;
		maxSize = size;
	}
	int get(int key){
		auto it = maps.find(key); 
		if (it != maps.end()){
			cacheEntry* node = it->second;
			updateList(node);
			int data = node->data;
			return data;
		}
		else return -1;
	}
	void updateList(cacheEntry* node){
		removeNode(node);
		addNode(node);
	}
	void set(int key, int value){
		cacheEntry* node = NULL;
		auto it = maps.find(key);
		if (it != maps.end())
			node = it->second;
		else node = NULL;
		if (node != NULL){
			node->data = value;
			updateList(node);
		}
		else{
			insertintoList(key, value);
		}
	}
	void addNode(cacheEntry* node){
		cacheEntry* first = head->next;
		node->prev = head;
		head->next = node;
		node->next = first;
		first->prev = node;
	}
	void removeNode(cacheEntry *node){
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	cacheEntry* poptail(){
		cacheEntry* node = tail->prev;
		node->prev->next = tail;
		tail->prev = node->prev;
		return node;
	}
	void insertintoList(int key, int value){
		cacheEntry* node = new cacheEntry(key, value);
		if (count == maxSize){
			cacheEntry* oldnode = poptail();
			maps.erase(oldnode->Key);
			delete oldnode;
			count--;
		}
		addNode(node);
		count++;
		maps[key] = node;
	}
	void LRUprint(){
		cacheEntry* tmp = head;
		cout << " Printing the Element" << endl;
		while (tmp){
			cout << tmp->data<<" ";
			tmp = tmp->next;
		}
	}
	LRUAdv::~LRUAdv()
	{

	}
};
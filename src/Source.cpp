#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <unordered_map>
#include <set>
#include "Tree.h"
#include <time.h>
#include "ArrayProg.h"
#include "StringProg.h"
#include "ThreadDemo.h"
#include <conio.h>
#include <thread>

using namespace std;
double findMedianSortedArrays(vector<int>&, vector<int>&);
double medianFind(vector<int>&, int, vector<int>&, int);
class CompareQuote{
public:
	bool operator()(const BidAskPair& a, const BidAskPair& b){
		float aval = (a.ask.price);
		float bval = b.ask.price;
		if (aval < bval)
			return true;
		else
			return false;
	}
};
class CompareQuoteMax{
public:
	bool operator()(const BidAskPair* a, const BidAskPair* b){
		return (a->bid.price > b->bid.price);
	}
};
class QuoteData {
public:
	CompareQuote comp;
	QuoteData(std::string exchanges)
		: exchanges(exchanges) {
		treeobj = new Tree();
		maxTreeRoot = NULL;
		minTreeRoot = NULL;
		bestBid = new BidAskPair();
	}
	void ProcessBid(char exch, Quote bid) {
		auto it = maxexchangeLocation.find(exch);
		if (it != maxexchangeLocation.end()){
			Quote oldQuote = it->second;
			maxTreeRoot = treeobj->deleteNode(maxTreeRoot, oldQuote, exch);
			maxTreeRoot = treeobj->insertNode(maxTreeRoot, bid, exch);
			maxexchangeLocation[exch] = bid;
		}
		else{
			maxTreeRoot = treeobj->insertNode(maxTreeRoot, bid, exch);
			maxexchangeLocation[exch] = bid;
		}
		populateBest();
	}

	void ProcessAsk(char exch, Quote ask) {
		auto it = minexchangeLocation.find(exch);
		if (it != minexchangeLocation.end()){
			Quote oldQuote = it->second;
			minTreeRoot = treeobj->deleteNode(minTreeRoot, oldQuote, exch);
			minTreeRoot = treeobj->insertNode(minTreeRoot, ask, exch);
			minexchangeLocation[exch] = ask;
		}
		else{
			minTreeRoot = treeobj->insertNode(minTreeRoot, ask, exch);
			minexchangeLocation[exch] = ask;
		}
		populateBest();
	}

	void populateBest() const{
		TreeNode* temp = maxTreeRoot;
		bestBid->bid.size = 0;
		bestBid->bid.price = 0.0;
		bestBid->ask.size = 0;
		bestBid->ask.price = 0.0;
		if (temp){
			while (temp->right != NULL)
				temp = temp->right;
		}
		if (temp){
			auto it = temp->treeList;
			bestBid->bid.price = temp->price;
			for (auto its = it.begin(); its != it.end(); its++){
				bestBid->bid.size += its->second.size;
			}
		}
		temp = minTreeRoot;
		if (temp){
			while (temp->left != NULL)
				temp = temp->left;
		}
		if (temp){
			auto it = temp->treeList;
			bestBid->ask.price = temp->price;
			for (auto its = it.begin(); its != it.end(); its++){
				bestBid->ask.size += its->second.size;
			}
		}
	}
	BidAskPair GetBest() const {
		return *bestBid;
	}

private:
	std::string exchanges;
	std::unordered_map<char, Quote> maxexchangeLocation;
	std::unordered_map<char, Quote> minexchangeLocation;
	TreeNode* maxTreeRoot;
	TreeNode* minTreeRoot;
	Tree* treeobj;
	BidAskPair* bestBid;
};


class QuoteDatas {
public:
	QuoteDatas(std::vector<string> quoteCombinations)
		: quoteCombinations(quoteCombinations) {
		int idx = 0;
		for (auto exchanges : quoteCombinations){
			quoteDatas.emplace_back(exchanges);
			processExchangeLocation(exchanges, idx);
			++idx;
		}
	}
	void processExchangeLocation(string exchanges, int idx){
		for (auto exch : exchanges){
			exchangeLocation[exch].push_back(idx);
		}
	}
	void ProcessBid(char exch, Quote bid) {
		vector<int> location = exchangeLocation[exch];
		for (auto loc : location){
			quoteDatas[loc].ProcessBid(exch, bid);
		}
		/*	for (auto exchList : quoteCombinations) {
		if (exchList.find(exch) != std::string::npos)
		quoteDatas[idx].ProcessBid(exch, bid);
		++idx;
		}*/
	}

	void ProcessAsk(char exch, Quote ask) {
		vector<int> location = exchangeLocation[exch];
		for (auto loc : location){
			quoteDatas[loc].ProcessAsk(exch, ask);
		}
		/*int idx = 0;
		for (auto exchList : quoteCombinations) {
		if (exchList.find(exch) != std::string::npos)
		quoteDatas[idx].ProcessAsk(exch, ask);
		++idx;
		}*/
	}

	BidAskPair GetBest(uint32_t exchSetIdx) {
		return quoteDatas[exchSetIdx].GetBest();
	}
private:
	std::unordered_map<char, vector<int>> exchangeLocation;
	std::vector<std::string> quoteCombinations;
	std::vector<QuoteData> quoteDatas;
};
class CompareMap{
public:
	bool operator()(int *a, int* b){
		return (*a < *b);
	}
};
class qComp{
public:
	bool operator()(pair<string, int>p1, pair<string, int>p2){
		return p1.second < p2.second;
	}
};
void getmostFrequentWord(FILE* fp, int k){
	
	char buffer[30];
	int j = 0;
	unordered_map<string, int> mp;
	priority_queue < pair<string, int>, vector<pair<string, int>>, qComp> q;
	//while (fscanf(fp, "%s", buffer) != EOF)
	{
		auto it = mp.find(buffer);
		if (it == mp.end())
			mp[buffer] = 1;
		else
			mp[buffer] += 1;
	}
	for (auto it = mp.begin(); it != mp.end(); it++){
		pair<string, int> p = make_pair(it->first, it->second);
		q.push(p);
	}
	/*while (!q.empty || j < k){
		pair<string, int> p = q.top;
		cout << p.first << endl;
		j++;
	}*/
}
string closestNumbers(int len, string s) {
	int i = 0;
	vector<string> arr ;
	string result;
	int diff = INT_MAX;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, ' ')) {
		arr.push_back(item);
	}
	int temp = 0;
	vector<int> no;
	for (int i = 0; i < len; i++){
		temp = stoi(arr[i]);
		no.push_back(temp);
	}
	sort(no.begin(), no.end());
	int tempDiff = 0;
	for (int i = 0; i < len - 1; i++){
		tempDiff = no[i + 1] - no[i];
		if (tempDiff < diff){
			result = to_string(no[i]) + ' ' + to_string(no[i+1]);
			diff = tempDiff;
		}
		else if (tempDiff == diff){
			result += ' ' + to_string(no[i]) + ' ' + to_string(no[i + 1]);
		}
	}
	return result;
}
void generatePermute(vector<int>& nums, int begin, vector<vector<int>> & results){
	if (begin >= nums.size())
		return;
	generatePermute(nums, begin + 1, results);
	for (int i = 0; i < begin; i++){
		swap(nums[i], nums[begin]);
		results.push_back(nums);
		generatePermute(nums, begin + 1, results);
		swap(nums[i], nums[begin]);
	}
}
vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> result;
	result.push_back(nums);
	generatePermute(nums, 0, result);
	return result;
}


vector<vector<string>> groupAnagrams(vector<string>& strs) {
	vector < vector<string>> result;
	if (strs.size() == 0)
		return result;
	unordered_map<string, vector<string>> mp;
	for (int i = 0; i < strs.size(); i++){
		string word = strs[i];
		string sword = word;
		sort(sword.begin(), sword.end());
		mp[sword].push_back(word);
	}
	for (auto it = mp.begin(); it != mp.end(); it++){
		result.push_back(it->second);
	}
	return result;
}

vector<string> parseSoln(vector<vector<int>>& sol, int n){
	vector<string> result;
	for (int i = 0; i < n; i++){
		string temp = "";
		for (int j = 0; j < n; j++){
			if (sol[i][j] == 1)
				temp += 'Q';
			else
				temp += '.';
		}
		result.push_back(temp);
	}
	return result;
}
void getNQueens(vector<vector<string>>& res, vector<vector<int>>& sol, int row, int n, vector<bool> cols, vector<bool>d1, vector<bool>d2) {
	if (row == n){
		vector<string> result = parseSoln(sol, n);
		res.push_back(result);
		return;
	}
	for (int i = 0; i < n; i++){
		int id1 = row - i + n;
		int id2 = row + i;
		if (!cols[i] && !d1[id1] && !d2[id2]){
			cols[i] = true;
			d1[id1] = true;
			d2[id2] = true;
			sol[row][i] = 1;
			getNQueens(res, sol, row + 1, n, cols, d1, d2);
			cols[i] = false;
			d1[id1] = false;
			d2[id2] = false;
			sol[row][i] = 0;
		}
	}
}
vector<vector<string>> solveNQueens(int n) {
	vector <vector<int>> sol;
	vector<vector<string>> res;
	if (n == 0)
		return res;
	for (int i = 0; i < n; i++){
		vector<int> temp;
		for (int j = 0; j < n; j++){
			temp.push_back(0);
		}
		sol.push_back(temp);
	}
	vector<bool> cols;
	vector<bool> d1;
	vector<bool> d2;
	for (int i = 0; i < n; i++)
		cols.push_back(false);
	for (int i = 0; i < (2 * n); i++)
		d1.push_back(false);
	for (int i = 0; i < (2 * n); i++)
		d2.push_back(false);
	getNQueens(res, sol, 0, n, cols, d1, d2);
	return res;
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
	enum direction
	{
		Left,
		Right,
		Up,
		Down
	};
	vector<int> result;
	int top = -1;
	int bottom = matrix.size();
	int right = matrix[0].size();
	int left = -1;
	int totalElements = right * bottom;
	int currCol = 0, currRow = 0;
	direction dir = Right;
	while (totalElements-- > 0){
		result.push_back(matrix[currRow][currCol]);
		if (dir == Right){
			if (currCol + 1 == right){
				dir = Down;
				currRow++;
				top++;
			}
			else
				currCol++;
		}else if (dir == Down){
			if (currRow + 1 == bottom){
				dir = Left;
				currRow--;
				right--;
			}
			else
				currRow++;
		}
		else if (dir == Left){
			if (currCol - 1 == left){
				dir = Up;
				currRow++;
				bottom --;
			}
			else
				currCol--;
		}
		else if (dir == Up){
			if (currRow - 1 == top){
				dir = Right;
				currCol++;
				left++;
			}
			else
				currCol--;
		}
	}
	return result;
}

vector<vector<int>> createSpiral(int n){
	int i = 0;
	int j = n - 1;
	int count = 1;
	vector<vector<int>> result(n, vector<int>(n,0));
	while (i < j){
		for (int k = i; k < j; k++)
			result[i][k] = count++;
		for (int k = i; k < j; k++)
			result[k][j] = count++;
		for (int k = i; k < j; k++)
			result[j][n - k - 1] = count++;
		for (int k = i; k < j; k++)
			result[n - k - 1][i] = count++;
		i++;
		j--;
	}
	return result;
}

int numIslands(vector<vector<char>>& grid) {
	int n = grid.size();
	if (n == 0)
		return 0;
	int m = grid[0].size();
	int count = 0;
	vector<vector<int>> mp (n, vector<int>(m, 0));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (grid[i][j] == '0')
				continue;
			else{
				if (i == 0){
					if (j == 0)
						count += 1;
					else if (j == m - 1){
						if (i == n - 1)
						{
							if (grid[i][j - 1] == '1')
								continue;
							else
								count += 1;
						}
						else{
							if (grid[i][j - 1] == '1' || grid[i + 1][j] == '1')
								continue;
							else
								count += 1;
						}
					}
					else{
						if (i == n - 1){
							if (grid[i][j - 1] == '1' || grid[i][j + 1] == '1')
								continue;
							else
								count += 1;
						}
						else{
							if (grid[i][j - 1] == '1' || grid[i + 1][j] == '1' || grid[i][j + 1] == '1')
								continue;
							else
								count += 1;
						}
					}
				}
				else if (i == n - 1){
					if (j == 0){
						if (grid[i - 1][j] == '1' || grid[i][j + 1] == '1')
							continue;
						else
							count += 1;
					}
					else if (j == m - 1){
						if (grid[i - 1][j] == '1' || grid[i][j - 1] == '1')
							continue;
						else
							count += 1;
					}
					else{
						if (grid[i - 1][j] == '1' || grid[i][j - 1] == '1' || grid[i][j + 1] == '1')
							continue;
						else
							count += 1;
					}
				}
				else{
					if (j == 0){
						if (grid[i - 1][j] == '1' || grid[i + 1][j] == '1' || grid[i][j + 1] == '1')
							continue;
						else
							count += 1;
					}
					else if (j == m - 1){
						if (grid[i - 1][j] == '1' || grid[i + 1][j] == '1' || grid[i][j - 1] == '1')
							continue;
						else
							count += 1;
					}
					else{
						if (grid[i - 1][j] == '1' || grid[i + 1][j] == '1' || grid[i][j - 1] == '1' || grid[i][j + 1] == '1')
							continue;
						else
							count += 1;
					}
				}
			}
			
		}
	}
	return count;
}

string excelWord(int n){
	string res;
	int s;
	while (n>0){
		s = (n) % 26;
		n = n / 26;
		if (s == 0){
			res += 'Z';
			n = n - 1;
		}
		else
			res += 'A' + (s - 1);

	}
	string z(res.rbegin(), res.rend());
	return z;
}

int pleasentWalk(int r, int c){
	int m = r + 1 + r;
	int n = c + c + 1;
	if (r == 0)
		m = 0;
	if (c == 0)
		n = 0;
	vector<vector<int>> map(m, vector<int>(n, 0));
	vector<vector<int>> comMap(m, vector<int>(n, 0));
	for (int i = 0; i < m; i++){
		if (i % 2 == 0){
			for (int k = 1; k < n; k += 2){
				int n = 0;
				cin >> n;
				map[i][k] = n;
			}
		}
		else{
			for (int k = 0; k < m; k += 2){
				int n = 0;
				cin >> n;
				map[i][k] = n;
			}
		}
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			if (i == 0 && j == 0)
				continue;
			else if (i == 0)
				map[i][j] += map[i][j - 1];
			else if (j == 0)
				map[i][j] += map[i - 1][j];
			else
				map[i][j] += (map[i][j - 1] > map[i - 1][j]) ? map[i][j - 1] : map[i - 1][j];
		}
	}
	return map[m - 1][n - 1];
}
void function1(){
	for (int i = 100; i > -100; i++)
		cout << "Thread t1 " << i << endl;
}

class abc {
public:
		int color;
		int getBase(){
			return 0;
		}
};

class bcd : public abc {
	int speed;
	abc::getBase;
public:
	bcd(int x, int y){
		abc::color = x;
		speed = y;
	}
	int getfunct(){
		return speed;
	}
};

void funcr(const int **ptr){
	int j = 223;
	int * temp = &j;
	printf("%d", *ptr);
	*ptr = temp;
	printf("%d", *ptr);
}

class exceDemo{
public:
	exceDemo(){
		int *p = new int[5];
		throw int();
	}
	~ exceDemo(){
		cout << "Destructor getting called" << endl;
	}
};
int myAtoi(string str) {
	int length = str.length();
	if (length == 0)
		return 0;
	int counter = 0;
	int result = 0;
	while (counter < length){
		int temp = str.at(counter) - '0';
		if (temp < 0 || temp > 9){
			result = 0;
			continue;
		}
		result += temp * pow(10, length - counter - 1);
		counter ++;
	}
	return result;
}

int max(int a, int b){
	return (a > b ? a : b);
}
int min(int a, int b){
	return (a < b ? a : b);
}
double findM3(int a, int b, int c){
	return (a + b + c - max(a, max(b, c)) - min(a, min(b, c)));
}

double findM4(int a, int b, int c, int d){
	return (a + b + c + d - max(a, (max(b, (max(c, d))))) - min(a, (min(b, (min(c, d))))))/ 2.0;
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int l = nums1.size();
	int r = nums2.size();
	if (l == 0 && r == 0)
		return 0;
	else if (l == 0){
		if (r % 2 == 0)
			return (nums2[r / 2 - 1] + nums2[r / 2]) / 2.0;
		else
			return nums2[r / 2];
	}
	else if (r == 0){
		if (l % 2 == 0)
			return (nums1[l / 2 - 1] + nums1[l / 2]) / 2.0;
		else
			return nums1[l / 2];
	}
	else{
		if (l <= r)
			return medianFind(nums1, l, nums2, r);
		else
			return medianFind(nums2, r, nums1, l);
	}
}
double medianFind(vector<int>& A, int n, vector<int>&B, int m){
	if (n == 1){
		if (m == 1)
			return (A[0] + B[0]) / 2.0;
		else if (m % 2 == 0){
			return findM3(A[0], B[m / 2], B[m / 2 - 1]);
		}
		else{
			int x = findM3(A[0], B[m / 2 - 1], B[m / 2 + 1]);
			return (x + B[m / 2]) / 2.0;
		}
	}
	else if (n == 2){
		if (m == 2)
			return findM4(A[0], A[1], B[0], B[1]);
		else if (m % 2 == 0){
			return findM4(B[m / 2], B[m / 2 - 1], max(A[0], B[m / 2 - 2]), min(A[1], B[m / 2 + 1]));
		}
		else{
			return findM3(B[m / 2], max(A[0], B[m / 2 - 1]), min(A[1], B[m / 2 + 1]));
		}
	}
	else{
		int lval = (n - 1) / 2;
		int rval = (m - 1) / 2;
		if (A[lval] <= B[rval]){
			vector<int> tempA(A[lval], A[n - 1]);
			vector<int> tempB(B[0], B[rval]);
			return findMedianSortedArrays(tempA, tempB);
		}
	}
}
int lengthOfLongestSubstring(string s) {
	int r = 0, l = 0;
	int hash[128] = { 0, };
	int len = 0;
	while (r < s.length()){
		if (hash[s[r]] == 1){
			if (r - l > len)
				len = r - l;
			while (s[l] != s[r])
				hash[s[l++]] --;
			hash[s[l++]]--;
		}
		hash[s[r++]]++;
	}
	if (r - l > len)
		len = r - l;
	return len;
}
int main() {
	//ofstream fout(getenv("OUTPUT_PATH"));
	string s = "MCMXCVI";
	vector<int> nums = { 2, 3, 1};
	StringProg obj;
	obj.nextPermutation(nums);
	for (int i = 0; i < nums.size(); i++)
		cout << nums[i];
	cout << endl;
	_getch();
}

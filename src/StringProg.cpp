#include "StringProg.h"
#include <sstream>
#include <math.h>
using namespace std;
StringProg::StringProg()
{
    //ctor
}

StringProg::~StringProg()
{
    //dtor
}

char* StringProg::reverseString(char* str)
{
    int i = 0, j = 0;
    char temp;
    while(str[i] != '\0')
        i++;
    i--;
    while(i != j)
    {
        temp = str[j];
        *(str + j) = *(str + i);
        //str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
    return str;
}

void StringProg::printString(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        cout << str[i];
        i++;
    }
}

int StringProg::makeAnagram(const char* str1, const char* str2)
{
    int i = 0;
    int diff = 0;
    int char1Count[26] = {0};
    int char2Count[26] = {0};
    while(str1[i] != '\0')
    {
        char1Count[str1[i]%97]++;
        i++;
    }
    i = 0;
    while(str2[i] != '\0')
    {
            char2Count[str2[i]%97]++;
            i++;
    }
    for(i = 0; i < 26; i++)
        diff += modDiff(char1Count[i], char2Count[i]);

    return diff;
}

int StringProg::minChartomakeAnagra(string str)
{
    int length = str.length();
    if((length - (length / 2)) != (length/2))
        return -1;
    int len1 = length / 2;
    int i = 0, diff = 0;
    string str1 = str.substr(0, len1);
    string str2 = str.substr(len1);
    int char1Count[26] = {0};
    int char2Count[26] = {0};
    while(i < (int)str1.length())
    {
        char1Count[str1[i]%97]++;
        i++;
    }
    i = 0;
    while(i < (int) str2.length())
    {
            char2Count[str2[i]%97]++;
            i++;
    }
    for(i = 0; i < 26; i++)
        diff += (char1Count[i] - char2Count[i] > 0) ? (char1Count[i] - char2Count[i]) : 0;
    return diff;
}
int StringProg::modDiff(int a, int b)
{
    return (a-b) > (b-a) ? (a-b) : (b-a);
}

bool StringProg:: isPallindrome(string input)
{
    return (input == string(input.rbegin(), input.rend())) ? true : false;
}
int StringProg::maxSubstring(string s1, string s2, int *maxInd)
{
    int m = s1.length();
    int n = s2.length();
    int max = 0;
    int maxIndex = 0;
    int **sCount;
    sCount = new int* [m+1];
    for(int i = 0; i<=m; i++)
        *(sCount + i) = new int[n+1];
    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <=n; j++)
            sCount[i][j] = 0;
    }

    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <=n; j++)
        {
            if(i == 0 || j == 0)
                sCount[i][j] = 0;
            else if(s1.at(i-1) == s2.at(j-1))
            {
                sCount[i][j] = sCount[i-1][j-1] + 1;
                if(max < sCount[i][j])
                {
                    max = sCount[i][j];
                    maxIndex = j;
                }
            }
            else
                sCount[i][j] = 0;
        }
    }
    for(int i =0; i <=m; i++)
        free(*(sCount+ i));
    free(sCount);
    *maxInd = maxIndex - max;
    return max;
}
void StringProg::generateAnagram(vector<string>* blueAnags, string prefix, string input)
{
    int n = input.length();
    if(n == 0)
        blueAnags->push_back(prefix);
    else
    {
        for(int i = 0; i < n; i++)
        {
            if( i == 0)
                generateAnagram(blueAnags, prefix + input.at(i), input.substr(0, i) + input.substr(i+1));
            else if(input.at(i) != input.at(i-1))  // Check for duplicate
                generateAnagram(blueAnags, prefix + input.at(i), input.substr(0, i) + input.substr(i+1));
        }
    }
}

bool StringProg::isAnagramPallindrome(string input)
{
    int charCount[26] = {0};
    int length = input.length();
    for(int i = 0; i < length;i++)
        charCount[input.at(i) %97] ++;
    if(length % 2 == 0)
    {
        for(int i = 0; i < 26; i++)
        {
            if(charCount[i] %2 != 0)
                return false;
        }
        return true;
    }
    else
    {
        int count = 0;
        for(int i = 0; i < 26; i++)
        {
            if(charCount[i] %2 != 0)
                count ++;
        }
        if(count == 1)
            return true;
        else
            return false;
    }
}

int StringProg::getCharCount(string word)
{
    int tagCount = 0;
    for(int i = 0; i < (int)word.length(); i++)
        tagCount += word.at(i);
    return tagCount;
}
bool StringProg::checkforAnags(vector<string>* blueAnags, string str)
{
    for(int i = 0; i < (int)blueAnags->size(); i++)
    {
        if(str == blueAnags->at(i))
            return true;
    }
    return false;
}
string StringProg::replaceBlue(string str)
{
    string tag = "BLUE";
    string result = "";
    vector<string> blueAnags;
    int blueCount = getCharCount(tag);
    vector<string> words;
    string buffer;
    std::istringstream ss (str);
    while(ss >> buffer)
        words.push_back(buffer);
    generateAnagram(&blueAnags, "", tag);
    cout << "The SIZE OF ANAGRAM" << blueAnags.size();
    if(words.size() == 0)
        return str;
    for(int i = 0; i < (int)words.size(); i++)
    {
        if(getCharCount(words[i]) == blueCount)
        {
            if(checkforAnags(&blueAnags, words[i]))
                words[i] = "XXXX";
        }
    }
    result += words[0];
    for(int i = 1; i < (int)words.size(); i++)
        result += " " + words[i];
    return result;
}

string StringProg::encode(vector<int> p, int k, string s)
{
    string temp = s;
    int n = s.length();
    for(int m = 0; m < k; m++)
    {
        string buff = temp;
        for(int i = 0; i < n; i++)
            temp.at(i) = buff.at(p[i]);
    }
    return temp;
}

void StringProg::countthePair(int *a, int count, int* num, int sumLeft, int currIndex, int l)
{
    if((a[currIndex] == sumLeft) && count == l)
    {
        *(num) += 1;
        return;
    }
    for(int i = currIndex; i<=26; i++)
    {
        if(count > l)
            break;
        if(a[i] < sumLeft)
            countthePair(a, (count+1), num, sumLeft-a[i], i+1, l);
    }
}
int StringProg::findFactorial(int a)
{
    unsigned long int result = 1;
    for(int i = 1; i <= a; i++)
        result *= i;
    return result;
}
int StringProg::countStrings(int l, int v) {

    int* a = new int[26];
    int num = 0;
    for(int i = 0; i < 26; i++)
        a[i] = pow(i+1 , 2);
    countthePair(a, 1 ,&num, v, 0, l);
    delete [] a;
    return num * findFactorial(l);
}

bool StringProg::isRepeating(int *a, int n){
    for(int i = 0; i < n; i++)
    {
        if(a[i] > 1)
            return true;
    }
    return false;
}
void StringProg:: resetArray(int* a, int n){
    for(int i = 0; i < n; i++)
        a[i] = 0;
}
int StringProg::maxSubstringwithoutRepition(string s){

    if(s.empty())
    {
        return 0;
    }
    int maxLen = 0;
    int start = 0;
    vector<int> registry;
    registry.resize(256, -1); // char can be the index here
    int j = start;
    while(j < (int)s.length())
    {
        int temp1 = s[j];
        int temp = registry[s[j]];
        if(registry[s[j]] != -1)
        {
            //maxLen = max(maxLen, j - start);
            // clean up the registry up to the previous occurence of the current char, inclusively
            for(int k = start; k < registry[s[j]]; ++k)
            {
                registry[s[k]] = -1;
            }
            start = registry[s[j]] + 1;
        }
        registry[s[j]] = j;
        ++j;
    }
    //return max(maxLen, j - start);
	return 0;
}

string StringProg::substringPallindrome(string s)
{
	int max = 0;
	int p, q = 0;
	int n = s.length();
	if (n < 2)
		return s;
	string result = "";
	while (s[n + 1] == ' ')
		cout << "test valid" << endl;
	for (int i = 0; i < n; i++){
		p = q = i;
		while (q < n && s[q] == s[q + 1])
			q++;
		while (p >= 0 && q < n && s[p] == s[q]){
			if (result.length() < q - p + 1)
				result = s.substr(p, q - p + 1);
			p--;
			q++;
		}
	}
    return result;
}

string StringProg::convertToZigzag(string s, int noOfrows){

    if(noOfrows == 1 || s.length() == 1)
        return s;
    int rows = 0;
    int count = 0;
    string result = "";
    bool isGoing_down = true;
    string *str = new string[noOfrows];
    while(count < (int)s.length()){
        str[rows] += s.at(count);
        if(rows == 0){
            rows++;
            isGoing_down = true;
        }
        else if(rows == (noOfrows-1)){
            rows --;
            isGoing_down = false;
        }
        else if(isGoing_down)
            rows++;
        else
            rows --;
        count ++;
    }
    for(int i = 0; i < noOfrows; i++)
        result += str[i];
    delete [] str;
    return result;
}

string StringProg::findPrefix(string s1, string s2){

    int i = 0;
    int j = 0;
    while(i < (int)s1.length() && j < (int)s2.length()){
        if(s1.at(i) != s2.at(j))
            break;
        i++;
        j++;
    }
    return s1.substr(0, i);
}

string StringProg::findMaxPrefix(vector<string>& strs){
    int i = 0;
    int j = strs.size()-1;
    string prefixL, prefixR;
    string maxPrefix = findPrefix(strs[i], strs[j]);
    while(i <= j){
        cout << "--------------------------------------------------------" << endl;
        prefixL = findPrefix(maxPrefix, strs[i]);
        prefixR = findPrefix(maxPrefix, strs[j]);
        maxPrefix = findPrefix(prefixL, prefixR);
        i++;
        j--;
    }
    if(maxPrefix.length() == 0)
        return "";
    return maxPrefix;
}

int StringProg::strStr(string haystack, string needle){
    if(needle.length() > haystack.length())
        return -1;
    if(haystack == needle)
        return 0;
    int n = haystack.length();
    int m = needle.length();
    for(int i = 0, j = i + m; i < n && j < n; i++){
        if(needle.compare(haystack.substr(i, j)) == 0)
            return i;
    }
    return -1;
}

int StringProg::shortestPallindrome(string word){
	int n = word.length();
	int maxPallindromeLength = 1;
	string temp, tempRev;
	for (int diff = 2; diff <= n; diff++){
		temp = word.substr(0, diff);
		tempRev = string(temp.rbegin(), temp.rend());
		if (temp == tempRev)
			maxPallindromeLength = diff;
	}
	return 2*n - maxPallindromeLength;
}

bool StringProg::allWordsChecked(bool *seen, int n){
	for (int i = 0; i < n; i++){
		if (!seen[i])
			return false;
	}
	return true;
}
void StringProg::resetSeen(bool *seen, int n){
	for (int i = 0; i < n; i++)
		seen[i] = false;
}
vector<int> StringProg::findSubstring(string s, vector<string>& words) {
	vector<int> result;
	int count = 0;
	if (words.size() == 0)
		return result;
	if (s.length() < (int)(words.at(0).length() * words.size()))
		return result;
	unordered_map<string, int> dict;
	int wordL = words.at(0).length();
	int num = words.size();
	int size = s.length();
	for (int i = 0; i < (words.size()); i++){
		dict[words[i]] ++;
	}
	for (int i = 0; i < (size - (num * wordL) + 1); i++){
		unordered_map<string, int> seen;
		int j = 0;
		for (; j < num; j++){
			string word = s.substr(i + j * wordL, wordL);
			auto it = dict.find(word);
			if (it != dict.end()) // word is found
			{ 
				seen[word]++;
				if (seen[word] > dict[word])
					break;
			}
			else break;
		}
		if (j == num)
			result.push_back(i);
	}
	return result;
}
void clear(bool *value){
	for (int i = 1; i <= 9; i++)
		value[i] = false;
}
bool StringProg::isValidSudoku(vector<vector<char>>& board){
	bool *value = new bool[10];  // since numbers are from 1 to 10
	for (int i = 0; i < 9; i++){
		clear(value);
		for (int j = 0; j < 9; j++){
			char c = board[i][j];
			if (c == '.') continue;
			c -= '0';
			if (value[c])
				return false;
			else
				value[c] = true;
		}
	}
	for (int j = 0; j < 9; j++){
		clear(value);
		for (int i = 0; i < 9; i++){
			char c = board[i][j];
			if (c == '.') continue;
			c -= '0';
			if (value[c])
				return false;
			else
				value[c] = true;
		}
	}
	// grid check 
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int m = 0; m < 3; m++){
				clear(value);
				for (int n = 0; n < 3; n++){
					int x = i * 3 + m;
					int y = j * 3 + n;
					char c = board[x][y];
					if (c == '.') continue;
					c -= '0';
					if (value[c])
						return false;
					else
						value[c] = true;
				}
			}
		}
	}
	return true;
}

string StringProg::countAndSay(int n){
	if (n == 1)
		return "1";
	if (n == 2)
		return "11";
	string s = "11";
	string temp = s;
	int k = 0;
	while (k < n-2){
		s = temp;
		int n = s.length();
		temp = ""; int i = 0;
		while (i < s.length()){
			int count = 1;
			char c = s.at(i);
			i++;
			while ((i <= (n - 1)) && ((char)s.at(i) == (char)s.at(i-1))){
				count++; i++;
			}
			temp += to_string(count) + c;
		}
		k++;
	}
	return temp;
}

string StringProg::multiply(string num1, string num2){

	if (num2 == "0" || num1 == "0")
		return "0";
	int ** row;
	int n = num1.length();
	int m = num2.length();
	vector<int> resultV;
	for (int i = 0; i < m + n; i++)
		resultV.push_back(0);
	num1 = string(num1.rbegin(), num1.rend());
	num2 = string(num2.rbegin(), num2.rend());
	for (int i = 0; i < n; i++){
		int v1 = num1[i] - '0';
		for (int j = 0; j < m; j++){
			int v2 = num2[j] - '0';
			resultV[i + j] += v1 * v2;
		}
	}
	int carryOn = 0;
	for (int i = 0; i < m + n; i++){
		int value = resultV[i] + carryOn;
		resultV[i] = value % 10;
		carryOn = value / 10;
	}
	string result;
	bool skippedZero = false;
	int start = m + n;
	if (resultV[m + n - 1] == 0)
		start = m + n - 1;
	for (int i = start - 1; i >= 0; i--)
		result += resultV[i] + '0';
	return result;
}

int StringProg::convertRomantoInteger(string s){
	int n = s.length();
	int result = 0;
	unordered_map<char, int> m = { { 'I', 1 }, {'V', 5},{ 'X', 10 }, { 'C', 50 }, { 'L', 100 }, { 'D', 500 }, { 'M', 1000 } };
	for (int i = 0; i < n; i++){
		if (i < n - 1 && m[s[i]] < m[s[i + 1]])
			result -= m[s[i]];
		else
			result += m[s[i]];
	}
	return result;
}

void StringProg::gameOfLife(vector<vector<int>>& board) {
	int n = board.size();
	int m = board[0].size();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			int count = 0;
			if (i > 0 && j > 0 && (board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == -1))
				count += 1;
			if (i > 0 && j < m - 1 && (board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == -1))
				count += 1;
			if (i > 0 && (board[i - 1][j] == 1 || board[i - 1][j] == -1))
				count += 1;
			if (j > 0 && (board[i][j - 1] == 1 || board[i][j - 1] == -1))
				count += 1;
			if (j < m - 1 && (board[i][j + 1] == 1 || board[i][j + 1] == -1))
				count += 1;
			if (i < n - 1 && (board[i + 1][j] == 1 || board[i + 1][j] == -1))
				count += 1;
			if (i < n - 1 && j > 0 && (board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == -1))
				count += 1;
			if (i < n - 1 && j < m - 1 && (board[i + 1][j + 1] == 1 || board[i + 1][j + 1] == -1))
				count += 1;
			if (board[i][j] == 1){
				if (count < 2 || count > 3)
					board[i][j] = -1;
			}
			else if (board[i][j] == 0){
				if (count == 3)
					board[i][j] = 2;
			}
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (board[i][j] == -1)
				board[i][j] = 0;
			else if (board[i][j] == 2)
				board[i][j] = 1;
		}
	}
}

void StringProg::nextPermutation(vector<int>& nums){
	if (nums.size() < 2)
		return;
	bool isFound = false;
	int count = nums.size() - 1;
	while (count > 0){
		if (nums[count] > nums[count - 1]){
			isFound = true;
			break;
		}
		count--;
	}
	if (!isFound){
		sort(nums.begin(), nums.end());
		return;
	}

	int mark = --count;
	int lindex = 0;
	//Finding smallest digit  and index after digit at mark 
	int min = INT_MAX;
	for(int i = nums.size() - 1; i > mark; i--){
		if (nums[i] < nums[mark])
			continue;
		if (nums[i] < min){
			min = nums[i];
			lindex = i;
		}
	}
	// Swap Digits at count and count - 1 index
	int temp = nums[mark];
	nums[mark] = nums[lindex];
	nums[lindex] = temp;
	sort(nums.begin() + mark + 1, nums.end());
}


#ifndef STRINGPROG_H
#define STRINGPROG_H
#include <iostream>
#include <String.h>
#include <string>
#include <malloc.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class StringProg
{
    public:
        StringProg();
        virtual ~StringProg();
        char* reverseString(char *);
        void printString(char* );
        int makeAnagram(const char *, const char *);
        int modDiff(int, int);
        int minChartomakeAnagra(std::string);
        int maxSubstring(std::string , std::string, int*);
        void generateAnagram(std::vector<std::string>*, std::string, std::string);
        bool isPallindrome(std::string);
        bool isAnagramPallindrome(std::string);
        int getCharCount(std::string);
        bool checkforAnags(std::vector<std::string>*, std::string);
        std::string replaceBlue(std::string);
        std::string encode(std::vector<int> , int , std::string );
        void countthePair(int *, int, int*, int, int, int);
        int countStrings(int , int );
        int findFactorial(int);
        bool isRepeating(int *, int);
        void resetArray(int*, int);
        int maxSubstringwithoutRepition(std::string);
        string substringPallindrome(std::string);
        std::string convertToZigzag(std::string, int);
        string findPrefix(string s1, string s2);
        string findMaxPrefix(vector<string>&);
        int strStr(string, string);
		int shortestPallindrome(string);
		vector<int> findSubstring(string, vector<string> &);
		bool allWordsChecked(bool *, int);
		void resetSeen(bool *, int);
		bool isValidSudoku(vector<vector<char>>&);
		string countAndSay(int);
		string multiply(string, string);
		int convertRomantoInteger(string);
		string getPermutation(int n, int k);
		void StringProg::gameOfLife(vector<vector<int>>& board);
		void nextPermutation(vector<int>&);
		string minWindow(string, string);
		void generatePermutation(vector<int>&, vector<int>&, vector<vector<int>>&);
		vector<vector<int>> permuteUnique(vector<int>&);
		int threeSumClosest(vector<int>&, int);
		int	difference(int, int);
	protected:
    private:
};

#endif // STRINGPROG_H

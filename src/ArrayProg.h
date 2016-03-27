#ifndef ARRAYPROG_H
#define ARRAYPROG_H

#include <math.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <sstream>
#include <climits>
#include <queue>
using namespace std;
class ArrayProg
{
    friend class demoClass;
    public:
		ArrayProg();
        ArrayProg(int);
        virtual ~ArrayProg();
        int FindSum (int , int, int);
        int abs(int );
        int sumofPlaces(int , int );
        int max(int a, int b, int c);
        int findMax(int *, int, int);
        int crossSum(int *, int , int , int );
        int minValue(int, int, int);
        int calcminCost(int**, int);
        int findMinIndex(int *,bool*, int);
        std::vector<int> twoSum(std::vector<int>&, int);
        int findSubArray(int *a, int n);
        int reverse_digigts_Integer(int);
        int maxAreaContainer(std::vector<int>&);
        void getTriple(vector<vector<int>>&, vector<int>&, int, int, int, bool*);
        vector<vector<int>> threeSum(vector<int>&);
        bool isExists(vector<vector<int>>&, vector<int>&);
        void bubblesort(vector<int>&);
        int no_of_paths(int);
        vector<int> converTosubset(int, vector<int>&);
        vector<vector<int>> subsetGeneration(vector<int>&);
        void generateParanthesis_Combination(vector<string>&, char*, int, int,int);
        int no_of_Coin_combination(int, int *, int **, int);
        int no_of_ways_expression(unordered_map<string,int>&, string, int, int, bool);
        string int_to_string(int);
        int findMissingNo(vector<int>&);
        int findMissingNo_LessMemory(vector<int>&);
        vector<vector<int> > twoSums(vector<int>& , int, int, int);
        vector<vector<int> > fourSum(vector<int>& , int);
        void printVector(vector<int>&);
        int campers(int, int, int*);
        int* dota_permuation(int);
        vector<int>toiletUsage(int, int);
        vector<int> toiletQues(int, int);
        int countYears(vector<int>&);
        vector<int> removeDeadPlants(vector<int>&, vector<int>&);
		void display(){ cout << "The Value of a" << a; }
		int divide(int, int);
		int searchInRotatedSortedArray(vector<int>& nums, int, int, int);
		int  ArrayProg::searchInsert(vector<int>&, int);
		void ArrayProg::searchPos(vector<int>&, int, int, int, int*);
		bool subsetSum(vector<int>&, int);
		vector<vector<int>> combinationSum(vector<int>&, int);
		int maxTeamScore(vector<int>&);
		void rotateArray(vector<vector<int>> &);
		bool canJump(vector<int>& nums);
		int jump(vector<int>& nums);
		int maxSubArray(vector<int>& nums);
		int maxProfit(vector<int>& prices);		//int no_of_Coin_combination(int);
		int maxProfitDP(vector<int>& prices);
		int minPathSum(vector<vector<int>>& grid);
		bool searchInRow(vector<vector<int>>& matrix, int left, int right, int target, int row);
		bool search(vector<vector<int>>& matrix, int left, int right, int target);
		bool searchMatrix(vector<vector<int>>& matrix, int target);
    protected:
    private:
        int a;
};

#endif // ARRAYPROG_H

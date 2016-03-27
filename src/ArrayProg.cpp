#include "ArrayProg.h"
#include <unordered_map>
#define MAX 999999999;
using namespace std;

#define byte uint8_t
ArrayProg::ArrayProg(){}
ArrayProg::ArrayProg(int b)
{
	a = b;
}

ArrayProg::~ArrayProg()
{
    //dtor
}
int ArrayProg::abs(int x)
{
    return (x > 0) ? x : (-1 *x);
}

int ArrayProg::sumofPlaces(int digit, int number)
{
    int sum = 0;
    for(int i = 0; i < number; i++ )
        sum += digit * pow(10 , i);
    return sum;
}
int ArrayProg::FindSum(int x,int y, int z)
{

    return 0;
}

int ArrayProg::max(int a, int b, int c)
{
    return (c >((a > b) ? a : c)) ? c : ((a > b) ? a : c);
}
int ArrayProg::crossSum(int *a, int left, int middle, int right)
{
    int k = 1;
    int leftsum = 0;
    int rightsum = 0;
    int leftmin = 0;
    int rightmin = 0;
    int leftCount = 0;
    int rightCount = 0;
    int lmin = 99999999;
    int rmin = 99999999;
    //int lmin = 0;
    if(left > right)
        return 0;
    for(int i = middle; i >= left; i--)
    {

        lmin = (lmin < a[i]) ? lmin :a[i];
        if(leftsum < (lmin * k)){
            leftmin = lmin;
            leftsum = leftmin * k;
            leftCount = k;
        }
        k++;
    }
    k = 1;
    for(int i = middle+1; i <= right; i++)
    {
        rmin = (rmin < a[i]) ? rmin :a[i];
        if(rightsum < (rmin * k)){
            rightmin = rmin;
            rightsum = rightmin * k;
            rightCount = k ;
        }
        k++;
    }
    leftmin = (leftmin < rightmin) ? leftmin : rightmin;
    return leftmin * (leftCount + rightCount);
}
int ArrayProg::findMax(int *a, int left, int right)
{
    if(left == right)
        return a[left];
    int middle =  (left + right) /2;
    int leftsum = findMax(a, left, middle);
    int crosSum = crossSum(a, left, middle, right);
    int rightSum = findMax(a, middle+1, right);
    return max(leftsum, crosSum, rightSum );
}

int ArrayProg::minValue(int a, int b, int c)
{
    return (c < ((a < b) ? a : b)) ? c : ((a < b) ? a : b);
}
int ArrayProg::findMinIndex(int *dist, bool* included, int n)
{
    int min = MAX;
    int minIndex = 0;
    for(int i = 0; i < n; i++)
    {
        if(dist[i] < min && (!included[i]))
        {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}
int ArrayProg::calcminCost(int** cost, int n)
{
    int* dist = new int[n];
    for(int i = 0; i < n; i++)
        dist[i] = MAX;
    dist[0] = 0;
    bool* included = new bool[n];
    for(int i = 0; i < n; i++)
        included[i] = false;
    for(int i = 0; i < n-1; i++)
    {
        int u = findMinIndex(dist, included, n);
        included[u] = true;
        for(int v = 0; v < n; v++)
        {
            if(cost[u][v] > -1 && ((dist[u] + cost[u][v] )< dist[v]))
                dist[v] = dist[u] + cost[u][v];
        }
    }
    int value = dist[n-1];
    delete [] dist;
    delete [] included;
    return value;
}

int ArrayProg::findSubArray(int *a, int n)
{
    int* maxSumArray = new int[n];
    int maxSum = 0;
    for(int i = 0; i < n; i++)
        maxSumArray[i] = 0;
    maxSumArray[0] = a[0];
    for(int i = 1; i < n; i++)
    {
        maxSumArray[i] = (maxSumArray[i-1] + a[i]) > a[i] ?
                                    (maxSumArray[i-1] + a[i]) : a[i];

        maxSum = (maxSumArray[i] > maxSum) ? maxSumArray[i] : maxSum;
    }
    for(int i = 0; i < n; i++)
        cout << maxSumArray[i] << " ";
    cout << endl;
    return maxSum;
}

vector<int> ArrayProg::twoSum(vector<int>& nums, int target)
{
    unordered_map<int, int> mp;
    int diffIndex, i =0;
    vector<int> result;
    for(i = 0; i < (int)nums.size(); i++)
        ++mp[nums[i]] = i;
    for(i = 0; i < (int)nums.size(); i++)
    {
        int currNum = nums[i];
        auto itr = mp.find(target - currNum);
        if(itr != mp.end())
            diffIndex = (*itr).second;
        else
            diffIndex = -1;
        if(diffIndex != -1 && diffIndex != i)
        {
            result.push_back((diffIndex < i ? diffIndex : i)+1);
            result.push_back((diffIndex > i ? diffIndex : i)+1);
            break;
        }
    }
    return result;
}

int ArrayProg::reverse_digigts_Integer(int x){

    int px = 0;
    while(x != 0)
    {
        if(px > 32767 || px < -32767)
            return 0;
        px = px * 10 + (x % 10);
        x = x/10;
    }
    return px;
}

int ArrayProg::maxAreaContainer(vector<int>& height){
    int current = 0, max  =0;
    int i = 0;
    int j = height.size()-1;
    max = (j - i)*(height[i] < height[j] ? height[i] : height[j]);
    while(i < j){
        if(height[i] <= height[j]){
            current = height[i];
            while(i<j && height[i] <= current){
                i ++;
            }
            int k = (j - i) * (height[i] < height[j] ? height[i] : height[j]);
            max = (max > k) ? max : k;
        }
        else{
            current = height[j];
            while(i < j && height[j] <= current){
                j--;
            }
            int k = (j - i) * (height[i] < height[j] ? height[i] : height[j]);
            max = max > k ? max : k;
        }
    }
    return max;
}

void ArrayProg::getTriple(vector<vector<int>>& arr, vector<int>& a, int level, int index, int sum, bool* flag){

    if(sum == 0 && level == 3)
    {
        bool result = true;
        vector<int> temp;
        for(int i = 0; i < (int)a.size(); i++){
            if(flag[i])
            {
                cout << "Inserting ELements " <<a[i] << endl;
                temp.push_back(a[i]);
            }
        }
        for(int i = 0; i < (int)arr.size(); i++)
        {
            if(arr[i] == temp)
            {
                cout <<"Duplicate element " << endl;
                result = false;
                break;
            }
        }
        if(result)
            arr.push_back(temp);
        cout << "------------------------------------------------------" << endl;
        return;
    }
    if(level > 3 || index >= (int)a.size())
        return;
    if((sum) > 0)
        return;
    for(int i = index; i < (int)a.size(); i++){
        flag[i] = true;
        getTriple(arr, a, level+1, i+1, sum+a[i], flag);
        flag[i] = false;
    }
}
bool ArrayProg::isExists(vector<vector<int>>& arr, vector<int>& temp){
    for(int i = 0; i < (int)arr.size(); i++){
        if(arr[i] == temp)
            return true;
    }
    return false;
}
 vector<vector<int>> ArrayProg::threeSum(vector<int>& num){
              if (num.size() < 2) { return {}; }
        sort(num.begin(), num.end());
        vector<vector<int> > result;
        int i = 0;
        while (i < (int)num.size() - 2) {
            int target = -num[i];
            int j = i + 1, k = num.size() - 1;
            while (j < k) {
                int value = num[j] + num[k];
                if (value == target) {
                   result.emplace_back(vector<int>{num[i], num[j], num[k]});
                   do { j++; } while (j < k && num[j] == num[j - 1]);
                   do { k--; } while (j < k && num[k] == num[k + 1]);
                } else if (value < target) {
                   do { j++; } while (j < k && num[j] == num[j - 1]);
                } else {
                   do { k--; } while (j < k && num[k] == num[k + 1]);
                }
            }
            do { i++; } while (i < (int)num.size() - 2 && num[i] == num[i - 1]);
        }
        return result;
 }

void ArrayProg::bubblesort(vector<int>& a){
    int n=a.size();
    int i, t, s = 1;
    while (1) {
        int min = a[0];
        int minIndex = 0;
        for(int j = 0; j < n; j++){
            if(a[j] <= min){
                min = a[j];
                minIndex = j;
            }
        }
        if(minIndex == 0 || (minIndex == 1 && a[0] == a[1]))
            break;
        s = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }
}

int ArrayProg::no_of_paths(int n){
    int *pathArray = new int[n+1];
    pathArray[0] = 1;
    for(int i = 1; i <= n; i++)
        pathArray[i] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            if(!(i < j)){
                pathArray[i] += pathArray[i - j];
            }
        }
    }
    return pathArray[n];
}

vector<int> ArrayProg::converTosubset(int x, vector<int>& inputSet){
    int index = 0;
    vector<int> result;
    for(int k = x; k > 0; k = k >> 1){
        if((k & 1) == 1)
            result.push_back(inputSet[index]);
        index ++;
    }
    return result;
}
vector<vector<int>> ArrayProg::subsetGeneration(vector<int>& inputSet){
    vector<vector<int>> result;
    vector<int> temp;
    int max = (1 << inputSet.size());
    for(int i = 0; i < max; i++){
        temp = converTosubset(i, inputSet);
        if(temp.size() != 0)
            result.push_back(temp);
    }
    return result;
}

void ArrayProg::generateParanthesis_Combination(vector<string>& result, char* ch, int leftCount, int rightCount,int count){
    if(leftCount == 0 && rightCount == 0){
        string combination = string(ch);
        result.push_back(combination);
    }
    if(leftCount < 0 || rightCount < leftCount)
        return;
    if(leftCount > 0)
    {
        ch[count] = '(';
        generateParanthesis_Combination(result, ch, leftCount-1, rightCount, count+1);
    }
    if(rightCount > leftCount){
        ch[count] = ')';
        generateParanthesis_Combination(result, ch, leftCount, rightCount-1, count+1);
    }
}

int ArrayProg::no_of_Coin_combination(int n, int *coindeno, int **deno_matrix, int index){
   if(deno_matrix[n][index] > 0)
        return deno_matrix[n][index];
    if(index >= 3)
        return 1;
    int deno = coindeno[index];
    int ways = 0;
    for(int i = 0; i * deno <= n; i++){
        if((n - i * deno) >= 0){
            ways += no_of_Coin_combination(n - i * deno, coindeno, deno_matrix, index+1);
        }
    }
    deno_matrix[n][index] = ways;
    return ways;
}
string ArrayProg::int_to_string(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}
int ArrayProg::no_of_ways_expression(unordered_map<string,int>& mapExp, string expression, int start, int end, bool result){
    string key = "" + expression+ int_to_string(start)+ int_to_string(end) + int_to_string(result);
    auto it = mapExp.find(key);
    int c = 0;
    if(it != mapExp.end())
        return (*it).second;
    if(start == end){
        if(expression.at(start) == '1' && result)
            return 1;
        else if(expression.at(start) == '0' && !result)
            return 1;
        else return 0;
    }
    if(result){
        for(int i = start + 1; i <= end; i++){
            if(expression.at(i) == '&'){
                c += no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true);
            }
            else if(expression.at(i) == '|'){
                c += (no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true));
                c += no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
                c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true);
            }
            else if(expression.at(i) == '^')
                c += no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
                c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true);
        }
    }
        else{
            for(int i = start + 1; i <= end; i++){
            if(expression.at(i) == '&'){
                c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
                c += no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
                c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true);
            }
            else if(expression.at(i) == '|'){
               c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
            }
            else if(expression.at(i) == '^')
                c += no_of_ways_expression(mapExp, expression, start, i-1, true) *
                        no_of_ways_expression(mapExp, expression, i+1, end, true);
                c += no_of_ways_expression(mapExp, expression, start, i-1, false) *
                        no_of_ways_expression(mapExp, expression, i+1, end, false);
        }
    }
    mapExp.insert(std::make_pair(key,c));
    return c;
}

int ArrayProg::findMissingNo(vector<int>& input){
    long numSize = INT_MAX;
    int num = -1;
    int* byteArray = new int[numSize / 8];
    for(int i = 0; i < input.size(); i++){
        byteArray[input[i] / 8] |= (1 << (input[i] % 8));
    }
    for(int i = 0; i < (numSize / 8); i++){
        for(int j = 0; j<8; j++){
            if(byteArray[i] && (1 << j) == 0){
                cout << "The Element Available " << (i * 8) + j;
                num = (i * 8) + j;
                break;
            }
        }
    }
    return num;
}

int ArrayProg::findMissingNo_LessMemory(vector<int>& input){
    int blockNum = 2^12;
    int bitSize = 2^20;
    int starting = 0;
    int num  = 0;
    int *bitArray = new int[bitSize/8];
    int *blocks = new int[blockNum];
    for(int i = 0; i < input.size(); i++){
        blocks[input[i]/bitSize]++;
    }
    for(int i = 0; i < input.size(); i++){
        if(blocks[i] < bitSize)
            starting = i * bitSize;
    }
    for(int i = 0; i < (int)input.size(); i++){
        if(input[i] > bitSize && input[i] < (starting + bitSize))
            bitArray[(input[i] - starting)/ bitSize] |= 1 << ((input[i] - starting) % bitSize);
    }
    for(int i = 0; i < blockNum; i++){
        for(int j = 0; j < 8; j++){
            if(bitArray[i] && (1 << j) == 0){
                num = i * bitSize + j + starting;
                break;
            }
        }
    }
    return num;
}

vector<vector<int>> ArrayProg::twoSums(vector<int>& input, int start, int end, int target){
    if(input.size() < 2)
        return {};
    if(end - start < 1)
        return {};
    vector<vector<int> > result;
    int i = start;
    int j = end;
    sort(input.begin(), input.end());
    while(i < j){
        int value = input[i] + input[j];
        if(value == target){
            result.emplace_back(vector<int>{input[i], input[j]});
            do {i++; } while(i < j && input[i] == input[i-1]);
            do {j--; } while(i <j && input[j] == input[j+1]);
        }
        else if (value < target){
            do {i++; } while(i < j && input[i] == input[i-1]);
        }
        else{
            do {j--; } while(i <j && input[j] == input[j+1]);
        }
    }
    return result;
}
void ArrayProg::printVector(vector<int>& v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i];
    cout << endl;
}
vector<vector<int>> ArrayProg::fourSum(vector<int>& input, int target){
    if(input.size() <= 3)
        return {};
    int n = input.size();
    vector<vector<int> > result;
    sort(input.begin(), input.end());
    vector<vector<int> > temp;
    for(int i = 0; i < (n - 3);){
        for(int j = i +3; j < n;){
            temp = twoSums(input, i+1, j-1, target - ((input[i] + input[j])));
            if(temp.size() != 0){
            for(int k = 0; k< (int)temp.size(); k++){
                temp[k].push_back(input[i]);
                temp[k].push_back(input[j]);
                sort(temp[k].begin(), temp[k].end());
                //printVector(temp[k]);
                result.push_back(temp[k]);
                }
            }
            do {j++;} while(input[j] == input[j-1]);
        }
        do { i++; } while(input[i] == input[i-1]);
    }
    return result;
}

int ArrayProg::campers(int n, int k, int* snipers){
    bool *players = new bool[n+1];
    int maxplayer = 0;
    int count = 0;
    for(int i = 0; i < n+1; i++)
        players[i] = false;
    for(int i = 0; i < k; i++)
        players[snipers[i]] = true;
    for(int i = 1; i < n+1; i++){
        if(i == n){
            if(!players[i - 1])
                count++;
        }
        else{
            if(!players[i-1] && !players[i+1]){
                count ++;
                players[i] = true;
            }
        }
    }
    return count;
}

int* ArrayProg::dota_permuation(int n){
    int *perm = new int[n];
    for(int i = 0; i < n; i++){
        perm[i] = i+1;
    }
    if(n < 3)
        return perm;
    int i = 0;
    int j = n-1;
    int* result = new int[n];
    for(int i = 0; i < n; i++)
        result[i] = -1;
    int count = n-1;
    while(i < j){
        result[count] = perm[j];
        count--;
        result[count] = perm[i];
        count --;
        i++;
        j--;
    }
    if(i == j)
        result[count] = perm[i];
    return result;
}

vector<int> ArrayProg::toiletUsage(int n, int m){
    vector<int> result;
    if (m > n){
        int div = m  / n;
        int rem = m % n;
        if(rem == 0){
            result.push_back((n/2)+1);
            result.push_back(div - 1);
        }
        else{
            if (rem%2==0){
                if (n%2==0){
                    result.push_back(n - rem/2 +1);
                    result.push_back(div);
                }
                else{
                    result.push_back(rem/2);
                    result.push_back(div);
                }
            }
            else{
                if (n%2==0){
                    result.push_back(rem/2 +1);
                    result.push_back(div);
                }
                else{
                    result.push_back(n - rem/2);
                    result.push_back(div);
                }
            }
        }
    }
    else {
        if(m %2 == 0 && m != n){
            result.push_back(n - m/2 +1);
            result.push_back(0);
        }
        else{
            result.push_back(m/2 + 1);
            result.push_back(0);
        }
    }
    return result;
}

vector<int> ArrayProg::toiletQues(int n, int m){
    vector<int> result;
    int *dirty = new int[n+1];
    for(int k = 0; k < n+1; k++)
        dirty[k] = 0;
    for(int k =1; k <= m; k+= 2){
        int lmax = 1;
        int rmax = n;
        while(dirty[lmax] > dirty[lmax+1]) { lmax++;}
        if(k == m){
            result.push_back(lmax);
            result.push_back(dirty[lmax]);
            break;
        }
        dirty[lmax]++;
        while(dirty[rmax] > dirty[rmax-1]) { rmax--;}
        if(k+1 == m){
            result.push_back(rmax);
            result.push_back(dirty[rmax]);
            break;
        }
        dirty[rmax]++;
    }
    return result;
}

vector<int> ArrayProg::removeDeadPlants(vector<int>& plants, vector<int>& dieIndex){
    int j = 0, i = 0;
    vector<int> buffer;
    while(i < plants.size()){
        if(i == dieIndex[j])
            j++;
        else
            buffer.push_back(plants[i]);
        i++;
    }
    return buffer;
}
int ArrayProg::countYears(vector<int>& plants){
    if(plants.size() < 2)
        return plants.size();
    bool result = true;
    int years = 0;
    vector<int> dieIndex;
    while(result){
        result = false;
        for(int i= 1; i < (int)plants.size(); i++){
            if(plants[i] > plants[i-1]){
                dieIndex.push_back(i);
                result = true;
            }
        }
        printVector(dieIndex);
        if(result){
            plants = removeDeadPlants(plants, dieIndex);
            years++;
        }
        printVector(plants);
        dieIndex.erase(dieIndex.begin(), dieIndex.begin() +dieIndex.size());
    }
    return years;
}

int ArrayProg::divide(int dividend, int divisor){
	if (!divisor)
		return INT_MAX;
	if (dividend == INT_MIN && divisor == -1)
		return INT_MAX;
	long long int x = (dividend > 0) ? dividend : (-(long long int) dividend);
	long long int y = (divisor > 0) ? divisor : (-(long long int) divisor);
	if (x < y)
		return 0;
	int shift = 32; int res = 0;
	bool neg = (dividend > 0) ^ (divisor > 0);
	while (x >= y){
		while (x < (y << shift)) --shift;
		res |= 1 << shift;
		x -= (y << shift);
	}
	return (neg) ? -res : res;
}

int ArrayProg::searchInRotatedSortedArray(vector<int>& nums, int left, int right, int target){
	if (nums.size() == 0)
		return -1;
	if (right < left)
		return -1;
	int mid = (left + right) / 2;
	if (nums[mid] == target)
		return mid;
	if (nums[left] < nums[mid]){	// left is ordered
		if (target >= nums[left] && target <= nums[mid])
			return searchInRotatedSortedArray(nums, left, mid - 1, target);
		else
			return searchInRotatedSortedArray(nums, mid + 1, right, target);
	} 
	else if (nums[mid] < nums[left]){ // right is ordered
		if (target >= nums[mid] && target <= nums[right])
			return searchInRotatedSortedArray(nums, mid + 1, right, target);
		else
			return searchInRotatedSortedArray(nums, left, mid - 1, target);
	}
	else if (nums[left] == nums[mid]){ // repeated elements
		if (nums[right] != nums[mid])
				return searchInRotatedSortedArray(nums, mid + 1, right, target);
		else{
			int result = searchInRotatedSortedArray(nums, left, mid - 1, target);
			if (result == -1)
				return searchInRotatedSortedArray(nums, mid + 1, right, target);
			else
				return result;
		}
	}
}

void ArrayProg::searchPos(vector<int>& nums, int target, int left, int right, int *pos){
	if (right < left)
		return;
	if (nums.size() == 0)
		return;
	if (target < nums[left] || target > nums[right])
		return;
	int mid = (left + right) / 2;
	if (nums[mid] == target){
		*pos = mid;
		return;
	}
	else {
		if (target >= nums[left] && target <= nums[mid]){
			*pos = mid;
			searchPos(nums, target, left, mid - 1, pos);
		}
		else {
			*pos = mid + 1;
			searchPos(nums, target, mid + 1, right, pos);
		}
	}
}
int  ArrayProg::searchInsert(vector<int>& nums, int target){
	if (nums.size() == 0 || target < nums[0])
		return 0;
	if (target > nums[nums.size() - 1])
		return nums.size();
	int pos = -1;
	searchPos(nums, target, 0, nums.size() - 1, &pos);
	return pos;

}

bool ArrayProg::subsetSum(vector<int>& arr, int target){
	int n = arr.size() + 1;
	bool **subset = new bool*[target + 1];
		for(int i = 0; i <= target; i++)
			subset[i] = new bool[n];
		for (int i = 0; i <= n; i++)
			subset[0][i] = true;
		for (int i = 0; i <= target; i++)
			subset[i][0] = false;
		for (int i = 1; i <= target; i++){
			for (int j = 1; j <= n; j++){
				subset[i][j] = subset[i][j - 1];
				if (i >= arr[j - 1])
					subset[i][j] = subset[i][j] || subset[i - arr[j - 1]][j - 1];
			}
		}
	return subset[target][n-1];
}

vector<vector<int>> ArrayProg::combinationSum(vector<int>&, int){
	vector<vector<int>> result;
	 return result;
}

int ArrayProg::maxTeamScore(vector<int>& score){
	sort(score.rbegin(), score.rend());
	int k = 0;
	vector<int> team1, team2;
	int score1 = 0, score2 = 0;
	while (k < 6){
		team1.push_back(score[k]);
		k++;
		team2.push_back(score[k]);
		k++;
	}
	for (int i = 0; i < 3; i++){
		score1 += team1[i];
		score2 += team2[i];
	}
	return (score1 > score2) ? score1 : score2;
}

void ArrayProg::rotateArray(vector<vector<int>> &matrix){
	int n = matrix.size()-1;
	for (int i = 0; i <= (n / 2); i++){
		for (int j = 0; j <= n - i ; j++){
			int temp1 = matrix[j][n-i]; // storing right top
			matrix[j][n-i] = matrix[i][j]; // left top -> right top
			int temp2 = matrix[n - i][n - j]; // saving value of right bottom
			matrix[n - i][n - j] = temp1; // right top --> right bottom
			int temp3 = matrix[n - i][j]; // saving value of left bottom
			matrix[n - j][i] = temp2; // right bottom -> left bottom
			matrix[i][j] = temp3; //; leftbottom -> right bottom
		}
	}
}

bool ArrayProg::canJump(vector<int>& nums){
	if (nums.size() == 0)
		return false;
	if (nums.size() == 1)
		return true;
	vector<bool> ispossible;
	int maxIndex = 0;
	for (int i = 0; i < nums.size(); i++)
		ispossible.push_back(false);
	for (int i = 0; i < nums.size()-1; i++){
		int toLocation = i + nums[i];
		if (i <= maxIndex)
			ispossible[i] = true;
		if (toLocation > nums.size() - 1){
			ispossible[nums.size() - 1] = (ispossible[i] && true);
			if (ispossible[nums.size() - 1])
				maxIndex = nums.size();
		}
		else{
			ispossible[toLocation] = (ispossible[i] && true);
			if (ispossible[toLocation])
				maxIndex = toLocation > maxIndex ? toLocation : maxIndex;
		}
	}
	return ispossible[nums.size() - 1];
}
int ArrayProg::jump(vector<int>& nums){
	vector<int> possibleJumps;
	if (nums.size() == 0)
		return 0;
	if (nums.size() == 1)
		return 1;
	for (int i = 0; i < nums.size(); i++)
		possibleJumps.push_back(INT_MAX);
	int maxIndex = 0;
	int currIndex = 0;
	possibleJumps[0] = 0;
	for (int i = 0; i < nums.size() - 1; i++){
		if (currIndex >= nums.size() - 1)
			break;
		maxIndex = i + nums[i];
		if (maxIndex > nums.size()-1)
			maxIndex = nums.size() - 1;
		if (maxIndex <= currIndex)
			continue;
		else{
			while (++currIndex <= maxIndex){
				possibleJumps[currIndex] = possibleJumps[currIndex] < (possibleJumps[i] + 1) ? possibleJumps[currIndex] : (1 + possibleJumps[i]);
			}
			currIndex--;
		}
	}
	if (possibleJumps[nums.size() - 1] == INT_MAX)
		return -1;
	else
		return possibleJumps[nums.size() - 1];
}

int ArrayProg::maxSubArray(vector<int>& nums) {
	vector<int> sumArray;
	int max = INT_MIN;
	for (int i = 0; i < nums.size(); i++){
		sumArray.push_back(INT_MIN);
	}
	sumArray[0] = nums[0];
	for (int i = 1; i < nums.size(); i++){
		sumArray[i] = (sumArray[i - 1] + nums[i]) > nums[i] ? (sumArray[i - 1] + nums[i]) : nums[i];
	}
	for (int i = 0; i < sumArray.size(); i++)
		max = max > sumArray[i] ? max : sumArray[i];
	return max;
}
int ArrayProg::maxProfit(vector<int>& prices) {
	int i = 0;
	int currLow = 0;
	int finalLow = 0, finalHigh = 0;
	for (int i = 0; i < prices.size(); i++){
		if (prices[i] < prices[currLow]){
			currLow = i;
		}
		if (prices[i] - prices[currLow > prices[finalHigh]] - prices[finalLow])
			finalLow = i;
		finalHigh = currLow;
	}
	return prices[finalHigh] - prices[finalLow];
}

int ArrayProg::maxProfitDP(vector<int>& prices){
	int mina = 0;
	vector<int> mindD;
	int temp = 0;
	for (int i = 0; i < prices.size(); i++)
		mindD.push_back(0);
	mindD[0] = 0;
	int min = INT_MIN;
	mina = prices[0];
	for (int i = 1; i < prices.size(); i++){
		if (prices[i] >= mina)
			mindD[i] = mindD[i - 1] + prices[i] - prices[i - 1];
		else{
			mindD[i] = 0;
			mina = prices[i];
		}
	}
	for (int i = 0; i < mindD.size(); i++){
		if (mindD[i] == 0){
			temp += min;
			min = 0;
		}
		else
			min = min > mindD[i] ? min : mindD[i];
	}
	return min;
}

bool ArrayProg::searchInRow(vector<vector<int>>& matrix, int left, int right, int target, int row){
	if (left <= right){
		int mid = (left + right) / 2;
		if (matrix[row][mid] == target)
			return true;
		else if (target < matrix[row][mid])
			return searchInRow(matrix, left, mid - 1, target, row);
		else
			return searchInRow(matrix, mid + 1, right, target, row);
	}
	return false;
}
bool ArrayProg::search(vector<vector<int>>& matrix, int left, int right, int target){
	if (left <= right){
		int mid = (left + right) / 2;
		int n = matrix[0].size() - 1;
		if (matrix[mid][n] == target)
			return true;
		if (mid - 1 >= 0 && target <= matrix[mid - 1][n])
			return search(matrix, left, mid - 1, target);
		else if (target > matrix[mid][n])
			return search(matrix, mid + 1, right, target);
		else
			return searchInRow(matrix, left, matrix[0].size()-1, target, mid);
	}
	return false;
}
bool ArrayProg::searchMatrix(vector<vector<int>>& matrix, int target){
	return search(matrix, 0, matrix.size() - 1, target);
}


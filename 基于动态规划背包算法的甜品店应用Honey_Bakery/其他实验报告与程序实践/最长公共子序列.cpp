#include <iostream>
#include <vector>

using namespace std;
//�����������
class Solution {
public:
	int longestCommonSubsequence(string text1,string text2) {
		vector< vector< int > > dp(text1.size() + 1,vector<int>(text2.size() + 1,0));
		for(int i=1;i<=text1.size();i++){
			for(int j=1;j<=text2.size();j++){
				if(text1[i-1] == text2[j-1]){//���һλ��� 
					dp[i][j]=dp[i-1][j-1] + 1;
				}else{//���һλ�����  
					dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
				}
			}
		}
		return dp[text1.size()][text2.size()];
	}
};

int main(){
//	Solution solution;
//	int value = solution.longestCommonSubsequence("abcde","abc");
//	cout<<"hello"<<endl;
//	cout<<value<<endl;
	Solution s1;
	int r1 = s1.longestCommonSubsequence("abcde", "abc");
	cout << r1 << endl;
//	cout << "Hello, world!" << endl;
	return 0;
} 

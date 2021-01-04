#include <stdio.h>
#include <vector>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

class Solution {
public:
	double findMedianSortedArrays(vector<int>& s1, vector<int>& s2) {
		int n1 = s1.size();
		int n2 = s2.size();
		if (n1 > n2){
			return findMedianSortedArrays(s2, s1);
		}
        int L1 = 0,  R1 = 0, c1;
        int L2 = 0,  R2 = 0, c2;
        int l = 0, r = n1;
		while (l <= r) {
			c1 = (r+l+1)/2;
			c2 = (n1+n2)/2-c1;

			L1 = (c1 == 0) ? INT_MIN : s1[c1 - 1];
			R1 = (c1 == n1) ? INT_MAX : s1[c1];
			L2 = (c2 == 0) ? INT_MIN : s2[c2 - 1];
			R2 = (c2 == n2) ? INT_MAX : s2[c2];

			if (L1 > R2) //往左找
				r = c1 - 1;
			else if (L2 > R1)//往右找
				l = c1 + 1;
			else
				break;
		}
		if ((n1 + n2) % 2)
			return min(R1, R2)/1.0;
		else
			return (max(L1, L2)+min(R1, R2))/2.0;
	}
};
//非常巧妙地只二分第一个数组的分割位置，通过分割位置左右大小比较确定分割的位置是否合适。值得收藏的解法。
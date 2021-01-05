#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
class Solution {
public:
    string longestPalindrome(string s) {
        int size=s.size();
        if (size<2){
            return s;
        }
        string str="#";
        for(int i=0; i<size; i++){
            str=str+s[i]+'#';
        }
        size=2*size+1;
        vector<int> p(size,0);

        int r=0;
        int c=0;
        int maxl=0;
        int start=0;
        
        for(int i=0; i<size; i++){
            if(i<r){//在已经中心拓展后的区域，回文性质直接填写
                int mirror=2*c-i;
                p[i]=min(r-i,p[mirror]);
            }
            int left=i-(1+p[i]);
            int right=i+(1+p[i]);
            while(left>=0&&right<=size&&str[left]==str[right]){
                p[i]++;left--;right++;
            }
            if(i+p[i]>r){//r是向右拓展的最远距离
                r=i+p[i];c=i;//c是对应的中心
            }
            if(p[i]>maxl){//记录最长子串位置
                maxl=p[i];
                start=(i-maxl)/2;
            }

        }

        return s.substr(start,maxl);
    }
};
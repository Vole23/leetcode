class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    int visit[130]={0};
    int head=0,ans=0;
    if(s=="") {return 0;}
        for(int i=0; i<s.length(); i++){
            if(visit[s[i]]){
                head=visit[s[i]]>head?visit[s[i]]:head;
            }
                visit[s[i]]=i+1;
            ans=ans>i-head+1?ans:i-head+1;
        }
        return ans;
    }
};
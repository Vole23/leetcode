class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1){return s;}
        int a=(numRows-1)*2;
        int b=0;
        int size=s.size();
        if(size<=numRows){return s;}
        string str="";
        for(int i=0; i<numRows;i++){
            int j=i;
            str+=s[i];
            while(j<size){
                j+=a;
                if(a&&j<size){str+=s[j];}
                j+=b;
                if(b&&j<size){str+=s[j];}
            }
            a-=2;
            b+=2;
        }
        return str;
    }
};
// test problem: https://codeforces.com/contest/2209/problem/E
struct KMP{
    int n;
    string s;
    vector<int> pi;
    vector<int> border;

    KMP(string s) : s(s){
        n = s.size();
        // KMP prefix function
        pi = vector<int>(n, 0);
        for(int i = 1;i < n;++i){
            int match = pi[i - 1];
            while(match > 0 && s[match] != s[i]){
                match = pi[match - 1];
            }
            if(s[match] == s[i]){
                ++match;
            }
            pi[i] = match;
        }
        // Borders (shortest suffix that is a prefix) for every prefix of s
        border = vector<int>(n);
        for(int i = 0;i < n;++i){
            if(pi[i] == 0){
                border[i] = i;
            }else{
                border[i] = border[ pi[i] - 1 ];
            }
        }
    }

    // number of times s occurs in T
    int search(string T){
        int ret = 0;
        int match = 0;
        for(char c : T){
            while(match > 0 && s[match] != c){
                match = pi[match - 1];
            }
            if(s[match] == c){
                ++match;
            }
            if(match == n){
                ++ret;
                match = pi[match - 1];
            }
        }
        return ret;
    }
};
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

const int inf = 1e6;
const int MAX_TRAVEL = 4000;
int cache[MAX_TRAVEL][2];
int best_distance[MAX_TRAVEL][2];
int steps[MAX_TRAVEL];
int a,b,x;
int check_forbidden[MAX_TRAVEL];
int dp(int cur,int f)
{
    // cout << cur << "," << f << endl;
    // f - > previously how many consecutive backward operation perform.
    //cur -> cur position of bug.   
   // stop condition of Memoization
    if(cur >= MAX_TRAVEL)
        return inf;
    if(cur < 0 or check_forbidden[cur] or f >= 2) 
        return inf;
    if(cur == x)
        return 0;
    int &ans = cache[cur][f];
    
    // DFS STARTED ON THIS AND NOT FINISHED YET
    if(ans==-2)
        return inf;
    
    // IS IT SOLVED?
    if(ans != -1)
        return ans;
    
    // START DFS
    ans=-2;

    // forward operation
    int p = dp(cur+a,0) + 1;
    // backward operation 
    int q = dp(cur-b , f+1)+1;
    ans = min(p, q);
    // printf("curr: %d, f: %d\n", cur, f);
    if(ans < inf)
    {
        if(ans == p)
        {
            steps[cur] = cur+a;
            best_distance[cur][0] = ans;
        }
        else if(ans == q)
        {
            steps[cur] = cur-b;
            best_distance[cur][f+1] = ans;
        }
    }

    return ans;
    
}
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a1, int b1, int x1) {
        a = a1,b = b1,x = x1;
        // initialize  check_forbidden array by zero      
        memset(check_forbidden,0,sizeof(check_forbidden));
        // make the position in check_forbidden array 1 where bug cannot jump.     
        for(auto it : forbidden)
            check_forbidden[it] = 1;
        // initialize  cache array by -1 
        memset(cache,-1,sizeof(cache));
        memset(best_distance,-1,sizeof(best_distance));
        memset(steps,-1,sizeof(steps));
        int ans = dp(0,0);
        // means no possible sequence found         
        if(ans >= inf)
            ans = -1;

        if(ans == -1)
        {
            // cout << "Ans: " << 0 << endl;
            cout << 0 << endl;
        }else
        {
            // cout << "Ans: " << ans << endl;
            cout << ans << endl;
            int at = 0;
            while(at != x)
            {
                int next = steps[at];
                if(next < at)
                {
                    cout << "a" << endl;
                }
                else
                {
                    cout << "w" << endl;
                }
                at = next;
                // if (at==x)
                // {
                //     cout << "Reached end \n";
                // }

            }
            cout << endl;
        }

        return ans;
    }
};

time_t to_time_t(string T, int hour)
{
    // convert
    tm t = {0};
    strptime(T.c_str(), "%Y-%m-%d", &t);
    t.tm_hour = hour;
    time_t timestamp = mktime(&t);

    // revert
    char buff[30];
    strftime(buff, 30, "\nCheck tm: %Y-%m-%d %H", &t);
    // cout << buff << endl; // std::tm t is correct
    // time_t timestamp is also correct
    // printf ( "Check time_t: %s \n ------------------- \n", ctime (&timestamp));
    return timestamp;
}

int main(){
    string T0;
    int T0h;
    // cout << "Enter T_0(YYYY-MM-DD hh): ";
    cin >> T0 >> T0h;

    string TS;
    int TSh;
    // cout << "Enter T_S(YYYY-MM-DD hh): ";
    cin >> TS >> TSh;

    int W, J;
    // cout << "Enter W:";
    cin >> W; 
    // cout << "Enter J:";
    cin >> J; 
    

    time_t t_0 = to_time_t(T0, T0h);
    time_t t_S = to_time_t(TS, TSh);

    time_t diff = t_S - t_0;
    int sec_diff = (int) diff;
    int hr_diff = sec_diff/60/60;

    // cout << "Diff:" << hr_diff << endl;

    Solution solved = Solution();

    vector<int> midnights; // forbidden
    int first = 24 - T0h;
    // forbidden can be higher than hr_diff
    int curr = first;
    while(curr < hr_diff)
    {
        midnights.push_back(curr);
        curr += 24;
    }


    // cout << "Forbidden: [";
    // for (int x : midnights)
    //     cout << x << " ";
    // cout << "]" << endl;

    int ans = solved.minimumJumps(midnights, W, J, hr_diff);
    return 0;
}
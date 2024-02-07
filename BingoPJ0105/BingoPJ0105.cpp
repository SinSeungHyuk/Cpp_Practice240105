// BingoPJ0105.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
using namespace std;
#include <cmath>


void BFS(vector<vector<int>> map, int y, int x) {
    queue<pair<int, int>> q;
    bool visit[100][100] = { 0, };
    int dist[100][100];

    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { -1,0,1,0 };

    for (int i = 0; i < map.size(); i++) { fill(dist[i], dist[i] + map.size(),-1); }
    visit[y][x] = true;
    dist[y][x] = 0;
    q.push({ y,x });

    while (q.size()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nX = x + dx[i];
            int nY = y + dy[i];
            if (nX >= 0 && nX < map.size() && nY >= 0 && nY < map.size()) {
                if (map[nY][nX] != 0 && dist[nY][nX] < 0) {
                    visit[nY][nX] = true;
                    dist[nY][nX] += dist[y][x] + 1;
                    q.push({ nY,nX });
                }
            }
        }
    }
}

void dfs(vector<vector<int>> map, int y, int x) {
    stack<pair<int, int>> s;
    bool visit[100][100] = { 0, };

    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { -1,0,1,0 };

    visit[y][x] = true;
    s.push({ y,x });

    while (s.size()) {
        int x = s.top().second;
        int y = s.top().first;
        s.pop();

        for (int i = 0; i < 4; i++) {
            int nX = x + dx[i];
            int nY = y + dy[i];
            if (nX >= 0 && nX < map.size() && nY >= 0 && nY < map.size()) {
                if (map[nY][nX] != 0 && visit[nY][nX] == false) {
                    s.push({ nY,nX });
                    visit[nY][nX] = true;
                }
            }
        }
    }
}

//const int MX = 1000005;
//int dat[MX], pre[MX], nxt[MX];
//int unused = 1;
//
//void insert(int addr, int num) {
//
//}
//
//void erase(int addr) {
//
//}
//
//void traverse() {
//    int cur = nxt[0];
//    while (cur != -1) {
//        cout << dat[cur] << ' ';
//        cur = nxt[cur];
//    }
//    cout << "\n\n";
//}
//
//void insert_test() {
//    cout << "****** insert_test *****\n";
//    insert(0, 10); // 10(address=1)
//    traverse();
//    insert(0, 30); // 30(address=2) 10
//    traverse();
//    insert(2, 40); // 30 40(address=3) 10
//    traverse();
//    insert(1, 20); // 30 40 10 20(address=4)
//    traverse();
//    insert(4, 70); // 30 40 10 20 70(address=5)
//    traverse();
//}
//
//void erase_test() {
//    cout << "****** erase_test *****\n";
//    erase(1); // 30 40 20 70
//    traverse();
//    erase(2); // 40 20 70
//    traverse();
//    erase(4); // 40 70
//    traverse();
//    erase(5); // 40
//    traverse();
//}

// 퀵 정렬
void quickSort(int* qs, int start, int end) {
    int pivot = start;
    int i = pivot + 1;
    int j = end;

    while (i <= j) {
        while (qs[i] < qs[pivot] && i <= end) i++;
        while (qs[j] > qs[pivot] && j >= start) j--;

        if (i > j) swap(qs[pivot], qs[j]);
        else swap(qs[i], qs[j]);

        quickSort(qs, start, j - 1);
        quickSort(qs, j + 1, end);
    }
}

// 병합 정렬
void merge(int start, int end, vector<int>& ms) {
    int mid = (start + end) / 2;
    int lidx = start;
    int ridx = mid;
    vector<int> tmp(ms.size());
    for (int i = start; i < end; i++) {
        if (ridx == end) tmp[i] = ms[lidx++];
        else if (lidx == mid) tmp[i] = ms[ridx++];
        else if (ms[lidx] <= ms[ridx]) tmp[i] = ms[lidx++];
        else tmp[i] = ms[ridx++];
    }
    for (int i = start; i < end; i++) ms[i] = tmp[i];
}
void mergeSort(int start, int end, vector<int>& ms) {
    if (start+1 == end) return;
    int mid = (start + end) / 2;
    mergeSort(start, mid, ms);
    mergeSort(mid, end, ms);
    merge(start, end, ms); // 병합
}

using ll = long long;
struct Compare {
    bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const {
        // 키 값이 같으면 밸류 값을 비교
        if (lhs.first == rhs.first) {
            return lhs.second < rhs.second;
        }
        // 키 값이 다르면 키 값을 비교
        return lhs.first > rhs.first;
    }
};

bool cmp (const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if (lhs.second == rhs.second) {
         return lhs.first < lhs.first;
    }
    return lhs.second < rhs.second;
}


int n;
vector<int> adj[100];
int p[100];
void dfs(int cur) {
    for (int nxt : adj[cur]) {
        if (p[cur] == nxt) continue;
        p[nxt] = cur;
        dfs(nxt);
    }
}


string byValue(string s) { string str = s+" value"; return str; }
string byLRef(string& s) { string str = s + " lvalue"; return str; }
string byRRef(string&& s) { string str = move(s) + " rvalue"; return str; }

void overloading(int&& v) {
    cout << "int&&" << endl;
}
void overloading(int& v) {
    cout << "int&" << endl;
}


int main(void) {
    //fill(pre, pre + MX, -1);
    //fill(nxt, nxt + MX, -1);
    //insert_test();
    //erase_test();

    //LinkedList<int> list;
    //list.pushBack(10);
    //list.pushBack(20);
    //LinkedList<int>::iterator listIter = list.begin();
    //cout << *listIter << endl;
    //list.insert(listIter, 5);
    //listIter = list.begin();
    //cout << *listIter << endl;

    //list<char> sl;
    //int cnt;
    //string word;
    //char mode;


    //CVector<int> cv;

    //cv.push_back(1);
    //cv.push_back(2);
    //cv.push_back(3);
    //cv.push_back(4);
    //cout << cv[3] << endl;

    //vector<int> v;
    //v.push_back(11);
    //v.push_back(22);
    //auto vIter = v.begin()+1;
    //cout << *vIter << endl << endl;

    //list<int> li;
    //li.push_back(50);
    //li.push_back(60);
    //auto liIter = li.begin();
    //cout << *liIter << endl;

    //CList<int> cl;
    //cl.push_back(12);
    //cl.push_back(13);
    //cl.push_back(14);
    //CList<int>::iterator clIter = cl.begin();
    //cout << *clIter << endl; // 12
    //cl.insert(clIter, 11);
    //clIter = cl.begin();
    //cout << *clIter << endl; // 11
    //cl.erase(cl.begin());
    //clIter = cl.begin();
    //cout << *clIter << endl;  // 12

    //vector<int> hv = { 1,6,5,2,3,8,4,9,7 };
    //for (int n : hv) cout << n << " ";
    //cout << endl;
    //make_heap(hv.begin(), hv.end());
    //for (int n : hv) cout << n << " ";
    //cout << endl; // 9 7 8 6 3 5 4 2 1
    //cout << endl;

    //CHeap ch;
    ////ch.push(6);
    ////ch.push(5);
    ////ch.push(2);
    ////ch.push(8);
    ////ch.push(4);
    ////ch.push(9);
    ////ch.push(7);
    //ch.push(10);
    //ch.push(15);
    //ch.push(2);
    //ch.push(28);
    //ch.push(34);
    //ch.push(29);
    //ch.push(17);
    //cout << endl;
    //for (int i = 1; i < 8; i++) {
    //    cout << ch[i] << " ";
    //}
    //ch.Heapify();
    //cout << endl;
    //for (int i = 1; i < 8; i++) {
    //    cout << ch[i] << " ";
    //}

    //cout << endl << endl;

    ////priority_queue<int,vector<int>, greater<int>> pq;

    //struct st {
    //    int num;
    //    string s;
    //    st(int n, string s) : num(n), s(s) {};
    //};
    //struct compareSt {
    //    bool operator ()(st s1, st s2) {
    //        if (s1.num == s2.num)
    //            return s1.s > s2.s;
    //        return s1.num > s2.num;
    //    }
    //};

    //priority_queue<st, vector<st> , compareSt> pq;
    //pq.push(st(1,"abc"));
    //pq.push(st(2, "abc"));
    //pq.push(st(3, "abc"));
    //pq.push(st(1, "bbb"));
    //
    //while (!pq.empty()) {
    //    st temp = pq.top();
    //    cout << temp.num << " " << temp.s << endl;
    //    pq.pop();
    //}

    //string s;
    //int ans = 0;
    //stack<char> st;
    //cin >> s;
    //int sz = s.length();
    //for (int i = 0; i < sz; i++) {
    //    if (s[i] == '(')
    //        st.push(s[i]);
    //    else {
    //        if (s[i - 1] == '(') { // 레이저일 경우
    //            st.pop(); // 앞에서 막대라고 착각하고 stack에 s[i]를 넣었으므로 pop
    //            ans += st.size(); // 막대의 개수만큼 ans에 추가
    //        }
    //        else { // 막대의 끝일 경우
    //            st.pop();  // 막대의 개수를 1 감소
    //            ans++; // 막대 1개가 절단된 것과 동일한 상황이므로 ans에 1 추가
    //        }
    //    }
    //}
    //cout << ans << "\n";

     //버블정렬
    //int bs[] = { 7,8,5,4,3,9,1,2,6 };
    //for (int i = 0; i < 9; i++) {
    //    for (int j = 0; j < i; j++) {
    //        if (bs[i] < bs[j]) {
    //            swap(bs[j], bs[i]);
    //        }
    //    }
    //}
    //for (int i = 0; i < 9; i++) {
    //    cout << bs[i] << ",";
    //} // 1,2,3,4,5,6,7,8,9,

    //cout << endl << endl;

    //// 선택정렬
    //int size = 9;
    //for (int i = 0; i < size - 1; i++) {
    //    for (int j = i + 1; j < size; j++) {
    //        if (bs[i] > bs[j]) {
    //            swap(bs[j], bs[i]);
    //        }
    //    }
    //}
    //for (int i = 0; i < 9; i++) {
    //    cout << bs[i] << ",";
    //} // 1,2,3,4,5,6,7,8,9,

    //cout << endl << endl;

    //// 삽입정렬
    //int is[] = { 7,8,5,4,3,9,1,2,6 };
    //int key,i,j;
    //for (i = 1; i < size; i++) {
    //    key = is[i];
    //    for (j = i - 1; j >= 0; j--) {
    //        if (is[j] > key) swap(is[j], is[j + 1]);
    //    }
    //}
    //for (int i = 0; i < 9; i++) {
    //    cout << is[i] << ",";
    //} // 1,2,3,4,5,6,7,8,9,

    //cout << endl << endl;

    // //퀵정렬
    //int qs[] = { 7,8,5,4,3,9,1,2,6 };
    //quickSort(qs, 0, 8);
    //for (int i = 0; i < 9; i++) {
    //    cout << qs[i] << ",q ";
    //} // 1,2,3,4,5,6,7,8,9,

    // //병합정렬
    //vector<int> v1 = { 5,3,8 ,2,9,10,6,7};
    //vector<int> v2 = { 2,9 };
    //mergeSort(0,8,v1);
    //for (int i = 0; i < v1.size(); i++) {
    //    cout << v1[i] << ",";
    //}


    //cout << endl << endl;
    //// 해시테이블
    //HashMap* hm = new HashMap();0

    //hm->Insert("first", 1);
    //hm->Insert("second", 2);
    //hm->Insert("three", 3);
    //hm->Insert("four", 4);
    //hm->Insert("five", 5);

    //cout << hm->Find("first") << endl;
    //cout << hm->Find("adf") << endl;
    //cout << hm->Find("second") << endl;
    //cout << hm->Find("three") << endl;
    //cout << hm->Find("four") << endl;
    //cout << hm->Find("five") << endl;
    //hm->Delete("second");
    //cout << hm->Find("second") << endl;


    
    //int n;
    //vector<int> v;
    //cin >> n;
    //while (n--) {
    //    int num;
    //    cin >> num;
    //    v.push_back(num);
    //}
    //sort(v.begin(), v.end());
    //map<pair<int,int>,int> cnt;
    //for (int i : v) {
    //    cnt[i]++;
    //}
    ////sort(cnt.begin(), cnt.end(),cmp);
    //for (const auto& pair : cnt) {
    //    std::cout << "Number: " << pair.first << ", Count: " << pair.second << std::endl;
    //}

     //DP 알고리즘
    //int dp[1000][3];
    //int score[1000];
    //int n;
    //cin >> n;

    //for (int i = 1;i <= n;i++) {
    //    int s;
    //    cin >> s;
    //    score[i] = s;
    //}
    //dp[1][1] = score[1];
    //dp[2][2] = score[2] + dp[1][1];
    //dp[2][1] = score[2];
    //
    //for (int i = 3; i <= n; i++) {
    //    dp[i][1] = max(dp[i - 2][1], dp[i - 2][2]) + score[i];
    //    dp[i][2] = dp[i - 1][1] + score[i];
    //}
    //int maxScore = max(dp[n][1], dp[n][2]);

    
    // 그리디 알고리즘
    //vector<pair<int, int>> time = {
    //    {5,7},{3,5},{0,6},{3,8},{1,4},
    //    {7,12},{2,13},{8,12},{5,9},
    //    {6,10},{12,14} };
    //sort(time.begin(), time.end(),cmp);

    //int cnt = 0;
    //int prev = 0;
    //for (int i = 0; i < time.size();i++) {
    //    if (time[i].first >= prev) {
    //        cnt++;
    //        prev = time[i].second;
    //    }
    //}

    //int cnt;
    //cin >> cnt;
    //unordered_set<string> s;
    //while (cnt--) {
    //    string mode;
    //    string name;
    //    cin >> name >> mode;
    //    if (mode == "enter") s.insert(name);
    //    else if (mode == "leave") s.erase(name);
    //}
    //vector<string> names(s.begin(), s.end());
    //sort(names.begin(), names.end(), greater<string>());
    //for (string s : names) cout << s << '\n';


    // 위상정렬
    //int n, m;
    //cin >> n >> m;
    //vector<int> adj[100];
    //int indeg[100] = { 0, };
    //while (m--) {
    //    int a, b;
    //    cin >> a >> b;
    //    adj[a].push_back(b);
    //    indeg[b]++;
    //}
    //queue<int> q;
    //vector<int> answer;
    //for (int i = 1; i <= n; i++) {
    //    if (indeg[i] == 0) q.push(i);
    //}
    //while (q.size()) {
    //    int cur = q.front();
    //    answer.push_back(q.front());
    //    q.pop();
    //    for (int nxt : adj[cur]) {
    //        indeg[nxt]--;
    //        if (indeg[nxt] == 0) q.push(nxt);
    //    }
    //}
    //for (auto iter = answer.begin(); iter < answer.end(); iter++) {
    //    cout << *iter << " ";
    //}



    //string a = "abc";

    //cout << byValue(a) << endl;

    ////cout << byLRef("abc") << endl;
    //cout << byLRef(a) << endl;

    ////cout << byRRef(a) << endl;
    //cout << byRRef(move(a)) << endl;
    //a = "d";
    //cout << "a : " << a << endl;

    //int i = 5;
    //overloading(4);
    //overloading(i);

} 


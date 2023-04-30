#include <vector>
#include <limits>
#include <iostream>

using std::pair;
using std::vector;
using std::numeric_limits;

class graph
{
protected:
    int n;

private:
    vector<vector<int> > adjacent_lists;

public:
    graph(int _n, vector<pair<int, int> > edges) : n(_n), adjacent_lists(_n)
    {
#if __cplusplus >= 201703L
        for (auto [a, b] : edges)
        {
#else
        for (vector<pair<int, int> >::iterator itr = edges.begin(); itr != edges.end(); itr++)
        {
            int a = itr->first, b = itr->second;
#endif
            adjacent_lists[a].push_back(b);
            adjacent_lists[b].push_back(a);
        }
    }

    vector<int> bfs(int) const; // Perform BFS traversal on a graph.
};

class tree : public graph
{
public:
    tree(int n, vector<pair<int, int> > edges) : graph(n, edges) {}
    int diameter() const; // Find the diameter by BFS traversal.
};

////////////////////////////////////////////////////////////////////////////////
//                              Separate Line!!!                              //
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * It's recommended that you should implement the 3 member functions in a different file.
 *
 * If you edit `function.h` directly, don't paste the codes above.
 *
 */

// Starter codes are provided below. Uncomment them and begin coding!


vector<int> graph::bfs(int source) const
{
    vector<int> ret(n,0);
    bool* passed = new bool[n];
    for(int i=0;i<n;i++) passed[i] = false;
    passed[source]=true;
    vector<int> queue;
    queue.push_back(source);
    for(int i=0;i<n;i++){
        int val = queue[i];
        for(int i=0;i<adjacent_lists[val].size();i++){
            if(!passed[adjacent_lists[val][i]]){
                passed[adjacent_lists[val][i]]=true;
                ret[adjacent_lists[val][i]] = ret[val]+1;
                queue.push_back(adjacent_lists[val][i]);
            }
        }
    }
    delete [] passed;
    return ret;
}

int tree::diameter() const
{
    vector<int> v = bfs(0);
    int max = 0, id = 0;
    for(int i=0;i<n;i++){
        if(v[i]>max){
            max = v[i];
            id = i;
        }
    }
    v = bfs(id);
    max = 0;
    for(int i=0;i<n;i++) if(v[i]>max) max = v[i];
    return max;
}





using std::cin;
using std::cout;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
#if __cplusplus >= 201703L
    for (auto &[a, b] : edges)
    {
#else
    for (vector<pair<int, int>>::iterator itr = edges.begin(); itr != edges.end(); itr++)
    {
        int &a = itr->first, &b = itr->second;
#endif
        cin >> a >> b;
    }
    tree t(n, edges);
#if __cplusplus >= 201703L
    for (int i : t.bfs(0))
        cout << i << ' ';
#else
    vector<int> d = t.bfs(0);
    for (auto itr = d.begin(); itr != d.end(); itr++)
        cout << *itr << ' ';
#endif
    cout << '\n'
         << t.diameter() << '\n';
    return 0;
}

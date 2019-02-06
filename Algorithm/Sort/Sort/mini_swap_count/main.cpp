#include<bits/stdc++.h>
using namespace std;

int a[] {4,3,1,2};
bool visited[4];

int solve(int n)
{
    pair<int, int> p[n];
    
    for (int i = 0; i < n; i++)
    {
        p[i].first = a[i];
        
        // Storing the original position of a[i]
        p[i].second = i;
        cout << p[i].first << " " << p[i].second << endl;
    }
    
    sort(p, p+n);
    // just for checking after sorting
    for (int i = 0; i < n; i++)
    {
        cout << p[i].first << " " << p[i].second << endl;
    }
    
    
    
    int ans = 0;
    
    for (int i = 0; i < n; i++)
    {	
    	//visited[i]=true indicates that index i belongs to a cycle that is already counted
        
        //p[i].second = i denotes that the ith element was at its correct position
        
        if (visited[i] || p[i].second == i)
            continue;
            
        int cycle_size = 0;
        int j = i;
        
        //Counting the size of the cycle
        while (!visited[j])
        {
            visited[j] = 1;
            j = p[j].second;
            cycle_size++;
        }
        
        ans += (cycle_size - 1);
    }
    
    return ans;
    
}

int main()
{

    int ans = solve(4);
    printf("%d\n", ans);
    return 0;
    
}
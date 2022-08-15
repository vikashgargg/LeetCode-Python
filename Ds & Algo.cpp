
TRIPLETS:----------------------------------------------------------------------------------

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector <int>> triplet(vector<int> arr,int targetsum){
    int n=arr.size();
    vector<vector<int>> result;
    sort(arr.begin(),arr.end());
    for(int i=0;i<n;i++)
    {
        int j=i+1;
        int k=n-1;
        while(j<k){
            int currentsum=arr[i];
            currentsum+=arr[j];
            currentsum+=arr[k];
            if(currentsum==targetsum)
            {
                result.push_back({arr[i],arr[j],arr[k]});
                j++;
                k--;
            }
            else if(currentsum>targetsum)
            {
                k--;
            }
            else{
                j++;
            }
        }
    }
    return result;
}
int main()
{
    vector<int> arr{1,2,3,4,5,6,7,8,9,15};
    int S=18;
    auto result=triplet(arr,S);
    for(auto v : result)
    {
        for(auto no:v){
            cout<<no<<",";
        }
        cout<<endl;
    }
}



MOUNTAIN: ------------------------------------------------------------



#include<iostream>
#include<vector>
using namespace std;
int highpeak(vector<int> a){
int n=a.size();
int largest=0;
for(int i=1;i<=n-2;){
    //check if there is a peak or not
    if(a[i]>a[i-1] and a[i]>a[i+1])
    {
        //some code
        int cnt=1;
        int j=i;
        //move backward
        while(j>=1 and a[j]>a[j-1])
        {
            j--;
            cnt++;
            
        }
        //move forward
        while(i<=n-2 and a[i]>a[i+1]){
            i++;
            cnt++;
            
        }
        //update largest
        largest=max(largest,cnt);
        
    }
    else
    {
        i++;
    }
}
    
    return largest;
}
int main()
{
    vector<int> arr{5,6,1,2,3,4,5,4,3,2,0,1,2,3};
    cout<<highpeak(arr)<<endl;
    return 0;
}




LARGEST BAND: -------------------------------------------------------------


#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
int largestband(vector<int> a){
    int n=a.size();
    unordered_set <int> s;
    int largestlength=1;
    for(int x : a){
        s.insert(x);
    }
    for(auto element : s)
    {
        int parent = element-1;
        if(s.find(parent)==s.end())
        {
            int next_no=element+1;
            int cnt=1;
        while(s.find(next_no)!=s.end())
        {
            next_no++;
            cnt++;
        
            
        }
        if(cnt>largestlength)
        {
            largestlength=cnt;
        }
        }
        
    }

    
    return largestlength;
}
int main()
{
    vector<int> arr{1,9,3,0,18,5,2,4,10,7,12,6};
    cout<<largestband(arr)<<endl;
    return 0;
}




RAIN WATER -----------------------------------------------------------------


// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
using namespace std;

int rainwater(vector <int> height)
{
    //complete condition
    int n= height.size();
    if(n<=2)
    {
        return 0;
    }
    // compute max (left and right array)
    vector <int> left(n,0),right(n,0);
    left[0]=height[0];
    right[n-1]=height[n-1];
    
    for(int i=1;i<n;i++) //first element already been initialized
    {
      left[i]=max(left[i-1],height[i]);
      right[n-i-1]=max(right[n-i],height[n-i-1]);
    }
    int water=0;
    for(int i=0;i<n;i++)
    {
        water+=min(left[i],right[i])-height[i];
    }
    return water;
}

int main() {
    vector <int> water ={0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<rainwater(water)<<endl;

    return 0;
}





SUBARRAY SORT ---------------------------------------------------------------




#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;
bool outoforder(vector<int> arr,int i){
    int x=arr[i];
    if (i==0)
        return x>arr[1];
    if (i==arr.size()-1)
        return x<arr[i-1];
    return x>arr[i+1] or x<arr[i-1];
}

pair<int,int>subarraysort(vector<int> arr)
{
    int smallest=INT_MAX;
    int largest= INT_MIN;
    for(int i=0;i<arr.size();i++)
    {
        int x=arr[i];
        if(outoforder(arr,i)){
            smallest=min(smallest,x);
            largest=max(largest,x);
            
        }
    }
    //next step is to find right index where smallest and largest i.e. (substrings) for our solution
    
    if(smallest==INT_MAX){
        return {-1,-1};
    }
    //assigning smallest to it right positon in the array
    int left=0;
    while(smallest>=arr[left]){
        left++;
    }
    int right=arr.size()-1;
    while(largest<=arr[right])
    {
        right--;
    }
    return {left,right};
}

int main()
{
    vector<int> arr ={1,2,3,4,5,8,6,7,9,10,11};
    auto p=subarraysort(arr);
    cout<<p.first<<"and"<<p.second<<endl;
    return 0;
}






------------------MINIMUM SWAPS PROBLEM------------------------------

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int countminswap(vector<int> arr)
{
    //know the actual position of elements (sorting)
    // store the current indices
    int n=arr.size();
    int ans=0;
    pair<int,int> ap[n];
    for(int i=0;i<n;i++)
    {
        ap[i].first=arr[i];
        ap[i].second=i;
      
    }
    //sort the given array
    sort(ap,ap+n);
    
    //build the main logic 
    vector<bool>visited(n,false);
    for(int i=0;i<n;i++)
    {
        //if element is visited or element is in right position 
        int oldposition=ap[i].second;
        if(visited[i]==true or oldposition == i)
        {
            continue;
        }
        //visiting the element(index) for the first time
        
        int node=i;
        int cycle=0;
        while(!visited[node])
        {
            visited[node]=true;
            int nextnode=ap[node].second;
            node=nextnode;
            cycle+=1;
        }
        ans=ans+(cycle-1);
    }
    return ans;
    
}


int main()
{
    vector<int> arr ={5,4,3,2,1};
    cout<<countminswap(arr)<<endl;
    return 0;
}











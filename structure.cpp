#include<bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
void build(int ind,int low,int high,int arr[],int seg[])
{
    if(low==high)
    {
        seg[ind]=arr[low];
        return;
    }
    int mid=(low+high)/2;
    build(2*ind+1,low,mid,arr,seg);
    build(2*ind+2,mid+1,high,arr,seg);
    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
}
int query(int ind,int low,int high,int l,int r,int seg[])
{
    //no overlap
    if(r<low || high<l)return INT_MAX;
    //complete overlap
    if(low>=l && high<=r)return seg[ind];
    int mid = (low+high)/2;
    int left = query(2*ind+1,low,mid,l,r,seg);
    int right = query(2*ind+2,mid+1,high,l,r,seg);
    return min(left,right);
}
void update(int ind,int low,int high,int i,int val,int seg[])
{
    if(low==high)
    {
        seg[ind]=val;
        return;
    }
    int mid=(low+high)>>1;
    if(i<=mid)update(2*ind+1,low,mid,i,val,seg);
    else update(2*ind+2,mid+1,high,i,val,seg);
    seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
}
int main()
{
    fast;
    int n,q;
    cin>>n>>q;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    int seg[4*n];
    build(0,0,n-1,arr,seg);
    for(int i=0;i<q;i++)
    {
        int type,l,r;
        cin>>type;
        if(type==1)
        {
            cin>>l>>r;
            cout<<query(0,0,n-1,l,r,seg)<<endl;
        }
        else if(type==2)
        {
            int pos,val;
            cin>>pos>>val;
            update(0,0,n-1,pos,val,seg);
            arr[i]=val;
        }
    }
    return 0;
}

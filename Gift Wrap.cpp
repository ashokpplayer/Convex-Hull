#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstring>
#include<iomanip>
#include<stdio.h>
#include<vector>
#define sz(x) x.size()
using namespace std;
int orientation(pair<int,int> p,pair<int,int> b,pair<int,int> c)
{
	int res=(b.second-p.second)*(c.first-b.first)-
            (c.second-b.second)*(b.first-p.first);
	if(res==0)
		return 0;//collinear
	if(res<0)
		return 2;//counter-clockwise
	return 1;// clockwise
}
int main()
{
    cout<<"enter number of points\n";
    int n;
    cin>>n;
    pair<int,int> a[n];
    cout<<"enter points\n";
    for(int i=0;i<n;i++)
    	cin>>a[i].first>>a[i].second;
    if(n<3)
	{
		cout<<"convex hull not possible\n";
		return 0;
	}
	vector<pair<int,int> >ans;
	int p=0;
	for(int i=1;i<n;i++)
	{
		if(a[p].first<a[i].first)
			p=i;
	}
	int same=p;
	do
	{
		ans.push_back(a[p]);
		int b=(p+1)%n;
		for(int i=0;i<n;i++)
		{
			if(orientation(a[p],a[i],a[b])==2)
				b=i;
		}
		p=b;
	}
	while(p!=same);
	cout<<"the points in convex ans are:\n";
	for(int i=0;i<sz(ans);i++)
		cout<<"("<<ans[i].first<<","<<ans[i].second<<")"<<endl;
    return 0;
}

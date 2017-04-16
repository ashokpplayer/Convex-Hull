#include<iostream>
#include<math.h>
#include<map>
#include<set>
#include<list>
#include<vector>
#define F first
#define S second
#define m_p make_pair
#define all(v) (v.begin(),v.end())
using namespace std;
set<pair<int,int> >hull;
int n;
pair<int,int> a[1000000];
int side(pair<int,int> P1,pair<int,int> P2,pair<int,int> P)
{
	int val=(P.S-P1.S)*(P2.F-P1.F)-(P2.S-P1.S)*(P.F-P1.F);
	if(val>0)
		return 1;
	if(val<0)
		return -1;
	return 0;
}
int dist(pair<int,int> P,pair<int,int> Q)
{
	int res=0;
	res+=(P.S-Q.S);
	res*=res;
	int tes=(P.F-Q.F);
	tes*=tes;
	res+=tes;
	return res;
}
double line_dist(pair<int,int> P1,pair<int,int> P2,pair<int,int> P)
{
	int val=abs((P.S-P1.S)*(P2.F-P1.F)-(P2.S-P1.S)*(P.F-P1.F));
	double temp=sqrt(dist(P1,P2));
	double res=1.0*val/temp;
	return res;
}
void solve(pair<int,int> P1,pair<int,int> P2,int num)
{
	int ind=-1;
	double max_dist=0.0;
	for(int i=0;i<n;i++)
	{
		double temp=line_dist(P1,P2,a[i]);
		if(side(P1,P2,a[i])==num&&temp>max_dist)
		{
			ind=i;
			max_dist=temp;
		}
	}
	if(ind==-1)
	{
		hull.insert(P1);
		hull.insert(P2);
		return;
	}
	solve(a[ind],P1,-side(a[ind],P1,P2));
	solve(a[ind],P2,-side(a[ind],P2,P1));

}
int main()
{
    ios::sync_with_stdio(0);
    cout<<"enter the number of points\n";
    cin>>n;
    cout<<"enter the points\n";
    for(int i=0;i<n;i++)
    	cin>>a[i].F>>a[i].S;
    int min_x=0,max_x=0;
    for(int i=1;i<n;i++)
    {
    	if(a[i].F<a[min_x].F)
    		min_x=i;
    	if(a[i].F>a[max_x].F)
    		max_x=i;
    }
    cout<<"convex hull is:\n";
    solve(a[min_x],a[max_x],1);
    solve(a[min_x],a[max_x],-1);
    while(!hull.empty())
    {
    	cout<<"("<<(*hull.begin()).F<<","<<(*hull.begin()).S<<")";
    	hull.erase(hull.begin());
    }
    return 0;
}

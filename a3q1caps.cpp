#include <bits/stdc++.h>
using namespace std;
#define ll long long int

struct suffix
{
 	ll index;
 	ll sortindex;
 	ll asciival;
 	string suf;
 	pair<ll,ll> p;
};

bool comp(suffix a, suffix b)
{
	if(a.p.first != b.p.first)
		return a.p.first < b.p.first;
	else
		return a.p.second < b.p.second;
}

void suffixarray(string st)
{
	//cout<<"here"<<st<<endl;
	int slen = st.length();
	string reversest  = st;
	reverse(reversest.begin(),reversest.end());
	st = st+"#"+reversest;
	ll len = st.length();
	suffix s[len];
	for(ll i=0; i<len;i++)
	{
		s[i].index = i;
		s[i].suf = st.substr(i, len-i);
		s[i].asciival = st.at(i)-'a';
		s[i].sortindex = i;
	}
	for(ll i=0; i<len;i++)
	{
		if(i==len-1)
		{
			s[i].p.first = s[i].asciival;
			s[i].p.second = -1;	
		}
		else
		{
			s[i].p.first = s[i].asciival;
			s[i].p.second = s[i+1].asciival;
		}
	}
	// for(ll i=0; i<len;i++)
	// {
	// 	cout<<s[i].suf<<" "<<s[i].index<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
	// }
//	cout<<"==================================="<<endl;
	ll loopcount = (ll)log2((double)len);
	ll k = 1;
	ll indexarr[len];
	while(loopcount>0)
	{
		sort(s, s+len, comp);
		// for(ll i=0; i<len;i++)
		// {
		// 	cout<<s[i].suf<<" "<<s[i].index<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
		// }
	//	cout<<"==================================="<<endl;
		int rank=0;
		for(ll i=0; i < len; i++)
		{
			if(i == 0)
			{
			//	cout<<s[i].suf<<" "<<rank<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
				indexarr[s[i].index] = rank;
			}
			else
			{
				if(s[i].p.first == s[i-1].p.first && s[i].p.second == s[i-1].p.second)
				{
			//		cout<<s[i].suf<<" "<<rank<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
					indexarr[s[i].index] = rank;
				}
				else
				{
			//		cout<<"here"<<endl;
					rank++;
			//		cout<<s[i].suf<<" "<<rank<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
					indexarr[s[i].index] = rank;
				}
			}
		}
	//	cout<<"==================================="<<endl;
		// for(ll i=0; i<len;i++)
		// {
		// 	cout<<s[i].suf<<" index "<<s[i].index<<" rank "<<indexarr[s[i].index]<<" first "<<s[i].p.first<<" second "<<s[i].p.second<<endl;
		// }
	//	cout<<"======================"<<endl;
		ll next = pow(2,k);
		//cout<<next<<endl;
		// for(ll i=0; i<len;i++)
		// {
		// 	cout<<i<<" "<<indexarr[i]<<endl;
		// }
	//	cout<<"======================"<<endl;
		for(ll i=0;i<len;i++)
		{
			if(s[i].index+next >= len)
			{
				s[i].p.first = indexarr[s[i].index];
				s[i].p.second = -1;
			}
			else
			{
				s[i].p.first = indexarr[s[i].index];
				s[i].p.second = indexarr[s[i].index+next];
			}
		}
	// 	for(ll i=0; i<len;i++)
	// 	{
	// //		cout<<s[i].suf<<" "<<s[i].index<<" "<<s[i].p.first<<" "<<s[i].p.second<<endl;
	// 	}
	//	cout<<"======================"<<endl;
		loopcount--;
		k++;
	}
	//cout<<len<<endl;
	

	ll lcp[len] = {0};
	ll inverselcp[len] = {0};

	for(ll i=0; i<len;i++)
	{
		inverselcp[s[i].index] = i;
	}
	ll l = 0;
	for(ll i = 0; i<len;i++)
	{
	 	if(inverselcp[i] == len-1)
	 	{
	 		l=0;	 		
	 	}
	 	else
	 	{
	 		ll j = s[inverselcp[i]+1].index;
	 		while((i+l)< len && (j+l) < len)
	 		{
	 			if(st[i+l] == st[j+l])
            		l++;
            	else 
            		break;
	 		}
        	lcp[inverselcp[i]] = l;
        	if(l>0)
        		l--;	
	 	}
	 	
	}
	// for(ll i=0; i<len;i++)
	// {
	//  	cout<<s[i].suf<<" "<<s[i].index<<" "<<lcp[i]<<endl;
	// }
	int rindex=-1;
	int rlcp = 0;
	for(int i=1; i<len;i++)
	{
		if(rlcp < lcp[i])
		{

		
		if(s[i-1].index < slen && s[i].index > slen)
		{
			
				rindex = s[i].index;
				rlcp = lcp[i];
			
		}
		if(s[i-1].index > slen && s[i].index < slen)
		{
			
				rindex = s[i].index;
				rlcp = lcp[i];
			
		}
		}
	}

	if(rindex == -1 && rlcp == -1)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<st.substr(rindex, rlcp)<<endl;
	}
}

int main()
{
	ll length;
	cin>>length;
	string st;
	cin>>st;
	if(length != st.length())
	{
		cout<<"Length mismatch"<<endl;
	}
	else
		suffixarray(st);
	return 0;
}

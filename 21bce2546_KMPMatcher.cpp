#include<iostream>
#include<string>
using namespace  std;

void Prefix(string pat, int M, int* lps);

void KMPMatcher(string pat, string txt)
{
	int M = pat.length();
	int N = txt.length();

	int lps[M];

	// Preprocessing
	Prefix(pat, M, lps);

	int i = 0; // -> T
	int j = 0; // -> P
	while ((N - i) >= (M - j)) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			cout<<"Valid Shift at index "<<i-j<<endl;
			j = lps[j - 1];
		}

		else if (i < N && pat[j] != txt[i]) {

			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}


void Prefix(string pat, int M, int* lps)
{
	
	int len = 0;

	lps[0] = 0; 

	
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else 
		{
	
			if (len != 0) {
				len = lps[len - 1];
			}
			else 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

// Driver code
int main()
{
	string txt= "000010001010001";
	string pat= "0001";
	KMPMatcher(pat, txt);
	return 0;
}

#include<iostream>

using namespace std;
int padWithZeroes(string &str1, string &str2)
{
int len1 = str1.size();
int len2 = str2.size();
if (len1 < len2)
{
for (int i = 0 ; i < len2 - len1 ; i++)
str1 = '0' + str1;
return len2;
}
else if (len1 > len2)
{
for (int i = 0 ; i < len1 - len2 ; i++)
str2 = '0' + str2;
}
return len1;
}

int multOneBit(string a, string b) {
    int mult=(a[0] - '0')*(b[0] - '0');
    return mult;
}
string & add(string & s1,string & s2)
{
    int len=padWithZeroes(s1,s2);
}
long int mult(string X, string Y)
{
    int size = padWithZeroes(X, Y);


    if (size == 0) return 0;
    if (size == 1) return multOneBit(X, Y);

    int mid = size/2;
    int secondHalf = (size-mid);

    string Xl = X.substr(0, mid);
    string Xr = X.substr(mid, secondHalf);
    string Yl = Y.substr(0, mid);
    string Yr = Y.substr(mid, secondHalf);


    long int a= mult(Xr, Yl);
    long int b= mult(Xl, Yr);
    long int d = mult(Xr, Yr);
    long int c = mult(Xl, Yl);
    return  c*(1<<(2*secondHalf))+(1<<secondHalf)*(a+b)+d;
}


int main()
{
    string x;
    string y;
    cin>>x;
    cin>>y;
    cout<<mult(x,y);
}

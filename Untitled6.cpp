//if you were not smart enough God would never had you put in this place
#include<iostream>
using namespace std;
class sponge
{public:
int s;
int a;	
int *array;
int last;
public:
	
sponge(int b)
{s=b;
array=new int[s];
last=s-1;
a=0;
}
void push(int x)
{if(a==s)
{cout<<"full"<<endl;
}
else
{
array[a]=x;
a++;}
}
void pop(int a)
{int i=0;
int d=0;	
int t;	
while(array[d]!=a&&d<last)
{d++;
}//d is the index to be deleted 
t=d-1;
while(t<last-1)
{t++;
d++;
array[t]=array[d];
}
last--;
};
void display()
{for(int i=0;i<last+1;i++)
{
cout<<array[i]<<" ";}
}
bool empty()
{if (last==-1)
cout<<"empty sponge"<<endl;
return true;
}
};
int main()
{sponge s(6);
s.push(0);
s.push(1);
s.push(2);
s.push(3);
s.push(4);
s.push(5);
s.display();
cout<<endl;
s.pop(3);
s.display();
return 0;
}

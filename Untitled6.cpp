//if you were not smart enough God would never had you put in this place
#include<iostream>
#include<list>
#include<cmath>
#include<cfloat>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<utility>
#include<vector>
#define big 10000000000
using namespace std;
void seed() {
    srand(time(0)); 
}
int random(int max) {
	
    return rand() % (max + 1); }
double distance(double x1,double y1,double x2,double y2)
{double d;
d=sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
cout<<"distance between these points is "<<d<<endl;
return d;
};
double rotations(double d)
{int rotations=d/0.1;
cout<<"total tyre rotations needed are "<<rotations<<"cm"<<endl;
return rotations;
    
};
pair<int,int> findcd(int limit)
{

int x=random(limit);
int y=random(limit);
return make_pair(x,y);};
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

class graph
{public:
	int s;
	list<pair<int,int>> *l;
	graph(int a)
	{s=a;
	l= new list<pair<int,int>>[a];
	}
void addedge(int a,int b,int w)
{l[a].push_back({b,w});
l[b].push_back({a,w});
}
 void display() {
        for (int i = 0; i < s; ++i) {
            cout << "Adjacency list of vertex " << i << ": ";
        
            for (auto neighbor : l[i]) {
                
                    cout << " -> ";  
                
                cout << neighbor.first << "(" << neighbor.second << ")";
            
            }
            cout << endl;
        }
    }
};
void dikefunction(graph &d,graph &g)
{sponge unvisited(6);
sponge visited(6);
    for (int i = 0; i < g.s; ++i) {
   unvisited.push(i);
}
 unvisited.display();   
    
};
class diketable
{public:
int r;
int c;
vector<vector<int>> array;
diketable(int a,int b)
{r=a;
c=b;
array.resize(r,vector<int>(c));
}
   
        
void storedikedata()
{ 
//array[r][c] = {
    //    {1, 2, 3, 4},
     //   {5, 6, 7, 8},}
}    
void displaydiketable()
{
for (int i = 0; i < r; i++) {
  for (int j = 0; j < c; j++) {
    cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

};

//int findobstacle()

//int storeingraph()

//every graph is a path
//run dijkstru
int main()
{seed();
cout<<"here alex will find coordinates of the destination by using IR sensors installed in its machine body ,to proceed code i have generated random coordinates"<<endl;
pair<int,int> coordinates=findcd(100);
cout<<"coordinates are "<<"("<<coordinates.first<<","<<coordinates.second<<")"<<endl;
int d=distance(0,0,coordinates.first, coordinates.second);
cout<<"now assuming radis of tyre is "<<0.1<<endl;
rotations(d);
//graph findpaths(8);
///////////////
graph g(6);
g.addedge(0,1,2);
g.addedge(0,3,8);
g.addedge(1,3,5);
g.addedge(1,4,6);
g.addedge(2,4,9);
g.addedge(2,5,3);
g.addedge(3,4,3);
g.addedge(4,5,1);
g.display();



graph dikegraph(6);
dikefunction(dikegraph,g );

    



	
	
	
	
	
	
return 0;
}

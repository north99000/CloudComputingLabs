#include<iostream> 
#include<fstream>
#include<string>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
using namespace std;
/* 构造完成标志 */
bool sign[1000] = {false};
 
/* 创建数独矩阵 */
//int num[9][9];
int test[1000][9][9];
int ge=1;
/* 函数声明 */
int Input(char filename[]);
void Output(int ge);
bool Check(int ge,int n, int key);
int DFS(int ge, int n); 
typedef struct 
{
   int first;
   int last;
   int result;
 
}ThreadParas;

void* calcSum(void* args) 
{
   ThreadParas* para = (ThreadParas*) args;
   int first=para->first;
   int last=para->last;
   int sum=0;
   for(int i=first;i<last;i++)
   {
   		DFS(i,0);
   } 
    pthread_t tid = pthread_self();       
// 	printf("[%ld] worker thread (sum of num[%04d]-num[%04d]): \t %d\n", pthread_self(), first, last-1, sum);
    
}
int main(int argc, char *argv[])
{
 	int numOfWorkerThread=1;
   	if(argc>=2)
    numOfWorkerThread=atoi(argv[1]);
	char filename[20];
	while(cin.getline(filename,20))
	{
		
		ge = 0;
		clock_t start,end,time;
		start = clock(); 
		ge = Input(filename);
		if(numOfWorkerThread>ge)
		{
			numOfWorkerThread=ge;
		}
		pthread_t th[numOfWorkerThread];
  		ThreadParas thPara[numOfWorkerThread];
	    for(int i=0;i<numOfWorkerThread;i++)
	    {
	     	int first=(int)(ge/numOfWorkerThread)*i;
	     	int last;
	    	if(i!=numOfWorkerThread-1)
	    	{
	    		last=(int)(ge/numOfWorkerThread)*(i+1);
			}
			else
			{
				last=ge;
			} 
	    	thPara[i].first=first;
	    	thPara[i].last=last;
	    	if(pthread_create(&th[i], NULL, calcSum, &thPara[i])!=0)
	    	{
	       		perror("pthread_create failed");
	       
	    	}
		}
	  
	    for(int i=0;i<numOfWorkerThread;i++)
	    {
	    	pthread_join(th[i], NULL);
		}
		Output(ge);
		end = clock();
		time = end -start;
		cout<<time<<"ms"<<endl;
	}
}
 int Input(char filename[])
{
	int ge = 0;//记录测试个数 
	ifstream in(filename);
	string line;
	if(in)//有该文件 
	{
		while(getline(in,line)) //line中不包括每行的换行符
		{
			char temp[9][9];
		    for (int i = 0; i < 9; i++)
		    {
		        for (int j = 0; j < 9; j++)
		        {
		            temp[i][j] = line[i*9+j];
		            test[ge][i][j] = temp[i][j] - '0';
		        }
		    }
		    ge++;
		} 
		in.close();
	}
	else//没有该文件 
	{
		cout<<"no such file"<<endl;
	}
	return ge;
}
 
/* 输出数独矩阵 */
void Output(int ge)
{
	ofstream out;
	out.open("./answer.txt", std::ios::app);
	for (int n = 0; n < ge; n++)
	{
		for (int i = 0; i < 9; i++)
	    {
	        for (int j = 0; j < 9; j++)
	        {
	            cout << test[n][i][j] ;
	            out << test[n][i][j]; 
	        }
	    }
	    sign[n] = false;
	    cout<<endl;
	    out<<endl;
	}
	out.close();
}

 
/* 判断key填入n时是否满足条件 */
bool Check(int ge, int n, int key)
{
    /* 判断n所在横列是否合法 */
    for (int i = 0; i < 9; i++)
    {
        /* j为n竖坐标 */
        int j = n / 9;
        if (test[ge][j][i] == key) return false;
    }
 
    /* 判断n所在竖列是否合法 */
    for (int i = 0; i < 9; i++)
    {
        /* j为n横坐标 */
        int j = n % 9;
        if (test[ge][i][j] == key) return false;
    }
 
    /* x为n所在的小九宫格左顶点竖坐标 */
    int x = n / 9 / 3 * 3;
 
    /* y为n所在的小九宫格左顶点横坐标 */
    int y = n % 9 / 3 * 3;
 
    /* 判断n所在的小九宫格是否合法 */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (test[ge][i][j] == key) return false;
        }
    }
 
    /* 全部合法，返回正确 */
    return true;
}
 
/* 深搜构造数独 */
int DFS(int ge, int n)
{
    /* 所有的都符合，退出递归 */
    if (n > 80)
    {
        sign[ge] = true;
        return 0;
    }
    /* 当前位不为空时跳过 */
    if (test[ge][n/9][n%9] != 0)
    {
        DFS(ge, n+1);
    }
    else
    {
        /* 否则对当前位进行枚举测试 */
        for (int i = 1; i <= 9; i++)
        {
            /* 满足条件时填入数字 */
            if (Check(ge, n, i) == true)
            {
                test[ge][n/9][n%9] = i;
                /* 继续搜索 */
                DFS(ge, n+1);
                /* 返回时如果构造成功，则直接退出 */
                if (sign[ge] == true) return 0;
                /* 如果构造不成功，还原当前位 */
                test[ge][n/9][n%9] = 0;
            }
        }
    }
}

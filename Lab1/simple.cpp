#include<iostream> 
#include<fstream>
#include<string>
#include<time.h> 

using namespace std;
 
/* ������ɱ�־ */
bool sign[1000] = {false};
 
/* ������������ */
int test[1000][9][9];
 
/* �������� */
int Input(char filename[]);
void Output(int ge);
bool Check(int ge,int n, int key);
int DFS(int ge, int n); 
 
/* ������ */
int main()
{
	char filename[20];
	while(cin.getline(filename,20))
	{
		
		int ge = 0;
		clock_t start,end,time;
		start = clock();
		ge = Input(filename);
		for(int i = 0;i < ge;i ++)
		{
			DFS(i, 0);
		}
	    Output(ge);
	    end = clock();
	    time = end - start;
	    cout<<time<<" ms"<<endl;
	    
	}
	system("pause");
    return 0;
}


int Input(char filename[])
{
	int ge = 0;//��¼���Ը��� 
	ifstream in(filename);
	string line;
	if(in)//�и��ļ� 
	{
		while(getline(in,line)) //line�в�����ÿ�еĻ��з�
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
	else//û�и��ļ� 
	{
		cout<<"no such file"<<endl;
	}
	return ge;
}
 
/* ����������� */
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
 
/* �ж�key����nʱ�Ƿ��������� */
bool Check(int ge, int n, int key)
{
    /* �ж�n���ں����Ƿ�Ϸ� */
    for (int i = 0; i < 9; i++)
    {
        /* jΪn������ */
        int j = n / 9;
        if (test[ge][j][i] == key) return false;
    }
 
    /* �ж�n���������Ƿ�Ϸ� */
    for (int i = 0; i < 9; i++)
    {
        /* jΪn������ */
        int j = n % 9;
        if (test[ge][i][j] == key) return false;
    }
 
    /* xΪn���ڵ�С�Ź����󶥵������� */
    int x = n / 9 / 3 * 3;
 
    /* yΪn���ڵ�С�Ź����󶥵������ */
    int y = n % 9 / 3 * 3;
 
    /* �ж�n���ڵ�С�Ź����Ƿ�Ϸ� */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (test[ge][i][j] == key) return false;
        }
    }
 
    /* ȫ���Ϸ���������ȷ */
    return true;
}
 
/* ���ѹ������� */
int DFS(int ge, int n)
{
    /* ���еĶ����ϣ��˳��ݹ� */
    if (n > 80)
    {
        sign[ge] = true;
        return 0;
    }
    /* ��ǰλ��Ϊ��ʱ���� */
    if (test[ge][n/9][n%9] != 0)
    {
        DFS(ge, n+1);
    }
    else
    {
        /* ����Ե�ǰλ����ö�ٲ��� */
        for (int i = 1; i <= 9; i++)
        {
            /* ��������ʱ�������� */
            if (Check(ge, n, i) == true)
            {
                test[ge][n/9][n%9] = i;
                /* �������� */
                DFS(ge, n+1);
                /* ����ʱ�������ɹ�����ֱ���˳� */
                if (sign[ge] == true) return 0;
                /* ������첻�ɹ�����ԭ��ǰλ */
                test[ge][n/9][n%9] = 0;
            }
        }
    }
}

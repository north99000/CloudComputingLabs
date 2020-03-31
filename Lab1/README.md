**【算法】**

DBS深度优先遍历

**【代码版本】**

实验中共使用两份不同的代码：**simple.cpp**和**sudoku_solve.cpp**。

**simple.cpp:** 原生的数独求解代码，即本实验中所提供的代码，只能以单线程模式运行。

**sudoku_solve.cpp:** 为适应多线程而在**simple.cpp**上进行了一系列的修改和增添而成。在**sudoku_solve.cpp**中，可通过参数的调节而控制线程数量。与**simple.cpp**相比，**sudoku_solve.cpp**的代码量多了五十行左右。注：**sudoku_solve.cpp**的多线程主要运用在DFS求解函数上，可以开多个线程分开求解样例，在求解进度上缩短时间。

如无特别说明，默认使用**sudoku_solve.cpp**。

**【函数及功能】**

（1）int Input(char filename[]);

按行读取并记录测试文件中的所有数独样例

（2）void Output(int ge);

按行输出当前文件中所有数独样例的解

（3）bool Check(int ge,int n, int key);

判断key填入n位置时是否满足条件

（4）int DFS(int ge, int n);

深搜构造数独

**【运行】**

./sudoku_solve

**【输入】**

一次输入一个测试文件名，等当前文件给出结果之后再输入下一个文件名，如下：

./test1

./test1000

**【输出】**

每次按行输出当前文件中所有数独样例的解，答案也会按照顺序输出到answer.txt中。

// 利用链栈解决走迷宫问题
#include <iostream>
#include "MazeLinkStack.cpp"
using namespace std;

// （1）定义迷宫数据结构

// 将迷宫抽象化为二维数组 maze[m][n] ，坐标值 0 表示畅通， 1 表示堵塞。

// 由于大小为 [m][n] 的迷宫的边缘和内部的坐标点的相邻坐标点数量不一致，内部是 4，边缘是 3，四个角是 2
// 所以在迷宫上下左右各加一行不通的路，即坐标值为 1 ，使得每个坐标点的相邻坐标点的数量都为 4 ，

// 定义迷宫，实际迷宫大小只有 [m][n]，外围一周都是堵塞的 1 ，
// 入口是 (1,1)，出口是 (m,n)

// int maze[m + 2][n + 2];

// （2）某个坐标点的前进试探方向，四个方向
// 某个坐标四个试探方向的坐标

/*
typedef struct
{
    int x;
    int y;
} item;
item move[4];
*/

// （3）栈结点的设计
// 每个结点不仅要保存坐标，还要保存上一个坐标到这个坐标的方向。

// typedef struct
// {
//     int x, y, d; // 横纵坐标 x、y 和前进方向 d
// } DataNode;

// 链栈的定义是 Stack.cpp 中的 LinkStack。
// LinkStack S;

// （4）如何防止已经走过的路不再走，即避免重复到达某点，以避免发生死循环
// 一种方法是另外设置一个标志数组mark[m]​[n]​，它的所有元素都初始化为0，
// 一旦到达某一点（i,j）之后，使mark[i]​[j]置1，下次再试探这个位置时就不能再走了。

// 另一种方法是当到达某点（i,j）后，使maze[i]​[j]置-1，以便区别未到过的点，
// 同样也能起到防止走重复点。本算法采用后者，算法结束前可恢复原迷宫。

// 迷宫求解算法思想如下：
/*
① 栈初始化；
② 将入口点坐标及到达该点的方向（设为-1）入栈；
③ while（栈不空）
  {  出栈并得到栈顶元素=＞(x, y, d)
      求出下一个要试探的方向d++ ;
      while  (还有剩余试探方向时)
      {  if(d方向可走)
        {  (x, y, d)入栈 ；
            求新点坐标  (i, j);
            将新点(i, j)切换为当前点(x, y);
            if( (x, y)==(m, n))
                结束 ；
            else
              重置d=0 ;           //新位置开始从正东方向的试探
        }
        else  d++ ;                //换个新方向
      }
  }
  */

//  （5）实际算法
// 二维数组不能直接作参数，函数用一维指针数组 "int *maze[]" 作参数。
int mazepath(int *maze[], int x0, int y0, int m, int n, MazeLinkStack &S)
{
    NodeType temp;
    int x, y, d, i, j;
    struct
    {
        int dx;
        int dy;
    } move[4];

    // 竖直方向向下是 x 正方向，水平方向向右是 y 正方向。
    // 移动试探的四个方向依次为东、南、西、北
    move[0].dx = 0;
    move[0].dy = 1;
    move[1].dx = 1;
    move[1].dy = 0;
    move[2].dx = 0;
    move[2].dy = -1;
    move[3].dx = -1;
    move[3].dy = 0;

    // 起点
    temp.x = x0;
    temp.y = y0;
    temp.d = -1;

    S.Push_Stack(temp);
    while (!S.IsEmpty())
    {
        S.Pop_Stack(temp);
        x = temp.x;
        y = temp.y;
        d = temp.d + 1; // 试探下一个方向
    }

    while (d < 4)
    {
        // 得到下一个方向的位置
        i = x + move[d].dx;
        j = y + move[d].dy;
        if (maze[i][j] == 0) // 试探的位置可通
        {
            temp.x = x;
            temp.y = y;
            temp.d = d;
            S.Push_Stack(temp); // 保存该位置以及方向
            x = i;              // 切换当前位置为新位置
            y = j;
            maze[x][y] = -1;          // 标记该位置已经走过
            if ((x == m) && (y == n)) // 到达迷宫的出口，成功走出迷宫
            {
                while (!S.IsEmpty()) // 按照出口到入口的顺序输出路径
                {
                    S.Pop_Stack(temp);
                    cout << "(" << temp.x << "," << temp.y << ")" << endl;
                }
                for (i = x0; i <= m; i++) // 恢复迷宫
                {
                    for (j = y0; j <= n; j++)
                    {
                        if (maze[i][j] == -1)
                            maze[i][j] == 0;
                    }
                }
                return (1); // 找到一条路径返回
            }
            else // 没有到出口，新位置从第一个方向试探
            {
                d = 0;
            }
        }
        else // 试探的方向不通，切换到下一个方向试探
        {
            d++;
        }
    }
    for (i = x0; i <= m; i++) // 恢复迷宫
    {
        for (j = y0; j <= n; j++)
        {
            if (maze[i][j] == -1)
                maze[i][j] == 0;
        }
    }
    return (0); // 迷宫无路返回
}
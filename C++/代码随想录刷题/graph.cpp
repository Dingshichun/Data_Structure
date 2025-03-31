#include"head.h"

// 图的定义包括邻接表和邻接矩阵
// 关于图的搜索，包括深度优先搜索（dfs）和广度优先搜索（bfs）

// 深度优先搜索实际上就是递归。按照递归三部曲来写
// 1. 确定递归函数的参数和返回值
// 2. 确定递归函数的终止条件
// 3. 确定递归函数的单层逻辑

// 1、所有可达路径
// 给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。
// 找出并返回所有从节点 1 到节点 n 的路径。每条路径应以节点编号的列表形式表示。

// 输入{{5,5},{1,3},{3,5},{1,2},{2,4},{4,5}} ，其中第一组数据表示有 5 个节点 5 条边
// 后面每组表示第一个节点指向第二个节点，比如 {1,3} 表示节点 1 指向节点 3，以此类推

// 使用邻接矩阵来表示图，有 n 个节点就创建一个 n*n 二维数组，然后根据输入的边来填充数组
// 因为节点标号是从 1 开始的，为了节点标号和下标对齐，我们申请 n + 1 * n + 1

/*
vector<vector<int>>graph(n + 1, vector<int>(n + 1, 0));
// 输入 m 条边
while (m--)
{
    cin >> s >> t;
    // 使用邻接矩阵 ，1 表示 节点 s 指向 节点 t
    graph[s][t] = 1;
}
*/

// 使用邻接表来表示图
/* 
// 邻接表是从边的数量来表示图，有多少边 才会申请对应大小的链表。
// 我们需要构造一个数组，数组里的元素是一个链表。
// 节点编号从 1 到 n，所以申请 n+1 这么大的数组
// vector<list<int>> graph(n + 1); // 邻接表，list 为 C++ 里的链表
while (m--) {
    cin >> s >> t;
    // 使用邻接表 ，表示 s -> t 是相连的
    graph[s].push_back(t);
}
*/

// 三部曲，以邻接矩阵为例
// 1、确定递归函数的参数和返回值
// 首先我们 dfs 函数一定要存一个图，用来遍历的，需要存一个目前我们遍历的节点，定义为 x。
// 还需要存一个 n，表示终点，我们遍历的时候，用来判断当 x == n 时候 标明找到了终点。
// 单一路径 path 和 路径集合 result 可以放在全局变量
/*
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 0节点到终点的路径
// x：目前遍历的节点
// graph：存当前的图
// n：终点
void dfs (const vector<vector<int>>& graph, int x, int n) {}
*/

// 2、确定递归函数的终止条件
/*
// 当前遍历的节点 x 为最后一个节点 n 时，说明找到了一条路径
if (x == n) { // 找到符合条件的一条路径
    result.push_back(path);
    return;
}
*/
// 3、确定递归函数的单层逻辑。
// 处理当前节点 x 的下一个节点，首先要找到 x 节点指向了哪些节点
/*
for (int i = 1; i <= n; i++) { // 遍历节点x链接的所有节点
    if (graph[x][i] == 1) { // 找到 x指向的节点，就是节点i
    }
}
*/
// 接下来就是将 选中的x所指向的节点，加入到 单一路径 来。
// path.push_back(i); // 遍历到的节点加入到路径中来

// dfs(graph, i, n); // 进入下一层递归
// 最后就是回溯的过程，撤销本次添加节点的操作。
// path.pop_back(); // 回溯，撤销本次操作
/*
// 递归函数的单层逻辑整体代码如下：
for (int i = 1; i <= n; i++) { // 遍历节点x链接的所有节点
    if (graph[x][i] == 1) { // 找到 x链接的节点
        path.push_back(i); // 遍历到的节点加入到路径中来
        dfs(graph, i, n); // 进入下一层递归
        path.pop_back(); // 回溯，撤销本节点
    }
}
*/

// 使用邻接矩阵的完整写法如下：
/*
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 1节点到终点的路径

void dfs (const vector<vector<int>>& graph, int x, int n) {
    // 当前遍历的节点 x 到达节点 n
    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) { // 遍历节点 x 链接的所有节点
        if (graph[x][i] == 1) { // 找到 x 链接的节点
            path.push_back(i); // 遍历到的节点加入到路径中来
            dfs(graph, i, n); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
}
*/

// 使用邻接表写法如下：
/*
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path; // 节点 1 到终点的路径

void dfs (const vector<list<int>>& graph, int x, int n) {

    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
    for (int i : graph[x]) { // 找到 x 指向的节点
        path.push_back(i); // 遍历到的节点加入到路径中来
        dfs(graph, i, n); // 进入下一层递归
        path.pop_back(); // 回溯，撤销本节点
    }
}
*/

// 广搜的搜索方式就适合于解决两个点之间的最短路径问题。
// 因为广搜是从起点出发，以起始点为中心一圈一圈进行搜索，
// 一旦遇到终点，记录之前走过的节点就是一条最短路。

// 我们仅仅需要一个容器，能保存我们要遍历过的元素就可以，
// 那么用队列，还是用栈，甚至用数组，都是可以的。
// 但是用队列，我们就可以保证最先遍历到终点的路径，就是最短路径。

/* 
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示某个点的上、下、左、右四个方向
// grid 是地图，也就是一个二维数组
// visited标记访问过的节点，不要重复访问
// x,y 表示开始搜索节点的下标
void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
    queue<pair<int, int>> que; // 定义队列
    que.push({x, y}); // 起始节点加入队列
    visited[x][y] = true; // 只要加入队列，立刻标记为访问过的节点
    while(!que.empty()) { // 开始遍历队列里的元素
        pair<int ,int> cur = que.front(); que.pop(); // 从队列取元素
        int curx = cur.first;
        int cury = cur.second; // 当前节点坐标
        for (int i = 0; i < 4; i++) { // 开始想当前节点的四个方向左右上下去遍历
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1]; // 获取周边四个方向的坐标
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 坐标越界了，直接跳过
            if (!visited[nextx][nexty]) { // 如果节点没被访问过
                que.push({nextx, nexty});  // 队列添加该节点为下一轮要遍历的节点
                visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
            }
        }
    }
}
*/

// 2、岛屿数量
// 给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算岛屿的数量。
// 岛屿由水平方向或垂直方向上相邻的陆地连接而成，并且四周都是水域。
// 你可以假设矩阵外均被水包围。

// 注意题目中每座岛屿只能由水平方向和 / 或竖直方向上相邻的陆地连接形成。
// 也就是说斜角度链接是不算了
/*
输入描述：
第一行包含两个整数 N, M，表示矩阵的行数和列数。
后续 N 行，每行包含 M 个数字，数字为 1 或者 0。

输出描述：
输出一个整数，表示岛屿的数量。如果不存在岛屿，则输出 0。

输入示例：
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

输出示例：3
*/

// 思路：
// 是用遇到一个没有遍历过的节点陆地，计数器就加一，然后把该节点陆地所能遍历到的陆地都标记上。
// 在遇到标记过的陆地节点和海洋节点的时候直接跳过。 这样计数器就是最终岛屿的数量。
/*
// 这段代码只是解释原理
int dir[4][2] = { 0,1,1,0,0,-1,-1,0 };// 表示某个点的上、下、左、右四个方向
void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
{
    // 终止条件，遇到访问过的或者遇到海水
    if (visited[x][y] || grid[x][y] == 0)return;
    visited[x][y] = true; // 标记访问过
    for (int i = 0; i < 4; ++i) // 遍历四个方向
    {
        int nextx = x + dir[i][0]; // 获取周边四个方向的坐标
        int nexty = y + dir[i][1];

        // 判断是否越界
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size())
            continue;
        dfs(grid, visited, nextx, nexty); // 递归调用
    }
}

int main() {
    int n, m; // n 行 m 列
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0)); // 定义一个 n 行 m 列的二维数组
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j]; // 输入二维数组
        }
    }

    // 定义一个 n 行 m 列的二维数组，用来标记是否访问过
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int result = 0; // 计数器，用来记录岛屿的数量
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 1) {
                result++; // 遇到没访问过的陆地，+1
                dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }
    cout << result << endl;
}
*/


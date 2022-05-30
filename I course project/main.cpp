#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void dijkstra(int **vertex, int src, int end, int n, int path[], string output[]);
void print_matrix(int **mow, int n, string output[]);
bool scan_matr (int **vertex, int n);
int minDistance(int dist[], bool sptSet[], int n);
int printSolution(int dist[], int n, string output[]);
void pathfinding(int n, int dist[], int start, int end, int path[], int **vertex, string output[]);
void print_path(int path[], int k, string output[]);

int main() {
    {
        string output[2];//  массив для хранения полученной информации
        char buffer[255];// массив для промежуточных данных
        int n;
        Start:
        cout << "Enter the number of vertexes.\n";
        cout << "Number must be positive integer!\n";
        while (!(cin >> n)){
            cout << "Number must be digit\nEnter the number of vertexes:\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (n <= 0) goto Start;
        output[0].append("Number of vertexes: ");
        sprintf(buffer, "%d\n", n);
        output[0].append(buffer);//  сразу сохраним строку для вывода
        //  create matrix of ways
        int **vertex = new int *[n];
        for (int i = 0; i < n; ++i)//
            vertex[i] = new int [n];//
        for (int i = 0; i < n; i++) {// init matrix
            for (int j = 0; j < n; ++j)//
                vertex[i][j] = NULL;
       }
        scan_matr(vertex, n);
        print_matrix(vertex, n, output);
        int src;
        StartPoint:
        cout << "Enter the start point:\n";
        while (!(cin >> src)){
            cout << "Number must be positive digit\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (src < 1 || src > n){
            cout << "Wrong input\n";
            goto StartPoint;
        }
        src--;
        sprintf(buffer, "Start point: %d\n", src+1);
        output -> append(buffer);
        int e;
        EndPoint:
        cout << "Enter the end point: \n";
        while (!(cin >> e)){
            cout << "Number must be positive digit\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (e < 1 || e > n) {
            cout << "Wrong input\n";
            goto EndPoint;
        }
        if (src+1 == e) {
            cout << "No way out\n";
            goto StartPoint;
        }
        //cin >> e;
        sprintf(buffer, "End point: %d\n", e);
        output -> append(buffer);

        int path[n];
        dijkstra(vertex, src, e, n, path, output);
        ofstream out("output.txt");
        out << output[0];
        out.close();
        //cout << output[0];
    }

        return 0;
}

void print_matrix(int **mow, int n, string output[]){
    char buffer[255];
    cout << setw(5) << "\t";
    output -> append("\n\tMatrix of Ways\n\t");
    for (int i=0; i<n; ++i) {
        cout << "X" << i+1;
        cout << setw(3);
        sprintf(buffer, "X%d\t", i+1);
        output -> append(buffer);
    }
    output -> append("\n");
    cout << endl;
    for (int i = 0; i < n; i++) {// init matrix
        cout << setw(4);
        cout << "X" << i+1;
        sprintf(buffer, "X%d\t", i+1);
        output -> append(buffer);
        for (int j = 0; j < n; ++j){
            cout << setw(4);
            cout << mow[i][j];
            sprintf(buffer, "%d\t", mow[i][j]);
            output -> append(buffer);
    }
        cout << endl;
        output -> append("\n");
    }
    output -> append("\n");
    //cout << output;
}

/*void print_matrix(int mow[9][9], int n){
    cout << setw(5) << "\t";
    for (int i=0; i<n; ++i) {
        cout << "X" << i+1;
        cout << setw(3);
    }
    cout << endl;
    for (int i = 0; i < n; i++) {// init matrix
        cout << setw(4);
        cout << "X" << i+1;
        for (int j = 0; j < n; ++j){
            cout << setw(4);
            cout << mow[i][j];
        }
        cout << endl;
    }
}*/

bool scan_matr (int **vertex, int n)
{
    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "enter length between x" << i + 1 << " and x" << j + 1 << ": ";
            int inp;
            StartInput:
            while (!(cin >> inp)){
                cout << "Wrong input!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (inp < 0) {cout << "Wrong input"; goto StartInput;}
            vertex[i][j] = inp;
            vertex[j][i] = vertex[i][j];
            cout << endl;
        }
    }
    return 1;
}

int minDistance(int dist[], bool sptSet[], int n)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n, string output[])
{
    char buffer[255];
    printf("Vertex   Distance from Source\n");
    output -> append("\nVertex   Distance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i + 1, dist[i]);
        sprintf(buffer, "%d \t\t %d\n", i+1, dist[i]);
        output -> append(buffer);
    }
}

void dijkstra(int **vertex, int src, int end, int n, int path[], string output[])
{
    int dist[n]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[n]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    int graph[n][n];
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            graph[i][j] = vertex[i][j];
        }
    }
    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, n);

        // Mark the picked vertex as processed
        sptSet[u] = true;



        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++) {
            //int path[v][v];
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }
    printSolution(dist, n, output);
    pathfinding(n, dist, src, end, path, vertex, output);
}

void init_matrix(int **vertex, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j)//
            vertex[i][j] = NULL;
    }
        return;
}

void pathfinding(int n, int dist[], int start, int end, int path[], int **vertex, string output[]){
    //int ver[n]; // массив посещенных вершин
    int xe = end - 1; // индекс конечной вершины = 3 - 1
    // начальный элемент - конечная вершинa, начинаем с конца
    path[0] = end;
    int k = 1; // индекс предыдущей вершины
    int weight = dist[xe]; // вес конечной вершины

    while (xe != start) // пока не дошли до начальной вершины
    {
        for (int i = 0; i<n; i++) // просматриваем все вершины
            if (vertex[i][xe] != 0)   // если связь есть
            {
                int temp = weight - vertex[i][xe]; // определяем вес пути из предыдущей вершины
                if (temp == dist[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    xe = i;       // сохраняем предыдущую вершину
                    path[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
    }
    print_path(path, k, output);
}
void print_path(int path[], int k, string output[]){
    char buffer[255];
    cout << endl << "The shortest way\n" << setw(4);
    output -> append("\n\tThe shortest way\n");
    for (int i = k - 1; i >= 0; i--) {
        cout << "X" << path[i] << " ";
        sprintf(buffer, "X%d ", path[i]);
        output -> append(buffer);
    }
    cout << endl;
    output -> append("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int ** network;
int ** subNetwork;
int ** serverG;
int * servers_list;
int * visitedDFS;
int nodes;
int current_nodes;
int totalServersSub = 0;
int total_servers;
int time = 0;
int tsp_cost;
int cost1;
int cost2;

int _find(int * parent, int i) {
	while (parent[i] != i) {
		i = parent[i];
	}
	return i;
}

void _union(int * parent, int i, int j) {

	int a, b;
	a = _find(parent, i);
	b = _find(parent, j);
	parent[a] = b;

}

int kruskalMST(int * parent) {

	int min_cost = 0;
	int min;
	int i, j, edges = 0;
	int a, b;

	for (i = 0; i < totalServersSub; i++) {
		parent[i] = i;
	}

	while (edges < totalServersSub - 1) {

		min = INT_MAX;
		a = -1;
		b = -1;

		for (i = 0; i < totalServersSub; i++) {
			for (j = 0; j < totalServersSub; j++) {
				if (_find(parent, i) != _find(parent, j) && serverG[i][j] < min) {
					min = serverG[i][j];
					a = i;
					b = j;
				}
			}
		}
		_union(parent, a, b);
		edges ++;
		min_cost += min;
	}

	return min_cost;
}

void kruskal() {

	int * parent = (int*)malloc(totalServersSub * sizeof(int));
	int i;

	for (i = 0; i < totalServersSub; i++) {
		parent[i] = i;
	}

	cost2 += kruskalMST(parent);
}

void combinationUtil(int * array, int * data, int start, int end, int index, int r) {

	if (index == r) {
		cost1 += serverG[data[0]][data[1]];
		return;
	}

	int i = start;

	while (i <= end && end - i + 1 >= r - index) {
		data[index] = array[i];
		combinationUtil(array, data, i + 1, end, index + 1, r);
		i++;
	}
}

void getComb(int * array, int n, int r) {

	int * data = (int*)calloc(r, sizeof(int));

	combinationUtil(array, data, 0, n - 1, 0, r);
}

int minDistance(int * distance, int * sptSet) {

	int min = INT_MAX;
	int min_index = 0;
	int i;

	for (i = 0; i < nodes; i++) {
		if(sptSet[i] == 0 && distance[i] <= min) {
			min = distance[i], min_index = i;
		}
	}

	return min_index;
}


void djikstra(int source, int * distance) {

	int * sptSet = (int*)calloc(nodes, sizeof(int));
	int u;
	int i, v;

	for (i = 0; i < nodes; i++) {
		distance[i] = INT_MAX;
	}

	distance[source] = 0;

	for (i = 0; i < nodes; i++) {

		u = minDistance(distance, sptSet);

		sptSet[u] = 1;

		for (v = 0; v < nodes; v++) {
			if (sptSet[v] == 0 && network[u][v] > 0 && distance[v] > distance[u] + network[u][v]) {
				distance[v] = distance[u] + network[u][v];
			}
		}
	}	
}

void serverGraph() {

	int i, j, col = 0, line = 0;

	int * distance = (int*)malloc(nodes * sizeof(int));
	int * array = (int*)malloc(totalServersSub * sizeof(int));

	serverG = (int**)malloc(totalServersSub * sizeof(int*));

	for (i = 0; i < nodes; i++) {

		if (i < totalServersSub) {
			array[i] = i;
		}
    	serverG[i] = (int*)calloc(totalServersSub, sizeof(int));

	}

	for (i = 0; i < totalServersSub; i++) {

		djikstra(servers_list[i], distance);
		col = 0;

		for (j = 0; j < totalServersSub; j++) {
			serverG[line][col] = distance[servers_list[j]];
			col ++;
		}
		line++;
	}

	if (totalServersSub == 2) {
		cost1 += distance[servers_list[0]];
		cost2 += distance[servers_list[0]];
	}
	else {
		getComb(array, totalServersSub, 2);
	}
}

void serversUtil(int u, int * visited, int * servers, int * parent, int * low, int * disc) {

	int children = 0;
	int i;
	visited[u] = 1;

	disc[u] = time; 
	low[u] = time;
	time ++;

	for (i = 0; i < nodes; i++) {

		if (subNetwork[u][i] != 0) {

			if (visited[i] == 0) {

				parent[i] = u;
				children += 1;

				serversUtil(i, visited, servers, parent, low, disc);

				if (low[u] > low[i])
					low[u] = low[i];

				if (parent[u] == -1 && children > 1) {
					if (servers[u] != 1) {
						servers[u] = 1;
						total_servers += 1;
						totalServersSub += 1;
					}
					
				}

				else if (parent[u] != -1 && low[i] >= disc[u]) {
					if (servers[u] != 1) {
						servers[u] = 1;	
						total_servers += 1;
						totalServersSub += 1;
					}
					
				}
			}

			else if (i != parent[u]) {
				if (low[u] > disc[i])
					low[u] = disc[i];
			}
		}
	}
}

void servers() {

	int * visited = (int*)calloc(nodes, sizeof(int));
	int * disc = (int*)malloc(nodes * sizeof(int));
	int * low = (int*)malloc(nodes * sizeof(int));
	int * parent = (int*)malloc(nodes * sizeof(int));
	int * servers = (int*)calloc(nodes, sizeof(int));
	totalServersSub = 0;
	time = 0;

	int i, j;

	for (i = 0; i < nodes; i++) {
		disc[i] = INT_MAX;
		low[i] = INT_MAX;
		parent[i] = -1;
	}

	for (i = 0; i < nodes; i++) {
		if (visited[i] == 0) {
			serversUtil(i, visited, servers, parent, low, disc);
		}
	}

	servers_list = (int*)malloc(totalServersSub * sizeof(int));

	j = 0;

	for (i = 0; i < nodes; i++) {
		if (servers[i] == 1) {
			servers_list[j] = i;
			j++;	
		}
	}
}

int getNotVisited(int * visited) {

	int i;

	for (i = 0; i < nodes; i++) {
		if (visited[i] == 0) {
			return i;
		}
	}
	return -1;
}

void DFSUtil(int * visited, int u) {

	int i;

	visited[u] = 1;

	for (i = 0; i < nodes; i++) {

		subNetwork[u][i] = network[u][i];
		subNetwork[i][u] = network[u][i];

		if (network[u][i] != 0 && visited[i] == 0) {
			visited[i] = 1;
			current_nodes += 1;
			DFSUtil(visited, i);
		}
	}
}

void DFS() {

	int * visited = (int*)calloc(nodes, sizeof(int));
	int u;
	int i;

	while (1) {

		current_nodes = 1;

		// INIT SUBNETWORK ===================================

		subNetwork = (int**)malloc(nodes * sizeof(int*));

		for (i = 0; i < nodes; i++) {

	    	subNetwork[i] = (int*)calloc(nodes, sizeof(int));
		}

		// ====================================================

		u = getNotVisited(visited);

		if (u == -1) {
			break;
		}

		DFSUtil(visited, u);
		servers();
		
		if (totalServersSub == 0) {
			continue;
		}
		else if (totalServersSub == 1) {
			continue;
		}
		else {
			
			serverGraph();

			if (totalServersSub > 2) {
				kruskal();
			}
		}
	}
}

void solve() {

	total_servers = 0;
	tsp_cost = INT_MAX;
	cost1 = 0;
	cost2 = 0;

	DFS();

	if (total_servers == 0)
		printf("no server\n");
	else
		printf("%d %d %d\n", total_servers, cost1, cost2);
}

int main() {

	char line[20];
	int node1, node2, length, i;

	while(scanf("%15s", line) == 1) {

		nodes = atoi(line);

		network = (int**)malloc(nodes * sizeof(int*));

		for (i = 0; i < nodes; i++) {

    		network[i] = (int*)calloc(nodes, sizeof(int));
		}

		while(1) {

			scanf("%d", &node1);

			if (node1 == 0) {

				solve();
				break;

			}

			scanf("%d %d", &node2, &length);

			network[node1 - 1][node2 - 1] = length;
			network[node2 - 1][node1 - 1] = length;

		}
	}
	return 0;
}
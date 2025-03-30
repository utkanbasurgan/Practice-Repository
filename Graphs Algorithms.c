//
// Utkan Başurgan
//
//--------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------------------------------------------------------------------------------------------------------------------------------

struct Graph_Fragment
{
    struct Edge_Fragment* head;
};

struct Edge_Fragment
{
    int direction;
    int weight;
    struct Edge_Fragment* next;
};

struct Cycle_Fragment {
    int* nodes;
    int perimeter;
    int length;
};

//--------------------------------------------------------------------------------------------------------------------------------

int Edge_Get(struct Graph_Fragment* graph, int v1, int v2);
void Search_Base(struct Graph_Fragment* graph, int vertex_start, int vertex_count);
void Search_Root(struct Graph_Fragment* graph, int vertex, int vertex_parent, bool* vertex_path, int* path, int path_index, int vertex_count, struct Cycle_Fragment* cycles, int* cycle_count);
void Search_Cycles(struct Graph_Fragment* graph, int vertex, int vertex_parent, bool* vertex_path, int* path, int path_index, int vertex_count, struct Cycle_Fragment* cycles, int* cycle_count);

//--------------------------------------------------------------------------------------------------------------------------------

struct Graph_Fragment* Graph_Create(int vertices)
{
    struct Graph_Fragment* graph = 
    (
        struct Graph_Fragment*
    )
    malloc
    (
        vertices * sizeof(struct Graph_Fragment)
    );
    
    for (int i = 0; i < vertices; i++)
    {
        graph[i].head = NULL;
    }
    
    return graph;
}

void Graph_Print(struct Graph_Fragment* graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        struct Edge_Fragment* current = graph[i].head;

        printf("Vertex %d: ", i);

        while (current != NULL)
        {
            printf("-> %d-%d ", current->direction, current->weight);
            current = current->next;
        }
        
        printf("-> NULL\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------------

struct Edge_Fragment* Edge_Create(int vertex_two, int weight)
{
    struct Edge_Fragment* edge_new = 
    (
        struct Edge_Fragment*
    )
    malloc
    (
        sizeof(struct Edge_Fragment)
    );

    edge_new->direction = vertex_two;
    edge_new->weight = weight;
    edge_new->next = NULL;

    return edge_new;
}

void Edge_Add(struct Graph_Fragment* graph, int vertex_one, int vertex_two, int weight)
{
    struct Edge_Fragment* edge_one_new = Edge_Create(vertex_two, weight);
    edge_one_new->next = graph[vertex_one].head;
    graph[vertex_one].head = edge_one_new;

    struct Edge_Fragment* edge_two_new = Edge_Create(vertex_one, weight);
    edge_two_new->next = graph[vertex_two].head;
    graph[vertex_two].head = edge_two_new;
}

int Edge_Get(struct Graph_Fragment* graph, int v1, int v2)
{
    struct Edge_Fragment* current = graph[v1].head;
    while (current != NULL)
    {
        if (current->direction == v2)
        {
            return current->weight;
        }
        current = current->next;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------

void Search_Base(struct Graph_Fragment* graph, int vertex_start, int vertex_count) 
{
    bool* vertex_path = (bool*) malloc(vertex_count * sizeof(bool));
    int* path = (int*) malloc(vertex_count * sizeof(int));
    int path_index = 0;

    struct Cycle_Fragment* cycles = (struct Cycle_Fragment*) malloc(vertex_count * sizeof(struct Cycle_Fragment));
    int cycle_count = 0;

    for (int i = 0; i < vertex_count; i++) 
    {
        vertex_path[i] = false;
    }

    for (int i = 0; i < vertex_count; i++) 
    {
        Search_Root(graph, i, -1, vertex_path, path, path_index, vertex_count, cycles, &cycle_count);
    }

    // Print cycles
    for (int i = 0; i < cycle_count; i++) 
    {
        printf("Cycle %d: ", i + 1);
        for (int j = 0; j < cycles[i].length; j++) 
        {
            printf("%d ", cycles[i].nodes[j]);
        }
        printf("with perimeter %d\n", cycles[i].perimeter);
    }

    printf("Total number of unique cycles: %d\n", cycle_count);
}

void Search_Root(struct Graph_Fragment* graph, int vertex, int vertex_parent, bool* vertex_path, int* path, int path_index, int vertex_count, struct Cycle_Fragment* cycles, int* cycle_count) 
{
    vertex_path[vertex] = true;

    struct Edge_Fragment* current = graph[vertex].head;

    while (current != NULL) 
    {
        int vertex_recursion = current->direction;

        if (!vertex_path[vertex_recursion])
        {
            Search_Cycles(graph, vertex_recursion, vertex, vertex_path, path, path_index, vertex_count, cycles, cycle_count);
            Search_Root(graph, vertex_recursion, vertex, vertex_path, path, path_index, vertex_count, cycles, cycle_count);
        }

        current = current->next;
    }

    vertex_path[vertex] = false;
}

void Search_Cycles(struct Graph_Fragment* graph, int vertex, int vertex_parent, bool* vertex_path, int* path, int path_index, int vertex_count, struct Cycle_Fragment* cycles, int* cycle_count)
{
    vertex_path[vertex] = true;
    path[path_index] = vertex;
    path_index++;

    struct Edge_Fragment* current = graph[vertex].head;

    while (current != NULL)
    {
        int vertex_recursion = current->direction;

        if (!vertex_path[vertex_recursion])
        {
            Search_Cycles(graph, vertex_recursion, vertex, vertex_path, path, path_index, vertex_count, cycles, cycle_count);
        }
        else if (vertex_recursion != vertex_parent) 
        {
            int cycle_start = -1;
            for (int i = 0; i < path_index; i++) 
            {
                if (path[i] == vertex_recursion) 
                {
                    cycle_start = i;
                    break;
                }
            }

            if (cycle_start != -1) 
            {
                int cycle_length = path_index - cycle_start;
                int perimeter = 0;
                for (int i = cycle_start; i < path_index - 1; i++) 
                {
                    perimeter += Edge_Get(graph, path[i], path[i + 1]);
                }
                perimeter += Edge_Get(graph, path[path_index - 1], path[cycle_start]);

                bool cycle_exists = false;
                for (int i = 0; i < *cycle_count; i++) 
                {
                    if (cycles[i].length == cycle_length) 
                    {
                        bool same_cycle = true;
                        for (int j = 0; j < cycle_length; j++) 
                        {
                            if (cycles[i].nodes[j] != path[(cycle_start + j) % cycle_length]) 
                            {
                                same_cycle = false;
                                break;
                            }
                        }
                        if (same_cycle) 
                        {
                            cycle_exists = true;
                            break;
                        }
                    }
                }

                if (!cycle_exists) 
                {
                    cycles[*cycle_count].nodes = (int*) malloc(cycle_length * sizeof(int));
                    for (int i = 0; i < cycle_length; i++) 
                    {
                        cycles[*cycle_count].nodes[i] = path[(cycle_start + i) % cycle_length];
                    }
                    cycles[*cycle_count].perimeter = perimeter;
                    cycles[*cycle_count].length = cycle_length;
                    (*cycle_count)++;
                }
            }
        }

        current = current->next;
    }

    vertex_path[vertex] = false;
    path_index--;
}

//--------------------------------------------------------------------------------------------------------------------------------

int main()
{
    printf("-----------------------------\n");

    int vertex_count = 5;

    struct Graph_Fragment* graph = Graph_Create(vertex_count);

    Edge_Add(graph, 0, 1, 10);
    Edge_Add(graph, 0, 2, 10);
    Edge_Add(graph, 1, 2, 10);
    Edge_Add(graph, 2, 3, 10);
    Edge_Add(graph, 3, 4, 10);
    Edge_Add(graph, 4, 0, 10);

    printf("Liste:\n");
    Graph_Print(graph, vertex_count);

    printf("\nCycle search:\n");
    Search_Base(graph, 0, vertex_count);

    printf("-----------------------------\n");

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------
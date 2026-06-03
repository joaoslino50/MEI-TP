#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXV 26

typedef struct AdjNode {
    int v;
    struct AdjNode *next;
} AdjNode;

typedef struct Edge {
    int u;
    int v;
} Edge;

typedef struct Component {
    int vertices[MAXV];
    int count;
} Component;

static AdjNode *graph[MAXV];

static int n;
static char root_label;

static int parent[MAXV];
static int height[MAXV];
static int disc[MAXV];
static int low[MAXV];
static bool articulation[MAXV];

static int timer = 0;

static Edge edge_stack[10000];
static int edge_top = 0;

static Component components[10000];
static int component_count = 0;

static int label_to_index(char c) {
    return c - 'a';
}

static char index_to_label(int i) {
    return (char)('a' + i);
}

static AdjNode *new_adj_node(int v) {
    AdjNode *node = malloc(sizeof(AdjNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->v = v;
    node->next = NULL;
    return node;
}

static void add_directed_edge_sorted(int u, int v) {
    AdjNode *node = new_adj_node(v);

    if (graph[u] == NULL || v < graph[u]->v) {
        node->next = graph[u];
        graph[u] = node;
        return;
    }

    AdjNode *cur = graph[u];

    while (cur->next != NULL && cur->next->v < v) {
        cur = cur->next;
    }

    /* Avoid duplicate edges. */
    if (cur->v == v || (cur->next != NULL && cur->next->v == v)) {
        free(node);
        return;
    }

    node->next = cur->next;
    cur->next = node;
}

static void add_edge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        fprintf(stderr, "Invalid vertex in edge: %c %c\n",
                index_to_label(u), index_to_label(v));
        exit(EXIT_FAILURE);
    }

    add_directed_edge_sorted(u, v);
    add_directed_edge_sorted(v, u);
}

static void push_edge(int u, int v) {
    edge_stack[edge_top].u = u;
    edge_stack[edge_top].v = v;
    edge_top++;
}

static bool component_has_vertex(Component *c, int v) {
    for (int i = 0; i < c->count; i++) {
        if (c->vertices[i] == v) {
            return true;
        }
    }

    return false;
}

static void component_add_vertex(Component *c, int v) {
    if (!component_has_vertex(c, v)) {
        c->vertices[c->count++] = v;
    }
}

/*
    Vertices inside each biconnected component are printed with deeper
    DFS vertices first. This matches the style of the example output.
*/
static void sort_component_vertices(Component *c) {
    for (int i = 0; i < c->count - 1; i++) {
        for (int j = i + 1; j < c->count; j++) {
            int a = c->vertices[i];
            int b = c->vertices[j];

            if (height[a] < height[b] ||
                (height[a] == height[b] && a > b)) {
                int tmp = c->vertices[i];
                c->vertices[i] = c->vertices[j];
                c->vertices[j] = tmp;
            }
        }
    }
}

static void create_biconnected_component_until(int stop_u, int stop_v) {
    Component c;
    c.count = 0;

    while (edge_top > 0) {
        Edge e = edge_stack[--edge_top];

        component_add_vertex(&c, e.u);
        component_add_vertex(&c, e.v);

        if (e.u == stop_u && e.v == stop_v) {
            break;
        }
    }

    sort_component_vertices(&c);
    components[component_count++] = c;
}

static void dfs(int u) {
    disc[u] = low[u] = ++timer;

    int children = 0;

    for (AdjNode *cur = graph[u]; cur != NULL; cur = cur->next) {
        int v = cur->v;

        if (disc[v] == 0) {
            children++;
            parent[v] = u;
            height[v] = height[u] + 1;

            push_edge(u, v);
            dfs(v);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (low[v] >= disc[u]) {
                if (parent[u] != u || children > 1) {
                    articulation[u] = true;
                }

                create_biconnected_component_until(u, v);
            }
        } else if (v != parent[u] && disc[v] < disc[u]) {
            push_edge(u, v);

            if (disc[v] < low[u]) {
                low[u] = disc[v];
            }
        }
    }
}

static void print_graph(void) {
    printf("Graph:\n");

    for (int i = 0; i < n; i++) {
        printf("[%c]:", index_to_label(i));

        AdjNode *cur = graph[i];

        if (cur != NULL) {
            printf(" ");
        }

        while (cur != NULL) {
            printf("%c", index_to_label(cur->v));

            if (cur->next != NULL) {
                printf(", ");
            }

            cur = cur->next;
        }

        printf("\n");
    }
}

static void print_parent(void) {
    printf("\nParent\n");

    for (int i = 0; i < n; i++) {
        printf("[%c]: %c\n", index_to_label(i), index_to_label(parent[i]));
    }
}

static void print_height(void) {
    printf("\nHeight\n");

    for (int i = 0; i < n; i++) {
        printf("[%c]: %d\n", index_to_label(i), height[i]);
    }
}

static void print_articulation_points(void) {
    printf("\nArticulation Points\n");

    for (int i = 0; i < n; i++) {
        printf("[%c]: %s\n", index_to_label(i),
               articulation[i] ? "True" : "False");
    }
}

static void print_biconnected_components(void) {
    printf("\nBiconnected Components\n");

    for (int i = 0; i < component_count; i++) {
        printf("{");

        for (int j = 0; j < components[i].count; j++) {
            printf("%c", index_to_label(components[i].vertices[j]));

            if (j + 1 < components[i].count) {
                printf(", ");
            }
        }

        printf("}\n");
    }
}

static void free_graph(void) {
    for (int i = 0; i < n; i++) {
        AdjNode *cur = graph[i];

        while (cur != NULL) {
            AdjNode *next = cur->next;
            free(cur);
            cur = next;
        }

        graph[i] = NULL;
    }
}

int main(void) {
    if (scanf("%d %c", &n, &root_label) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 1 || n > MAXV) {
        fprintf(stderr, "Number of vertices must be between 1 and 26\n");
        return EXIT_FAILURE;
    }

    int root = label_to_index(root_label);

    if (root < 0 || root >= n) {
        fprintf(stderr, "Invalid root vertex: %c\n", root_label);
        return EXIT_FAILURE;
    }

    char a;
    char b;

    while (scanf(" %c %c", &a, &b) == 2) {
        int u = label_to_index(a);
        int v = label_to_index(b);

        add_edge(u, v);
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        height[i] = 0;
        disc[i] = 0;
        low[i] = 0;
        articulation[i] = false;
    }

    /*
        DFS starts from the requested root.

        If the graph is disconnected, the remaining components are also
        explored afterward so that every vertex gets parent, height,
        articulation, and biconnected-component information.
    */
    parent[root] = root;
    height[root] = 0;
    dfs(root);

    for (int i = 0; i < n; i++) {
        if (disc[i] == 0) {
            parent[i] = i;
            height[i] = 0;
            dfs(i);
        }
    }

    print_graph();
    print_parent();
    print_height();
    print_articulation_points();
    print_biconnected_components();

    free_graph();

    return EXIT_SUCCESS;
}

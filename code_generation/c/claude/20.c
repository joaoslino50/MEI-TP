#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 128
#define MAX_LABEL     64

/* ── Adjacency list ─────────────────────────────────────────────────────── */
typedef struct AdjNode {
    int            vertex;
    struct AdjNode *next;
} AdjNode;

/* ── Edge stack for biconnected components ──────────────────────────────── */
typedef struct EdgeNode {
    int u, v;
    struct EdgeNode *next;
} EdgeNode;

/* ── Graph ──────────────────────────────────────────────────────────────── */
int      n;                          /* number of vertices                  */
char     label[MAX_VERTICES][MAX_LABEL]; /* index → label                  */
int      labelIndex[MAX_VERTICES];   /* quick lookup: unused here directly  */
AdjNode *adj[MAX_VERTICES];          /* adjacency lists                     */

/* ── DFS results ────────────────────────────────────────────────────────── */
int parent[MAX_VERTICES];
int height[MAX_VERTICES];
int disc[MAX_VERTICES];              /* discovery time                      */
int low[MAX_VERTICES];               /* low value                           */
int articulationPoint[MAX_VERTICES]; /* bool                                */
int visited[MAX_VERTICES];
int timer_g = 0;

/* ── BCC edge stack ─────────────────────────────────────────────────────── */
EdgeNode *edgeStack       = NULL;
int       bccCount        = 0;

/* ── BCC storage: each component is a sorted array of vertex indices ────── */
typedef struct {
    int *verts;
    int  size;
} BCC;

BCC bccs[MAX_VERTICES * 2];

/* ── Helpers ─────────────────────────────────────────────────────────────── */
/* Return vertex index for a label, creating it if needed */
int getOrAddVertex(const char *lbl) {
    for (int i = 0; i < n; i++)
        if (strcmp(label[i], lbl) == 0) return i;
    /* label not found — shouldn't happen after pre-scan, but keep safe */
    strcpy(label[n], lbl);
    return n++;
}

/* Insert v into u's adjacency list, keeping it sorted */
void addEdge(int u, int v) {
    AdjNode **cur = &adj[u];
    while (*cur && strcmp(label[(*cur)->vertex], label[v]) < 0)
        cur = &(*cur)->next;
    /* avoid duplicate */
    if (*cur && (*cur)->vertex == v) return;
    AdjNode *node = malloc(sizeof(AdjNode));
    node->vertex = v;
    node->next   = *cur;
    *cur         = node;
}

/* Push edge onto the stack */
void pushEdge(int u, int v) {
    EdgeNode *e = malloc(sizeof(EdgeNode));
    e->u = u; e->v = v;
    e->next   = edgeStack;
    edgeStack = e;
}

/* Pop and collect a BCC until (and including) edge (u,v) */
void popBCC(int u, int v) {
    /* first pass: count unique vertices */
    int seen[MAX_VERTICES] = {0};
    EdgeNode *e = edgeStack;
    int collecting = 1;
    while (e && collecting) {
        seen[e->u] = seen[e->v] = 1;
        if (e->u == u && e->v == v) collecting = 0;
        e = e->next;
    }

    /* count */
    int cnt = 0;
    for (int i = 0; i < MAX_VERTICES; i++) if (seen[i]) cnt++;

    bccs[bccCount].verts = malloc(cnt * sizeof(int));
    bccs[bccCount].size  = 0;

    for (int i = 0; i < MAX_VERTICES; i++)
        if (seen[i]) bccs[bccCount].verts[bccs[bccCount].size++] = i;

    /* pop edges off the stack */
    collecting = 1;
    while (edgeStack && collecting) {
        EdgeNode *tmp = edgeStack;
        edgeStack = edgeStack->next;
        if (tmp->u == u && tmp->v == v) collecting = 0;
        free(tmp);
    }

    bccCount++;
}

/* ── DFS ─────────────────────────────────────────────────────────────────── */
void dfs(int u, int par) {
    visited[u] = 1;
    disc[u] = low[u] = timer_g++;
    int childCount = 0;

    for (AdjNode *nb = adj[u]; nb; nb = nb->next) {
        int v = nb->vertex;
        if (!visited[v]) {
            childCount++;
            parent[v] = u;
            height[v] = height[u] + 1;
            pushEdge(u, v);
            dfs(v, u);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            /* articulation point check */
            if (par == u) { /* u is root */
                if (childCount > 1) articulationPoint[u] = 1;
            } else {
                if (low[v] >= disc[u]) articulationPoint[u] = 1;
            }

            /* BCC: a new component ends when low[v] >= disc[u] */
            if (low[v] >= disc[u])
                popBCC(u, v);

        } else if (v != par && disc[v] < disc[u]) {
            /* back edge */
            pushEdge(u, v);
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

/* Comparator for qsort on vertex labels */
static int cmpVerts(const void *a, const void *b) {
    return strcmp(label[*(const int *)a], label[*(const int *)b]);
}

/* ── Main ─────────────────────────────────────────────────────────────────── */
int main(void) {
    char line[256];

    /* ── Read first line: n and root label ── */
    int  nCount;
    char rootLabel[MAX_LABEL];
    if (!fgets(line, sizeof(line), stdin)) return 1;
    sscanf(line, "%d %s", &nCount, rootLabel);

    n = 0; /* will be filled as we discover labels */

    /* We need to pre-register vertex labels in the order they will appear
     * alphabetically, but the spec just says n vertices exist; we discover
     * them from edges. Pre-create n slots with empty labels so getOrAddVertex
     * works correctly. We will actually build labels on-the-fly. */

    /* ── Read edges, collect labels ── */
    typedef struct { char a[MAX_LABEL]; char b[MAX_LABEL]; } RawEdge;
    RawEdge rawEdges[1024];
    int     edgeCount = 0;

    while (fgets(line, sizeof(line), stdin)) {
        char ua[MAX_LABEL], ub[MAX_LABEL];
        if (sscanf(line, "%s %s", ua, ub) == 2) {
            strcpy(rawEdges[edgeCount].a, ua);
            strcpy(rawEdges[edgeCount].b, ub);
            edgeCount++;
            /* register labels */
            int found_a = 0, found_b = 0;
            for (int i = 0; i < n; i++) {
                if (strcmp(label[i], ua) == 0) found_a = 1;
                if (strcmp(label[i], ub) == 0) found_b = 1;
            }
            if (!found_a) strcpy(label[n++], ua);
            if (!found_b) {
                /* re-check after possible n++ */
                int fb2 = 0;
                for (int i = 0; i < n; i++) if (strcmp(label[i], ub) == 0) fb2 = 1;
                if (!fb2) strcpy(label[n++], ub);
            }
        }
    }

    /* Also register root if it somehow had no edges */
    {
        int found = 0;
        for (int i = 0; i < n; i++) if (strcmp(label[i], rootLabel) == 0) { found = 1; break; }
        if (!found) strcpy(label[n++], rootLabel);
    }

    /* Sort label array alphabetically and rebuild index */
    /* Build a sorted index array */
    int sortedIdx[MAX_VERTICES];
    for (int i = 0; i < n; i++) sortedIdx[i] = i;
    /* Bubble sort labels alphabetically (n is small) */
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(label[sortedIdx[i]], label[sortedIdx[j]]) > 0) {
                int tmp = sortedIdx[i]; sortedIdx[i] = sortedIdx[j]; sortedIdx[j] = tmp;
            }
    /* Re-index: assign positions 0..n-1 in alphabetical order */
    char newLabel[MAX_VERTICES][MAX_LABEL];
    for (int i = 0; i < n; i++) strcpy(newLabel[i], label[sortedIdx[i]]);
    for (int i = 0; i < n; i++) strcpy(label[i], newLabel[i]);

    /* ── Build adjacency lists ── */
    for (int i = 0; i < edgeCount; i++) {
        int u = getOrAddVertex(rawEdges[i].a);
        int v = getOrAddVertex(rawEdges[i].b);
        addEdge(u, v);
        addEdge(v, u);
    }

    /* ── Print Graph ── */
    printf("Graph:\n");
    for (int i = 0; i < n; i++) {
        printf("[%s]:", label[i]);
        int first = 1;
        for (AdjNode *nb = adj[i]; nb; nb = nb->next) {
            printf("%s %s", first ? "" : ",", label[nb->vertex]);
            first = 0;
        }
        printf("\n");
    }

    /* ── DFS ── */
    int root = getOrAddVertex(rootLabel);
    for (int i = 0; i < n; i++) { parent[i] = i; height[i] = 0; visited[i] = 0; articulationPoint[i] = 0; }
    height[root] = 0;
    dfs(root, root);

    /* Print Parent */
    printf("\nParent\n");
    for (int i = 0; i < n; i++)
        printf("[%s]: %s\n", label[i], label[parent[i]]);

    /* Print Height */
    printf("\nHeight\n");
    for (int i = 0; i < n; i++)
        printf("[%s]: %d\n", label[i], height[i]);

    /* Print Articulation Points */
    printf("\nArticulation Points\n");
    for (int i = 0; i < n; i++)
        printf("[%s]: %s\n", label[i], articulationPoint[i] ? "True" : "False");

    /* Print BCCs — sort vertices within each component, then print */
    printf("\nBiconnected Components\n");
    for (int c = 0; c < bccCount; c++) {
        qsort(bccs[c].verts, bccs[c].size, sizeof(int), cmpVerts);
        printf("{");
        for (int j = 0; j < bccs[c].size; j++) {
            if (j) printf(", ");
            printf("%s", label[bccs[c].verts[j]]);
        }
        printf("}\n");
        free(bccs[c].verts);
    }

    return 0;
}

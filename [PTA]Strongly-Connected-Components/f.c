/***************************
 * non-recursive tarjan algorithm
 *****************************/
typedef int Vertex;
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
    typedef enum
    {
        false,
        true
    } bool;

    // time, dfn and low in tarjan
    int visited_time;
    int dfs_num[G->NumOfVertices];
    int dfs_low[G->NumOfVertices];

    // stack in tarjan and a bool array indicates which vertex is in the stack
    Vertex tarjan_stack[G->NumOfVertices];
    int tarjan_stack_top;
    bool is_in_stack[G->NumOfVertices];

    // non recursive dfs needs a stack
    Vertex dfs_stack[G->NumOfVertices];
    int dfs_stack_top;

    // record each vertex's reachable vertex which are being processed,
    // such as updating its dfs_low when just got back from its p_next
    // details are discussed in the /* judgement */ sector
    PtrToVNode p_next[G->NumOfVertices];

    int i;
    Vertex t;
    
    /* initialization */
    for(i = 0; i < G->NumOfVertices; i++)
    {
        dfs_num[i] = dfs_low[i] = 0;
        is_in_stack[i] = false;
        p_next[i] = G->Array[i];
    }
    visited_time = 0;
    tarjan_stack_top = -1;
    dfs_stack_top = -1;
    /* initialization */

    /* tarjan */
    for (i = 0; i < G->NumOfVertices; i++)
    {
        if(dfs_num[i] == 0)
        {
            dfs_stack[++dfs_stack_top] = i;
            while(dfs_stack_top >= 0)
            {
                t = dfs_stack[dfs_stack_top];

                // first visit of this vertex
                // initialize its time stamp and push it into tarjan_stack
                if(dfs_num[t] == 0)
                {
                    tarjan_stack[++tarjan_stack_top] = t;
                    is_in_stack[t] = true;
                    dfs_num[t] = dfs_low[t] = ++visited_time;
                }

                /* judgement */
                // p_next array has been initialized in /* initialization */

                // we get a reachable vertex and it's not been visited
                // push it into dfs_stack, don't forward the p_next because we need it to update this vertex's dfs_low
                if(p_next[t] != NULL && dfs_num[p_next[t]->Vert] == 0)
                {
                    dfs_stack[++dfs_stack_top] = p_next[t]->Vert;
                }

                // we get a reachable vertex and it has been visited and in the tarjan_stack
                // it means this is either an ancestor vertex or a vertex that we back from
                // so update its dfs_low and forward p_next to the next reachable vertex
                else if(p_next[t] != NULL && dfs_num[p_next[t]->Vert] != 0 && is_in_stack[p_next[t]->Vert] == true)
                {
                    dfs_low[t] = dfs_low[t] < dfs_low[p_next[t]->Vert] ? dfs_low[t] : dfs_low[p_next[t]->Vert];
                    p_next[t] = p_next[t]->Next;
                }

                // we get a reachable vertex and it has been visited and not in tarjan stack
                // it means the vertex has found its SCC
                // just forward p_next to the next reachable vertex
                // this sector and previous sector have the same function of the "for" loop in recursive tarjan
                else if(p_next[t] != NULL && dfs_num[p_next[t]->Vert] != 0 && is_in_stack[p_next[t]->Vert] == false)
                {
                    p_next[t] = p_next[t]->Next;
                }

                // for this situation, there is no vertices reachable but not visited
                // if dfs_num == dfs_low, we get a SCC
                // finally, pop out from dfs_stack because we have finished its traversal
                // this sector have the same function of "if(dfn == low)" block
                else
                {
                    if(dfs_num[t] == dfs_low[t])
                    {
                        while(tarjan_stack[tarjan_stack_top] != t)
                        {
                            visit(tarjan_stack[tarjan_stack_top]);
                            is_in_stack[tarjan_stack[tarjan_stack_top]] = false;
                            tarjan_stack_top--;
                        }
                        visit(tarjan_stack[tarjan_stack_top]);
                        is_in_stack[tarjan_stack[tarjan_stack_top]] = false;
                        tarjan_stack_top--;
                        printf("\n");
                    }
                    dfs_stack_top--;
                }
                /* judgement */
            }
        }
    }
    /* tarjan */
}
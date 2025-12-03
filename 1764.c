#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, w; } Edge;
Edge e[400000];
int parent[400000];

int find(int x){ return parent[x]==x ? x : (parent[x]=find(parent[x])); }
int cmp(const void *a,const void *b){ return ((Edge*)a)->w - ((Edge*)b)->w; }

int main(){
    int n, m;
    while(scanf("%d %d",&n,&m), n){
        for(int i=0;i<n;i++) parent[i]=i;
        for(int i=0;i<m;i++) scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
        qsort(e,m,sizeof(Edge),cmp);
        long long sum=0;
        for(int i=0;i<m;i++){
            int a=find(e[i].u), b=find(e[i].v);
            if(a!=b) parent[a]=b, sum+=e[i].w;
        }
        printf("%lld\n",sum);
    }
    return 0;
}

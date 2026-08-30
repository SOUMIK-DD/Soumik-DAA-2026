#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

/* ---------- 1. UNSORTED ARRAY ---------- */

int ua[MAX], un = 0;

void ua_insert(int x) {
    ua[un++] = x;
}

int ua_search(int x) {
    for(int i=0;i<un;i++)
        if(ua[i]==x) return i;
    return -1;
}

void ua_delete(int x) {
    int p=ua_search(x);
    if(p!=-1)
        ua[p]=ua[--un];
}

int ua_min() {
    int p=0;
    for(int i=1;i<un;i++)
        if(ua[i]<ua[p]) p=i;
    return ua[p];
}

int ua_max() {
    int p=0;
    for(int i=1;i<un;i++)
        if(ua[i]>ua[p]) p=i;
    return ua[p];
}

int ua_pred(int x) {
    int p=-1;
    for(int i=0;i<un;i++)
        if(ua[i]<x && (p==-1 || ua[i]>ua[p])) p=i;
    return p==-1 ? -1 : ua[p];
}

int ua_succ(int x) {
    int p=-1;
    for(int i=0;i<un;i++)
        if(ua[i]>x && (p==-1 || ua[i]<ua[p])) p=i;
    return p==-1 ? -1 : ua[p];
}


/* ---------- 2. SORTED ARRAY ---------- */

int sa[MAX], sn=0;

void sa_insert(int x) {
    int i=sn-1;

    while(i>=0 && sa[i]>x) {
        sa[i+1]=sa[i];
        i--;
    }

    sa[i+1]=x;
    sn++;
}

int sa_search(int x) {
    int l=0,r=sn-1;

    while(l<=r) {
        int m=(l+r)/2;

        if(sa[m]==x) return m;
        if(sa[m]<x) l=m+1;
        else r=m-1;
    }

    return -1;
}

void sa_delete(int x) {
    int p=sa_search(x);

    if(p!=-1) {
        for(int i=p;i<sn-1;i++)
            sa[i]=sa[i+1];
        sn--;
    }
}

int sa_min() {
    return sa[0];
}

int sa_max() {
    return sa[sn-1];
}

int sa_pred(int x) {
    int p=-1;

    for(int i=0;i<sn && sa[i]<x;i++)
        p=i;

    return p==-1 ? -1 : sa[p];
}

int sa_succ(int x) {
    for(int i=0;i<sn;i++)
        if(sa[i]>x) return sa[i];

    return -1;
}


/* ---------- 3. SINGLY LINKED UNSORTED ---------- */

typedef struct SNode {
    int data;
    struct SNode *next;
} SNode;

SNode *su=NULL;

void su_insert(int x) {
    SNode *p=malloc(sizeof(SNode));

    p->data=x;
    p->next=su;
    su=p;
}

SNode* su_search(int x) {
    for(SNode *p=su;p;p=p->next)
        if(p->data==x) return p;

    return NULL;
}

void su_delete(int x) {
    SNode *p=su,*q=NULL;

    while(p && p->data!=x) {
        q=p;
        p=p->next;
    }

    if(p) {
        if(q) q->next=p->next;
        else su=p->next;

        free(p);
    }
}

int su_min() {
    int m=su->data;

    for(SNode *p=su;p;p=p->next)
        if(p->data<m) m=p->data;

    return m;
}

int su_max() {
    int m=su->data;

    for(SNode *p=su;p;p=p->next)
        if(p->data>m) m=p->data;

    return m;
}

int su_pred(int x) {
    int m=-1;

    for(SNode *p=su;p;p=p->next)
        if(p->data<x && p->data>m)
            m=p->data;

    return m;
}

int su_succ(int x) {
    int m=-1;

    for(SNode *p=su;p;p=p->next)
        if(p->data>x && (m==-1 || p->data<m))
            m=p->data;

    return m;
}


/* ---------- 4. SINGLY LINKED SORTED ---------- */

SNode *ss=NULL;

void ss_insert(int x) {
    SNode *p=malloc(sizeof(SNode));
    p->data=x;

    if(!ss || x<ss->data) {
        p->next=ss;
        ss=p;
        return;
    }

    SNode *q=ss;

    while(q->next && q->next->data<x)
        q=q->next;

    p->next=q->next;
    q->next=p;
}

SNode* ss_search(int x) {
    for(SNode *p=ss;p && p->data<=x;p=p->next)
        if(p->data==x) return p;

    return NULL;
}

void ss_delete(int x) {
    SNode *p=ss,*q=NULL;

    while(p && p->data<x) {
        q=p;
        p=p->next;
    }

    if(p && p->data==x) {
        if(q) q->next=p->next;
        else ss=p->next;

        free(p);
    }
}

int ss_min() {
    return ss->data;
}

int ss_max() {
    SNode *p=ss;

    while(p->next)
        p=p->next;

    return p->data;
}

int ss_pred(int x) {
    int m=-1;

    for(SNode *p=ss;p && p->data<x;p=p->next)
        m=p->data;

    return m;
}

int ss_succ(int x) {
    for(SNode *p=ss;p;p=p->next)
        if(p->data>x)
            return p->data;

    return -1;
}


/* ---------- 5. DOUBLY LINKED UNSORTED ---------- */

typedef struct DNode {
    int data;
    struct DNode *prev,*next;
} DNode;

DNode *du=NULL;

void du_insert(int x) {
    DNode *p=malloc(sizeof(DNode));

    p->data=x;
    p->prev=NULL;
    p->next=du;

    if(du)
        du->prev=p;

    du=p;
}

DNode* du_search(int x) {
    for(DNode *p=du;p;p=p->next)
        if(p->data==x)
            return p;

    return NULL;
}

void du_delete(int x) {
    DNode *p=du_search(x);

    if(p) {
        if(p->prev)
            p->prev->next=p->next;
        else
            du=p->next;

        if(p->next)
            p->next->prev=p->prev;

        free(p);
    }
}

int du_min() {
    int m=du->data;

    for(DNode *p=du;p;p=p->next)
        if(p->data<m)
            m=p->data;

    return m;
}

int du_max() {
    int m=du->data;

    for(DNode *p=du;p;p=p->next)
        if(p->data>m)
            m=p->data;

    return m;
}

int du_pred(int x) {
    int m=-1;

    for(DNode *p=du;p;p=p->next)
        if(p->data<x && p->data>m)
            m=p->data;

    return m;
}

int du_succ(int x) {
    int m=-1;

    for(DNode *p=du;p;p=p->next)
        if(p->data>x && (m==-1 || p->data<m))
            m=p->data;

    return m;
}


/* ---------- 6. DOUBLY LINKED SORTED ---------- */

DNode *ds=NULL;

void ds_insert(int x) {
    DNode *p=malloc(sizeof(DNode));
    p->data=x;

    if(!ds || x<ds->data) {
        p->prev=NULL;
        p->next=ds;

        if(ds)
            ds->prev=p;

        ds=p;
        return;
    }

    DNode *q=ds;

    while(q->next && q->next->data<x)
        q=q->next;

    p->next=q->next;
    p->prev=q;

    if(q->next)
        q->next->prev=p;

    q->next=p;
}

DNode* ds_search(int x) {
    for(DNode *p=ds;p && p->data<=x;p=p->next)
        if(p->data==x)
            return p;

    return NULL;
}

void ds_delete(int x) {
    DNode *p=ds_search(x);

    if(p) {
        if(p->prev)
            p->prev->next=p->next;
        else
            ds=p->next;

        if(p->next)
            p->next->prev=p->prev;

        free(p);
    }
}

int ds_min() {
    return ds->data;
}

int ds_max() {
    DNode *p=ds;

    while(p->next)
        p=p->next;

    return p->data;
}

int ds_pred(int x) {
    DNode *p=ds,*last=NULL;

    while(p && p->data<x) {
        last=p;
        p=p->next;
    }

    return last ? last->data : -1;
}

int ds_succ(int x) {
    DNode *p=ds_search(x);

    if(p && p->next)
        return p->next->data;

    return -1;
}


/* ========================================================= */
/*                         MAIN                              */
/* ========================================================= */

int main() {

    int a[]={50,20,80,10,40,70,90};
    int n=7;
    int x=50;

    /* Insert data into all structures */

    for(int i=0;i<n;i++) {
        ua_insert(a[i]);
        sa_insert(a[i]);
        su_insert(a[i]);
        ss_insert(a[i]);
        du_insert(a[i]);
        ds_insert(a[i]);
    }


    /* ---------- OPERATIONS OUTPUT ---------- */

    printf("\n========== SEARCH ==========\n");

    printf("Unsorted Array  : %s\n",
           ua_search(x)!=-1 ? "Found" : "Not Found");

    printf("Sorted Array    : %s\n",
           sa_search(x)!=-1 ? "Found" : "Not Found");

    printf("Singly Unsorted : %s\n",
           su_search(x) ? "Found" : "Not Found");

    printf("Singly Sorted   : %s\n",
           ss_search(x) ? "Found" : "Not Found");

    printf("Doubly Unsorted : %s\n",
           du_search(x) ? "Found" : "Not Found");

    printf("Doubly Sorted   : %s\n",
           ds_search(x) ? "Found" : "Not Found");


    printf("\n========== MINIMUM / MAXIMUM ==========\n");

    printf("Unsorted Array  : Min=%d Max=%d\n",
           ua_min(),ua_max());

    printf("Sorted Array    : Min=%d Max=%d\n",
           sa_min(),sa_max());

    printf("Singly Unsorted : Min=%d Max=%d\n",
           su_min(),su_max());

    printf("Singly Sorted   : Min=%d Max=%d\n",
           ss_min(),ss_max());

    printf("Doubly Unsorted : Min=%d Max=%d\n",
           du_min(),du_max());

    printf("Doubly Sorted   : Min=%d Max=%d\n",
           ds_min(),ds_max());


    printf("\n========== PREDECESSOR / SUCCESSOR ==========\n");

    printf("Unsorted Array  : Pred=%d Succ=%d\n",
           ua_pred(x),ua_succ(x));

    printf("Sorted Array    : Pred=%d Succ=%d\n",
           sa_pred(x),sa_succ(x));

    printf("Singly Unsorted : Pred=%d Succ=%d\n",
           su_pred(x),su_succ(x));

    printf("Singly Sorted   : Pred=%d Succ=%d\n",
           ss_pred(x),ss_succ(x));

    printf("Doubly Unsorted : Pred=%d Succ=%d\n",
           du_pred(x),du_succ(x));

    printf("Doubly Sorted   : Pred=%d Succ=%d\n",
           ds_pred(x),ds_succ(x));


    /* ---------- DELETE ---------- */

    printf("\n========== DELETE ==========\n");

    printf("Deleting %d from all structures...\n",x);

    ua_delete(x);
    sa_delete(x);
    su_delete(x);
    ss_delete(x);
    du_delete(x);
    ds_delete(x);

    printf("Deletion completed.\n");


    /* ===================================================== */
    /*              COMPLEXITY COMPARISON                    */
    /* ===================================================== */

    printf("\n\n===============================================================\n");
    printf("              WORST CASE COMPLEXITY COMPARISON\n");
    printf("===============================================================\n");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Operation","UA","SA","SU","SS","DU","DS");

    printf("---------------------------------------------------------------\n");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Search",
           "O(n)","O(logn)","O(n)","O(n)","O(n)","O(n)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Insert",
           "O(1)","O(n)","O(1)","O(n)","O(1)","O(n)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Delete",
           "O(1)*","O(n)","O(n)","O(n)","O(1)*","O(n)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Minimum",
           "O(n)","O(1)","O(n)","O(1)","O(n)","O(1)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Maximum",
           "O(n)","O(1)","O(n)","O(n)","O(n)","O(n)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Predecessor",
           "O(n)","O(n)","O(n)","O(n)","O(n)","O(n)");

    printf("%-15s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Successor",
           "O(n)","O(n)","O(n)","O(n)","O(n)","O(n)");

    printf("===============================================================\n");

    printf("\nUA = Unsorted Array\n");
    printf("SA = Sorted Array\n");
    printf("SU = Singly Linked Unsorted\n");
    printf("SS = Singly Linked Sorted\n");
    printf("DU = Doubly Linked Unsorted\n");
    printf("DS = Doubly Linked Sorted\n");
    printf("* Delete is O(1) when pointer/index to item is already given.\n");


    /* ===================================================== */
    /*                GNUPLOT DATA GENERATION                */
    /* ===================================================== */

      /* ---------- GNUPLOT DATA ---------- */

    /* ---------- GNUPLOT DATA ---------- */

FILE *f = fopen("operations.dat","w");

fprintf(f,"# n Search_UA Search_SA Search_SU Search_SS Search_DU Search_DS ");
fprintf(f,"Insert_UA Insert_SA Insert_SU Insert_SS Insert_DU Insert_DS ");
fprintf(f,"Delete_UA Delete_SA Delete_SU Delete_SS Delete_DU Delete_DS ");
fprintf(f,"Min_UA Min_SA Min_SU Min_SS Min_DU Min_DS ");
fprintf(f,"Max_UA Max_SA Max_SU Max_SS Max_DU Max_DS ");
fprintf(f,"Pred_UA Pred_SA Pred_SU Pred_SS Pred_DU Pred_DS ");
fprintf(f,"Succ_UA Succ_SA Succ_SU Succ_SS Succ_DU Succ_DS\n");

for(int n=10;n<=1000;n+=10) {

    int lg=(int)(log2(n)+1);

    /* Search */
    int a1=n,b1=lg,c1=n,d1=n,e1=n,g1=n;

    /* Insert */
    int a2=1,b2=n,c2=1,d2=n,e2=1,g2=n;

    /* Delete */
    int a3=n,b3=n,c3=n,d3=n,e3=n,g3=n;

    /* Minimum */
    int a4=n,b4=1,c4=n,d4=1,e4=n,g4=1;

    /* Maximum */
    int a5=n,b5=1,c5=n,d5=n,e5=n,g5=n;

    /* Predecessor */
    int a6=n,b6=n,c6=n,d6=n,e6=n,g6=n;

    /* Successor */
    int a7=n,b7=n,c7=n,d7=n,e7=n,g7=n;

    fprintf(f,
    "%d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d "
    "%d %d %d %d %d %d\n",
    n,
    a1,b1,c1,d1,e1,g1,
    a2,b2,c2,d2,e2,g2,
    a3,b3,c3,d3,e3,g3,
    a4,b4,c4,d4,e4,g4,
    a5,b5,c5,d5,e5,g5,
    a6,b6,c6,d6,e6,g6,
    a7,b7,c7,d7,e7,g7);
}

fclose(f);


/* ---------- GNUPLOT SCRIPT ---------- */

f=fopen("plot.gp","w");

fprintf(f,
"set grid\n"
"set xlabel 'Number of elements (n)'\n"
"set ylabel 'Operation Count'\n"
"set key outside\n"
"set xrange [0:1000]\n\n"

/* SEARCH */
"set title 'Search Operation'\n"
"plot 'operations.dat' using 1:2 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:3 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:4 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:5 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:6 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:7 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* INSERT */
"set title 'Insert Operation'\n"
"plot 'operations.dat' using 1:8 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:9 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:10 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:11 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:12 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:13 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* DELETE */
"set title 'Delete Operation'\n"
"plot 'operations.dat' using 1:14 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:15 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:16 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:17 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:18 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:19 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* MINIMUM */
"set title 'Minimum Operation'\n"
"plot 'operations.dat' using 1:20 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:21 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:22 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:23 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:24 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:25 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* MAXIMUM */
"set title 'Maximum Operation'\n"
"plot 'operations.dat' using 1:26 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:27 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:28 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:29 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:30 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:31 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* PREDECESSOR */
"set title 'Predecessor Operation'\n"
"plot 'operations.dat' using 1:32 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:33 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:34 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:35 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:36 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:37 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n"

/* SUCCESSOR */
"set title 'Successor Operation'\n"
"plot 'operations.dat' using 1:38 with lines lw 2 title 'Unsorted Array',"
"'operations.dat' using 1:39 with lines lw 2 title 'Sorted Array',"
"'operations.dat' using 1:40 with lines lw 2 title 'Singly Unsorted',"
"'operations.dat' using 1:41 with lines lw 2 title 'Singly Sorted',"
"'operations.dat' using 1:42 with lines lw 2 title 'Doubly Unsorted',"
"'operations.dat' using 1:43 with lines lw 2 title 'Doubly Sorted'\n"
"pause -1\n");

fclose(f);

printf("\nCreated operations.dat and plot.gp\n");

return 0;
}
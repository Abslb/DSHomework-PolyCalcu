#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<F:\shangji\polycalcus.h>
//#define DEBUG 1
typedef struct X{
    double para;
    int index;
    struct X* next;
}xiang;

typedef struct Y{
    int num;
    xiang *cont;
    struct Y*next;
}poly; 

poly head,*end;
//They are initiallized in the main function.

void showerrs(int k){
    switch(k){
        case -2:printf("ERROR: An OVERFLOW has Happened.\n");break;
        default:break;
    }
    return;
}
//below: two basic item operations
xiang* createxiang(int index,double para){
    //creating one of the items of the polymer.
    xiang* x;
    x=(xiang*)malloc(sizeof(xiang));
    if(x==NULL){
        return NULL;
        //the overflow will be proccessed, but not here.
    }
    x->index=index;
    x->para=para;
    x->next=NULL;
    return x;
}

xiang* destroyxiang(xiang* x){
    //destroying an item and returning its next
    xiang *t;
    t=x->next;
    free(x);
    return t;
}

//below: the basic polymer operations
int manage(poly *p){
    //Simplify and manage the polymer. Make it sequenced from x^1 to x^5.
    xiang *t,*px,*px2,*pn;
    for(px=(p->cont);px->next!=NULL;px=px->next){
        #ifdef DEBUG
        printf("%lfx^%d is processed.\n",(px->next)->para,(px->next)->index);
        #endif
        if(((px->next)->para>0?(px->next)->para:-(px->next)->para)<1E-5){
            t=destroyxiang(px->next);
            (p->cont)->index=(p->cont)->index-1;//l--
            px->next=t;if(px->next==NULL)break;
            continue;
        }
        for(px2=px->next;px2->next!=NULL;){
            if(px2==NULL)break;
            #ifdef DEBUG
            printf("%lfx^%d is compared.\n",(px2->next)->para,(px2->next)->index);
            #endif
            if((px2->next)->index<(px->next)->index){
                t=px->next;
                px->next=px2->next;
                px2->next=(px2->next)->next;
                (px->next)->next=t;
                if(px2->next==NULL)break;
                else continue;
            }
            if((px2->next)->index==(px->next)->index){
                (px->next)->para=(px2->next)->para+(px->next)->para;
                t=destroyxiang(px2->next);
                (p->cont)->index=(p->cont)->index-1;//l--
                px2->next=t;
                if(px2->next==NULL)break;
                else continue;
            }
            px2=px2->next;
        }
    }
    return 0;
}

int creater(poly *(*rtr)){
    //create a polymer and put it into rtr
    poly* destroypoly(poly*,int);
    poly *t;
    xiang *px,*tx;
    double pr;
    int idx,l=0;
    t=(poly*)malloc(sizeof(poly));
    if(t==NULL){
        showerrs(-2);
        return -2;
    }
    t->cont=(xiang*)malloc(sizeof(xiang));
    if(t->cont==NULL){
        showerrs(-2);
        return -2;
    }
    (t->cont)->next=NULL;
    t->next=NULL;
    t->num=end->num+1;
    px=t->cont;
    printf("The input will end when you input an coefficient of 0.\n");
    while(1){
        printf("Please input a coefficient:");
        readdoub(&pr);
        if(pr==0)break;
        printf("Please input the index:");
        readint(&idx);
        #ifdef DEBUG
        printf("%lfx^%d is inputed.\n",pr,idx);
        #endif
        tx=createxiang(idx,pr);
        l++;
        if(tx==NULL){
            showerrs(-2);
            destroypoly(t,1);
            return -2;
        }
        px->next=tx;
        px=tx;
    }
    *rtr=t;
    end->next=t;
    end=t;
    (t->cont)->index=l;
    //the lenth is stored in the index of the head pointer.
    manage(*rtr);
    return 0;
}

int shower(poly *toshow){
    //show a polymer
    xiang *px;
    #ifdef DEBUG
    printf("True.\n");
    printf("%d\n",toshow);
    #endif
    for(px=(toshow->cont);px->next!=NULL;px=px->next){
        printf("(%lfx^%d)%c",(px->next)->para,(px->next)->index,((px->next)->next!=NULL)?'+':'\n');
    }
    if((toshow->cont)->next==NULL){
        printf("This is 0, or say an empty polymer.\n");
    }
    return 0;
}

int addmaking(poly *a,poly *b,poly *(*rtr)){
    //add a and b in a new polymer, rtr
    poly *t;
    xiang *px,*pxa,*pxb,*tx;
    double pr;
    int idx,l=0;
    t=(poly*)malloc(sizeof(poly));
    if(t==NULL){
        showerrs(-2);
        return -2;
    }
    t->cont=(xiang*)malloc(sizeof(xiang));
    if(t->cont==NULL){
        showerrs(-2);
        return -2;
    }
    (t->cont)->next=NULL;
    t->next=NULL;
    t->num=end->num+1;
    px=t->cont;pxa=a->cont;pxb=b->cont;
    pxa=pxa->next;pxb=pxb->next;
    while(pxa!=NULL){
        tx=createxiang(pxa->index,pxa->para);
        pxa=pxa->next;
        if(tx==NULL){
            showerrs(-2);
            return -2;
        }
        px->next=tx;
        px=tx;
        l++;
    }
    while(pxb!=NULL){
        tx=createxiang(pxb->index,pxb->para);
        pxb=pxb->next;
        if(tx==NULL){
            showerrs(-2);
            return -2;
        }
        px->next=tx;
        px=tx;
        l++;
    }
    *rtr=t;
    end->next=t;
    end=t;
    (t->cont)->index=l;//lenth of added.
    manage(*rtr);
    manage(*rtr);
    manage(*rtr);
    return 0;
}

int subsmaking(poly *a,poly *b,poly *(*rtr)){
    //a-b in a new polymer, rtr
    poly *t;
    xiang *px,*pxa,*pxb,*tx;
    double pr;
    int idx,l=0;
    t=(poly*)malloc(sizeof(poly));
    if(t==NULL){
        showerrs(-2);
        return -2;
    }
    t->cont=(xiang*)malloc(sizeof(xiang));
    if(t->cont==NULL){
        showerrs(-2);
        return -2;
    }
    (t->cont)->next=NULL;
    t->next=NULL;
    t->num=end->num+1;
    px=t->cont;pxa=a->cont;pxb=b->cont;
    pxa=pxa->next;pxb=pxb->next;
    while(pxa!=NULL){
        tx=createxiang(pxa->index,pxa->para);
        pxa=pxa->next;
        if(tx==NULL){
            showerrs(-2);
            return -2;
        }
        px->next=tx;
        px=tx;
        l++;
    }
    while(pxb!=NULL){
        tx=createxiang(pxb->index,-pxb->para);
        pxb=pxb->next;
        if(tx==NULL){
            showerrs(-2);
            return -2;
        }
        px->next=tx;
        px=tx;
        l++;
    }
    *rtr=t;
    end->next=t;
    end=t;
    (t->cont)->index=l;//lenth of added.
    manage(*rtr);
    manage(*rtr);
    manage(*rtr);
    return 0;
}

poly* destroypoly(poly *a,int way){
    //destroy a polymer.
    //if way is 0, it destroys a polymer in the polymer list;
    //else, it destroys a one failed to create.
    poly *tp,*p1;
    xiang *t;
    if(way==0) p1=&head;
    while(p1!=a)p1=p1->next;
    while((a->cont)->next!=NULL){
        t=destroyxiang((a->cont)->next);
        (a->cont)->next=t;
    }
    destroyxiang(a->cont);
    tp=a->next;
    if(way==0){
        for(p1=&head;p1->next!=a;p1=p1->next){}
        p1->next=tp;
        for(p1=tp;p1!=NULL;p1=p1->next){
            p1->num=p1->num-1;
        }
    }
    free(a);
    return tp;
}

int clearpoly(poly *a){
    //clear a polymer.
    xiang *t;
    while((a->cont)->next!=NULL){
        t=destroyxiang((a->cont)->next);
        (a->cont)->next=t;
    }
    (a->cont)->index=0;//l=0
    return 0;
}

int editxiang(poly *a){
    //edit an item that is found with its index.
    int aimind,aimind2;
    double aimpr;
    xiang *finder;
    printf("Please input the index of the item you want to edit:");
    readint(&aimind);
    for(finder=a->cont;finder->next!=NULL;finder=finder->next){
        if((finder->next)->index==aimind)break;
    }
    if(finder->next==NULL){
        printf("That index does not exist.\n");
        return -1;
    }
    printf("Please input the new index that you want to change it into;\n");
    printf("if you don\'t want to change it, input the original index:");
    readint(&aimind2);
    (finder->next)->index=aimind2;
    printf("Please input the new coefficient:");
    readdoub(&aimpr);
    (finder->next)->para=aimpr;
    manage(a);
    return 0;
}

int insertxiang(poly *a){
    //insert an item.
    xiang *px,*tx;
    double pr;
    int idx;
    px=(a->cont);
    printf("Please input the coefficient:");
    readdoub(&pr);
    printf("Please input the index:");
    readint(&idx);
    #ifdef DEBUG
    printf("%lfx^%d is inputed.\n",pr,idx);
    #endif
    tx=createxiang(idx,pr);
    (a->cont)->index=(a->cont)->index+1;//l++
    if(tx==NULL){
        showerrs(-2);
        return -2;
    }
    tx->next=px->next;
    px->next=tx;
    manage(a);
    return 0;
}

int deletexiang(poly *a){
    //delete an item from the polymer.
    int aimind;
    xiang *finder;
    printf("Please input the index of the item you want to edit:");
    readint(&aimind);
    for(finder=a->cont;finder->next!=NULL;finder=finder->next){
        if((finder->next)->index==aimind)break;
    }
    if(finder->next==NULL){
        printf("That index does not exist.\n");
        return -1;
    }
    finder->next=destroyxiang(finder->next);
    return 0;
}

int deriver(poly *a,poly *(*rtr)){
    //calculate the new polymer of its one-step derivation.
    poly *p,*t;
    xiang *px,*tx,*p1;
    double pr;
    int idx;
    p=&head;
    while(p->next!=NULL)p=p->next;
    t=(poly*)malloc(sizeof(poly));
    if(t==NULL){
        showerrs(-2);
        return -2;
    }t->cont=(xiang*)malloc(sizeof(xiang));
    if(t->cont==NULL){
        showerrs(-2);
        return -2;
    }
    (t->cont)->next=NULL;
    t->next=NULL;
    t->num=p->num+1;
    px=t->cont;
    p1=(a->cont)->next;
    while(p1!=NULL){
        pr=p1->para*p1->index;
        idx=p1->index-1;
        if(p1->index==0){
            pr=0;idx=0;
        }
        #ifdef DEBUG
        printf("%lfx^%d is calced.\n",pr,idx);
        #endif
        tx=createxiang(idx,pr);
        if(tx==NULL){
            showerrs(-2);
            return -2;
        }
        px->next=tx;
        px=tx;
        p1=p1->next;
    }
    *rtr=t;
    p->next=t;
    manage(*rtr);
    return 0;
}

int indefinite(poly *a){
    //indefinite integral. only outputing, no storing;
    //that's because it cannot store ln(x).
    xiang *p1;
    double pr;
    int idx;
    p1=(a->cont)->next;
    while(p1!=NULL){
        pr=p1->para/(p1->index+1);
        idx=p1->index+1;
        if(p1->index==-1){
            printf("(%lf*ln(x))%c",p1->para,(p1->next!=NULL?'+':'\n'));
        }
        else printf("(%lfx^%d)%c",pr,idx,(p1->next!=NULL?'+':'\n'));
        p1=p1->next;
    }
    if((a->cont)->next==NULL)printf("This is 0, and its integral is also 0.\n");
    return 0;
}

int definite(poly *a,double low,double high,double *rtr){
    //a definite integral, rtr is the returning value.
    xiang *p1;
    double pr,sum=0;
    int idx;
    p1=(a->cont)->next;
    if(low==high) return 0;
    while(p1!=NULL){
        pr=p1->para/(p1->index+1);
        idx=p1->index+1;
        if(idx<=0){
            if(high*low<=0){
                printf("ERROR:DIVISION BY ZERO.\n");
                return -1;
            }
        }
        if(p1->index==-1){
            sum+=p1->para*log(high/low);
        }
        else sum+=pr*(pow(high,idx)-pow(low,idx));
        p1=p1->next;
    }
    *rtr=sum;
    return 0;
}

int calc(poly *a,double x,double *rtr){
    //calculate the value of a at x.
    xiang *p1;
    double sum=0;
    p1=(a->cont)->next;
    while(p1!=NULL){
        if((p1->index<=0)&&(x==0)){
            printf("ERROR:DIVISION BY ZERO.\n");
            return -1;
        }
        sum+=p1->para*pow(x,p1->index);
        p1=p1->next;
    }
    *rtr=sum;
    return 0;
}

int multimaking(poly *a,poly *b,poly *(*rtr)){
    //multiply a and b in a new polymer, rtr
    poly *t;
    xiang *px,*pxa,*pxb,*tx;
    double pr;
    int idx,l;
    t=(poly*)malloc(sizeof(poly));
    if(t==NULL){
        showerrs(-2);
        return -2;
    }
    t->cont=(xiang*)malloc(sizeof(xiang));
    if(t->cont==NULL){
        showerrs(-2);
        return -2;
    }
    (t->cont)->next=NULL;
    t->next=NULL;
    t->num=end->num+1;
    px=t->cont;pxa=a->cont;
    pxa=pxa->next;
    while(pxa!=NULL){
        pxb=b->cont;pxb=pxb->next;
        while(pxb!=NULL){
            tx=createxiang((pxb->index)+(pxa->index),(pxb->para)*(pxa->para));
            #ifdef DEBUG
            printf("%lfx^%d is calced.\n",tx->para,tx->index);
            #endif
            pxb=pxb->next;
            if(tx==NULL){
                showerrs(-2);
                return -2;
            }
            px->next=tx;
            px=tx;
            l++;
        }
        pxa=pxa->next;
    }
    *rtr=t;
    end->next=t;
    end=t;
    (t->cont)->index=l;//lenth stored.
    manage(*rtr);
    manage(*rtr);
    manage(*rtr);
    return 0;
}


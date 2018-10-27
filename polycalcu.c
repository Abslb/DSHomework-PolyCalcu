#include<F:\shangji\polycalcu.h>
//below is the functions of transitions
void creates(){
    poly *t;
    int flag;
    flag=creater(&t);
    if(flag!=0){printf("Sorry, Failed.\n");return;}
    printf("The result is:\n");
    shower(t);
}

void show(){
    //the function that provides io for showing polymers.
    int n,i=0;
    poly *p;
    printf("Please Tell me the number of the polymer that you want to show;\n");
    printf("if you want to show them all, type in 0.\n");
    readint(&n);
    if(n<0){
        printf("That is not a reasonable number.\n");
        printf("Exit function.\n");return;
    }
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {
                printf("Polymer%d:\n",n);
                shower(p);
                break;
            }
        }
        if(p==NULL){
        printf("That number does not exist;\n");
        printf("Exit function.\n");return;
    }
    }
    else {
        for(p=head.next;p!=NULL;p=p->next){
            i++;
            printf("Polymer%d:\n",i);
            shower(p);
        }
        if(head.next==NULL)printf("There are no polymers to show.\n");
        else printf("That is all.\n");
    }
}

void gotooperates(int way){
    //the function that provides io forr add, subs, multi.
    //use the add, substract or multiply with 0,1,2 respectively.
    int numa,numb;
    poly *a,*b,*t;
    printf("Please input the number of the first polymer:");
    readint(&numa);
    while(numa<=0){
        printf("It should be positive.\n");
        readint(&numa);
    }
    for(a=&head;a!=NULL;a=a->next)
        if(a->num==numa)break;
    if(a==NULL){
        printf("That number does not exist;\n");
        printf("Exit function.\n");return;
    }
    printf("Please input the number of the second polymer:");
    readint(&numb);
    while(numb<=0){
        printf("It should be positive.\n");
        readint(&numb);
    }
    for(b=&head;b!=NULL;b=b->next)
        if(b->num==numb)break;
    if(b==NULL){
        printf("That number does not exist;\n");
        printf("Exit function.\n");return;
    }
    switch(way){
        case 0:addmaking(a,b,&t);break;
        case 1:subsmaking(a,b,&t);break;
        case 2:multimaking(a,b,&t);break;
    }
    printf("The result is:\n");
    shower(t);
}

void destroy(){
    //the function that provides io for destroying polymers.
    int n;
    poly *p,*t;
    char c;
    printf("Please Tell me the number of the polymer that you want to destroy;\n");
    printf("if you want to destroy them all, type in 0.\n");
    readint(&n);
    if(n<0)if(n<0){
        printf("That is not a reasonable number.\n");
        printf("Exit function.\n");return;
    }
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {
                shower(p);
                printf("Do you really want to destory this polymer?Y for yes.\n");
                scanf("%c",&c);lineflush();
                if(c=='Y') {
                    t=destroypoly(p,0);
                    printf("OK.\n");
                    if(t==NULL){
                        for(end=&head;end->next!=NULL;end=end->next);
                    }
                }
                else printf("Canceled.\n");
                return;
            }
        }
        if(p==NULL)printf("That number does not exist.\n");
    }
    else {
        printf("ALARMING: THIS OPERATION WILL DESTROY ALL THE POLYMERS YOU INPUTED.\n\
REALLY TO CONTIUE? IF YOU DO NOT KNOW WHAT YOU ARE DOING, TYPE N.\n\
Type Y to confirm detroying all.\n");
        scanf("%c",&c);lineflush();
        if(c!='Y'){printf("Canceled.\n");return;}
        if(head.next==NULL){
            printf("But there are no polymers to destory.\n");
            return;
        }
        for(p=head.next;p!=NULL;){
            t=destroypoly(p,0);
            p=t;
        }
        printf("Destroyed all Polymers.\n");
        end=&head;
    }
}

void clear(){
    //the function that provides io for clearing polymers.
    int n;
    poly *p;
    char c;
    printf("Please Tell me the number of the polymer that you want to clear;\n");
    printf("if you want to clear them all, type in 0.\n");
    readint(&n);
    if(n<0){printf("That is not a reasonable number.\n");return;}
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {
                shower(p);
                printf("Do you really want to clear this polymer?Y for yes.\n");
                scanf("%c",&c);lineflush();
                if(c=='Y') {
                    clearpoly(p);
                    printf("OK.\n");
                }
                else printf("Canceled.\n");
                return;
            }
        }
        if(p==NULL)printf("That number does not exist.\n");
    }
    else {
        shower(p);
        printf("This operation will clear all the polymers.\
            Type Y to confirm clearing all.\n");
        scanf("%c",&c);lineflush();
        if(c!='Y'){printf("Canceled.\n");return;}
        for(p=head.next;p!=NULL;p=p->next){
            clearpoly(p);
        }
        if(head.next==NULL)printf("But there are no polymers to clear.\n");
        else printf("cleared all Polymers.\n");
    }
}

void edit(){
    //the function that provides io for editting polymers.
    //use 1,2,3 for insert,delete and edit respectively.
    int func=1,numa,flag;
    poly *a;
    printf("Please input the number of the polymer you want to edit:");
    readint(&numa);
    while(numa<=0){
        printf("It should be positive.\n");
        readint(&numa);
    }
    for(a=&head;a!=NULL;a=a->next)
        if(a->num==numa)break;
    if(a==NULL){
        printf("That number does not exist;\n");
        printf("Exit function.\n");return;
    }
    do{
    if((func<=0)||(func>4))printf("Only 1,2,3 is accepted.\n");
    printf("What are your purpose?\n");
    printf("Type 1 for insert an item.\n");
    printf("2 for delete an item.\n");
    printf("3 for edit an item.\n");
    readint(&func);
    }while((func<=0)||(func>4));
    switch(func){
        case 1:flag=insertxiang(a);break;
        case 2:flag=deletexiang(a);break;
        case 3:flag=editxiang(a);break;
        default:break;
    }
    if(flag!=0){
        printf("Sorry,Failed.\n");
    }
    else{
        printf("Complete.Result is:\n");
        shower(a);
    }
}

void derives(){
    //the function that provides io for derivation.
    int times=0,numa,flag,i;
    poly *a[256];
    printf("Please input the number of the polymer you want to derive:");
    readint(&numa);
    while(numa<=0){
        printf("It should be positive.\n");
        readint(&numa);
    }
    for(a[0]=&head;a[0]!=NULL;a[0]=a[0]->next)
        if(a[0]->num==numa)break;
    if(a[0]==NULL){
        printf("That number does not exist;\n");
        printf("Exit function.\n");return;
    }
    do{
    if((times<0)||(times>255))printf("That is not accepted.\n");
    printf("Please input the times youwant to derive it.\n");
    readint(&times);
    }while((times<0)||(times>255));
    for(i=0;i<times;i++){
        flag=deriver(a[i],a+(i+1));
        if(flag!=0){
            printf("Sorry,Failed.\n");
            return;
        }
    }
    printf("Complete.Result is:\n");
    shower(a[times]);
}

void calcvalue(){
    //the function that provides io for calculating polymers' values.
    int n,f;
    double x,y;
    poly *p;
    printf("Please Tell me the number of the polymer that you want to calculate the value;\n");
    readint(&n);
    printf("Please input x:");
    readdoub(&x);
    if(n<=0){
        printf("That is not a reasonable number.\n");
        printf("Exit function.\n");return;
    }
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {
                shower(p);
                f=calc(p,x,&y);
                if(f==-1){
                    printf("Sorry,Failed.\n");
                    return;
                }
                printf("%lf is the value at x:%lf.\n",y,x);
                break;
            }
        }
        if(p==NULL){
            printf("That number does not exist.\n");
            printf("Exit function.\n");return;
        }
    }
}

void indinteg(){
    //the function that provides io for showing polymers' indefinite integrals.
    int n=0;
    poly *p;
    printf("NOTICE: THIS FUNCTION ONLY SHOWS YOU THE INDEFINITE INTEGRAL.\n");
    printf("It will NOT store the result, as it may contain ln(x).\n");
    printf("Please Tell me the number of the polymer that you want to show;\n");
    while(n<=0){
        printf("Please Mind that it have to be positive.\n");
        readint(&n);
    }
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {indefinite(p);break;}
        }
        if(p==NULL){
            printf("That number does not exist;\n");
            printf("Exit function.\n");return;
        }
    }
    
}

void integrals(){
    //the function that provides io for calculating polymers' integral's value
    int n,f;
    double l,h,y;
    poly *p;
    printf("Please Tell me the number of the polymer that you want the integral;\n");
    readint(&n);
    printf("Please input the lower edge:");
    readdoub(&l);
    printf("Please input the higher edge:");
    readdoub(&h);
    if(n<=0){
        printf("That is not a reasonable number.\n");
        printf("Exit function.\n");return;
    }
    if(n>0){
        for(p=&head;p!=NULL;p=p->next){
            if(p->num==n) {
                printf("The polymer being integraled is:\n");
                shower(p);
                f=definite(p,l,h,&y);
                if(f==-1){
                    printf("Sorry,Failed.\n");
                    return;
                }
                printf("%lf is the value on %lf to %lf.\n",y,l,h);
                break;
            }
        }
        if(p==NULL){
            printf("That number does not exist.\n");
            printf("Exit function.\n");return;
        }
    }
}

//the main function.
int main (){
    int cmd;
    head.num=0;
    head.next=NULL;
    end=&head;
    showsomething(0);
    while((cmd=readcmd())!=11){
        if(cmd==11)return 0;
        switch(cmd){
            case -1:showsomething(-1);break;
            case 0:break;
            case 1:showhelp();break;
            case 2:creates();break;
            case 3:show();break;
            case 4:gotooperates(0);break;
            case 5:gotooperates(1);break;
            case 6:destroy();break;
            case 7:clear();break;
            case 8:edit();break;
            case 10:showsomething(10);break;
            case 12:derives();break;
            case 13:indinteg();break;
            case 14:integrals();break;
            case 15:calcvalue();break;
            case 16:gotooperates(2);break;
            default:showsomething(-2);break;
        }
    }
    return 0;
}

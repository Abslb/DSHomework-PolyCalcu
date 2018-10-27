//below: the reading part
void lineflush(){
    //flush the buffer of a line
    char c;
    while(1){
        scanf("%c",&c);
        if(c=='\n')break;
    }
}

int readint(int *rt){
    //read a integer, in case of you don't put in a int
    char st[10],c='\0';
    int i,flag=1,k=0,hasnega=0,stillzero=1;
    while(flag){
        for(i=0;i<=9;i++){
            scanf("%c",&c);
            if((stillzero==1)&&(c=='0')){i--;continue;}
            stillzero=0;
            if(c=='\n'){
                flag=0;break;
            }
            if(c=='-'){
                if(i!=0){
                    printf("Only a negative symbol at the start should be accepted.\n");
                    lineflush();
                    break;
                }
                else hasnega=1;
                continue;
            }
            if(i==9){
                printf("That is Too long for a int.\n");
                lineflush();
                break;
            }
            if((c<'0')||(c>'9')){
                printf("PLEASE input an INTEGER.\n");
                lineflush();
                break;
            }
            st[i]=c;
            if((k>214748364)||(k<-214748364)){
                printf("That is not int, maybe long.\n");
                lineflush();break;
            }
            k*=10;k+=st[i]-48;
        }
        if(flag!=0){k=0;hasnega=0;stillzero=1;}
    }
    #ifdef DEBUG
    printf("%d is the received int.\n",k);
    #endif
    if(hasnega==0)*rt=k;
    else *rt=-k;
    if(c!='\n')lineflush();
    return 0;
}

int readdoub(double *rt){
    //read a double, in case of you don't put in a double
    char st[20],c='\0';
    int i,flag=1,havepoint=0,inde=0,countmode=0,cnt=0,hasnega=0;
    int stillzero=1;
    double k=0;
    while(flag){
        for(i=0;;i++){
            scanf("%c",&c);
            if((stillzero==1)&&(c=='0')){i--;continue;}
            stillzero=0;
            if(c=='\n'){
                flag=0;break;
            }
            if(c=='-'){
                if(i!=0){
                    printf("Only a negative symbol at the start should be accepted.\n");
                    lineflush();
                    break;
                }
                else hasnega=1;
                continue;
            }
            if(((c<'0')||(c>'9'))&&(c!='.')){
                printf("PLEASE do not input SOMETHING ELSE.\n");
                lineflush();
                break;
            }
            if(c=='.'){
                if(havepoint==0){
                    havepoint=1;
                    continue;
                }
                if(countmode==1){
                    flag=0;break;
                }
                else {
                    printf("What is your point with SO MANY points?\n");
                    lineflush();
                    break;
                }
            }
            if(countmode==1){
                k*=10;continue;
            }
            if(i==16){
                if(havepoint==1){
                    flag=0;break;
                }
                countmode=1;
                continue;
            }
            st[i]=c;
            if(havepoint==0){
                k*=10;k+=st[i]-48;
            }
            else {
                k+=(st[i]-48)* pow(10,-inde-1);
                inde++;
            }
        }
        if(flag!=0){k=0;havepoint=0;inde=0;countmode=0;cnt=0;hasnega=0;stillzero=1;}
    }
    #ifdef DEBUG
    printf("%lf is the received double.\n",k);
    #endif
    if(hasnega==0)*rt=k;
    else *rt=-k;
    if(c!='\n')lineflush();
    return 0;
}

int readcmd(){
    //reading what to do from the cmd lines
    char str[256],c;
    int i;
    scanf("%c",&c);
    for(i=0;(i<255)&&(c!='\n');i++){
        str[i]=c;
        scanf("%c",&c);
    }
    str[i]='\0';
    if(str[0]=='\0')return 0;
    //do nothing
    if(str[0]=='h')return 1;
    //show help
    switch(str[0]){
        case 'a':
            switch(str[1]){
                case 'b':return 10;//about
                case 'd':return 4;//add
                default:return -1;//error
            }
        case 'c':
            switch(str[1]){
                case 'r':return 2;//create
                case 'l':
                    if(str[2]=='e')return 7;//clear
                    else {system("cls");return 0;}//cls
                default:return -1;
            }
        case 'd':
            switch(str[2]){
                case 's':return 6;//destroy
                case 'r':return 12;//derive
                default:return -1;
            }
        case 'e':
            switch(str[1]){
                case 'd':return 8;//edit
                case 'x':return 11;//exit
                default:return -1;
            }
        case 'i':
            switch(str[2]){
                case 'd':return 13;//edit
                case 't':return 14;//exit
                default:return -1;
            }
        case 's':
            switch(str[1]){
                case 'u':return 5;//subs
                case 'h':return 3;//show
                default:return -1;
            }
        case 'v':
            return 15;//calcu value
        case 'm':
            return 16;//multiply polymers
        default:return -1;
    }
}

//below: the showing part
int showhelp(){
    //show help, or the commands plan
    printf("\n\
    Type \"help\" or \"h\" to consult the help;\n\
    type \"create\" to create your polymer;\n\
    type \"show\" to show your polymers;\n\
    type \"add\" to add your polymers;\n\
    similarly, \"subs\" to operate substract on them.\n\
    Type in \"value\" to calculate the value of the polymer.\n\
    You can type \"destroy\" to destroy your polymer;\n\
    and also \"clear\" to clear one of them.\
    Type \"edit\" to edit a polymer.\n\
    Type \"cls\" to clean screen.\n\
    Type \"about\" to show about.\n\
    Type \"exit\" to exit.\n\
    Type \"derive\" to calculate derivatives.\n\
    Type \"indinteg\" to calculate indefinite integral.\n\
    Type \"integtral\" to calculate definite integral.\n\
    Type \"multiply\" to multily two polymers.\n\
    \n");
    #ifdef DEBUG
    printf("DEBUG MODE\n");
    #endif
    return 0;
}

int showsomething(int k){
    //show about or show invalid command
    switch(k){
        case 10:printf("\nMadeby zhang luanxiang, PB17000004.\n");break;
        case -1:printf("\nThat is not a valid command, pal.\n");break;
        case 0:printf("\nThis is the polymer calculator by Zhang Luanxiang.\n");
        printf("type \"help\" to show help.\n");break;
        default:printf("\nThat is something odd.\n");
    }
}


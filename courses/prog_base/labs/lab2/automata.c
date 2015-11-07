enum State { INIT_STATE = -1, END_STATE};

int run(int moves[], int movesLen, int res[], int resLen){
int i,j,k;
int mark=0;
int stats[4][4]={0};
int proc=0;
int remas=0;
stats[0][0]=11;
stats[0][1]=55;
stats[0][2]=101;
stats[1][2]=1;
stats[2][1]=5;
stats[2][3]=11;
stats[3][3]=2;
for (k=0; k<movesLen;k++){
    switch (moves[k]){
    case 11:{
    if (proc==0){
        res[mark]=stats[proc][0];
        mark++;
        proc=1;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==1||proc==3){
        if (stats[1][0]==END_STATE)
        return -1;
        continue;
    }
    if (proc==2){
        res[mark]=0;
        mark--;
        proc=0;
        if (mark<0)
            return 0;
        continue;
    }
    break;
    }
     case 19:{
    if (proc==0){
        res[mark]=stats[proc][1];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==2){
        res[mark]=stats[proc][1];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==3){
        if (stats[proc][1]==END_STATE)
        return -1;
        continue;
    }
    if (proc==1){
        res[mark]=0;
        mark--;
        proc=1;
        remas--;
        if (mark<0)
            return 0;
        continue;
    }
    break;
    }
     case 29:{
    if (proc==0){
        res[mark]=stats[proc][2];
        mark++;
        proc=3;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==1){
        res[mark]=stats[proc][2];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==3){
        if (stats[proc][2]==END_STATE)
        return remas;
        continue;
    }
    if (proc==2){
        proc=1;
        res[mark]=stats[proc][2];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    break;
    }
    case 209:{
    if (proc==0){
        proc=0;
        continue;
    }
    if (proc==2){
        res[mark]=stats[proc][3];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    if (proc==1){
        if (stats[proc][3]==END_STATE)
        return -1;
        continue;
    }
    if (proc==3){
        res[mark]=stats[proc][3];
        mark++;
        proc=2;
        remas++;
        if(mark>resLen)
            return remas;
        continue;
    }
    break;
    }
    default{
        return -1;
    }
    }
}
return remas;
}

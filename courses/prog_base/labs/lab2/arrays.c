void fillRand1(int arr[],int size){
int i;
for (i=0;i<size;i++){
    arr[i]=1+rand()%1;
}
return;
}

int checkRand1(int arr[], int size){
int i;
for (i=0;i<size;i++){
    if (arr[i]<1||arr[i]>99)
        return 0;
}
return 1;
}

float meanValue(int arr[], int size){
int i;
float result;
int sum=0;
float sizem;
sizem=size;
for (i=0;i<size;i++){
    sum=sum+arr[i];
}
result=sum/sizem;
return result;
}

int maxValue(int arr[], int size){
int i;
int max;
max=arr[0];
for (i=0;i<size;i++){
    if (arr[i]>max)
        max=arr[i];
}
return max;
}

int meanIndex(int arr[], int size){
int i;
int dex;
float result;
int sum=0;
float sizem;
int rizn;
sizem=size;
for (i=0;i<size;i++){
    sum=sum+arr[i];
}
result=sum/sizem;
rizn=abs(arr[0]-(int)result);
for (i=0;i<size;i++){
    if (abs(arr[i]-(int)result)<rizn){
        rizn=abs(arr[i]-(int)result);
        dex=i;
        }
}
return dex;
}

int maxIndex(int arr[], int size){
int i;
int max;
int ind=0;
max=arr[0];
for (i=0;i<size;i++){
    if (arr[i]>max){
        max=arr[i];
        ind=i;
    }
}
return ind;
}

int maxOccurance(int arr[], int size){
    int i, k, num, frq, max_frq;
    num = arr[0];
    max_frq = 1;
    for (i=0; i < size; i++) {
        frq = 1;
        for (k = i+1; k<size; k++)
            if (arr[i] == arr[k])
                frq += 1;
        if (frq > max_frq) {
            max_frq = frq;
            num = arr[i];
        }
    }
    if (max_frq > 1)
    return num;
    else
        return 0;
}

int diff(int arr[], int arr2[], int res[], int size){
int i;
for (i=0;i<size;i++){
    res[i]=arr[i]-arr2[i];
}
for (i=0;i<size;i++){
    if (res[i]!=0)
        return 0;
}
    return 1;
}

void sub(int arr[], int arr2[], int res[], int size){
int i;
for (i=0;i<size;i++){
    res[i]=arr[i]-arr2[i];
}
return;
}

int gteq(int arr[], int arr2[], int size){
int i;
int res[size];
for (i=0;i<size;i++){
        if (arr[i]>=arr2[i])
        res[i]=1;
        else
        res[i]=0;
}
for (i=0;i<size;i++){
    if (res[i]==0)
        return 0;
}
    return 1;


}

void lor(int arr[], int arr2[], int res[], int size){
int i;
for (i=0;i<size;i++){
        if (arr[i]==0||arr2[i]==0)
        res[i]=0;
        if (arr[i]==1||arr2[i]==1)
        res[i]=1;
}
    return ;
}

void fillRand(int mat[4][4]){
int i, j;
for(i=0; i<4; i++) {
    for ( j = 0; j < 4; j++ )
    {
    mat[i][j] = -999+rand()%1998;
    }
}
return;
}

void flipV(int mat[4][4]){
int i, j;
int matr[4][4];
for ( i = 0; i < 4; ++i)
{
  for ( j = 0; j <4; ++j)
    matr[i][j] = mat[i][j];
}
for (i=0; i<4; i++){
 for (j=0; j<4; j++)
{
   mat[3-i][j]=matr[i][j];
}
}
return;
}

void rotateCCW90(int mat[4][4]){
int i, j;
int matr[4][4];
for ( i = 0; i < 4; ++i)
{
  for ( j = 0; j < 4; ++j)
    matr[i][j] = mat[i][j];
}
for (i=0; i<4; i++){
 for (j=0; j<4; j++)
{
   mat[3-j][i]=matr[i][j];
}
}
return;
}

void transposSide(int mat[4][4]){
int i, j;
int matr[4][4];
for ( i = 0; i < N; ++i)
{
  for ( j = 0; j <4; ++j)
    matr[i][j] = mat[i][j];
}
for (i=0; i<4; i++){
 for (j=0; j<4; j++)
{
   mat[3-j][3-i]=matr[i][j];
}
}
return;
}






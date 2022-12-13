#include <iostream>

using namespace std;

void insert(int arr[10][11],int x,int rrn){
    if(arr[0][1]==1){
        arr[0][1]=2;
        arr[1][0]=0;
        arr[1][1]=x;
        arr[1][2]=rrn;
    }
    else if(arr[0][1]==2){
            if(arr[1][10]==-1){
                    int i=1,j=1;
                    while(arr[i][j]!=-1){
                        j+=2;
                    }
                    arr[i][j]=x;
                    arr[i][j+1]=rrn;
                    int temp=arr[i][j];
                    j-=2;
                    while(temp<arr[i][j]){
                        int temp1=arr[i][j+3];
                        arr[i][j+2]=arr[i][j];
                        arr[i][j+3]=arr[i][j+1];
                        arr[i][j+1]=temp1;
                        arr[i][j]=temp;
                        temp=arr[i][j];
                        j-=2;
                    }
            }
            else{
                int arr1[6],arr2[4];
                for(int i=1;i<=6;i++){
                    arr1[i-1]=arr[1][i];
                }
                int j=0;
                for(int i=7;i<=10;i++){
                    arr2[j]=arr[1][i];
                    j++;
                }
                int x=arr1[4];
                int x1=arr[0][1]++;
                int y=arr2[2];
                int y2=arr[0][1]++;
                arr[1][0]=1;
                arr[1][1]=x;
                arr[1][2]=x1;
                arr[1][3]=y;
                arr[1][4]=y2;
                for(int i=5;i<11;i++){
                    arr[1][i]=-1;
                }
                arr[x1][0]=0;
                arr[y2][0]=0;
                int size1=sizeof(arr1)/sizeof(arr1[0]);
                int size2=sizeof(arr2)/sizeof(arr2[0]);
                for(int i=1;i<=size1;i++){
                    arr[x1][i]=arr1[i-1];
                }
                for(int i=1;i<=size2;i++){
                    arr[y2][i]=arr2[i-1];
                }
                int row;
                for(int i=1;i<11;i+=2){
                    if(x<arr[1][i]){
                       row=arr[1][i+1];
                       break;
                    }
                }
                j=1;
                while(arr[row][j]!=-1){
                    j+=2;
                }
                arr[row][j]=x;
                arr[row][j+1]=rrn;
                int temp=arr[row][j];
                j-=2;
                while(temp<arr[row][j]){
                    int temp1=arr[row][j+3];
                    arr[row][j+2]=arr[row][j];
                    arr[row][j+3]=arr[row][j+1];
                    arr[row][j+1]=temp1;
                    arr[row][j]=temp;
                    temp=arr[row][j];
                    j-=2;
                    }
            }
    }
}

int main()
{
    int x[10][11];
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            if(j==1){
                x[i][j]=i+1;
            }
            else{
                x[i][j]=-1;
            }
        }
    }

    insert(x,3,12);
    insert(x,7,24);
    insert(x,10,48);
    insert(x,24,60);
    insert(x,14,72);
    insert(x,19,84);

    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            cout<<x[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}

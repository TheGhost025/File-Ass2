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

    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            cout<<x[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}

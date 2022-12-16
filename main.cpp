#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

void insert(int arr[10][11],int x,int rrn){
    //if file is empty
    if(arr[0][1]==1){
        arr[0][1]=2;
        arr[1][0]=0;
        arr[1][1]=x;
        arr[1][2]=rrn;
    }
    else if(arr[0][1]==2){
            //file is in space to fill
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
            //if record is full
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
                int x1=arr1[4];
                int x2=arr[0][1]++;
                int y=arr2[2];
                int y2=arr[0][1]++;
                arr[1][0]=1;
                arr[1][1]=x1;
                arr[1][2]=x2;
                arr[1][3]=y;
                arr[1][4]=y2;
                for(int i=5;i<11;i++){
                    arr[1][i]=-1;
                }
                arr[x2][0]=0;
                arr[y2][0]=0;
                int size1=sizeof(arr1)/sizeof(arr1[0]);
                int size2=sizeof(arr2)/sizeof(arr2[0]);
                for(int i=1;i<=size1;i++){
                    arr[x2][i]=arr1[i-1];
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
    else{
            int j=1;
            while(x>arr[1][j]&&j<10){
                j+=2;
            }
            if(arr[1][j-1]!=-1){
                int row=arr[1][j+1];
                j=1;
                int count1=0;
                while(arr[row][j]!=-1&&j<11){
                    j+=2;
                    count1++;
                }
                if(count1==5){
                    int arr1[12];
                    for(int i=1;i<11;i++){
                        arr1[i-1]=arr[row][i];
                    }
                    arr1[10]=x;
                    arr1[11]=rrn;
                    int temp=x;
                    int i=10;
                    i-=2;
                    while(temp<arr1[i]){
                        int temp1=arr1[i+3];
                        arr1[i+2]=arr1[i];
                        arr1[i+3]=arr1[i+1];
                        arr1[i+1]=temp1;
                        arr1[i]=temp;
                        temp=arr1[i];
                        i-=2;
                    }
                    int arr2[6],arr3[6];
                    for(int i=1;i<=6;i++){
                        arr2[i-1]=arr1[i-1];
                    }
                    int j=0;
                    for(int i=7;i<=12;i++){
                        arr3[j]=arr1[i-1];
                        j++;
                    }
                    int x2=arr[0][1]++;
                    int min1=arr2[4];
                    int max1=arr3[4];
                    int arr4[5];
                    j=1;
                    i=0;
                    while(arr[1][j]!=-1){
                        arr4[i]=arr[1][j];
                        j+=2;
                        i++;
                    }
                     int size1=sizeof(arr4)/sizeof(arr4[0]);
                    if(find(arr4,arr4+size1,min1)!=(arr4+size1)){
                        for(int i=1;i<11;i+=2){
                            if(arr[1][i]==min1){
                                arr[1][i+1]=row;
                                break;
                            }
                        }
                        j=1;
                        while(arr[1][j]!=-1){
                            j+=2;
                        }
                        arr[1][j]=max1;
                        arr[1][j+1]=x2;
                        temp=arr[1][j];
                        j-=2;
                        while(temp<arr[1][j]){
                            int temp1=arr[1][j+3];
                            arr[1][j+2]=arr[1][j];
                            arr[1][j+3]=arr[1][j+1];
                            arr[1][j+1]=temp1;
                            arr[1][j]=temp;
                            temp=arr[1][j];
                            j-=2;
                        }
                    }
                    else if(find(arr4,arr4+size1,max1)!=(arr4+size1)){
                        for(int i=1;i<11;i+=2){
                            if(arr[1][i]==max1){
                                arr[1][i+1]=x2;
                                break;
                            }
                        }
                        j=1;
                        while(arr[1][j]!=-1){
                            j+=2;
                        }
                        arr[1][j]=min1;
                        arr[1][j+1]=row;
                        temp=arr[1][j];
                        j-=2;
                        while(temp<arr[1][j]){
                            int temp1=arr[1][j+3];
                            arr[1][j+2]=arr[1][j];
                            arr[1][j+3]=arr[1][j+1];
                            arr[1][j+1]=temp1;
                            arr[1][j]=temp;
                            temp=arr[1][j];
                            j-=2;
                        }
                    }
                    for(int i=1;i<=6;i++){
                        arr[row][i]=arr2[i-1];
                    }
                    for(int i=7;i<=10;i++){
                        arr[row][i]=-1;
                    }
                    arr[x2][0]=0;
                    for(int i=1;i<=6;i++){
                    arr[x2][i]=arr3[i-1];
                  }

                }
                else{
                    arr[row][j]=x;
                    arr[row][j+1]=rrn;
                    int temp=x;
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
            else{
                j=1;
                while(arr[1][j]!=-1){
                        j+=2;
                    }
                j-=2;
                arr[1][j]=x;
                int row=arr[1][j+1];
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
    insert(x,30,96);
    insert(x,15,108);
    insert(x,1,120);
    insert(x,5,132);
    insert(x,2,144);
    insert(x,8,156);
    insert(x,9,168);
    insert(x,6,180);
    insert(x,11,192);
    insert(x,12,204);
    insert(x,17,216);
    insert(x,18,228);

    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            cout<<x[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}

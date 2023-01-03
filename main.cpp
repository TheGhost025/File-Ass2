#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;


void CreateIndexFileFile(char* filename, int numberOfRecords, int m){
    fstream file(filename,ios::in|ios::out|ios::app);
     for(int i=0;i<numberOfRecords;i++){
        for(int j=0;j<(m*2)+1;j++){
            if(j==1){
                int z=i+1;
                file.write((char*)& z,sizeof(int));
            }
            else{
                int z=-1;
                file.write((char*)& z,sizeof(int));
            }
        }
    }
    file.close();
}

void DisplayIndexFileContent (char* filename){
    fstream file(filename,ios::in|ios::out);
     for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
                int z;
                file.read((char*)&z,sizeof(int));
                cout<<z<<" ";
        }
        cout<<endl;
    }
    file.close();
}

void readFile(int arr[10][11],char* filename){
    fstream file(filename,ios::in|ios::out);
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
                file.read((char*)&arr[i][j],sizeof(int));
        }
    }
    file.close();
}

void writeFile(int arr[10][11],char* filename){
    fstream file(filename,ios::in|ios::out);
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
                file.write((char*)&arr[i][j],sizeof(int));
        }
    }
    file.close();
}

int InsertNewRecordAtIndex(char* filename,int x,int rrn){
    int arr[10][11];
    readFile(arr,filename);
    int number=0;
    for(int i=1;i<10;i++){
        if(arr[i][0]==-1){
            number++;
        }
    }
    //if file is empty
    if(arr[0][1]==1){
        arr[0][1]=2;
        arr[1][0]=0;
        arr[1][1]=x;
        arr[1][2]=rrn;
        writeFile(arr,filename);
        return 1;
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
                    writeFile(arr,filename);
                    return 1;
            }
            //if record is full
            else{
                    if(number>=2){
                            number-=2;
                            int arr1[12];
                            for(int i=1;i<11;i++){
                                arr1[i-1]=arr[1][i];
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
                            int x1=arr2[4];
                            int x2=arr[0][1];
                            arr[x2][0]=0;
                            int size1=sizeof(arr2)/sizeof(arr2[0]);
                            for(int i=1;i<=size1;i++){
                                arr[x2][i]=arr2[i-1];
                            }
                            int y=arr3[4];
                            for(int i=1;i<10;i++){
                                if(arr[i][0]==-1){
                                    arr[0][1]=i;
                                    break;
                                }
                                arr[0][1]=-1;
                            }
                            int y2=arr[0][1];
                            arr[1][0]=1;
                            arr[1][1]=x1;
                            arr[1][2]=x2;
                            arr[1][3]=y;
                            arr[1][4]=y2;
                            for(int i=5;i<11;i++){
                                arr[1][i]=-1;
                            }
                            arr[y2][0]=0;
                            int size2=sizeof(arr3)/sizeof(arr3[0]);
                            for(int i=1;i<=size2;i++){
                                arr[y2][i]=arr3[i-1];
                            }
                            for(int i=1;i<10;i++){
                                if(arr[i][0]==-1){
                                    arr[0][1]=i;
                                    break;
                                }
                                arr[0][1]=-1;
                            }
                            writeFile(arr,filename);
                            if(find(arr2,arr2+6,x)!=arr2+6){
                                return x2;
                            }
                            else{
                                return y2;
                            }
                    }
            }
    }
    else{
            int j=1;
            int count2=0;
            while(x>arr[1][j]&&j<10){
                j+=2;
                count2++;
            }
            if(count2!=5||arr[1][j]==-1){
                            int row=arr[1][j+1];
                            if(arr[row][0]==0){
                                j=1;
                                int count1=0;
                                while(arr[row][j]!=-1&&j<11){
                                    j+=2;
                                    count1++;
                                }
                                if(count1==5){
                                        if(number>=1){
                                                number--;
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
                                                int x2=arr[0][1];
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
                                                for(int i=1;i<10;i++){
                                                    if(arr[i][0]==-1){
                                                        arr[0][1]=i;
                                                        break;
                                                    }
                                                    arr[0][1]=-1;
                                                }
                                                writeFile(arr,filename);
                                                if(find(arr2,arr2+6,x)!=arr2+6){
                                                    return row;
                                                }
                                                else{
                                                    return x2;
                                                }
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
                                        writeFile(arr,filename);
                                        return row;
                                }
                                }
                                else{
                                       while(x>arr[row][j]&&j<10){
                                            j+=2;
                                            count2++;
                                        }
                                        if(count2!=5||arr[1][j]==-1){
                                             row=arr[row][j+1];
                                                j=1;
                                                int count1=0;
                                                while(arr[row][j]!=-1&&j<11){
                                                    j+=2;
                                                    count1++;
                                                }
                                                if(count1==5){
                                                        if(number>=1){
                                                            number--;
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
                                                            int x2=arr[0][1];
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
                                                            for(int i=1;i<10;i++){
                                                                if(arr[i][0]==-1){
                                                                    arr[0][1]=i;
                                                                    break;
                                                                }
                                                                arr[0][1]=-1;
                                                            }
                                                            writeFile(arr,filename);
                                                            if(find(arr2,arr2+6,x)!=arr2+6){
                                                                    return row;
                                                                }
                                                                else{
                                                                    return x2;
                                                                }
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
                                                        writeFile(arr,filename);
                                                        return row;
                                                }
                                                }
                                                else{
                                                    j=1;
                                                    int count1=0;
                                                    while(arr[1][j]!=-1&&j<10){
                                                            j+=2;
                                                            count1++;
                                                        }
                                                        if(count1!=5){
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
                                                                writeFile(arr,filename);
                                                                return row;
                                                        }
                                                        else{
                                                                number-=2;
                                                                j-=2;
                                                                arr[1][j]=x;
                                                                int row=arr[1][j+1];
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
                                                                int x2=arr[0][1];
                                                                int min1=arr2[4];
                                                                int max1=arr3[4];
                                                                int mn=min1;
                                                                int mx=max1;
                                                                int arr4[6];
                                                                j=1;
                                                                i=0;
                                                                while(arr[1][j]!=-1){
                                                                    arr4[i]=arr[1][j];
                                                                    j+=2;
                                                                    i++;
                                                                }
                                                                int z=1;
                                                                int count3=0;
                                                                while(arr[1][z]!=-1&&z<10){
                                                                    z+=2;
                                                                    count3++;
                                                                }
                                                                if(count3!=5){
                                                                        if(number>=1){
                                                                                number--;
                                                                                int size1=sizeof(arr4)/sizeof(arr4[0]);
                                                                                if(find(arr4,arr4+size1,mn)!=(arr4+size1)){
                                                                                    for(int i=1;i<11;i+=2){
                                                                                        if(arr[1][i]==mn){
                                                                                            arr[1][i+1]=row;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                    j=1;
                                                                                    while(arr[1][j]!=-1){
                                                                                        j+=2;
                                                                                    }
                                                                                    arr[1][j]=mx;
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
                                                                                else if(find(arr4,arr4+size1,mx)!=(arr4+size1)){
                                                                                    for(int i=1;i<11;i+=2){
                                                                                        if(arr[1][i]==mx){
                                                                                            arr[1][i+1]=x2;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                    j=1;
                                                                                    while(arr[1][j]!=-1){
                                                                                        j+=2;
                                                                                    }
                                                                                    arr[1][j]=mn;
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
                                                                                for(int i=1;i<10;i++){
                                                                                    if(arr[i][0]==-1){
                                                                                        arr[0][1]=i;
                                                                                        break;
                                                                                    }
                                                                                    arr[0][1]=-1;
                                                                                }
                                                                                writeFile(arr,filename);
                                                                                if(find(arr2,arr2+6,x)!=arr2+6){
                                                                                    return row;
                                                                                }
                                                                                else{
                                                                                    return x2;
                                                                                }
                                                                        }
                                                                }
                                                                else{
                                                                        if(number>=3){
                                                                                int size1=sizeof(arr4)/sizeof(arr4[0]);
                                                                                if(find(arr4,arr4+size1,min1)!=(arr4+size1)){
                                                                                        arr4[5]=max1;
                                                                                        for(int i=1;i<11;i+=2){
                                                                                            if(arr[1][i]==min1){
                                                                                                arr[1][i+1]=row;
                                                                                                break;
                                                                                            }
                                                                                        }
                                                                                        int arr5[12];
                                                                                        for(int i=1;i<11;i++){
                                                                                            arr5[i-1]=arr[1][i];
                                                                                            }
                                                                                        arr5[10]=max1;
                                                                                        arr5[11]=x2;
                                                                                        int temp=max1;
                                                                                        int i=10;
                                                                                        i-=2;
                                                                                        while(temp<arr5[i]){
                                                                                            int temp1=arr5[i+3];
                                                                                            arr5[i+2]=arr5[i];
                                                                                            arr5[i+3]=arr5[i+1];
                                                                                            arr5[i+1]=temp1;
                                                                                            arr5[i]=temp;
                                                                                            temp=arr1[i];
                                                                                            i-=2;
                                                                                        }
                                                                                        int arr6[6],arr7[6];
                                                                                        for(int i=1;i<=6;i++){
                                                                                            arr6[i-1]=arr5[i-1];
                                                                                        }
                                                                                        int j=0;
                                                                                        for(int i=7;i<=12;i++){
                                                                                            arr7[j]=arr5[i-1];
                                                                                            j++;
                                                                                        }
                                                                                        arr[x2][0]=0;
                                                                                        for(int i=1;i<10;i++){
                                                                                                if(arr[i][0]==-1){
                                                                                                    arr[0][1]=i;
                                                                                                    break;
                                                                                                }
                                                                                                arr[0][1]=-1;
                                                                                            }
                                                                                        int x3=arr[0][1];
                                                                                        arr[x3][0]=1;
                                                                                        for(int i=1;i<10;i++){
                                                                                            if(arr[i][0]==-1){
                                                                                                arr[0][1]=i;
                                                                                                break;
                                                                                            }
                                                                                            arr[0][1]=-1;
                                                                                        }
                                                                                        int x4=arr[0][1];
                                                                                        arr[x4][0]=1;
                                                                                        for(int i=1;i<10;i++){
                                                                                            if(arr[i][0]==-1){
                                                                                                arr[0][1]=i;
                                                                                                break;
                                                                                            }
                                                                                            arr[0][1]=-1;
                                                                                        }
                                                                                        int min2=arr6[4];
                                                                                        int max2=arr7[4];
                                                                                        arr[1][1]=min2;
                                                                                        arr[1][2]=x3;
                                                                                        arr[1][3]=max2;
                                                                                        arr[1][4]=x4;
                                                                                        for(int i=5;i<11;i++){
                                                                                            arr[1][i]=-1;
                                                                                        }
                                                                                        for(int i=1;i<=6;i++){
                                                                                            arr[x3][i]=arr6[i-1];
                                                                                        }
                                                                                        for(int i=1;i<=6;i++){
                                                                                            arr[x4][i]=arr7[i-1];
                                                                                        }
                                                                                        for(int i=1;i<=6;i++){
                                                                                            arr[row][i]=arr2[i-1];
                                                                                        }
                                                                                        for(int i=7;i<=10;i++){
                                                                                                arr[row][i]=-1;
                                                                                            }
                                                                                        for(int i=1;i<=6;i++){
                                                                                            arr[x2][i]=arr3[i-1];
                                                                                      }
                                                                                      writeFile(arr,filename);
                                                                                      if(find(arr2,arr2+6,x)!=arr2+6){
                                                                                            return row;
                                                                                        }
                                                                                        else{
                                                                                            return x2;
                                                                                        }
                                                                                }
                                                                                else if(find(arr4,arr4+size1,max1)!=(arr4+size1)){
                                                                                    arr4[5]=min1;
                                                                                    for(int i=1;i<11;i+=2){
                                                                                        if(arr[1][i]==max1){
                                                                                            arr[1][i+1]=x2;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                    int arr5[12];
                                                                                    for(int i=1;i<11;i++){
                                                                                        arr5[i-1]=arr[1][i];
                                                                                        }
                                                                                    arr5[10]=min1;
                                                                                    arr5[11]=row;
                                                                                    int temp=min1;
                                                                                    int i=10;
                                                                                    i-=2;
                                                                                    while(temp<arr5[i]){
                                                                                        int temp1=arr5[i+3];
                                                                                        arr5[i+2]=arr5[i];
                                                                                        arr5[i+3]=arr5[i+1];
                                                                                        arr5[i+1]=temp1;
                                                                                        arr5[i]=temp;
                                                                                        temp=arr1[i];
                                                                                        i-=2;
                                                                                    }
                                                                                    int arr6[6],arr7[6];
                                                                                    for(int i=1;i<=6;i++){
                                                                                        arr6[i-1]=arr5[i-1];
                                                                                    }
                                                                                    int j=0;
                                                                                    for(int i=7;i<=12;i++){
                                                                                        arr7[j]=arr5[i-1];
                                                                                        j++;
                                                                                    }
                                                                                    int x3=arr[0][1];
                                                                                    arr[x3][0]=1;
                                                                                    for(int i=1;i<10;i++){
                                                                                        if(arr[i][0]==-1){
                                                                                            arr[0][1]=i;
                                                                                            break;
                                                                                        }
                                                                                        arr[0][1]=-1;
                                                                                    }
                                                                                    int x4=arr[0][1];
                                                                                    arr[x4][0]=1;
                                                                                    for(int i=1;i<10;i++){
                                                                                        if(arr[i][0]==-1){
                                                                                            arr[0][1]=i;
                                                                                            break;
                                                                                        }
                                                                                        arr[0][1]=-1;
                                                                                    }
                                                                                    int min2=arr6[4];
                                                                                    int max2=arr7[4];
                                                                                    arr[1][1]=min2;
                                                                                    arr[1][2]=x3;
                                                                                    arr[1][3]=max2;
                                                                                    arr[1][4]=x4;
                                                                                    for(int i=5;i<11;i++){
                                                                                        arr[1][i]=-1;
                                                                                    }
                                                                                    for(int i=1;i<=6;i++){
                                                                                        arr[x3][i]=arr6[i-1];
                                                                                    }
                                                                                    for(int i=1;i<=6;i++){
                                                                                        arr[x4][i]=arr7[i-1];
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
                                                                                  for(int i=1;i<10;i++){
                                                                                        if(arr[i][0]==-1){
                                                                                            arr[0][1]=i;
                                                                                            break;
                                                                                        }
                                                                                        arr[0][1]=-1;
                                                                                    }
                                                                                    writeFile(arr,filename);
                                                                                    if(find(arr2,arr2+6,x)!=arr2+6){
                                                                                            return row;
                                                                                        }
                                                                                        else{
                                                                                            return x2;
                                                                                        }
                                                                        }
                                                                        }
                                                            }
                                                }
                                                }
                                                }
            }
            else{
                j=1;
                int count1=0;
                while(arr[1][j]!=-1&&j<10){
                        j+=2;
                        count1++;
                    }
                    if(count1!=5){
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
                            writeFile(arr,filename);
                            return row;
                    }
                    else{
                        j-=2;
                        arr[1][j]=x;
                        int row=arr[1][j+1];
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
                        int x2=arr[0][1];
                        int min1=arr2[4];
                        int max1=arr3[4];
                        int mn=min1;
                        int mx=max1;
                        int arr4[6];
                        j=1;
                        i=0;
                        while(arr[1][j]!=-1){
                            arr4[i]=arr[1][j];
                            j+=2;
                            i++;
                        }
                        int z=1;
                        int count3=0;
                        while(arr[1][z]!=-1&&z<10){
                            z+=2;
                            count3++;
                        }
                        if(count3!=5){
                                if(number>=1){
                                    number--;
                                    int size1=sizeof(arr4)/sizeof(arr4[0]);
                                    if(find(arr4,arr4+size1,mn)!=(arr4+size1)){
                                        for(int i=1;i<11;i+=2){
                                            if(arr[1][i]==mn){
                                                arr[1][i+1]=row;
                                                break;
                                            }
                                        }
                                        j=1;
                                        while(arr[1][j]!=-1){
                                            j+=2;
                                        }
                                        arr[1][j]=mx;
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
                                    else if(find(arr4,arr4+size1,mx)!=(arr4+size1)){
                                        for(int i=1;i<11;i+=2){
                                            if(arr[1][i]==mx){
                                                arr[1][i+1]=x2;
                                                break;
                                            }
                                        }
                                        j=1;
                                        while(arr[1][j]!=-1){
                                            j+=2;
                                        }
                                        arr[1][j]=mn;
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
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    for(int i=1;i<=6;i++){
                                    arr[x2][i]=arr3[i-1];
                                  }
                                  writeFile(arr,filename);
                                  if(find(arr2,arr2+6,x)!=arr2+6){
                                        return row;
                                    }
                                    else{
                                        return x2;
                                    }
                                }
                        }
                        else{
                                if(number>=3){
                                        number-=3;
                                        int size1=sizeof(arr4)/sizeof(arr4[0]);
                                        if(find(arr4,arr4+size1,min1)!=(arr4+size1)){
                                                arr4[5]=max1;
                                            for(int i=1;i<11;i+=2){
                                                if(arr[1][i]==min1){
                                                    arr[1][i+1]=row;
                                                    break;
                                                }
                                            }
                                        int arr5[12];
                                        for(int i=1;i<11;i++){
                                    arr5[i-1]=arr[1][i];
                                    }
                                    arr5[10]=max1;
                                    arr5[11]=x2;
                                    int temp=max1;
                                    int i=10;
                                    i-=2;
                                    while(temp<arr5[i]){
                                        int temp1=arr5[i+3];
                                        arr5[i+2]=arr5[i];
                                        arr5[i+3]=arr5[i+1];
                                        arr5[i+1]=temp1;
                                        arr5[i]=temp;
                                        temp=arr1[i];
                                        i-=2;
                                    }
                                    int arr6[6],arr7[6];
                                    for(int i=1;i<=6;i++){
                                        arr6[i-1]=arr5[i-1];
                                    }
                                    int j=0;
                                    for(int i=7;i<=12;i++){
                                        arr7[j]=arr5[i-1];
                                        j++;
                                    }
                                    int x3=arr[0][1];
                                    int x4=arr[0][1];
                                    int min2=arr6[4];
                                    int max2=arr7[4];
                                    arr[1][1]=min2;
                                    arr[1][2]=x3;
                                    arr[1][3]=max2;
                                    arr[1][4]=x4;
                                    for(int i=5;i<11;i++){
                                        arr[1][i]=-1;
                                    }
                                    arr[x3][0]=1;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    arr[x4][0]=1;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[x3][i]=arr6[i-1];
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[x4][i]=arr7[i-1];
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[row][i]=arr2[i-1];
                                    }
                                    for(int i=7;i<=10;i++){
                                            arr[row][i]=-1;
                                        }
                                    arr[x2][0]=0;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[x2][i]=arr3[i-1];
                                  }
                                        }
                                        else if(find(arr4,arr4+size1,max1)!=(arr4+size1)){
                                            arr4[5]=min1;
                                            for(int i=1;i<11;i+=2){
                                                if(arr[1][i]==max1){
                                                    arr[1][i+1]=x2;
                                                    break;
                                                }
                                            }
                                        int arr5[12];
                                        for(int i=1;i<11;i++){
                                    arr5[i-1]=arr[1][i];
                                    }
                                    arr5[10]=min1;
                                    arr5[11]=row;
                                    int temp=min1;
                                    int i=10;
                                    i-=2;
                                    while(temp<arr5[i]){
                                        int temp1=arr5[i+3];
                                        arr5[i+2]=arr5[i];
                                        arr5[i+3]=arr5[i+1];
                                        arr5[i+1]=temp1;
                                        arr5[i]=temp;
                                        temp=arr1[i];
                                        i-=2;
                                    }
                                    int arr6[6],arr7[6];
                                    for(int i=1;i<=6;i++){
                                        arr6[i-1]=arr5[i-1];
                                    }
                                    int j=0;
                                    for(int i=7;i<=12;i++){
                                        arr7[j]=arr5[i-1];
                                        j++;
                                    }
                                    int min2=arr6[4];
                                    int max2=arr7[4];
                                    arr[1][1]=min2;
                                    arr[1][3]=max2;
                                    for(int i=5;i<11;i++){
                                        arr[1][i]=-1;
                                    }
                                    arr[x2][0]=0;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    int x3=arr[0][1];
                                    arr[x3][0]=1;
                                    arr[1][2]=x3;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    int x4=arr[0][1];
                                    arr[x4][0]=1;
                                    arr[1][4]=x4;
                                    for(int i=1;i<10;i++){
                                        if(arr[i][0]==-1){
                                            arr[0][1]=i;
                                            break;
                                        }
                                        arr[0][1]=-1;
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[x3][i]=arr6[i-1];
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[x4][i]=arr7[i-1];
                                    }
                                    for(int i=1;i<=6;i++){
                                        arr[row][i]=arr2[i-1];
                                    }
                                    for(int i=7;i<=10;i++){
                                            arr[row][i]=-1;
                                        }
                                    for(int i=1;i<=6;i++){
                                        arr[x2][i]=arr3[i-1];
                                  }
                                  writeFile(arr,filename);
                                  if(find(arr2,arr2+6,x)!=arr2+6){
                                        return row;
                                    }
                                    else{
                                        return x2;
                                    }
                                }
                                }
                    }
            }
    }
    }
    return -1;
    }

    // -----------------------------
// -----------------------------
// -----------------------------
// -----------------------------
// --------redistribution-------
// -----------------------------
// -----------------------------
// -----------------------------
// -----------------------------

//editedRow is the row we deleted from
//redistributedRow is the row we will take values from
//rl is a char either 'r' for right or 'l' for left
//deleted is the key we deleted from the tree

void redistribution(char *filename, int arr[10][11], int editedRow, int redistributedRow, int parentRow, char rl, int deleted) {
    // if the redistribution leads us to the right sibling
    if (rl == 'r') {
        // take the first key : value as it will always be sorted
        int tempKey = arr[redistributedRow][1];
        int tempValue = arr[redistributedRow][2];
        // if we deleted the first key : value shift the row to the left
        if (arr[editedRow][1] == -1) {
            arr[editedRow][1] = arr[editedRow][3];
            arr[editedRow][2] = arr[editedRow][4];
        }
        // assign the right key : value to the value we took
        arr[editedRow][3] = tempKey;
        arr[editedRow][4] = tempValue;
        // update the parent node with the new values
        for (int i = 1; i < 11; i += 2) {
            if (arr[parentRow][i] == arr[editedRow][1] || arr[parentRow][i] == arr[editedRow][2]) {
                arr[parentRow][i] = tempKey;
                break;
            }
        }
        // update the root if we didn't updated it
        if (parentRow != 1) {
            for (int i = 1; i < 11; i += 2) {
                if (arr[1][i] == arr[editedRow][1] || arr[1][i] == arr[editedRow][2]) {
                    arr[1][i] = tempKey;
                    break;
                }
            }
        }
        // shift the redistributed row
        for (int i = 3; i < 11; i++) {
            arr[redistributedRow][i - 2] = arr[redistributedRow][i];
        }
    }
    // the left sibling
    else if (rl == 'l') {
        int tempKey, tempValue;

        for (int i = 1; i < 11; i += 2) {
            // get the right most key : value from the e redistributed row;
            if (arr[redistributedRow][i] == -1) {
                tempKey = arr[redistributedRow][i - 2];
                tempValue = arr[redistributedRow][i - 1];
                arr[redistributedRow][i - 2] = -1;
                arr[redistributedRow][i - 1] = -1;
                // update the parent node with the new values
                for (int j = 1; j < 11; j += 2) {
                    if (arr[parentRow][j] == tempKey) {
                        arr[parentRow][j] = arr[redistributedRow][i - 4];
                        break;
                    }
                }

                // update the root if we didn't updated it
                if (parentRow != 1) {
                    for (int k = 1; k < 11; k += 2) {
                        if (arr[1][k] == arr[editedRow][1] || arr[1][k] == arr[editedRow][2]) {
                            arr[1][k] = tempKey;
                            break;
                        }
                    }
                }
                break;
            }
        }
        // the max key in the edited row
        int maxKey = arr[editedRow][1];
        // shift the value
        arr[editedRow][3] = arr[editedRow][1];
        arr[editedRow][4] = arr[editedRow][2];
        // assign the value
        arr[editedRow][1] = tempKey;
        arr[editedRow][2] = tempValue;

        if (deleted > maxKey) {
            // update the parent node with the new values
            for (int j = 1; j < 11; j += 2){
                if (arr[parentRow][j] == deleted) {
                    arr[parentRow][j] = maxKey;
                    break;
                }
            }
            // update the root if we didn't updated it
            if (parentRow != 1) {
                for (int k = 1; k < 11; k += 2) {
                    if (arr[1][k] == tempKey) {
                        arr[1][k] = maxKey;
                        break;
                    }
                }
            }
        }
    }
    else {
        cout << "Redistribution error accured" << endl;
    }
    // write the new values to the file
    writeFile(arr, filename);
}
// -----------------------------
// -----------------------------
// -----------------------------
// -----------------------------
// -----------Search------------
// -----------------------------
// -----------------------------
// -----------------------------
// -----------------------------

// used with the root first
// int value = search(arr, key, 1);
int SearchARecord(char* filename, int key) {
    fstream file(filename,ios::out|ios::in);
    int x;
    file.seekg(44,ios::beg);
    file.read((char*)& x,sizeof(int));
    while(x!=0){
            int y;
            file.read((char*)& y,sizeof(int));
            while(key>y){
                file.seekg(4,ios::cur);
                file.read((char*)& y,sizeof(int));
            }
            file.read((char*)& y,sizeof(int));
            file.seekg(44*y,ios::beg);
            file.read((char*)& x,sizeof(int));
    }
    if(x==0){
        file.read((char*)& x,sizeof(int));
        while(key!=x&&x!=-1){
            file.seekg(4,ios::cur);
            file.read((char*)& x,sizeof(int));
        }
        if(key==x){
            file.read((char*)& x,sizeof(int));
            file.close();
            return x;
        }
        else{
            file.close();
            return -1;
        }
    }
    else{
        return -1;
    }
}

void DeleteRecordFromIndex (char* filename,int ID){
    fstream file(filename,ios::in|ios::out);
    int arr[10][11];
    readFile(arr,filename);
    int i=1;
    while(ID>arr[1][i]){
        i+=2;
    }
    if(ID!=arr[1][i]){
        int row=arr[1][i+1];
        if(arr[row][0]==1){
            int j=1;
            while(ID>arr[row][j]){
            j+=2;
            }
            int rw=arr[row][j+1];
            if(arr[rw][0]==0){
                int z=1;
                while(ID>arr[rw][z]){
                z+=2;
            }
            arr[rw][z]=-1;
            arr[rw][z+1]=-1;
            int temp=arr[rw][z];
            z+=2;
            while(arr[rw][z]!=-1){
                int temp1=arr[rw][z+1];
                arr[rw][z-2]=arr[rw][z];
                arr[rw][z+1]=arr[rw][z-1];
                arr[rw][z-1]=temp1;
                arr[rw][z]=temp;
                temp=arr[rw][z];
                z+=2;
            }
             int k=1;
            int count3=0;
            while(arr[rw][k]!=-1){
                count3++;
                k+=2;
            }
            if(count3<=1){
                    int row1=arr[row][j-1];
                    int row2=arr[row][j+3];
                    int count4=0;
                    int count5=0;
                    k=1;
                    while(arr[row1][k]!=-1){
                        count4++;
                        k+=2;
                    }
                    k=1;
                    while(arr[row2][k]!=-1){
                        count5++;
                        k+=2;
                    }
                    if(count4>2&&row1!=-1){
                        redistribution(filename,arr,rw,row1,row,'l',ID);
                    }
                    else if(count5>2&&row2!=-1){
                        redistribution(filename,arr,rw,row1,row,'r',ID);
                    }
                    else{
                            int o=j-1;
                            arr[row][o]=-1;
                            o--;
                            arr[row][o]=-1;
                            o+=2;
                            while(arr[row][o]!=-1){
                                int temp1=arr[row][o+1];
                                arr[row][o-2]=arr[row][o];
                                arr[row][o+1]=arr[row][o-1];
                                arr[row][o-1]=temp1;
                                arr[row][o]=temp;
                                temp=arr[row][o];
                                o+=2;
                            }
                           vector<int> arr1;
                           int l=1;
                           while(arr[row1][l]!=-1){
                                arr1.push_back(arr[row1][l]);
                                l++;
                           }
                           l=0;
                            while(arr[row1][l]!=-1){
                                arr[row1][l]=-1;
                                l++;
                           }
                           arr[0][1]=row1;
                           writeFile(arr,filename);
                           for(int i=0;i<arr1.size();i+=2){
                                InsertNewRecordAtIndex(filename,arr1[i],arr1[i+1]);
                           }
                    }
                }
                else{
                    writeFile(arr,filename);
                }
           }
        }
            else if(arr[row][0]==0){
                int j=1;
                while(ID>arr[row][i]){
                j+=2;
            }
                arr[row][j]=-1;
                arr[row][j+1]=-1;
                int temp=arr[row][j];
                j+=2;
                while(arr[row][j]!=-1){
                    int temp1=arr[row][j+1];
                    arr[row][j-2]=arr[row][j];
                    arr[row][j+1]=arr[row][j-1];
                    arr[row][j-1]=temp1;
                    arr[row][j]=temp;
                    temp=arr[row][j];
                    j+=2;
                }
                int k=1;
            int count3=0;
            while(arr[row][k]!=-1){
                count3++;
                k+=2;
            }
            if(count3<=1){
                    int row1=arr[1][i-1];
                    int row2=arr[row][i+3];
                    int count4=0;
                    int count5=0;
                    k=1;
                    while(arr[row1][k]!=-1){
                        count4++;
                        k+=2;
                    }
                    k=1;
                    while(arr[row2][k]!=-1){
                        count5++;
                        k+=2;
                    }
                    if(count4>2&&row1!=-1){
                        redistribution(filename,arr,row,row1,1,'l',ID);
                    }
                    else if(count5>2&&row2!=-1){
                        redistribution(filename,arr,row,row1,1,'r',ID);
                    }
                    else{
                            int o=j-1;
                            arr[row][o]=-1;
                            o--;
                            arr[row][o]=-1;
                            o+=2;
                            while(arr[row][o]!=-1){
                                int temp1=arr[row][o+1];
                                arr[row][o-2]=arr[row][o];
                                arr[row][o+1]=arr[row][o-1];
                                arr[row][o-1]=temp1;
                                arr[row][o]=temp;
                                temp=arr[row][o];
                                o+=2;
                            }
                           vector<int> arr1;
                           int l=1;
                           while(arr[row1][l]!=-1){
                                arr1.push_back(arr[row1][l]);
                                l++;
                           }
                           l=0;
                            while(arr[row1][l]!=-1){
                                arr[row1][l]=-1;
                                l++;
                           }
                           arr[0][1]=row1;
                           writeFile(arr,filename);
                           for(int i=0;i<arr1.size();i+=2){
                                InsertNewRecordAtIndex(filename,arr1[i],arr1[i+1]);
                           }
                    }
                }
                else{
                    writeFile(arr,filename);
                }
            }
    }
    else{
        int row=arr[1][i+1];
        if(arr[row][0]==1){
            int j=1;
            while(ID>arr[row][j]){
            j+=2;
            }
            int rw=arr[row][j+1];
            if(arr[rw][0]==0){
            int z=1;
            while(ID>arr[rw][z]){
                z+=2;
            }
            arr[rw][z]=-1;
            arr[rw][z+1]=-1;
            int temp=arr[rw][z];
            z+=2;
            while(arr[rw][z]!=-1){
                int temp1=arr[rw][z+1];
                arr[rw][z-2]=arr[rw][z];
                arr[rw][z+1]=arr[rw][z-1];
                arr[rw][z-1]=temp1;
                arr[rw][z]=temp;
                temp=arr[rw][z];
                z+=2;
            }
            arr[row][j]=arr[rw][z-4];
            arr[1][i]=arr[rw][z-4];
            int k=1;
            int count3=0;
            while(arr[rw][k]!=-1){
                count3++;
                k+=2;
            }
            if(count3<=1){
                    int row1=arr[row][j-1];
                    int row2=arr[row][j+3];
                    int count4=0;
                    int count5=0;
                    k=1;
                    while(arr[row1][k]!=-1){
                        count4++;
                        k+=2;
                    }
                    k=1;
                    while(arr[row2][k]!=-1){
                        count5++;
                        k+=2;
                    }
                    if(count4>2&&row1!=-1){
                        redistribution(filename,arr,rw,row1,row,'l',ID);
                    }
                    else if(count5>2&&row2!=-1){
                        redistribution(filename,arr,rw,row1,row,'r',ID);
                    }
                    else{
                            int o=j-1;
                            arr[row][o]=-1;
                            o--;
                            arr[row][o]=-1;
                            o+=2;
                            while(arr[row][o]!=-1){
                                int temp1=arr[row][o+1];
                                arr[row][o-2]=arr[row][o];
                                arr[row][o+1]=arr[row][o-1];
                                arr[row][o-1]=temp1;
                                arr[row][o]=temp;
                                temp=arr[row][o];
                                o+=2;
                            }
                           vector<int> arr1;
                           int l=1;
                           while(arr[row1][l]!=-1){
                                arr1.push_back(arr[row1][l]);
                                l++;
                           }
                           l=0;
                            while(arr[row1][l]!=-1){
                                arr[row1][l]=-1;
                                l++;
                           }
                           arr[0][1]=row1;
                           writeFile(arr,filename);
                           for(int i=0;i<arr1.size();i+=2){
                                InsertNewRecordAtIndex(filename,arr1[i],arr1[i+1]);
                           }
                    }
                }
                else{
                    writeFile(arr,filename);
                }
            }

        }
            else if(arr[row][0]==0){
                int j=1;
                while(ID>arr[row][j]){
                j+=2;
            }
                arr[row][j]=-1;
                arr[row][j+1]=-1;
                int temp=arr[row][j];
                j+=2;
                while(arr[row][j]!=-1){
                    int temp1=arr[row][j+1];
                    arr[row][j-2]=arr[row][j];
                    arr[row][j+1]=arr[row][j-1];
                    arr[row][j-1]=temp1;
                    arr[row][j]=temp;
                    temp=arr[row][j];
                    j+=2;
                }
                arr[1][i]=arr[row][j-4];
                i=1;
                int count3=0;
                while(arr[row][i]!=-1){
                    count3++;
                    i+=2;
                }
                if(count3<=1){
                    int row1=arr[1][i-1];
                    int row2=arr[1][i+3];
                    int count4=0;
                    int count5=0;
                    int k=1;
                    while(arr[row1][k]!=-1){
                        count4++;
                        k+=2;
                    }
                    k=1;
                    while(arr[row2][k]!=-1){
                        count5++;
                        k+=2;
                    }
                    if(count4>2&&row1!=-1){
                        redistribution(filename,arr,row,row1,1,'l',ID);
                    }
                    else if(count5>2&&row2!=-1){
                        redistribution(filename,arr,row,row1,1,'r',ID);
                    }
                    else{
                            int o=j-1;
                            arr[row][o]=-1;
                            o--;
                            arr[row][o]=-1;
                            o+=2;
                            while(arr[row][o]!=-1){
                                int temp1=arr[row][o+1];
                                arr[row][o-2]=arr[row][o];
                                arr[row][o+1]=arr[row][o-1];
                                arr[row][o-1]=temp1;
                                arr[row][o]=temp;
                                temp=arr[row][o];
                                o+=2;
                            }
                            vector<int> arr1;
                            int l=1;
                            while(arr[row1][l]!=-1){
                                arr1.push_back(arr[row1][l]);
                                l++;
                            }
                            l = 0;
                            while(arr[row1][l]!=-1){
                                arr[row1][l]=-1;
                                l++;
                            }
                            arr[0][1]=row1;
                            writeFile(arr,filename);
                            for(int i=0;i<arr1.size();i+=2){
                                InsertNewRecordAtIndex(filename,arr1[i],arr1[i+1]);
                            }
                    }
                }
                else{
                    writeFile(arr,filename);
                }
            }
    }
}

int main() {
    fstream bTreeFile("btree.txt", ios::in | ios::out);
    bTreeFile.seekg(0, ios::end);
    if(bTreeFile.tellg() != 0) {
        CreateIndexFileFile("btree.txt",10,5);
    }
    bTreeFile.close();
    int choice, key, ref, searched, inserted;
    do {
        cout << "1- Insert Record           2- Delete Record\n3- Search Record           4- Display\n5- Exit\n-->  ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter the key and reference: ";
                cin >> key >> ref;
                inserted = InsertNewRecordAtIndex("btree.txt", key, ref);
                if(inserted == -1) {
                    cout << "Error Insertion\n";
                    break;
                }
                cout << "Inserted at " << inserted << endl;
                break;
            case 2:
                cout << "Enter the key: ";
                cin >> key;
                DeleteRecordFromIndex("btree.txt", key);
                break;
            case 3:
                cout << "Enter the key: ";
                cin >> key;
                searched = SearchARecord("btree.txt", key);
                if(searched == -1) {
                    cout << "Not Found\n";
                    break;
                }
                cout << "Reference " << searched << " Found\n";
                break;
            case 4:
                DisplayIndexFileContent("btree.txt");
                break;
            default:
                break;
        }
    } while(choice != 5);

    return 0;

//    InsertNewRecordAtIndex("btree.txt",3,12);
//    InsertNewRecordAtIndex("btree.txt",7,24);
//    InsertNewRecordAtIndex("btree.txt",10,48);
//    InsertNewRecordAtIndex("btree.txt",24,60);
//    InsertNewRecordAtIndex("btree.txt",14,72);
//    InsertNewRecordAtIndex("btree.txt",19,84);
//    InsertNewRecordAtIndex("btree.txt",30,96);
//    InsertNewRecordAtIndex("btree.txt",15,108);
//    InsertNewRecordAtIndex("btree.txt",1,120);
//    InsertNewRecordAtIndex("btree.txt",11,192);
//    InsertNewRecordAtIndex("btree.txt",5,132);
//    InsertNewRecordAtIndex("btree.txt",2,144);
//    InsertNewRecordAtIndex("btree.txt",8,156);
//    InsertNewRecordAtIndex("btree.txt",9,168);
//    InsertNewRecordAtIndex("btree.txt",6,180);
//    InsertNewRecordAtIndex("btree.txt",12,204);
//    InsertNewRecordAtIndex("btree.txt",17,216);
//    InsertNewRecordAtIndex("btree.txt",18,228);
//    InsertNewRecordAtIndex("btree.txt",32,240);
//    DeleteRecordFromIndex("btree.txt",10);
//    DeleteRecordFromIndex("btree.txt",9);
//    DeleteRecordFromIndex("btree.txt",8);

    //CreateIndexFileFile("btree.txt",10,5);
    // DisplayIndexFileContent("btree.txt");

    // cout<<SearchARecord("btree.txt",32);
}

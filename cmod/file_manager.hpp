#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector<string> get_files(string PATH=""){
    DIR *dir_ptr = NULL;
    struct dirent *file;
    vector<string> files;
    
    if((dir_ptr = opendir(PATH.c_str())) == NULL){
        cout << "can't read files in " << PATH << endl;
        return files;
    }

    while ((file = readdir(dir_ptr)) != NULL ){
        if (strcmp(file->d_name,".")&&strcmp(file->d_name,".."))
        files.push_back(file->d_name);
        
    }    
    
    closedir(dir_ptr);
    sort(files.begin(),files.end());
    return files;
}

string read_image (string PATH=""){
    vector<string> files = get_files(PATH);
    string file = PATH;
    
    for (int i=0; i<files.size(); i++){
        cout << i << " :\t" << files[i] << endl;
    }

    int n;
    cout << "Enter number" << endl;
    cin >> n;

    file += files[n];
    cout << file << endl;
    return file;
}

double** read_filter2D (string PATH="",int num=-1){
    vector<string> files = get_files(PATH);
    char file[256] = "";
    strcat(file,PATH.c_str());
    
    double** filter2D;

    if (num==-1){
        for (int i=0; i<files.size(); i++)
            cout << i << " :\t" << files[i] << endl;
        
        cout << "Enter number" << endl;
        cin >> num;
    }

    strcat(file,files[num].c_str());

    FILE *fp;
    fp = fopen(file,"r");
    if(fp == NULL){
        cout << "Read Filter Error!!\n";
        return filter2D;
    }

    int m,n;
    double temp;
    fscanf(fp,"%d",&m);
    fscanf(fp,"%d",&n);

    filter2D = (double**)malloc(sizeof(double*)*m);
    for (int i=0; i<m;i++){
        filter2D[i] = (double*)malloc(sizeof(double)*n);
    }

    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            fscanf(fp,"%lf",&temp);
            filter2D[i][j] = temp;
        }
    }

    fclose(fp);

    return filter2D;
}

double*** read_filter2D_all (string PATH=""){
    vector<string> files = get_files(PATH);
    
    double*** filters = (double***)malloc(sizeof(double**)*files.size());

    for (int iter=0; iter<files.size(); iter++){
        cout << iter << " :\t" << files[iter] << endl;
        filters[iter] = read_filter2D(PATH,iter);
    }

    return filters;
}

double**** read_filter3D_mult (string PATH="",int num=-1){
    vector<string> files = get_files(PATH);
    char file[256] = "";
    strcat(file,PATH.c_str());
    
    double**** filter3D_mult;

    if (num==-1){
        for (int i=0; i<files.size(); i++)
            cout << i << " :\t" << files[i] << endl;
        cout << "Enter number" << endl;
        cin >> num;
    }
   
    strcat(file,files[num].c_str());

    FILE *fp;
    fp = fopen(file,"r");
    if(fp == NULL){
        cout << "Read Filter Error!!\n";
        return filter3D_mult;
    }

    int depth,ch,m,n;
    double temp;

    fscanf(fp,"%d",&depth);
    fscanf(fp,"%d",&ch);
    fscanf(fp,"%d",&m);
    fscanf(fp,"%d",&n);

    filter3D_mult = (double****)malloc(sizeof(double***)*depth);
    for (int i=0; i<depth; i++){
        filter3D_mult[i] = (double***)malloc(sizeof(double**)*ch);
        for (int j=0; j<ch; j++){
            filter3D_mult[i][j] = (double**)malloc(sizeof(double*)*m);
            for (int k=0; k<m; k++){
                filter3D_mult[i][j][k] = (double*)malloc(sizeof(double)*n);
            }
        }
    }

    for (int dep=0; dep<depth; dep++){
        for (int iter=0; iter<ch; iter++){
            for (int i=0; i<m; i++){       
                for (int j=0; j<n; j++){
                    fscanf(fp,"%lf",&temp);
                    filter3D_mult[dep][iter][i][j] = temp;
                }   
            }
        }
    }
    fclose(fp);

    return filter3D_mult;
}

double***** read_filter3D_mult_all (string PATH=""){
    vector<string> files = get_files(PATH);

    double***** filters = (double*****)malloc(sizeof(double****)*files.size());
    for (int iter=0; iter<files.size(); iter++){
        cout << iter << " :\t" << files[iter] << endl;
        filters[iter] = read_filter3D_mult(PATH,iter);
    }
    return filters;
}

double* read_bias (string PATH="",int num=-1){
    vector<string> files = get_files(PATH);
    char file[256] = "";
    strcat(file,PATH.c_str());
    
    double* bias;

    if (num==-1){
        for (int i=0; i<files.size(); i++)
            cout << i << " :\t" << files[i] << endl;
        
        cout << "Enter number" << endl;
        cin >> num;
    }

    strcat(file,files[num].c_str());

    FILE *fp;
    fp = fopen(file,"r");
    if(fp == NULL){
        cout << "Read Bias Error!!\n";
        return bias;
    }

    int ch;
    double temp;
    fscanf(fp,"%d",&ch);
    bias = (double*)malloc(sizeof(double)*ch);

    for (int i=0; i<ch; i++){
            fscanf(fp,"%lf",&temp);
            bias[i] = temp;
    }

    fclose(fp);

    return bias;
}

double** read_bias_all (string PATH=""){
    vector<string> files = get_files(PATH);
    
    double** bias_all = (double**)malloc(sizeof(double*)*files.size());

    for (int iter=0; iter<files.size(); iter++){
        cout << iter << " :\t" << files[iter] << endl;
        bias_all[iter] = read_bias(PATH,iter);
    }

    return bias_all;
}

double** divide_filter2D(double** filter){
    double sum=0;
    for (int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            sum+=filter[i][j];
        }
    }
    for (int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            if (sum!=0)
                filter[i][j] /= sum;
        }
    }
    return filter;
}


#endif
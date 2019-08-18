#ifndef CNNLAYER_HPP
#define CNNLAYER_HPP

#include "cnn1ch.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class CNNLAYER{ // multi Channel CNN CLASS
public:
	CNN1CH *data; //CNN1CH * type data (2D data -> 3D data)
	int H; //height
	int W; //width
    int ch; //channel
	CNNLAYER();
	CNNLAYER(double***data,int H,int W, int ch); //생성자(data type 3D)  
    CNNLAYER(vector<Mat> img);//생성자(img를 vector로 받겠다) 
	~CNNLAYER();
	double** convolution(double***F, int F_row, int F_col, double bias, int stride, int padding);//function declaration 
    double*** convolution(double****F, int F_row, int F_col, double* bias, int F_ch, int stride, int padding);
	double*** maxpooling(int kernel ,int stride);
	double*** innerproduct(double**F, int F_row, int F_col);
	void activation();
    double*** softmax();
    void tempfunc();
};

CNNLAYER::CNNLAYER(double***data,int H,int W,int ch){ //생성자 declaration 
	this->H = H;
	this->W = W; 
    this->ch = ch;

	this->data = (CNN1CH*)malloc(ch * sizeof(CNN1CH)); //data memory allocation(using cnn1ch) //datasize = CNN1CH* 

    for(int i=0; i<ch;i++){ //for 3D data making
        CNN1CH data2D(data[i],H,W); //cnn1ch 생성자 호출(name : data2D)
        this->data[i] = data2D; //cnn1ch data2D -> class 2D data * channel number   
    }  
}

CNNLAYER::CNNLAYER(vector<Mat> img){ //생성자 declaration 
    this->ch = img.size();
    this->H = img[0].rows;
    this->W = img[0].cols;
    this->data = (CNN1CH*)malloc(sizeof(CNN1CH)*this->ch); //data memory allocation(using cnn1ch) //datasize = CNN1CH* 
    
    for(int i=0; i< this->ch; i++){
        CNN1CH data2D(img[i]); //cnn1ch 생성자 호출 (name : data2D)  
        this->data[i] = data2D; //cnn1ch data2D -> class 2D data * channel number 
    }
}

CNNLAYER::~CNNLAYER(){
}

double**CNNLAYER::convolution(double***F, int F_row, int F_col, double bias, int stride, int padding){
    double ** data2D;
    double ** temp;
    
    int C_row = (this->H - F_row + 2*padding)/stride +1;
    int C_col = (this->W - F_col + 2*padding)/stride +1;

    data2D = (double**)malloc(C_row* sizeof(double*)); //data 2D memory allocation
	for (int i = 0; i < C_row; i++){
		data2D[i] = (double*)malloc(C_col*sizeof(double));
        for(int j=0; j < C_col; j++){
            data2D[i][j] = 0; //data 2D initailization
        }
	}

    for(int i=0; i < this->ch; i++){ 
        temp = this->data[i].convolution(F[i], F_row, F_col, stride, padding); //temp <= class data[i] <- convolution result saving

        for (int row=0; row<C_row; row++){
            for (int col=0; col<C_col; col++){
                data2D[row][col] += temp[row][col]; //all convolution results saving -> data2D[row][col] 
            }
        }
    }
    for (int row=0; row<C_row; row++){
            for (int col=0; col<C_col; col++){
                data2D[row][col] += bias;
            }
        }
    return data2D;
}

//including depth value convolution//
double*** CNNLAYER::convolution(double****F, int F_row, int F_col, double* bias, int F_ch, int stride, int padding){
    double*** data3D = (double***)malloc(sizeof(double**)*F_ch); //data3D memory allocation

    for (int i=0; i<F_ch; i++){ //F_ch : depth
        data3D[i] = this->convolution(F[i], F_row, F_col, bias[i], stride, padding); //data3D[i] => convolution result saving
    }
   
    return data3D;
}

double*** CNNLAYER::maxpooling(int kernel,int stride){
    double*** data3D = (double***)malloc(sizeof(double**)*this->ch); //channel size -> memory allocation
    for (int i=0; i<this->ch; i++)
       data3D[i] = this->data[i].maxpooling(kernel, stride); //data3D[i] <= cnn1ch maxpooling result -> class data[i] saving 
    
    return data3D;
}

double*** CNNLAYER::innerproduct(double**F, int F_row, int F_col){ //3D -> 1D
    double*** data3D = (double***)malloc(sizeof(double**)*1); 
    data3D[0] = (double**)malloc(sizeof(double*)*1);
    data3D[0][0] = (double*)malloc(sizeof(double)*F_row); //data3D[0][0][F_row] 
    
    for (int i=0; i<F_row; i++) data3D[0][0][i] = 0;

    double** data2D; 
    double** T_F = (double**)malloc(sizeof(double*)*F_col);[ 
    for (int i=0; i<F_col; i++){
        T_F[i] = (double*)malloc(sizeof(double)*F_row); //T_F[F_col][F_row]
        for (int j=0; j<F_row; j++){
            T_F[i][j] = F[j][i]; //filter's F_row <-> F_col change
        }
    }

    double** slice_F = (double**)malloc(sizeof(double*)*this->H*this->W); //slice_F (size : input's H*W ) memory allocation
    for (int i=0; i<this->H*this->W; i++) 
        slice_F[i] = (double*)malloc(sizeof(double)*F_row); //slice_F[H*W][F_row]
    
    for (int iter=0; iter < this->ch; iter++){
        for (int i=0; i<this->H*this->W; i++){
            for (int j=0; j<F_row; j++){
                slice_F[i][j] = T_F[iter*(this->H*this->W)+i][j];
            }
        }
        data2D = this->data[iter].innerproduct(slice_F,this->H*this->W,F_row);
        for (int i=0; i<F_row; i++){
             data3D[0][0][i] += data2D[0][i];
        }
    }
    return data3D;
}

void CNNLAYER::activation(){
    for (int i=0; i<this->ch; i++)
        this->data[i].activation();

    return;
}

double*** CNNLAYER::softmax(){
    double*** data3D = (double***)malloc(sizeof(double**)*this->ch);
    for (int i=0; i<this->ch; i++){
        data3D[i] = this->data[i].softmax();
    }

    return data3D;
}

void CNNLAYER::tempfunc(){
    for (int i=0; i<this->ch; i++){
        for (int j=0; j<this->H; j++){
            for (int k=0; k<this->W; k++){
                if (this->data[i].data[j][k]<127)
                    this->data[i].data[j][k] = 1;
                else this->data[i].data[j][k] = 0;
            }
        }
    }
}


#endif

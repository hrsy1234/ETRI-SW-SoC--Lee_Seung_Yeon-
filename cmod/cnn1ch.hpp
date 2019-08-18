#ifndef CNN1CH_HPP
#define CNN1CH_HPP

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class CNN1CH{ //1 Channel CNN CLASS
public: 
	double **data; //data
	int H; //height
	int W; //width

	CNN1CH();
	CNN1CH(double**data,int H,int W); //생성자  
	CNN1CH(Mat img); //생성자 
	~CNN1CH(); // 소멸자  
	double** convolution(double**F, int F_row, int F_col, int stride, int padding); // class convolution function
	double** maxpooling(int kernel ,int stride); //class maxpooling function
	double** innerproduct(double**F, int F_row, int F_col); //class innerproduct function
	void activation(); //class activation function
	double** softmax(); //class softmax function
};

CNN1CH::CNN1CH(double**data,int H,int W){ //생성자 declaration
	this->H = H; //class에있는 H를쓰겠다
	this->W = W; //class에있는 W를 쓰겠다 

	this->data = (double**)malloc(H * sizeof(double*));   ////2 dimension data memory allocation 
	for(int i=0 ; i<H; i++){
		this->data[i] = (double*)malloc( W * sizeof(double));
		for(int j=0; j<W; j++){
			this->data[i][j] = data[i][j];
		}
	}
}

CNN1CH::CNN1CH(Mat img){ //생성자 declaration 
	this->H = img.rows; //class ->H  image row value saving 
	this->W = img.cols; // class ->W image col value saving 
	this->data = (double**)malloc(sizeof(double*)*this->H); //2 demension data memory allocation
	for (int i=0; i<this->H; i++){
		this->data[i] = (double*)malloc(sizeof(double)*this->W);
		for (int j=0; j<this->W; j++){
			this->data[i][j] = img.at<uchar>(i,j); //data[i][j] gray scale image saving   
		}
	}
}

CNN1CH::~CNN1CH()
{
}



double** padding(double **data, int H, int W,int padding_size){ //padding function
	
	double **padding; 
	int padding_row = H+2*padding_size; 
	int padding_col = W+2*padding_size;
	
    padding = (double**)malloc(padding_row * sizeof(double*));   //padding memory allocation
	for (int i = 0; i < padding_row; i++)
	{
		padding[i] = (double*)malloc(padding_col * sizeof(double));
	}
	
	
	for(int i=0; i<padding_row; i++){ 
			for(int j=0; j<padding_col; j++)
			{
				padding[i][j] = 0; //padding initialization
			}
			
	}
	
	for(int i=0; i<padding_row; i++){
			for(int j=0; j<padding_col; j++){
				double max=0;
				if(i<padding_size|| j<padding_size || 
				i>=padding_row-padding_size || j>=padding_col-padding_size) padding[i][j] = 0; //zero padding
				else padding[i][j] = data[i-padding_size][j-padding_size];
			}
	}
	
	return padding;
}

double** CNN1CH::convolution(double**F, int F_row, int F_col, int stride, int padding_size){

	double **C;
	int C_row = (this->H - F_row+ 2*padding_size)/stride + 1;
    int C_col = (this->W - F_col+ 2*padding_size)/stride + 1;

    double ** pad = padding(this->data,this->H,this->W,padding_size);

	C = (double**)malloc(C_row* sizeof(double*));   ////Convolution result C-> memory allocation
	for (int i = 0; i < C_row; i++){
		C[i] = (double*)malloc( C_col * sizeof(double));
	}
	
	for(int i=0; i<C_row; i++){ 
		for(int j=0; j<C_col; j++){
			C[i][j] = 0;             // C -> initialization
		}
	}

	
	////convolution calculation////
	for(int i=0; i<C_row; i++){  
     	for(int j=0; j<C_col; j++){
			double temp = 0;
         	for(int k=0; k<F_row;k++){
             	for(int l=0; l<F_col; l++)
					temp += double(pad[k+i*stride][l+j*stride] * F[k][l]); 
            }
			C[i][j] = temp;		
        }    
    }
	
    return C;
}
	
double** CNN1CH::maxpooling(int kernel, int stride){
	double max = 0;
	double **pooling;
	int pooling_row = (this->H-kernel)/stride +1;
	int pooling_col = (this->W-kernel)/stride +1;
	
    pooling = (double**)malloc(pooling_row* sizeof(double*));   //max_pooling 3D memory allocation
	for (int i = 0; i < pooling_row; i++){
		pooling[i] = (double*)malloc(pooling_col * sizeof(double));
		
	}
	
	for(int i=0; i<pooling_row; i++){
		for(int j=0; j<pooling_col; j++){
			pooling[i][j] = 0; // pooling value initialization
		}
	}
	
	
	for(int i=0; i<pooling_row; i++){  
		for(int j=0; j<pooling_col; j++){
			max=this->data[i*stride][j*stride];//max initialization//same way : max = INT_MIN(because of nagative number)
			for(int k=0; k<kernel;k++){
				for( int l=0; l<kernel; l++){
					if(max < this->data[i*stride+k][j*stride+l]) max = this->data[i*stride+k][j*stride+l];
				}
			} 
			pooling[i][j] = max; 
		}
	}
	return pooling;
}

double** CNN1CH::innerproduct(double**F, int F_row, int F_col){  // 2D -> 1D function
	double**ip = (double**)malloc(1* sizeof(double*)); // ip row value = 1 memory allocation
	ip[0] = (double*)malloc(F_col * sizeof(double)); // ip col value = F_col memory allocation
	
	for (int i = 0; i < F_col; i++){
		for (int j = 0; j < this->H*this->W; j++){
			ip[0][i] += this->data[j/this->W][j%this->W] * F[j][i]; //data * filter matrix multiplication(ip = 1D)
		}		
	}
	return ip;
}
void CNN1CH::activation(){ // relu function

	double sigma;
	for(int i=0; i<this->H; i++){
		for(int j=0; j<this->W; j++){
			sigma = this->data[i][j];
			if(sigma < 0){
				sigma = 0;
			}
			this->data[i][j] = sigma;
		}
	}
	return;
}

double** CNN1CH::softmax(){ //probability calculation 
	double** data2D = (double**)malloc(sizeof(double*)*this->H); 
	for (int i=0; i < this->H; i++)
		data2D[i] = (double*)malloc(sizeof(double)*this->W);
	
	double sum = 0;
	for (int i=0; i < this->H; i++){
		for (int j=0; j < this->W; j++){
			sum += exp(this->data[i][j]);
		}
	}

	for (int i=0; i < this->H; i++){
		for (int j=0; j < this->W; j++){
			data2D[i][j] = exp(this->data[i][j])/sum;
		}
	}
	return data2D;
}
// ///// filter /////
// double** filter(double F_row, double F_col){
// 	double i,j;
// 	double **F;
	
//     F = (double**)malloc(F_row * sizeof(double*));   //Filter
// 		for (i = 0; i < F_row; i++){
// 			F[i] = (double*)malloc(F_col * sizeof(double));
// 		}
	
// 	prdoublef("write Filter value");
// 	for (i = 0; i < F_row; i++){
// 		for (j = 0; j < F_col; j++){
// 			scanf("%d", &F[i][j]);
// 		}
// 	}
// 	return F;
// }
////padding function//////


// double *** image_to_double_arr(Mat A){
// 	double*** result;
// 	double A_row = A.rows;
// 	double A_col = A.cols;
// 	int i,j,m;
	
// 	result = (double***)malloc(ch * sizeof(double**));   
// 	for (i = 0; i < ch; i++)
// 	{
// 		*(result+i) = (double**)malloc(A_row * sizeof(double*));
// 		for(j=0; j<A_row;j++){
// 			*(*(result+i)+j) = (double*)malloc(A_col * sizeof(double));
// 		}
// 	}
	
// 	for(int k=0; k<ch; k++){
// 	for( i=0; i<A_row; i++){
// 		for( j=0; j<A_col; j++){
// 			result[k][i][j] = 0;
// 		}
// 	}
// 	}
// 	for(m=0; m<ch; m++){
// 		for(i=0; i<A_row; i++){  
//      		for( j=0; j<A_col; j++){
//             	result[m][i][j] = A.at<Vec3b>(i,j)[m];
//          	}
//     	}
// 	}
        
// 	return result;
// }

// //////array -> image /////
// Mat double_arr_to_image(double ***A,double A_row, double A_col,double type){
// 	Mat result(A_row,A_col,type);

// 	int i,j,m;

// 	for(m=0; m<ch; m++){
// 		for(i=0; i<A_row; i++){  
//      		for( j=0; j<A_col; j++){
//              	 result.at<Vec3b>(i,j)[m]=A[m][i][j]; 
//          	}
//      	}
// 	}

// 	return result;
// }


#endif

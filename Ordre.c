/*
date：2018/11/30
author:BetterMe1
program:关于选择排序、冒泡排序、归并排序、快速排序、插入排序算法时间效率的研究;
compiler:Visual Studio 2013
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>//用到clock()函数
#include<Windows.h>

int begintime = 0;
int endtime = 0;
int arr1[100000] = { 0 };

//交换数组函数;
void swap(int* a, int* b){
	int c = 0;
	c = *a;
	*a = *b;
	*b = c;
}

//选择排序;
//分析：选出一个最值将其与第一个数进行交换，len个数是len-1趟;
void select_sort(int arr[], int len){
	int min = 0;
	for (int i = 0; i < len - 1; i++){//外层循环控制趟数;
		min = i;//假设第一个数为最小值;
		for (int j = i + 1; j < len; j++){//从下一个数至以后一个数中寻找最值;
			if (arr[min] > arr[j]){ //后面有比最值更小的;
				min = j;     //下标记到min中;
			}
		}
		if (min != i){
			swap(&arr[min], &arr[i]);//交换两数的值，此时将最小的数交换到了第一位;
		}
	}
}

//冒泡排序;
//分析：每趟比价中进行len-1次的两两比较，第j次比较中进行len-j次的比较，每趟结束后，将最值沉底;
void maopao_sort(int arr[], int len){
	for (int i = 0; i < len - 1; i++){//外层循环控制趟数;
		for (int j = 0; j < len - i; j++){//第j趟比较len-j次;
			if (arr[j] > arr[j + 1]){  //若下一个小;
				swap(&arr[j], &arr[j + 1]);//交换;
			}
		}
	}
}
void merge(int arr[], int low, int mid, int high){
	int i, k;
	int *tmp = (int *)malloc((high - low + 1)*sizeof(int));
	//申请空间，使其大小为两个;
	int left_low = low;
	int left_high = mid;
	int right_low = mid + 1;
	int right_high = high;
	for (k = 0; left_low <= left_high && right_low <= right_high; k++){ // 比较两个指针所指向的元素;
		if (arr[left_low] <= arr[right_low]){
			tmp[k] = arr[left_low++];
		}
		else{
			tmp[k] = arr[right_low++];
		}
	}
	if (left_low <= left_high){ //若第一个序列有剩余，直接复制出来粘到合并序列尾;
		for (i = left_low; i <= left_high; i++){
			tmp[k++] = arr[i];
		}
	}
	if (right_low <= right_high){
		//若第二个序列有剩余，直接复制出来粘到合并序列尾;
		for (i = right_low; i <= right_high; i++){
			tmp[k++] = arr[i];
		}
	}
	for (i = 0; i < high - low + 1; i++){
		arr[low + i] = tmp[i];
	}
	free(tmp);
}
//合并排序;
//分析：将待排序序列分为两部分，依次对分得的两个部分再次使用归并排序，之后再对其进行合并;
void merge_sort(int arr[], unsigned int first, unsigned int last){
	int mid = 0;
	if (first < last){
		mid = first/2 + last/2;// 防止溢出 ;
		merge_sort(arr, first, mid);
		merge_sort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
}

//快速排序的作用;
//分析：数组中取出第一个数（默认）作为基准数。将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。
//再对左右区间重复上述步骤，直到各区间只有一个数;
//交换的次数较少，提高了程序的运行速度;
//在最差的情况下，时间复杂度仍和冒泡排序一样是O(N ^ 2)，但是平均复杂度是O(NlonN);
void quick_sort(int arr[], int begin, int end){
	int i = begin;
	int j = end;
	int x = arr[begin];
	if (begin < end){
		while (begin < end){
			while (begin<end && arr[end]>x){
				end--;
			}
			if (begin < end){
				arr[begin++] = arr[end];
			}
			while (begin < end && arr[begin] < x){
				begin++;
			}
			if (begin < end){
				arr[end--] = arr[begin];
			}
		}
		arr[begin] = x;
		quick_sort(arr, i, end - 1);//用递归将选取的标准数左右两边都进行排序;
		quick_sort(arr, begin + 1, j);
	}
}



//插入排序;
//分析：将数组的第一个数记为有序序列，其后len-1个数组成无序列，将无序序列中的数依次插入有序序列;
void charu_sort(int arr[], int len){
	int t = 0;
	int j = 0;
	for (int i = 1; i < len; i++){//从第二个数开始，直至最后一个数;
		t = arr[i];//待插入的数;
		for (j = i - 1; j >= 0 && t < arr[j]; j--){//在有序序列中寻找插入位置;
			arr[j + 1] = arr[j];//还未找到插入位置,当前元素后移，为插入的数准备空间;
		}
		arr[j + 1] = t;//找到插入位置，将元素插入;
	}
}

//计算20组样本选择排序所用的时间
void select_time(int len){
	int sum = 0;
	int n = 0;//样本;
	printf("20组样本(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		/*for (int i = 0; i < len; i++){
			printf("%d\n", arr1[i]);
			count++;
		}*/
		/*printf("\n");
		printf("%d\n", count);*/
		begintime = clock();	//计时开始;
		select_sort(arr1,len);//选择排序;
		endtime = clock();	//计时结束;
		sum = sum + endtime - begintime;//总时间;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("排序所花平均时间:> %d \n", (sum / 20));
}
//计算20组样本冒泡排序所用的时间
void maopao_time(int len){
	int sum = 0;
	int n = 0;//样本;
	printf("20组样本(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//计时开始;
		maopao_sort(arr1, len);//冒泡排序;
		endtime = clock();	//计时结束;
		sum = sum + endtime - begintime;//总时间;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("排序所花平均时间:> %d \n", (sum / 20));
}
//计算20组样本合并排序所用的时间
void merge_time(int len){
	int sum = 0;
	int n = 0;//样本;
	printf("20组样本(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//计时开始;
		merge_sort(arr1, 0, len - 1);//合并排序;
		endtime = clock();	//计时结束;
		sum = sum + endtime - begintime;//总时间;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("排序所花平均时间:> %d \n", (sum / 20));
}
//计算20组样本快速排序所用的时间
void quick_time(int len){
	int sum = 0;
	int n = 0;//样本;
	printf("20组样本(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//计时开始;
		quick_sort(arr1, 0, len - 1);//快速排序;
		endtime = clock();	//计时结束;
		sum = sum + endtime - begintime;//总时间;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("排序所花平均时间:> %d \n", (sum / 20));
}
//计算20组样本插入排序所用的时间
void charu_time(int len){
	int sum = 0;
	int n = 0;//样本;
	printf("20组样本(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//计时开始;
		charu_sort(arr1, len);//插入排序;
		endtime = clock();	//计时结束;
		sum = sum + endtime - begintime;//总时间;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("排序所花平均时间:> %d \n", (sum / 20));
}
int main(){
	int input = 0;
	int len = 10;
	while (input<1||input>5){
		printf("1.选择排序  2.冒泡排序  3.合并排序  4.快速排序  5.插入排序\n");
		printf("请输入你的选择:>");
		scanf("%d", &input);
		switch (input){
		case 1:
			while (len <= 100000){
				printf("数组长度为%d时：\n",len);
				select_time(len); //数据规模为10时;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 2:
			while (len <= 100000){
				printf("数组长度为%d时：\n", len);
				maopao_time(len);//计算冒泡排序所用的时间;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 3:
			while (len <= 100000){
				printf("数组长度为%d时：\n", len);
				merge_time(len);//计算合并排序所用的时间;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 4:
			while (len <= 100000){
				printf("数组长度为%d时：\n", len);
				quick_time(len);//计算快速排序所用的时间;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 5:
			while (len <= 100000){
				printf("数组长度为%d时：\n", len);
				charu_time(len);//计算插入排序所用的时间;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		default:
			printf("选择错误，请重新输入！");
		}
	}
	/*for (i = 0; i < len; i++){
		printf("%d\n", arr1[i]);
	}*/
	system("pause");
	return 0;
}
/*
date��2018/11/30
author:BetterMe1
program:����ѡ������ð�����򡢹鲢���򡢿������򡢲��������㷨ʱ��Ч�ʵ��о�;
compiler:Visual Studio 2013
*/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>//�õ�clock()����
#include<Windows.h>

int begintime = 0;
int endtime = 0;
int arr1[100000] = { 0 };

//�������麯��;
void swap(int* a, int* b){
	int c = 0;
	c = *a;
	*a = *b;
	*b = c;
}

//ѡ������;
//������ѡ��һ����ֵ�������һ�������н�����len������len-1��;
void select_sort(int arr[], int len){
	int min = 0;
	for (int i = 0; i < len - 1; i++){//���ѭ����������;
		min = i;//�����һ����Ϊ��Сֵ;
		for (int j = i + 1; j < len; j++){//����һ�������Ժ�һ������Ѱ����ֵ;
			if (arr[min] > arr[j]){ //�����б���ֵ��С��;
				min = j;     //�±�ǵ�min��;
			}
		}
		if (min != i){
			swap(&arr[min], &arr[i]);//����������ֵ����ʱ����С�����������˵�һλ;
		}
	}
}

//ð������;
//������ÿ�˱ȼ��н���len-1�ε������Ƚϣ���j�αȽ��н���len-j�εıȽϣ�ÿ�˽����󣬽���ֵ����;
void maopao_sort(int arr[], int len){
	for (int i = 0; i < len - 1; i++){//���ѭ����������;
		for (int j = 0; j < len - i; j++){//��j�˱Ƚ�len-j��;
			if (arr[j] > arr[j + 1]){  //����һ��С;
				swap(&arr[j], &arr[j + 1]);//����;
			}
		}
	}
}
void merge(int arr[], int low, int mid, int high){
	int i, k;
	int *tmp = (int *)malloc((high - low + 1)*sizeof(int));
	//����ռ䣬ʹ���СΪ����;
	int left_low = low;
	int left_high = mid;
	int right_low = mid + 1;
	int right_high = high;
	for (k = 0; left_low <= left_high && right_low <= right_high; k++){ // �Ƚ�����ָ����ָ���Ԫ��;
		if (arr[left_low] <= arr[right_low]){
			tmp[k] = arr[left_low++];
		}
		else{
			tmp[k] = arr[right_low++];
		}
	}
	if (left_low <= left_high){ //����һ��������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β;
		for (i = left_low; i <= left_high; i++){
			tmp[k++] = arr[i];
		}
	}
	if (right_low <= right_high){
		//���ڶ���������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β;
		for (i = right_low; i <= right_high; i++){
			tmp[k++] = arr[i];
		}
	}
	for (i = 0; i < high - low + 1; i++){
		arr[low + i] = tmp[i];
	}
	free(tmp);
}
//�ϲ�����;
//�����������������з�Ϊ�����֣����ζԷֵõ����������ٴ�ʹ�ù鲢����֮���ٶ�����кϲ�;
void merge_sort(int arr[], unsigned int first, unsigned int last){
	int mid = 0;
	if (first < last){
		mid = first/2 + last/2;// ��ֹ��� ;
		merge_sort(arr, first, mid);
		merge_sort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
}

//�������������;
//������������ȡ����һ������Ĭ�ϣ���Ϊ��׼������������������ȫ�ŵ������ұߣ�С�ڻ����������ȫ�ŵ�������ߡ�
//�ٶ����������ظ��������裬ֱ��������ֻ��һ����;
//�����Ĵ������٣�����˳���������ٶ�;
//����������£�ʱ�临�Ӷ��Ժ�ð������һ����O(N ^ 2)������ƽ�����Ӷ���O(NlonN);
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
		quick_sort(arr, i, end - 1);//�õݹ齫ѡȡ�ı�׼���������߶���������;
		quick_sort(arr, begin + 1, j);
	}
}



//��������;
//������������ĵ�һ������Ϊ�������У����len-1������������У������������е������β�����������;
void charu_sort(int arr[], int len){
	int t = 0;
	int j = 0;
	for (int i = 1; i < len; i++){//�ӵڶ�������ʼ��ֱ�����һ����;
		t = arr[i];//���������;
		for (j = i - 1; j >= 0 && t < arr[j]; j--){//������������Ѱ�Ҳ���λ��;
			arr[j + 1] = arr[j];//��δ�ҵ�����λ��,��ǰԪ�غ��ƣ�Ϊ�������׼���ռ�;
		}
		arr[j + 1] = t;//�ҵ�����λ�ã���Ԫ�ز���;
	}
}

//����20������ѡ���������õ�ʱ��
void select_time(int len){
	int sum = 0;
	int n = 0;//����;
	printf("20������(ms):>");
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
		begintime = clock();	//��ʱ��ʼ;
		select_sort(arr1,len);//ѡ������;
		endtime = clock();	//��ʱ����;
		sum = sum + endtime - begintime;//��ʱ��;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("��������ƽ��ʱ��:> %d \n", (sum / 20));
}
//����20������ð���������õ�ʱ��
void maopao_time(int len){
	int sum = 0;
	int n = 0;//����;
	printf("20������(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//��ʱ��ʼ;
		maopao_sort(arr1, len);//ð������;
		endtime = clock();	//��ʱ����;
		sum = sum + endtime - begintime;//��ʱ��;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("��������ƽ��ʱ��:> %d \n", (sum / 20));
}
//����20�������ϲ��������õ�ʱ��
void merge_time(int len){
	int sum = 0;
	int n = 0;//����;
	printf("20������(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//��ʱ��ʼ;
		merge_sort(arr1, 0, len - 1);//�ϲ�����;
		endtime = clock();	//��ʱ����;
		sum = sum + endtime - begintime;//��ʱ��;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("��������ƽ��ʱ��:> %d \n", (sum / 20));
}
//����20�����������������õ�ʱ��
void quick_time(int len){
	int sum = 0;
	int n = 0;//����;
	printf("20������(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//��ʱ��ʼ;
		quick_sort(arr1, 0, len - 1);//��������;
		endtime = clock();	//��ʱ����;
		sum = sum + endtime - begintime;//��ʱ��;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("��������ƽ��ʱ��:> %d \n", (sum / 20));
}
//����20�����������������õ�ʱ��
void charu_time(int len){
	int sum = 0;
	int n = 0;//����;
	printf("20������(ms):>");
	while (n < 20){
		for (int i = 0; i < len; i++){
			arr1[i] = rand();
		}
		begintime = clock();	//��ʱ��ʼ;
		charu_sort(arr1, len);//��������;
		endtime = clock();	//��ʱ����;
		sum = sum + endtime - begintime;//��ʱ��;
		printf(" %d ", endtime - begintime);
		if (n == 19){
			printf("\n");
		}
		n++;
	}
	printf("��������ƽ��ʱ��:> %d \n", (sum / 20));
}
int main(){
	int input = 0;
	int len = 10;
	while (input<1||input>5){
		printf("1.ѡ������  2.ð������  3.�ϲ�����  4.��������  5.��������\n");
		printf("���������ѡ��:>");
		scanf("%d", &input);
		switch (input){
		case 1:
			while (len <= 100000){
				printf("���鳤��Ϊ%dʱ��\n",len);
				select_time(len); //���ݹ�ģΪ10ʱ;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 2:
			while (len <= 100000){
				printf("���鳤��Ϊ%dʱ��\n", len);
				maopao_time(len);//����ð���������õ�ʱ��;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 3:
			while (len <= 100000){
				printf("���鳤��Ϊ%dʱ��\n", len);
				merge_time(len);//����ϲ��������õ�ʱ��;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 4:
			while (len <= 100000){
				printf("���鳤��Ϊ%dʱ��\n", len);
				quick_time(len);//��������������õ�ʱ��;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		case 5:
			while (len <= 100000){
				printf("���鳤��Ϊ%dʱ��\n", len);
				charu_time(len);//��������������õ�ʱ��;
				if (len != 100000){
					printf("----------------------------------------------------------------------------------\n");
				}
				len = len * 10;
			}
			break;
		default:
			printf("ѡ��������������룡");
		}
	}
	/*for (i = 0; i < len; i++){
		printf("%d\n", arr1[i]);
	}*/
	system("pause");
	return 0;
}
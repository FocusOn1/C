#include<stdio.h>
#include<stdlib.h>
void print(int arr[], int n)//���
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}putchar('\n');
}
void getone(int arr[], int tarr[], int left, int mid, int right)//�����Һϲ�
{
	int L_arr = left;//�������һλ
	int R_arr = mid + 1;//�������һλ
	int i = left;
	while (L_arr <= mid && R_arr <= right)//������Ա�����
	{
		if (arr[L_arr] < arr[R_arr])
		{
			tarr[i++] = arr[L_arr++];
		}
		else tarr[i++] = arr[R_arr++];
	}
	while (L_arr <= mid)//ʣ����������
	{
		tarr[i++] = arr[L_arr++];
	}
	while (R_arr <= right)//ʣ����������
	{
		tarr[i++] = arr[R_arr++];;
	}
	while (left <= right)//����ʱ���������ת��
	{
		arr[left] = tarr[left];
		left++;
	}
}
void gettwo(int arr[], int tarr[], int left, int right)//�ݹ����
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		gettwo(arr, tarr, left, mid);
		gettwo(arr, tarr, mid + 1, right);
		getone(arr, tarr, left, mid, right);
	}
}
void merge(int arr[], int n)//����ռ�
{
	int* tarr = (int*)malloc(n * sizeof(int));
	if (tarr)//����ɹ�
	{
		gettwo(arr, tarr, 0, n - 1);
		free(tarr);//�ͷ���ʱ����ռ�
	}
	else printf("error!");//����ʧ��
}
int main(int argc, char const* argv[])
{
	int arr[] = { 38,27,43,3,9,82,10 };
	int n = 7;
	printf("����ǰ��\n");
	print(arr, n);
	merge(arr, n);
	printf("�����\n");
	print(arr, n);
	return 0;
}

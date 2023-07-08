#include<stdio.h>
#include<stdlib.h>
void print(int arr[], int n)//输出
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}putchar('\n');
}
void getone(int arr[], int tarr[], int left, int mid, int right)//排序且合并
{
	int L_arr = left;//左数组第一位
	int R_arr = mid + 1;//右数组第一位
	int i = left;
	while (L_arr <= mid && R_arr <= right)//左右组对比排序
	{
		if (arr[L_arr] < arr[R_arr])
		{
			tarr[i++] = arr[L_arr++];
		}
		else tarr[i++] = arr[R_arr++];
	}
	while (L_arr <= mid)//剩下左组排序
	{
		tarr[i++] = arr[L_arr++];
	}
	while (R_arr <= right)//剩下右组排序
	{
		tarr[i++] = arr[R_arr++];;
	}
	while (left <= right)//将临时数组的数据转移
	{
		arr[left] = tarr[left];
		left++;
	}
}
void gettwo(int arr[], int tarr[], int left, int right)//递归分组
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		gettwo(arr, tarr, left, mid);
		gettwo(arr, tarr, mid + 1, right);
		getone(arr, tarr, left, mid, right);
	}
}
void merge(int arr[], int n)//分配空间
{
	int* tarr = (int*)malloc(n * sizeof(int));
	if (tarr)//分配成功
	{
		gettwo(arr, tarr, 0, n - 1);
		free(tarr);//释放临时数组空间
	}
	else printf("error!");//分配失败
}
int main(int argc, char const* argv[])
{
	int arr[] = { 38,27,43,3,9,82,10 };
	int n = 7;
	printf("排序前：\n");
	print(arr, n);
	merge(arr, n);
	printf("排序后：\n");
	print(arr, n);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i,j,k;
	int s,n;//s个n维向量组
	int groupNum=0;//极大线性无关组个数
	double **array,**deterArray;
	double **groupArray,**result;
	int *groupPosition;
	
	void printfDouble2Dimension(int s, int n, double **array);
	void printfInt1Dimension(int n, int *array);	
	void primaryRowChange(int s, int n, double **array);
	int getGreatLinerlyIndependentGroup(int s, int n, double **array, int *result);
	void calcOrthogonalization(int s, int n, double **array, double **result);
	
	printf("请输入向量个数S:");
	scanf("%d",&s);
	printf("请输入向量维度N:");
	scanf("%d",&n);
	array=(double**)malloc(s*sizeof(double*));
	deterArray=(double**)malloc(n*sizeof(double*));
	groupPosition =(int*)malloc(s*sizeof(int));

	for(i=0;i<n;i++)
	{		
		deterArray[i]=(double*)malloc(n*sizeof(double));
	}
	for(i=0;i<s;i++)
		*(groupPosition+i)=-1;
	//
	for(i=0;i<s;i++)
	{
		array[i]=(double*)malloc(n*sizeof(double));
		for(j=0;j<n;j++)
		{
			scanf("%lf",*(array+i)+j);
			*(*(deterArray+j)+i) = *(*(array+i)+j);
		}
	}

	printf("1:\n");
	printfDouble2Dimension(s,n,array);
	printf("2:\n");
	printfDouble2Dimension(n,s,deterArray);

	primaryRowChange(n,s,deterArray);
	
	printf("2:\n");
	printfDouble2Dimension(n,s,deterArray);

	groupNum = getGreatLinerlyIndependentGroup(n,s,deterArray,groupPosition);

	printf("极大线性无关组:\n");
	printfInt1Dimension(s,groupPosition);

	groupArray= (double**)malloc(groupNum*sizeof(double*));
	result = (double**)malloc(groupNum*sizeof(double*));
	for(i=0;i<groupNum;i++)
	{
		if(*(groupPosition+i)!=-1)
		{
			groupArray[i] = (double*)malloc(n*sizeof(double));
			result[i] = (double*)malloc(n*sizeof(double));
			groupArray[i] = *(array+ *(groupPosition+i));
			result[i] = *(array+ *(groupPosition+i));
		}
	}

	printfDouble2Dimension(groupNum,n,groupArray);

	calcOrthogonalization(groupNum,n,groupArray,result);
	
	printf("正交向量组:\n");
	printfDouble2Dimension(groupNum,n,result);

	system("pause");
}
//初等行变换
void primaryRowChange(int s, int n, double **array)
{
	int i,j,k,ii,kk,flag;
	double temp;
	for(i=0,j=0;i<s-1;i++,j++)//s行，最外围只需要变换s-1
	{		
		ii=i;
		//如果行的首元为0，向下查找一个不为0的，然后换行
		if(*(*(array+i)+j) == 0)
		{
			flag=0;
			for(k=i+1;k<s;k++)
			{
				if(*(*(array+k)+j)!=0)//第k行与第i行交换
				{
					for(kk=j;kk<n;kk++)
					{	
						temp=*(*(array+k)+kk);
						*(*(array+k)+kk) = *(*(array+i)+kk);
						*(*(array+i)+kk) = temp;
					}			
					flag =1;
					break;
				}
			}		
			//判断是交换成功，如果没有成功，则i--
			if(!flag)
			{				
				i--;
				continue;
			}
			i--;
			j--;
			continue;
		}
		for(;ii<s-1;ii++)
		{
			if(*(*(array+ii+1)+j)==0)
				continue;
			temp =-*(*(array+ii+1)+j) / *(*(array+i)+j);
			for(k=j;k<n;k++)
				*(*(array+ii+1)+k) += *(*(array+i)+k) * temp;
				
		}
	}
}

//获取极大线性无关组位置及个数
int getGreatLinerlyIndependentGroup(int s, int n, double **array, int *result)
{
	int i,j,num=0;
	for(i=0;i<s;i++)
	{
		for(j=0;j<n;j++)
		{
			if(*(*(array+i)+j)!=0)
			{
				*(result + num++)=j;
				break;
			}
		}
	}
	return num;
}

//计算正交向量组
void calcOrthogonalization(int s, int n, double **array, double **result)
{
	int i,j,k;
	double **tempArray ,temp;
	double getInnerProduct(int n,double *array1, double *array2);
	for(i=0;i<s;i++)
	{
		tempArray = (double**)malloc(i*sizeof(double*));
		for(j=0;j<i;j++)
		{
			tempArray[j] = (double*)malloc(n*sizeof(double));
			temp = getInnerProduct(n,*(array+i),*(result+j)) / getInnerProduct(n,*(result+j),*(result+j));
			for(k=0;k<n;k++)
			{
				*(*(tempArray+j)+k) = temp * *(*(result+j)+k);
			}
		}
		for(j=0;j<i;j++)
		{
			for(k=0;k<n;k++)
				*(*(array+i)+k) -= *(*(tempArray+j)+k);
		}
	}
}

//计算两个向量的内积
double getInnerProduct(int n, double *array1, double *array2)
{
	int i;
	double result=0;
	for(i=0;i<n;i++)
		result += *(array1+i) * *(array2+i);
	return result;
}
//print array
void printfDouble2Dimension(int s, int n, double **array)
{
	int i,j;
	for(i=0;i<s;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%6.2lf",*(*(array+i)+j));
		}
		printf("\n");
	}
}


void printfInt1Dimension(int n, int *array)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%4d",*(array+i));
	}
	printf("\n");
}

#include<stdio.h>

int target[1024],cluster[1024][1024],total_of_cluster[1024];

double means[1024];

int cnt;

int select(int now,int total);

void add(int now,int select);

void clustering(int k);

double compute(int k);

int main()
{
	FILE *fin  = fopen ("test.in", "r");
	while(fscanf(fin,"%d",target+cnt)!=EOF)
	{
		cnt++;
	}
	clustering(3);
	return 0;
}

void clustering(int k)
{
	int i,j;
	double e,E;
	for(i=0;i<k;i++)
	{
		means[i]=target[i];
	}
	e=0;
	do
	{
		e=E;
		for(i=0;i<k;i++)
		{
			total_of_cluster[i]=0;
		}
		for(i=0;i<cnt;i++)
		{
			add(i,select(i,k));
		}
		E=compute(k);
	}
	while(E!=e);
	for(i=0;i<k;i++)
	{
		printf("{");
		for(j=0;j<total_of_cluster[i];j++)
		{
			printf(" %d ",cluster[i][j]);
		}
		printf("}\n");
	}
}

int select(int now,int total)
{
	double min,tmin;
	int sel,i;
	min=target[now]>means[0]?target[now]-means[0]:-target[now]+means[0];
	sel=0;
	for(i=1;i<total;i++)
	{
		tmin=target[now]>means[i]?target[now]-means[i]:-target[now]+means[i];
		if(tmin<min)
		{
			sel=i;
			min=tmin;
		}
	}
	return sel;
}

void add(int now,int select)
{
	cluster[select][total_of_cluster[select]++]=target[now];
}

double compute(int k)
{
	int i,j;
	double mean,result;
	for(i=0;i<k;i++)
	{
		mean=0;
		for(j=0;j<total_of_cluster[i];j++)
		{
			mean+=cluster[i][j];
		}
		mean/=total_of_cluster[i];
		means[i]=mean;
	}
	result=0;
	for(i=0;i<k;i++)
	{
		for(j=0;j<total_of_cluster[i];j++)
		{
			result+=(means[i]-cluster[i][j])*(means[i]-cluster[i][j]);
		}
	}
	return result;
}
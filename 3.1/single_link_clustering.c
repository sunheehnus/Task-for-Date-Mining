#include<stdio.h>

struct Cluster{int x1,x2;}cluster[1024][1024];

int total[1024];

int cnt;

double min_distance;

double compute(int pos1,int pos2);

int main()
{
	int selecti,selectj,i,j,step;
	double min,mintmp;
	FILE *fin  = fopen ("test.in", "r");
	fscanf(fin,"%lf",&min_distance);
	min_distance*=min_distance;
	while(fscanf(fin,"%d %d",&cluster[cnt][0].x1,&cluster[cnt][0].x2)!=EOF)
	{
		total[cnt++]=1;
	}
	step=0;
	while(1)
	{
		step++;
		selecti=selectj=-1;
		for(i=0;i<cnt;i++)
		{
			for(j=i+1;j<cnt;j++)
			{
				if(total[i]!=0&&total[j]!=0)
				{
					mintmp=compute(i,j);
					if(selecti==-1&&selectj==-1||mintmp<min)
					{
						min=mintmp;
						selecti=i;
						selectj=j;
					}
				}
			}
		}
		if(selecti==-1&&selectj==-1)
		{
			break;
		}
		if(min>min_distance)
		{
			break;
		}
		for(i=0;i<total[selectj];i++)
		{
			cluster[selecti][total[selecti]++]=cluster[selectj][i];
		}
		total[selectj]=0;
		printf("Step %d:\n",step);
		for(i=0;i<cnt;i++)
		{
			if(total[i]!=0)
			{
				printf("{ ");
				for(j=0;j<total[i];j++)
				{
					printf(" (%d %d) ",cluster[i][j].x1,cluster[i][j].x2);
				}
				printf(" }\n");
			}
		}
		printf("\n");
	}
	return 0;
}

double distance(struct Cluster p1,struct Cluster p2)
{
	return (p2.x1-p1.x1)*(p2.x1-p1.x1)+(p2.x2-p1.x2)*(p2.x2-p1.x2);
}

double compute(int pos1,int pos2)
{
	double min;
	int i,j;
	min=distance(cluster[pos1][0],cluster[pos2][0]);
	for(i=0;i<total[pos1];i++)
	{
		for(j=0;j<total[pos2];j++)
		{
			if(distance(cluster[pos1][i],cluster[pos2][j])<min)
				min=distance(cluster[pos1][i],cluster[pos2][j]);
		}
	}
	return min;
}
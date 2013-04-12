#include<stdio.h>
#include<string.h>
#define MAX 1<<10

char item[MAX][32];

int tid[MAX];

int just4sort[MAX];

int map[MAX];

int total_of_rank[MAX];

int pos_of_sets[MAX],fresets[MAX],frecnts[MAX],sum_of_sets[MAX];

int nowtid,cnt,total_of_thisitem,mincnt,rank,totalsets,fretotal;

int target[128],tmp[128];

double minsupport,minconfidence;

void quicksort(int l,int u);
void selectsort(int l,int u);

void mapandsort();

void add(int cnt,int k);
void setpos_of_sets(int k);
int judge(int i,int j,int k);

void Find(int k);

void related(int length1,int pos1,int length2,int pos2,int rank1,int rank2);

int main()
{
	int i,j,l,total,flag,k,i1,i2,j1,j2,rank1,rank2;
	
	char TID[32];
	FILE *fin  = fopen ("test.in", "r");

	fscanf(fin,"%lf %lf",&minsupport,&minconfidence);
	while(fscanf(fin,"%s %d",TID,&total)!=EOF)
	{
		nowtid++;
		tid[nowtid]=tid[nowtid-1]+total;
		for(i=0;i<total;i++)
		{
			fscanf(fin,"%s",&item[++cnt][0]);
		}
	}
	
	mapandsort();

	mincnt=(int)(minsupport*nowtid)+((minsupport*nowtid-((int)(minsupport*nowtid)))>0);

	for(i=1;i<=rank;i++)
	{
		if(total_of_rank[i]>=mincnt)
		{
			target[0]=i;
			add(total_of_rank[i],1);
		}
	}

	for(k=2,flag=1;flag;k++)
	{
		flag=0;
		setpos_of_sets(k);
		for(i=pos_of_sets[k-2]+1;i<=pos_of_sets[k-1];i+=k-1)
		{
			for(j=i+k-1;j<=pos_of_sets[k-1];j+=k-1)
			{
				if(judge(i,j,k-2))
				{
					Find(k);
					if(total_of_thisitem>=mincnt)
					{
						add(total_of_thisitem,k);
						flag=1;
					}
				}
			}
		}
	}
	printf("\nTotalcnts    Frequentsets\n");
	for(i=1,k--,fretotal=1;i<=k;i++)
	{
		for(j=pos_of_sets[i-1]+1;j<=pos_of_sets[i];j+=i)
		{
			printf("%8d    ",frecnts[fretotal++]);
			printf("  (");
			for(l=0;l<i;l++)
			{
				printf(" %d ",fresets[j+l]);
			}
			printf(")");
			printf("\n");
		}
	}
	printf("\nRelationship:\n");
	rank1=0;
	for(i1=1;pos_of_sets[i1]>pos_of_sets[i1-1];i1++)
	{
		for(j1=pos_of_sets[i1-1]+1;j1<=pos_of_sets[i1];j1+=i1)
		{
			rank1++;
			rank2=0;
			for(i2=1;pos_of_sets[i2]>pos_of_sets[i2-1];i2++)
			{
				for(j2=pos_of_sets[i2-1]+1;j2<=pos_of_sets[i2];j2+=i2)
				{
					rank2++;
					related(i1,j1,i2,j2,rank1,rank2);
				}
			}
		}
	}

	return 0;
}

int Exist(int l,int u,int k)
{
	while(k!=0&&l<=u)
	{
		if(map[u]>target[k-1])
			u--;
		else if(map[u]==target[k-1])
		{
			u--;
			k--;
		}
		else
			return 0;
	}
	if(k==0)
		return 1;
	return 0;
}

void Find(int k)
{
	int i;
	total_of_thisitem=0;
	for(i=1;i<=nowtid;i++)
	{
		if(Exist(tid[i-1]+1,tid[i],k))
			total_of_thisitem++;
	}
}

int CMP(int *a,int *b,int l)
{
	while(l)
	{
		if(a[l-1]!=b[l-1])
		{
			return 0;
		}
		l--;
	}
	return 1;
}

int judge(int i,int j,int k)
{
	int l,m,n,n1,n2;
	for(l=0;l<k;l++)
	{
		if(fresets[i+l]!=fresets[j+l])
			return 0;
		target[l]=fresets[i+l];
	}
	target[l]=fresets[i+l];
	target[l+1]=fresets[j+l];
	l++;
	n=pos_of_sets[k]+1;
	for(m=l;m>=0;m--)
	{
		for(n1=0,n2=0;n2<=l;n2++)
		{
			if(n2!=m)
			{
				tmp[n1]=target[n2];
				n1++;
			}
		}
		for(;n<=pos_of_sets[k+1];n+=k+1)
		{
			if(CMP(tmp,fresets+n,k+1))
				break;
		}
		if(n>pos_of_sets[k+1])
			return 0;
	}
	return 1;
}

void add(int cnt,int k)
{
	int i,j;
	frecnts[++totalsets]=cnt;
	pos_of_sets[k]+=k;
	sum_of_sets[k]++;
	for(i=pos_of_sets[k]-k+1,j=0;i<=pos_of_sets[k];i++,j++)
	{
		fresets[i]=target[j];
	}
}

void setpos_of_sets(int k)
{
	pos_of_sets[k]=pos_of_sets[k-1];
	sum_of_sets[k]=sum_of_sets[k-1];
}

void quicksort(int l,int u)
{
	int i,j,mid,tmp,flag;
	if(l<u)
	{
		i=l;
		j=u;
		mid=(l+u)>>1;
		tmp=just4sort[mid];
		just4sort[mid]=just4sort[l];
		while(i<j)
		{
			while(i<j&&(flag=strcmp(&item[tmp][0],&item[just4sort[j]][0]))<=0)
				j--;
			just4sort[i]=just4sort[j];
			while(i<j&&(flag=strcmp(&item[just4sort[i]][0],&item[tmp][0]))<=0)
				i++;
			just4sort[j]=just4sort[i];
		}
		just4sort[i]=tmp;
		quicksort(l,i-1);
		quicksort(i+1,u);
	}
}

void selectsort(int l,int u)
{
	int min,i,select;
	while(l<u)
	{
		for(i=l+1,min=map[l],select=l;i<=u;i++)
		{ 
			if(map[i]<min)
			{
				min=map[i];
				select=i;
			}
		}
		map[select]=map[l];
		map[l]=min;
		l++;
	}
}

void mapandsort()
{
	int i;
	for(i=1;i<=cnt;i++)
	{
		just4sort[i]=i;
	}
	quicksort(1,cnt);
	printf("Mapping function:\n");
	rank=1;
	map[just4sort[1]]=rank;
	printf("%d -----> %s\n",rank,&item[just4sort[1]][0]);
	total_of_rank[rank]++;
	for(i=2;i<=cnt;i++)
	{
		if(strcmp(&item[just4sort[i]][0],&item[just4sort[i-1]][0]))
		{
			rank++;
			printf("%d -----> %s\n",rank,&item[just4sort[i]][0]);
		}
		map[just4sort[i]]=rank;
		total_of_rank[rank]++;
	}
	for(i=1;i<=nowtid;i++)
	{
		selectsort(tid[i-1]+1,tid[i]);
	}
}

int SAME(int length,int pos)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(target[i]!=fresets[pos+i])
		{
			return 0;
		}
	}
	return 1;
}

void related(int length1,int pos1,int length2,int pos2,int rank1,int rank2)
{
	int t_cnt,i1,i2,rank_target,i;
	t_cnt=i1=i2=0;
	while(i1<length1&&i2<length2)
	{
		if(fresets[pos1+i1]<fresets[pos2+i2])
		{
			target[t_cnt++]=fresets[pos1+i1++];
		}
		else if(fresets[pos1+i1]>fresets[pos2+i2])
		{
			target[t_cnt++]=fresets[pos2+i2++];
		}
		else
		{
			return ;
		}
	}
	while(i1<length1)
	{
		target[t_cnt++]=fresets[pos1+i1++];
	}
	while(i2<length2)
	{
		target[t_cnt++]=fresets[pos2+i2++];
	}
	rank_target=sum_of_sets[t_cnt-1];
	for(i=pos_of_sets[t_cnt-1]+1;i<=pos_of_sets[t_cnt];i+=t_cnt)
	{
		rank_target++;
		if(SAME(t_cnt,i))
		{
			if(((double)frecnts[rank_target]/frecnts[rank1])>minconfidence)
			{
				printf("(");
				for(i1=0;i1<length1;i1++)
				{
					printf(" %d ",fresets[i1+pos1]);
				}
				printf(")");
				printf(" -----> ");
				printf("(");
				for(i2=0;i2<length2;i2++)
				{
					printf(" %d ",fresets[i2+pos2]);
				}
				printf(")");
				printf("    [support=%.2lf] [confidence=%.2lf]",((double)frecnts[rank_target]/cnt),((double)frecnts[rank_target]/frecnts[rank1]));
				printf("\n");
			}
			return ;
		}
	}
}
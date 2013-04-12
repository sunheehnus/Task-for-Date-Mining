#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<math.h>

int state[1024][5],cnt,cnt_s[3];

char t_age[32],t_income[32],t_student[32],t_credit_rating[32],t_buys_computer[32];

struct Tree{int total,select,*state;struct Tree *c0,*c1,*c2;char *exist,YorN,Isleaf;};


char * name[5]={"age          ","income        ","student      ","credit_rating","buys_computer"};

char *selection[5][3]={{"<=30     ","31...40  ",">40      "},{"low      ","medium   ","high     "},{"no       ","yes      "},{"fair     ","excellent"},{"no       ","yes      "}};

struct Tree * newtree(int total,int *state,char *exist);
struct Tree * Initialize();
void add();
int Same(struct Tree *p);
int Empty(struct Tree *p);
void Fillincnt_s(struct Tree *p);
int Select(struct Tree *p);
void Do(struct Tree *p);
void print(int lev,char *means,struct Tree *tree);

int main()
{
	FILE *fin  = fopen ("test.in", "r");
	struct Tree *p;
	while(fscanf(fin,"%s %s %s %s %s",t_age,t_income,t_student,t_credit_rating,t_buys_computer)!=EOF)
	{
		add();
	}
	p=Initialize();
	Do(p);
	print(0,NULL,p);
	return 0;
}

struct Tree * newtree(int total,int *state,char *exist)
{
	struct Tree *p;
	if(total==0)
	{
		return NULL;
	}
	p=(struct Tree *)malloc(sizeof(struct Tree ));
	p->c0=p->c1=p->c2=NULL;
	p->Isleaf=0;
	p->total=total;
	p->state=state;
	p->exist=exist;
	return p;
}

struct Tree * Initialize()
{
	int i,*state;
	char *exist;
	state=(int *)malloc(sizeof(int)*cnt);
	for(i=0;i<cnt;i++)
	{
		state[i]=i;
	}
	exist=(char *)malloc(sizeof(char)*5);
	for(i=0;i<5;i++)
	{
		exist[i]=1;
	}
	return newtree(cnt,state,exist);
}

void add()
{
	if(strcmp(t_age,"<=30")==0)
		state[cnt][0]=0;
	else if(strcmp(t_age,"31...40")==0)
		state[cnt][0]=1;
	else 
		state[cnt][0]=2;
	if(strcmp(t_income,"low")==0)
		state[cnt][1]=0;
	else if(strcmp(t_income,"medium")==0)
		state[cnt][1]=1;
	else 
		state[cnt][1]=2;
	if(strcmp(t_student,"no")==0)
		state[cnt][2]=0;
	else 
		state[cnt][2]=1;
	if(strcmp(t_credit_rating,"fair")==0)
		state[cnt][3]=0;
	else 
		state[cnt][3]=1;
	if(strcmp(t_buys_computer,"no")==0)
		state[cnt][4]=0;
	else 
		state[cnt][4]=1;
	cnt++;
}

int Same(struct Tree *p)
{
	int i;
	for(i=1;i<p->total;i++)
	{
		if(state[p->state[i]][4]!=state[p->state[i-1]][4])
			break;
	}
	if(i==p->total)
	{
		p->Isleaf=1;
		p->YorN=state[p->state[0]][4];
		return 1;
	}
	return 0;
}

int Empty(struct Tree *p)
{
	int i,tmp;
	for(i=0;i<4;i++)
	{
		if(p->exist[i]==1)
			break;
	}
	if(i==4)
	{
		p->Isleaf=1;
		for(tmp=0,i=0;i<p->total;i++)
		{
			if(state[p->state[i]][4]==1)
			{
				tmp++;
			}
		}
		if(tmp>=((p->total+1)>>1))
		{
			p->YorN=1;
		}
		else
		{
			p->YorN=0;
		}
		return 1;
	}
	return 0;
}

int Select(struct Tree *p)
{
	double Info[5];
	int t_cnt[3][2],i,j,select;
	double c_cnt[3][2];
	double min,tot;
	for(i=0;i<4;i++)
	{
		if(p->exist[i]==1)
		{
			memset(t_cnt,0,sizeof(t_cnt));
			for(j=0;j<p->total;j++)
			{
				t_cnt[state[p->state[j]][i]][state[p->state[j]][4]]++;
			}
			for(j=0,tot=0;j<=2;j++)
			{
				c_cnt[j][0]=t_cnt[j][0];
				c_cnt[j][1]=t_cnt[j][1];
				tot+=c_cnt[j][0]+c_cnt[j][1];
			}
			Info[i]=0;
			for(j=0;j<=2;j++)
			{
				if(t_cnt[j][0]!=0)
					Info[i]+=c_cnt[j][0]*(log((c_cnt[j][0])/(c_cnt[j][0]+c_cnt[j][1]))/log(2));
				if(t_cnt[j][1]!=0)
					Info[i]+=c_cnt[j][1]*(log((c_cnt[j][1])/(c_cnt[j][0]+c_cnt[j][1]))/log(2));
			}
			Info[i]=-Info[i]/tot;
		}
	}
	for(i=0;i<4&&p->exist[i]!=1;i++);
	min=Info[i];
	select=i;
	for(i++;i<4;i++)
	{
		if(p->exist[i]==1&&Info[i]<min)
		{
			min=Info[i];
			select=i;
		}
	}
	return select;
}

void Fillincnt_s(struct Tree *p)
{
	int i;
	memset(cnt_s,0,sizeof(cnt_s));
	for(i=0;i<p->total;i++)
	{
		cnt_s[state[p->state[i]][p->select]]++;
	}
}

void Add0(struct Tree *p,int this_cnt)
{
	int *t_state,i,j;
	char *t_exist;
	if(this_cnt!=0)
	{
		t_state=(int *)malloc(sizeof(int)*this_cnt);
		for(i=0,j=0;j<p->total;j++)
		{
			if(state[p->state[j]][p->select]==0)
			{
				t_state[i]=p->state[j];
				i++;
			}
		}
		t_exist=(char *)malloc(sizeof(char)*5);
		memset(t_exist,0,sizeof(t_exist));
		for(i=0;i<5;i++)
		{
			if(p->select!=i&&p->exist[i]==1)
				t_exist[i]=1;
		}
		p->c0=newtree(this_cnt,t_state,t_exist);
	}
	else
	{
		p->c0=newtree(0,NULL,NULL);
	}
}

void Add1(struct Tree *p,int this_cnt)
{
	int *t_state,i,j;
	char *t_exist;
	if(this_cnt!=0)
	{
		t_state=(int *)malloc(sizeof(int)*this_cnt);
		for(i=0,j=0;j<p->total;j++)
		{
			if(state[p->state[j]][p->select]==1)
			{
				t_state[i]=p->state[j];
				i++;
			}
		}
		t_exist=(char *)malloc(sizeof(char)*5);
		for(i=0;i<5;i++)
		{
			if(p->select!=i&&p->exist[i]==1)
				t_exist[i]=1;
		}
		p->c1=newtree(this_cnt,t_state,t_exist);
	}
	else
	{
		p->c1=newtree(0,NULL,NULL);
	}
}


void Add2(struct Tree *p,int this_cnt)
{
	int *t_state,i,j;
	char *t_exist;
	if(this_cnt!=0)
	{
		t_state=(int *)malloc(sizeof(int)*this_cnt);
		for(i=0,j=0;j<p->total;j++)
		{
			if(state[p->state[j]][p->select]==2)
			{
				t_state[i]=p->state[j];
				i++;
			}
		}
		t_exist=(char *)malloc(sizeof(char)*5);
		for(i=0;i<5;i++)
		{
			if(p->select!=i&&p->exist[i]==1)
				t_exist[i]=1;
		}
		p->c2=newtree(this_cnt,t_state,t_exist);
	}
	else
	{
		p->c2=newtree(0,NULL,NULL);
	}
}

void Do(struct Tree *p)
{
	int tmp_cnt[3];
 	if(Same(p))
	{
		return ;
	}
	if(Empty(p))
	{
		return ;
	}
	p->select=Select(p);
	Fillincnt_s(p);
	tmp_cnt[0]=cnt_s[0];
	tmp_cnt[1]=cnt_s[1];
	tmp_cnt[2]=cnt_s[2];
	Add0(p,tmp_cnt[0]);
	if(p->c0!=NULL)
	{
		Do(p->c0);
	}
	Add1(p,tmp_cnt[1]);
	if(p->c1!=NULL)
	{
		Do(p->c1);
	}
	Add2(p,tmp_cnt[2]);
	if(p->c2!=NULL)
	{
		Do(p->c2);
	}
}

void print(int lev,char *means,struct Tree *tree)
{
	int i;
	if(tree->Isleaf==1)
	{
		for(i=0;i<lev;i++)
		{
			printf("                       ");
		}
		printf("%s ",means);
		if(tree->YorN==1)
			printf("Yes\n");
		else
			printf("No\n");
		return;
	}
	for(i=0;i<lev;i++)
	{
		printf("                       ");
	}
	printf("%s ",means);
	printf("%s\n",name[tree->select]);
	if(tree->c0!=NULL)
	{
		print(lev+1,selection[tree->select][0],tree->c0);
	}
	if(tree->c1!=NULL)
	{
		print(lev+1,selection[tree->select][1],tree->c1);
	}
	if(tree->c2!=NULL)
	{
		print(lev+1,selection[tree->select][2],tree->c2);
	}
	
}
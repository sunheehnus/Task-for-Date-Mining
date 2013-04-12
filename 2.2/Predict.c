#include<stdio.h>

#include<stdlib.h>

int cnt;

double minutes[1024];

double marks[1024];

double ave_minutes,ave_marks;

double w1up,w1down,w1,w0;

double minute,mark;

int main()
{
	int i;
	FILE *fin  = fopen ("test.in", "r");
	ave_minutes=ave_marks=0;
	while(fscanf(fin,"%lf %lf",&minutes[cnt],&marks[cnt])!=EOF)
	{
		ave_minutes+=minutes[cnt];
		ave_marks+=marks[cnt];
		cnt++;
	}
	ave_minutes/=(double)cnt;
	ave_marks/=(double)cnt;
	for(i=0,w1up=w1down=0;i<cnt;i++)
	{
		w1up+=(marks[i]-ave_marks)*(minutes[i]-ave_minutes);
		w1down+=(minutes[i]-ave_minutes)*(minutes[i]-ave_minutes);
	}
	w1=w1up/w1down;
	w0=ave_marks-w1*ave_minutes;
	for(i=0;i<100;i++)
	{	
		minute=(double)(rand()%600);
		mark=w0+w1*minute;
		printf("minutes : %.0lf   marks : %.0lf\n",minute,mark);
	}
	return 0;
}
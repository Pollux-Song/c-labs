#include<stdio.h>
#include<limits.h>
int main(void){
printf("~0 =%08X\n",(unsigned)~0);
printf("1<<31 =%08X\n",(unsigned)(1<<31));
printf("1U<<31 =%08X\n",1U<<31);
printf("-1>>1 =%08X\n",(unsigned)(-1>>1));
printf("sizeof(1) =%d,sizeof(1U)=%d\n",(int)sizeof(1),(int)sizeof(1U));
return 0;


}

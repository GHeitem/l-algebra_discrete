#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "relations_on_points.h"
int var1(t_point a, t_point b) {
	return (a.x <= b.x) && (a.y <= b.y);
}
int var4(t_point a, t_point b)
{
	return(a.x - a.y) <= (b.x - b.y);
};
int func(int a, int b)
{
	return a % b==0;
}
void getReltmp(relation A, int pow,const int*M, int(*func)(int, int)) {
	for (int x = 0; x < pow; x++) {
		for (int y = 0; y < pow; y++) {
			A[x][y] = func(M[x], M[y]);
		};
	};
	//std::cout << "Matrix was changed with special function to:" << std::endl;
	//printRel(A, pow, M);
}
//void test1() {
//	relation a = NULL,c=NULL;
//	getMem(&a, M1P);
//	getMem(&c, M1P);
//	getRel(a, M1P, M1, var4);
//	printRel(a, M1P, M1);
//	dominate(a, M1P, c);
//	determine(chRel(a, M1P));
//	done(&a, M1P);
//	/*getMem(&a, M2P);
//	getRel(a, M2P, M2, var4);
//	determine(chRel(a, M2P));
//	printRel(a, M2P, M2);
//	done(&a, M2P);*/
//	//system("pause");
//}
void test2() {
	relation a = NULL;
	getMem(&a, M1P);
	getReltmp(a,4,Mtmp,func);
	//delDiag(a,M1P);
	determine(chRel(a, M1P));
	printRel(a,M1P,M1);
	int levels[M1P]={0};
	dominate(a,M1P,a);
	ttsort(a,M1P,levels,0,1);
	printf("Levels:");
	printArr(levels,M1P);
	printf("\n");
	printRel(a,M1P,M1);
};


int main() {
//	test1();
	test2();
	system("pause");
}

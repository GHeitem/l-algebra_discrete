#include <iostream>
#include "relations_on_points.h"
using namespace std;

void getMem(relation *a, int pow) {
	*a = (char **)calloc(pow, sizeof(char*));
	for (int i = 0; i < pow; i++) {
		(*a)[i] = (char*)calloc(pow, sizeof(char));
	};
}
void putPoint(t_point a) {
	printf("(%2d;%2d)", a.x, a.y);
}
void printS(const t_point *M, int pow) {
	for (int i = 0; i < pow; i++) {
		putPoint(M[i]);
		cout << " ";
	}
}
void printRel(relation a, int pow, const t_point * M) {
	cout << '\t';
	printS(M, pow);
	cout << '\n';
	for (int i = 0; i < pow; i++) {
		putPoint(M[i]);
		cout << " ";
		for (int j = 0; j < pow; j++) {
			cout << " " << int(a[i][j]) << "\t";

		}
		cout << endl;
	};
}
void getRel(relation A, int pow, const t_point *M, int(*func)(t_point, t_point)) {
	for (int x = 0; x < pow; x++) {
		for (int y = 0; y < pow; y++) {
			A[x][y] = func(M[x], M[y]);
		};
	};
	cout << "Matrix was changed with special function to:" << endl;
	printRel(A, pow, M);
}
int var11(t_point a, t_point b) {
	return a.x <= b.y;
}
void done(relation *a, int size) {
	for (int i = 0; i < size; i++) {
		free((*a)[i]);
	}
	free(*a);
	a = NULL;
	cout << "Deleted\n";
}
int reflex(relation a, int size)
{
	int x;
	for (x = 0; x<size; x++)
	{
		if (!a[x][x])
		{
			return 0;
		}
	}
	return 1;
}
int areflex(relation a, int size)
{
	int x;
	for (x = 0; x<size; x++)
	{
		if (a[x][x])
		{
			return 0;
		}
	}
	return 1;
}
int simmetry(relation a, int size)
{
	int x, y;
	for (x = 0; x<size; x++)
	{
		for (y = 0; y<x; y++)
		{
			if (a[x][y] != a[y][x])
			{
				return 0;
			}
		}
	}
	return 1;
}
int assimetry(relation a, int size)
{
	int x, y;
	for (x = 0; x<size; x++)
	{
		for (y = 0; y<size; y++)
		{
			if (a[x][y] && a[y][x]&&(x!=y))
			{
				return 0;
			}
		}
	}
	return 1;
}
//Кем бы ты ни был, протестируй эту функцию перед использованием.
int transitivity(relation a, int size)
{
	int x, y, z;
	for (x = 0; x<size; x++)
	{
		for (y = 0; y<size; y++)
		{
			for (z = 0; z<size; z++)
			{
				if (a[x][z] && a[z][y] && !a[x][y])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
int atransitivity(relation a, int size)
{
	int x, y, z;
	for (x = 0; x<size; x++)
	{
		for (y = 0; y<size; y++)
		{
			for (z = 0; z<size; z++)
			{
				if (!(a[x][z] && a[z][y]) && a[x][y])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
void done(set *a, int size) {
	free(a);
}
void univ(set b, int N)
{
	for (int i = 0; i < N; i++)
	{
		b[i] = 0;
	}
}
int full(relation a, int N)
{
	set d=NULL;
	d = new int[N];
	univ(d, N);
	for (int x = 0; x<N; x++)
	{
		for (int y = 0; y<N; y++) {

			if ((x != y) && (!a[x][y]) && (!a[y][x])) return 0;
		};
	};
	return 1;
}
	
int chRel(relation a, int N)
{
	if (simmetry(a, N) && reflex(a, N)) {
		return transitivity(a, N) ? EquivRel : TolRel;
	};
	if (assimetry(a,N) && transitivity(a, N)) {
		if (reflex(a, N))
		{
			return full(a, N) ? LinearRel : NotStrictRel;
		};
		if (areflex(a, N))
		{
			return (full(a, N) ? StrictLinearRel : StrictRel);
		};

	}
	return 0;
}


void determine(int a) {
	switch (a) {
	case TolRel:cout << "Relation is tolerant.\n"; break;
	case EquivRel:cout << "Relation is equivalent.\n"; break;
	case StrictRel:cout << "Relation has strict order.\n"; break;
	case NotStrictRel:cout << "Relation has non-strict order.\n"; break;
	case LinearRel:cout << "Relation has linear order.\n"; break;
	case StrictLinearRel:cout << "Relation has strict linear order.\n"; break;
	default: cout << "Cant determine. \n";
	};
}


void composition(relation a, relation b, int size, relation dest) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			dest[i][j] = 0;
			for (int k = 0; k < size; k++) {
				dest[i][j] = dest[i][j] || (a[i][k] && b[k][j]);
			}
		}
	}
}
void copyRel(relation a, relation c, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			c[i][j] = a[i][j];
		}
	}
}
void dominate(relation a, int size, relation c) {
	relation tmp;
	int t=chRel(a,size);
	if ((t==StrictLinearRel)||(t==StrictRel)){
	copyRel(a, c, size);
	getMem(&tmp, size);
	composition(a, a, size, tmp);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tmp[i][j] && c[i][j]) {
				c[i][j] = 0;
			};
		};
	};
	} else
	{
		printf("Error! Cant make a domination of nonStrict relation!");
	};
};

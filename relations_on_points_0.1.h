#pragma once

#define TolRel 1
#define EquivRel 2
#define StrictRel 3
#define NotStrictRel 4
#define LinearRel 5
#define StrictLinearRel 6
typedef struct {
	int x;
	int y;
}t_point;
#define M1P 9
#define M2P 13
#define M0P 6
const t_point M0[M0P] = { { 0, 0 },{ 0, 1 },{ 0, 2 },{ 1, 0 },{ 2, 0 },{ 1, 1 } };
const t_point M1[M1P] = { -1,-1,0,-1,1,-1,-1,0,0,0,1,0,-1,1,0,1,1,1 };
const t_point M2[M2P] = { { -1, -1 },{ 0, -1 },{ -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 },{ 1, -1 },{ -1, 1 },{ 0, 2 },{ -2, 0 },{ 0, -2 },{ 2, 0 } };
const int Mtmp[]={1,2,3,6};
typedef char **relation;
typedef int *set;
void getMem(relation*a, int);
void putPOint(t_point);
void printS(const t_point *, int);
void printRel(relation, int, const t_point *);
void getRel(relation, int, const t_point*, int(*)(t_point, t_point));
int var11(t_point, t_point);
void done(relation*, int size);
int reflex(relation, int);
int areflex(relation, int);
int simmetry(relation, int);
int assimetry(relation, int);
int transitivity(relation, int);
int atransitivity(relation, int);
int full(relation, int);
int chRel(relation, int);
void getMem(set*, int);
void done(set*, int);
void univ(set, int);
void determine(int);
void composition(relation, relation, int, relation);
void dominate(relation a, int size, relation c);
void copyRel(relation, relation, int);
void topsort(relation,int,int,int*,int*);
void ttsort(relation c, int size,int *levels, int j,int l);
void printArr(int *arr, int size);
void delDiag(relation c, int size);

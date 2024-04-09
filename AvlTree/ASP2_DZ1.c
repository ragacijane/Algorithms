#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
typedef struct tnode {
	int b, key, h;
	struct tnode *left, *right;
}TNODE;
typedef struct node {
	TNODE *point;
	struct node *next;
}NODE;
int POW(int x, int y) {
	int i, z = 1;
	for (i = 0; i < y; i++)z *= x;
	return z;
}
void RIGHTROT(TNODE *x) {
	TNODE *temp, *y;
	y = x->left;
	temp = y->right;
	y->right = x;
	x->left = temp;
}
void LEFTROT(TNODE *x) {
	TNODE *temp, *y;
	y = x->right;
	temp = y->left;
	y->left = x;
	x->right = temp;
}
int AVLINSERT(TNODE **root, int k) {
	TNODE *p , *fp = NULL, *fx = NULL, *x , *q, *y;
	int imbal;
	p = *root;
	x = p;
	/*pretraga*/
	while (p != NULL) {
		if (k < p->key)
			q = p->left;
		else q = p->right;
		if (q != NULL && q->b != 0) {
			fx = p;
			x = q;
		}
		fp = p;
		p = q;
	}
	/*stvaranje novog cvora*/
	q = calloc(1, sizeof(TNODE));
	q->left = NULL;
	q->right = NULL;
	q->key = k;
	q->b = 0;
	if (k < fp->key)fp->left = q;
	else fp->right = q;
	/*azuriranje balansa*/
	if (k < x->key)p = x->left;
	else p = x->right;
	y = p;
	while (p != q) {
		if (k < p->key) {
			p->b = 1;
			p = p->left;
		}
		else {
			p->b = -1;
			p = p->right;
		}
	}
	/*provera da li je balansiranost narušena*/
	if (k < x->key)imbal = 1;
	else imbal = -1;
	/*balans u x nije narušen pa se setuje na imbal*/
	if (x->b == 0) {
		x->b = imbal;
		return 1;
	}
	/*balans u x potpuno uravnotezen*/
	if (x->b != imbal) {
		x->b = 0;
		return 1;
	}
	/*Balansiranost narusena*/
	/*naginjanje na istu stranu*/
	if (y->b == imbal) {
		p = y;
		if (imbal == 1)RIGHTROT(x);
		else LEFTROT(x);
		x->b = y->b = 0;
	}
	/*naginjanje na suprotnu stranu*/
	else {
		if (imbal == 1) {
			p = y->right;
			LEFTROT(y);
			x->left = p;
			RIGHTROT(x);
		}
		else {
			p = y->left;
			x->right = p;
			RIGHTROT(y);
			LEFTROT(x);
		}
		if (p->b == 0)x->b = y->b = 0;
		else {
			if (x->b == imbal) {
				x->b = -imbal;
				y->b = 0;
			}
			else {
				x->b = 0;
				y->b = imbal;
			}
			p->b = 0;
		}
	}
	/*azuriranje novog korena podstabla u ocu kriticnog cvora*/
	if (fx == NULL)*root = p;
	else {
		if (x == fx->right)fx->right = p;
		else fx->left = p;
	}
	return 1;
} 
int levelorder(NODE **root) {
	int hm = 0, hm1;
	NODE *q, *p, *c;
	p = calloc(1, sizeof(NODE));
	p->point = *root;
	p->point->h = 0;
	p->next = NULL;
	q = p;
	while (p != NULL) {
		if (p->point->left != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->left;
			hm1 = c->point->h = p->point->h +1;
			q->next = c;
			q = c;
			c->next = NULL;
			if (hm1 > hm)hm = hm1;
		}
		if (p->point->right != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->right;
			hm1 = c->point->h = p->point->h + 1;
			q->next = c; 
			q = c;
			c->next = NULL;
			if (hm1 > hm)hm = hm1;
		}
		c = p;
		p = p->next;
		free(c);
	}
	return hm;
}
void ispis(TNODE **root) {
	/*levelorderom*/
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j, H, n, m, **matricaispisa, pom;
	NODE *q, *p, *c;
	H = levelorder(root);
	n = H + 1;
	m = POW(2, H) * 2 - 1;
	matricaispisa = calloc(n, sizeof(int*));
	for (i = 0; i < n; i++) {
		matricaispisa[i] = calloc(m, sizeof(int));
		for (j = 0; j < m; j++)matricaispisa[i][j] = 32000;
	}
	p = calloc(1, sizeof(NODE));
	p->point = *root;
	p->point->h = m / 2;
	p->next = NULL;
	matricaispisa[0][m / 2] = p->point->key;
	q = p;
	while (p != NULL) {
		if (p->point->left != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->left;
			pom = p->point->h - (m / 2) / POW(2, c->point->h) - 1;
			matricaispisa[c->point->h][pom]=c->point->key;
			c->point->h = pom;
			q->next = c;
			q = c;
			c->next = NULL;
		}
		if (p->point->right != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->right;
			pom = p->point->h + (m / 2 )/ POW(2, c->point->h) + 1;
			matricaispisa[c->point->h][pom] = c->point->key;
			c->point->h = pom;
			q->next = c;
			q = c;
			c->next = NULL;
		}
		c = p;
		p = p->next;
		free(c);
	}
	for (i = 0; i < n; i++) {
		printf("\n");
		SetConsoleTextAttribute(hConsole, i%5 + 10); 
		for (j = 0; j < m; j++)
			if (matricaispisa[i][j] == 32000)printf("   ");
			else printf("%3d", matricaispisa[i][j]);
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, 15);
	for (i = 0; i < n; i++)free(matricaispisa[i]);
	free(matricaispisa);
}
int TreeSrc(TNODE *root,int kljuc) {
	TNODE *p;
	int i = 0;
	p = root;
	while (p != NULL) {
		if (p->key == kljuc)return i;
		if (kljuc < p->key)p = p->left;
		else p = p->right;
		i++;
	}
	return i;
}
void FreeTreeLEV(NODE **root) {
	NODE *q, *p, *c;
	p = calloc(1, sizeof(NODE));
	p->point = *root;
	p->point->h = 0;
	p->next = NULL;
	q = p;
	while (p != NULL) {
		if (p->point->left != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->left;
			q->next = c;
			q = c;
			c->next = NULL;
		}
		if (p->point->right != NULL) {
			c = calloc(1, sizeof(NODE));
			c->point = p->point->right;
			q->next = c;
			q = c;
			c->next = NULL;
		}
		c = p;
		p = p->next;
		free(c->point);
		free(c);
	}
	*root = NULL;
}
int MAX(x, y) {
	if (x > y)return x;
	else return y;
}
int MIN(x, y) {
	if (x < y)return x;
	else return y;
}
int randomi(int opseg1, int opseg2) {
	int x;
	x = rand();
	x = x % 10;
	x = opseg2 - x;
	while (x < opseg1) {
		x = rand();
		x = x % 10;
		x = opseg2 - x;
	}
	return x;
}
int pretraga(int kljuc, int **matrica,int n,int m,int ispis) {
	int i, j,x=0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			x++;
			if (matrica[i][j] == kljuc) {
				if(ispis==1)printf("\nPozicija %d %d\n", i + 1, j + 1);
				return x;
			}
		}
	return x;
}
int main() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i,j,izbor, n, m, **matrica=NULL,kljuc,opseg1,opseg2,x;
	int brk,*nizkljuceva=NULL;
	float ukbrk = 0, ukbrkt = 0;;
	TNODE *root = NULL;
	char c[50];
	FILE *f;
	while (1) {
		srand(time(0));
		SetConsoleTextAttribute(hConsole, 10);
		printf("1. Unos matrice\n2. Generisanje matrice\n3. Pretraga matrice\n4. Performanse\n5. Formiranje stabla\n6. Pretragu stabla\n7. Umetanje kljuca u stablo\n8. Ispis stabla\n9. Brisanje stabla\n10. Poredjenje performansi\n0. Kraj\n");
		printf("Unesite Izbor:\n");
		SetConsoleTextAttribute(hConsole, 15);
		scanf("%d", &izbor);
		/*Prekid*/
		if (izbor == 0) {
			break;
		}
		/*Unos matrice*/
		if (izbor == 1) {
			if (matrica != NULL)for (i = 0; i < n; i++)free(matrica[i]);
			free(matrica);
			printf("1.Sa standardnog ulaza\n2.Iz .txt datoteke\n");
			printf("Unesite Izbor:\n");
			scanf("%d", &izbor);
			/*Sa standardnog ulaza*/
			if (izbor == 1) {
				printf("Unesite dimenzije matrice:\n");
				scanf("%d%d", &n, &m);
				matrica = calloc(n, sizeof(int*));
				for (i = 0; i < n; i++) {
					matrica[i] = calloc(m, sizeof(int));
					for (j = 0; j < m; j++)scanf("%d", &matrica[i][j]);
				}
			}
			/*Iz datoteke*/
			if (izbor == 2) {
				if (matrica != NULL)for (i = 0; i < n; i++)free(matrica[i]);
				free(matrica);
				printf("Unesi ime datoteke ( sa .txt):\n");
				scanf("%s", &c);
				f = fopen(c, "r");
				fscanf(f,"%d %d",&n,&m);
				matrica = calloc(n, sizeof(int*));
				for (i = 0; i < n; i++) {
					matrica[i] = calloc(m, sizeof(int));
					for (j = 0; j < m; j++)fscanf(f,"%d", &matrica[i][j]);
				}
				izbor = 11;
				fclose(f);
			}
		}
		/*Generisanje matrice*//*poboljsaj algoritam*/
		if (izbor == 2) {
			if (matrica != NULL)for (i = 0; i < n; i++)free(matrica[i]);
			free(matrica);
			printf("Unesite dimenzije matrice:\n");
			scanf("%d%d", &n, &m);
			matrica = calloc(n, sizeof(int*));
			for (i = 0; i < n; i++)
				matrica[i] = calloc(m, sizeof(int));
			printf("Unesite opseg brojeva za generisanje:\n");
			scanf("%d%d", &opseg1, &opseg2);
			matrica[0][0] = randomi(opseg1,opseg2);
			for (j = 1; j < m; j++)matrica[0][j] = randomi(opseg2 / 2,matrica[0][j - 1]);
			for (i = 1; i < n; i++)matrica[i][0] = randomi( opseg2 / 2,matrica[i - 1][0]);
			for (i = 1; i < n; i++)
				for (j = 1; j < m; j++)matrica[i][j] = randomi(opseg1, MIN(matrica[i - 1][j], matrica[i][j - 1]));
		}
		/*Pretraga matrice*/
		if (izbor == 3) {
			printf("Unesi kljuc:\n");
			scanf("%d", &kljuc);
			x = pretraga(kljuc, matrica,n,m,1);
		}
		/*Evaluacija performansi*/
		if (izbor == 4) {
			if (nizkljuceva != NULL)free(nizkljuceva);
			printf("Unesite opseg kljuceva:\n");
			scanf("%d%d", &opseg1, &opseg2);
			printf("Unesite broj kljuceva:\n");
			scanf("%d", &brk);
			nizkljuceva = calloc(brk, sizeof(int));
			nizkljuceva[0] = randomi(opseg1, opseg2);
			for (i = 1; i < brk; i++)nizkljuceva[i] = randomi(opseg1, nizkljuceva[i - 1]);
			for (i = 0; i < brk; i++) 
				ukbrk += pretraga(nizkljuceva[i], matrica, n, m, 0);
			printf("Performanse: %f\n", ukbrk / brk);
		}
		/*formiranje stabla*/
		if (izbor == 5) {
			if (root != NULL)FreeTreeLEV(&root);
			root = calloc(1, sizeof(TNODE));
			root->key = matrica[0][0];
			for (j = 1; j < m; j++)x = AVLINSERT(&root, matrica[0][j]);
			for (i = 1; i < n; i++)
				for (j = 0; j < m; j++)x = AVLINSERT(&root, matrica[i][j]);
			printf("Stablo je kreirano.\n");
		}
		/*pretraga stabla*/
		if (izbor == 6) {
			printf("Unesi kljuc:\n");
			scanf("%d", &kljuc);
			printf("Potrebni koraci do kljuca: %d\n",TreeSrc(root, kljuc));
		}
		/*umetanje kljuca*/
		if (izbor == 7) {
			printf("Unesi kljuc:\n");
			scanf("%d", &kljuc);
			x = AVLINSERT(&root,kljuc);
			printf("Kljuc je umetnut.\n");
		}
		/*ispis stabla*/
		if (izbor == 8) {
			if (root != NULL)ispis(&root);
			else printf("Prvo kreirajte stablo.\n");
		}
		/*brisanje stabla*/
		if (izbor == 9) {
			if (root != NULL)FreeTreeLEV(&root);
			if (root == NULL)printf("Stablo je obrisano.\n");
		}
		/*poredjenje performansi stabla*/
		if (izbor == 10) {
			if (nizkljuceva != NULL)free(nizkljuceva);
			nizkljuceva = NULL;
			printf("Unesite opseg kljuceva:\n");
			scanf("%d%d", &opseg1, &opseg2);
			printf("Unesite broj kljuceva:\n");
			scanf("%d", &brk);
			nizkljuceva = calloc(brk, sizeof(int));
			nizkljuceva[0] = randomi(opseg1, opseg2);
			for (i = 1; i < brk; i++)nizkljuceva[i] = randomi(opseg1, nizkljuceva[i - 1]);
			for (i = 0; i < brk; i++)
				ukbrk += pretraga(nizkljuceva[i], matrica, n, m, 0);
			for (i = 0; i < brk; i++)ukbrkt += TreeSrc(root, nizkljuceva[i]);
			printf("Prosecan broj koraka matrice je %.2f, a stabla %.2f .\n", ukbrk / brk, ukbrkt / brk);
		}
	}
	printf("\nKRAJ\n");
	if (matrica != NULL)for (i = 0; i < n; i++)free(matrica[i]);
	free(matrica);
	if (nizkljuceva != NULL)free(nizkljuceva);
}
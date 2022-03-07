#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour echanger deux entiers
void echange(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction qui affiche un tableau de taille n
void affiche(int *t, int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("\n");
}

// Structure representant une experience
// Un marqueur est un entier compris entre 0 et m
typedef struct {
    int m; // Nombre de marqueurs
    int *marqueurs; // Tous les marqueurs

    int p; // Nombre de marqueurs positifs
    int *marqueurs_positifs; // Les marqueurs positifs
} EXPERIENCE;

// Fonction qui cree une expérience et la stocke dans la structure passee en parametre
// Attention : il faut que p <= m
void cree_experience(EXPERIENCE *xp, int p, int m) {
    int i, j;

    xp->m = m;

    xp->marqueurs = (int *)malloc(m*sizeof(int));
    for (i = 0; i < m; ++i)
        xp->marqueurs[i] = i;

    // On melange les marqueurs dans l'ensemble des marqueurs par l'algorithme de Fisher-Yates
    for (i = m-1; i >= 0; --i) {
        j = rand() % (i+1);
        echange(&xp->marqueurs[i], &xp->marqueurs[j]);
    }

    // On choisit p marqueurs parmi les m qui seront les marqueurs positifs
    int *tmp = (int *)malloc(m*sizeof(int));
    for (i = 0; i < m; ++i)
        tmp[i] = i;

    xp->p = p;

    xp->marqueurs_positifs = (int *)malloc(p*sizeof(int));
    for (int i = 0; i < p; ++i) {
        j = rand() % (m-i);
        xp->marqueurs_positifs[i] = xp->marqueurs[tmp[j]];
        tmp[j] = tmp[m-i-1];
    }

    free(tmp);
}

// Algorithme de tri fusion
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

// Fonction qui libere la memoire dans une experience
void libere_experience(EXPERIENCE *xp) {
    free(xp->marqueurs);
    free(xp->marqueurs_positifs);
}

int recherche_dicho(EXPERIENCE *xp, int *cptOP, int valeur)
{
    int milieu, borne_inf, borne_sup, position;
    borne_inf = 0, borne_sup = (xp->p)-1, position = -1;
    while ((position == -1) && (borne_inf <= borne_sup))
    {
        milieu = (borne_inf+borne_sup)/2;
        if(xp->marqueurs[valeur] < xp->marqueurs_positifs[milieu])
        {
            borne_sup = milieu-1;
            *cptOP+=1;
        }
        else if(xp->marqueurs[valeur] > xp->marqueurs_positifs[milieu])
        {
            borne_inf = milieu+1;
            *cptOP+=1;
        }
        else
        {
            position = milieu;
            *cptOP+=1;
        }
    }
    return position;
}

// Fonction a completer - Strategie 1
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs1(EXPERIENCE *xp, int *cptOP) {
    *cptOP = 0;
    int *res = (int *)malloc((xp->m-xp->p)*sizeof(int));
    int emplacement_res = 0;
    int present = 0;
    for (int i = 0; i < xp->m; i++)
    {
        for (int j = 0; j < xp->p; j++)
        {
            if(xp->marqueurs[i] == xp->marqueurs_positifs[j]) present = 1;
            *cptOP+=1;
        }
        if(present != 1)
        {
            res[emplacement_res] = xp->marqueurs[i];
            emplacement_res++;
        }
        present = 0;
    }
    mergeSort(res,0,(xp->m-xp->p)-1);
    return res;
}


// Fonction a completer - Strategie 2
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs2(EXPERIENCE *xp, int *cptOP) {
    *cptOP = 0;
    int *res = (int *)malloc((xp->m-xp->p)*sizeof(int));
    mergeSort(xp->marqueurs_positifs,0,xp->p-1);
    mergeSort(xp->marqueurs,0,xp->m-1);
    int emp = 0;
    int rep;
    for (int i = 0; i < xp->m; i++)
    {
        rep = recherche_dicho(xp,cptOP,i);
        if(rep == -1)
        {
            res[emp] = xp->marqueurs[i];
            emp++;
        }
        else{

        }
    }
    //mergeSort(res,0,(xp->m-xp->p)-1);
    return res;
}


// Fonction a completer - Strategie 3
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs3(EXPERIENCE *xp, int *cptOP) {
    *cptOP = 0;
    mergeSort(xp->marqueurs_positifs,0,xp->p-1);
    mergeSort(xp->marqueurs,0,xp->m-1);
    int *res = (int *)malloc((xp->m-xp->p)*sizeof(int));
    int emplacement_res = 0;
    int emplacement= 0;
    int borne_inf = 0;
    for (int i = 0; i < xp->m; i++)
    {
        if(xp->marqueurs[i] == xp->marqueurs_positifs[emplacement_res])
        {
            for (int j = borne_inf; j < i; j++)
            {
                res[emplacement] = xp->marqueurs[j];
                emplacement++;
            }
            if(emplacement_res == ((xp->p)-1))
            {
                for (int k = (xp->m)-1; k > i; k--)
                {
                    res[emplacement] = xp->marqueurs[k];
                    emplacement++;
                }
            }
            emplacement_res++;
            borne_inf = i+1;
        }
        *cptOP+=1;

    }
    mergeSort(res,0,(xp->m-xp->p)-1);
    return res;
}

void test(int p, int m) {
    EXPERIENCE xp;
    int cpt, *marqueurs_negatifsA, *marqueurs_negatifsB, *marqueurs_negatifsC;
    // Creation de l'experience
    cree_experience(&xp, p, m);
    /*
    //printf("Marqueurs :\n");
    //affiche(xp.marqueurs, m);
    //printf("\nMarqueurs positfis :\n");
    //affiche(xp.marqueurs_positifs, p);
    // Test strategie 1
    //printf("\nStrategie 1\n");
    //marqueurs_negatifsA = marqueurs_negatifs1(&xp, &cpt);
    //printf("Marqueurs negatifs :\n");
    //affiche(marqueurs_negatifsA, xp.m-xp.p);
    //printf("Strategie 1 / nombres OP : %d\n\n", cpt);

    // Test strategie 2
    printf("\nStrategie 2\n");
    marqueurs_negatifsB = marqueurs_negatifs2(&xp, &cpt);
    printf("Marqueurs negatifs :\n");
    affiche(marqueurs_negatifsB, xp.m-xp.p);
    printf("Strategie 2 / nombres OP : %d\n\n", cpt);


    // Test strategie 3
    printf("\nStrategie 3\n");
    marqueurs_negatifsC = marqueurs_negatifs3(&xp, &cpt);
    printf("Marqueurs negatifs :\n");
    affiche(marqueurs_negatifsC, xp.m-xp.p);
    printf("Strategie 3 / nombres OP : %d\n\n", cpt);
    */
    xp.p = 1;
    for (int j = 0; j < xp.m; j++)
    {
        marqueurs_negatifs1(&xp, &cpt);
        printf("%2d %2d %2d",xp.m,xp.p,cpt);
        marqueurs_negatifs2(&xp, &cpt);
        printf(" %2d",cpt);
        marqueurs_negatifs3(&xp, &cpt);
        printf(" %2d\n",cpt);
        xp.p++;
    }

    for (int i = 0; i < (xp.m-xp.p); i++)
    {
        if (marqueurs_negatifsA[i] != marqueurs_negatifsB[i]
        || marqueurs_negatifsB[i] != marqueurs_negatifsC[i]
        || marqueurs_negatifsC[i] != marqueurs_negatifsA[i])
        {
            printf("---------- ATTENTION !!! ------------\n");
            printf("Les trois tableaux ne sont PAS IDENTIQUES !\n");
        }
    }

    free(marqueurs_negatifsA);
    free(marqueurs_negatifsB);
    free(marqueurs_negatifsB);

    libere_experience(&xp);
}



int main(int argc, const char * argv[]) {
    int m, p;

    srand((unsigned int)time(NULL));

    printf("Entrez le nombre de marqueurs positifs : ");
    scanf("%d", &p);
    printf("Entrez le nombre de marqueurs : ");
    scanf("%d", &m);

    test(p, m);

    return 0;
}

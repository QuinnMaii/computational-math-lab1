#include <iostream>
#include <algorithm>
#include <math.h>
float a[21][21], b[21], accuracy, x[21], Deviation[21], errorRate[21], deviation[21],sum[21];
float new_a[21][21],new_b[21];
int how, n;
void  nhap()
{
    printf("Выберите способ ввода: 1- ввод с клавиатуры, 2- ввод из файла \n");
    scanf("%d",&how);
    if(how == 1)
    {
        printf("\nВведите размер матрицы n = ");
        scanf("%d",&n);
        printf("\nВведите введите точность a = ");
        scanf("%f",&accuracy);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                float t;
                printf("a[%d][%d]=",i,j);
                scanf("%f",&t);
                a[i][j]=t;
                printf("b[%d]=",i);
                scanf("%f",&b[i]);
                sum[i]+=abs(a[i][j]);
            }
         }
    }
    else
    {
        freopen("input.inp", "r", stdin);
        scanf("%d",&n);
        scanf("%f",&accuracy);
         for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                scanf("%f",&a[i][j]);
                sum[i]+=abs(a[i][j]);
            }
            scanf("%f",&b[i]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            new_a[i][j]=-100;
        new_b[i]=-100;
    }

}

int check_dominant()
{
    float t;
    for(int i=1;i<=n;i++)
    {
        t=0;
        for(int j=1;j<=n;j++) t+=abs(new_a[i][j]);
        if(t >= 2*abs(new_a[i][i]))
            return 0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            a[i][j]=new_a[i][j];
        b[i]=new_b[i];
    }
    return 1;
}

bool make_diagonally_dominant(int x)
{
    if(x>n) return check_dominant();
    for(int j=1;j<=n;j++)
    {
        if(new_b[j]==-100)
        if(sum[x]<=2*abs(a[x][j]))
        {
            for(int k=1;k<=n;k++)
                new_a[j][k]=a[x][k];
            new_b[j]=b[x];
            std::swap(sum[x],sum[j]);
            return(make_diagonally_dominant(x+1));
            for(int k=1;k<=n;k++)
                new_a[j][k]=-100;
            new_b[j]=-100;
            std::swap(sum[x],sum[j]);

        }
    }
    return 0;
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
        float t=-a[i][i];
        for(int j=1;j<=n;j++)
        {
            if(i==j) a[i][j]=0;
            else a[i][j]/=t;
        }
        b[i]/=-t;
    }

    for(int i=1;i<=n;i++) x[i]=b[i];

    int currencyIterate=0;
    int check=0;


    while(check!=n)
    {
        if(currencyIterate>1000)
        {
            printf("Достингуто пиковое число итераций. Итерации расходятся :(");
            return;
        }
        currencyIterate++;
        float max_err=-100,t=0;
        check=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) t+=a[i][j]*x[j];

            t+=b[i];
            deviation[i]=abs(t-x[i]);

            errorRate[i]=std::max(deviation[i],abs(t-x[i]));
            max_err=std::max(max_err,errorRate[i]);
            check += (deviation[i] <= accuracy ? 1 : 0);
            x[i]=t;
            t=0;
        }
        printf("%3d | ", currencyIterate);
        for(int i=1;i<=n;i++) printf("%7.4f | ",x[i]);

        printf("%7.4f | \n", max_err);
    }
    printf("\nОтвет:");
    for(int i=1;i<=n;i++)
        printf("\t%7.4f",x[i]);

    printf("\nИтараций: %d", currencyIterate);

    printf("\nПогрешность:");
    for(int i=1;i<=n;i++) printf("\t%7.4f",errorRate[i]);

}
int main()
{
    nhap();
    if(!make_diagonally_dominant(1))
        printf("\nНевозможно сделать диагональное доминирование из исходной матрицы");
    else solve();
}

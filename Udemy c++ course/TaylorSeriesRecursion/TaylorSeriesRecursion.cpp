#include <stdio.h>


/**Serie : Somatório de: ( (f'(n)(a)) / n!)(x-a)^n
 * 
 *   
 *      
 *  f(x) = e^x; f'(x) = e^x; f''(x) = e^x; ...
 *  Em torno do valor x = 0, temos: f(0) = e^0 + ((e^0)/1!)(x-0)^1 + ((e^0)/2!)(x-0)^2 + ((e^0)/3!)(x-0)^3 ...
 *  f(0) = 1 + x + (x^2)/2! + (x^3)/3! + (x^4)/4! + (x^5)/5! + (x^6)/6! ...
 * 
 *  Isso quer dizer que f(x) = e^x, quando x = 0, tende a ter o mesmo resultado da expressão acima, tendo uma precisão maior a medida que aumentamos n, tendendo ao infinito.
 * 
*/

double e(int x, int n){
    static double p =1, f=1;
    double r;

    if(n ==0){
        return 1;
    }

    r=e(x, n-1);
    p=p*x;
    f=f*n;
    return r+p/f;
}

int main(){

    printf("%lf \n", e(1,10)); 
    return 0;
}
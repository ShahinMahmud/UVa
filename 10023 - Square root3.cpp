#include <stdio.h>
#include <string.h>

int main() {
    char s[1024];
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        short x[1024] = {}, y[1024] = {};
        int i, j;
        for(i = 0, j = len-1; j >= 0; i++) {
            x[i] = s[j]-'0';
            if(j-1 >= 0)    x[i] = x[i] + (s[j-1]-'0')*10;
            j -= 2;
        }
        int xlen = len, ylen = 0, head = 0;
        while(xlen >= 0 && x[xlen] == 0) xlen--;
        for(j = (len-1)/4, i = j*2; j >= 0; j--, i -= 2) {
            ylen++;
            for(int p = ylen; p >= 1; p--) {
                y[p] = y[p-1];
            }
            y[0] = 0;
            if(xlen < j) {
                if(!head)   putchar('0'), head = 1;
                else {
                    putchar('0');
                    putchar('0');
                }
                continue;
            }
            int l = 0, r = 99, p;
            short z[1024]; // z = (y*10 + p)*p;
            while(l <= r) {
                p = (l+r)/2;
                y[0] += p;
                z[0] = 0;
                for(int q = 0; q <= ylen+5; q++) {
                    z[q] += p*y[q];
                    z[q+1] = z[q]/100;
                    z[q] %= 100;
                }
                /*printf("loop %d\n", p);
                for(int q = ylen+2; i+q >= 0; q--)
                    printf("%02d", x[i+q]);
                puts(" x");
                for(int q = ylen+2; q >= 0; q--)
                    printf("%02d", z[q]);
                puts(" z");*/
                int chflag = 0;
                for(int q = ylen+5; q >= 0; q--) {
                    if(z[q] > x[i+q]) {
                        chflag = 1;
                        break;
                    } else if(z[q] < x[i+q]) {
                        chflag = 0;
                        break;
                    }
                }
                y[0] -= p;
                if(chflag)
                    r = p-1;
                else
                    l = p+1;
            }
            p = l-1;
            y[0] = p;
            z[0] = 0;
            for(int q = 0; q <= ylen+5; q++) {
                z[q] += p*y[q];
                z[q+1] = z[q]/100;
                z[q] %= 100;
            }
            for(int q = ylen+5; q >= 0; q--)
                x[i+q] -= z[q];
            for(int q = 0; q <= ylen+5; q++) {
                while(x[i+q] < 0)
                    x[i+q] += 100, x[i+q+1]--;
            }
            y[0] += p;
            for(int q = 0; q <= ylen+5; q++) {
                if(y[q] >= 100) {
                    y[q+1] += y[q]/100;
                    y[q] %= 100;
                }
            }
            ylen += 5;
            while(ylen >= 0 && y[ylen] == 0)    ylen--;
            while(xlen >= 0 && x[xlen] == 0)    xlen--;
            if(!head)   printf("%d", p), head = 1;
            else        printf("%02d", p);
        }
        puts("");
        if(t)
            puts("");
    }
    return 0;
}

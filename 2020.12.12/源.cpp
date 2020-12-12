#include<stdio.h>
#include<stdlib.h>
int* addToArrayForm(int* A, int ASize, int k) {
    int ksize = 0;
    int kuum = k;
    while (kuum) {
        kuum = kuum / 10;
        ksize++;
    }
    int len = ASize > ksize ? ASize : ksize;
    int sizenum = 0;//进位
    int i = ASize - 1;
    int* retarr = (int*)malloc(sizeof(int) * (len + 1));//新数组
    int retaize = 0;//新数组大小
    while (len--) {
        int a = 0;
        if (i >= 0) {
            a = A[i];
            i--;
        }
        int ret = 0;
        ret = a + k % 10 + sizenum;
        k /= 10;
        if (ret > 9) {
            ret -= 10;
            sizenum = 1;
        }
        else {
            sizenum = 0;
        }
        retarr[retaize] = ret;
        retaize++;
    }
    if (sizenum == 1) {
        retarr[retaize] = 1;
        retaize++;
    }
    int left = 0;
    int right = retaize - 1;
    while (left < right) {
        int tem = retarr[left];
        retarr[left] = retarr[right];
        retarr[right] = tem;
        left++;
        right--;

    }
    return retarr;
}
int main() {
    int a[5] = { 1,2,5,4,4 };
    int k = 254;
    int* arr = addToArrayForm(a, 5, 254);
    for (int i = 0; i < 5; i++) {
        printf("%5d", arr[i]);
    }

}

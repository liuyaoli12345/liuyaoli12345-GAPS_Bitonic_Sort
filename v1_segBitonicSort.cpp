#include <cmath>
#include <iostream>
#include "segBitonicSort.h"

// 初始实现，没有递归

void compare(float *a, float *b, int N, int a_index, int b_index)
{
    if (a_index >= N) return;
    float A = *a;
    float B = (b_index >= N) ? INFINITY : *b;
    if (A > B)
    {
        *a = B;
        if (b_index < N) *b = A;
    }
}

void bitonic(float *mem, int N, int size)
{
    int K = log2(size);
    int d = 1 << K;
    for (int n = 0; n < d >> 1; n++)
    {
        compare(&mem[n], &mem[d - n - 1], N, n, d - n - 1);
    }
    K--;
    if (K <= 0)
    {
        return;
    }
    for (int k = K; k > 0; k--)
    {
        d = 1 << k;
        for (int m = 0; m < size; m += d)
        {
            for (int n = 0; n < d >> 1; n++)
            {
                compare(&mem[m + n], &mem[m + (d >> 1) + n], N, m + n, m + (d >> 1) + n);
            }
        }
    }
}

void BitonicSort(float *mem, int N)
{
    float *map = new float[N];
    for (int n = 0; n < N; n++)
    {
        map[n] = mem[n];
    }
    int size = 1 << (int)ceil(log2(N));
    for (int k = 1; k <= log2(size); k++)
    {
        int d = 1 << k;
        for (int n = 0; n < size; n += d)
        {
            float *map_ptr = &map[n];
            bitonic(map_ptr, N-n, d);
        }
    }
    for (int n = 0; n < N; n++)
    {
        mem[n] = map[n];
    }
    delete[] map;
}

void segmentedBitonicSort(float *data, int *seg_id, int *seg_start, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        BitonicSort(data + *(seg_start+i), *(seg_start+i+1)-*(seg_start+i));
    }
}
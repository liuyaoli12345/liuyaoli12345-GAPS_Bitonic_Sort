#include <cmath>
#include "segBitonicSort.h"
// 优化版本三 没有任何函数调用

void segmentedBitonicSort(float *data, int *seg_id, int *seg_start, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        float *mem = data + *(seg_start + i);
        int N = *(seg_start + i + 1) - *(seg_start + i);
        int nearest_pow_of_2 = 1;
        for (; nearest_pow_of_2 < N; nearest_pow_of_2 <<= 1)
            ;
        for (int outer_step = 2; outer_step <= nearest_pow_of_2; outer_step<<=1)
        {
            for (int n = 0; n < nearest_pow_of_2; n += outer_step)
            {
                float *p = &mem[n];
                int limit = N - n;
                for (int z = 0; z < outer_step >> 1; z++)
                {
                    int a_index = z;
                    int b_index = outer_step - z - 1;
                    if (a_index >= limit)
                        break;
                    float A = p[a_index];
                    float B = (b_index >= limit) ? INFINITY : p[b_index];
                    if (A > B)
                    {
                        p[a_index] = B;
                        if (b_index < limit)
                            p[b_index] = A;
                    }
                }
                for(int inner_step = outer_step>>1; inner_step>1; inner_step>>=1)
                {
                    for (int m = 0; m < outer_step; m += inner_step)
                    {
                        for (int n = 0; n < inner_step >> 1; n++)
                        {
                            int a_index = m + n;
                            int b_index = m + (inner_step >> 1) + n;
                            if (a_index >= limit)
                                break;
                            float A = p[a_index];
                            float B = (b_index >= limit) ? INFINITY : p[b_index];
                            if (A > B)
                            {
                                p[a_index] = B;
                                if (b_index < limit)
                                    p[b_index] = A;
                            }
                        }
                    }
                }
            }
        }
    }
}


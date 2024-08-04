#include <cmath>
#include <iostream>
#include "segBitonicSort.h"

// 优化一遍的实现： 没有函数调用：没有除ceil()、log2()以外的其他函数调用 内存高效：所有操作直接对data本身进行，没有动态容器等内存分配，没有全局变量

void segmentedBitonicSort(float *data, int *seg_id, int *seg_start, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        float *mem = data + *(seg_start + i);
        int N = *(seg_start + i + 1) - *(seg_start + i);
        int size = 1 << (int)ceil(log2(N));
        for (int k = 1; k <= log2(size); k++)
        {
            int d = 1 << k;
            for (int n = 0; n < size; n += d)
            {
                float *p = &mem[n];
                int limit = N - n;
                int batch = d;
                int depth = log2(batch);
                int step = 1 << depth;
                for (int z = 0; z < step >> 1; z++)
                {
                    int a_index = z;
                    int b_index = step - z - 1;
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
                depth--;
                if (depth <= 0)
                {
                    continue;
                }
                for (int l = depth; l > 0; l--)
                {
                    step = 1 << l;
                    for (int m = 0; m < batch; m += step)
                    {
                        for (int n = 0; n < step >> 1; n++)
                        {
                            int a_index = m + n;
                            int b_index = m + (step >> 1) + n;
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


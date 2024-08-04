#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "segBitonicSort.h"

void generateRandomData(float *data, int *seg_id, int *seg_start, int n, int m)
{
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; i++)
    {
        data[i] = static_cast<float>(std::rand()) / RAND_MAX;
    }
    for (int i = 0; i < n; i++)
    {
        seg_id[i] = std::rand() % m;
    }
    std::sort(seg_id, seg_id + n);
    seg_start[0] = 0;
    for (int i = 1, current_seg = 0; i < n; i++)
    {
        if (seg_id[i] != seg_id[i - 1])
        {
            current_seg++;
            seg_start[current_seg] = i;
        }
    }
    seg_start[m] = n;
    for (int i = 1; i < m; i++)
    {
        if (seg_start[i] == 0)
        {
            seg_start[i] = seg_start[i - 1];
        }
    }
}

bool verifySegmentedSort(float *data, int *seg_start, int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        if (!std::is_sorted(data + seg_start[i], data + seg_start[i + 1]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    bool all_passed=true;
    int error_count=0;
    for (int i = 0; i < 100; i++)
    {
        int n = 10000;
        int m = 20;
        float *data = new float[n];
        int *seg_id = new int[n];
        int *seg_start = new int[m + 1];

        generateRandomData(data, seg_id, seg_start, n, m);

        std::cout << "Generated Data: ";
        for (int i = 0; i < n; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;

        std::cout << "Segment IDs: ";
        for (int i = 0; i < n; i++)
            std::cout << seg_id[i] << " ";
        std::cout << std::endl;

        std::cout << "Segment Starts: ";
        for (int i = 0; i < m + 1; i++)
            std::cout << seg_start[i] << " ";
        std::cout << std::endl;

        segmentedBitonicSort(data, seg_id, seg_start, n, m);

        std::cout << "Sorted Data: ";
        for (int i = 0; i < n; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;

        if (verifySegmentedSort(data, seg_start, n, m))
        {
            std::cout << "\033[32mSegemented Bitonic Sort passed.\033[0m" << std::endl;
        }
        else
        {
            all_passed=false;
            error_count++;
            std::cout << "\033[31mSegemented Bitonic Sort failed.\033[0m" << std::endl;
        }
        delete[] data;
        delete[] seg_id;
        delete[] seg_start;
    }
    if(all_passed){
        std::cout << "all 100 tests passed."<<std::endl;
    } else {
        std::cout << "WA occurred for " << error_count << " times." << std::endl;
    }
    return 0;
}

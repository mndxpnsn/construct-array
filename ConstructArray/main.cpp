//
//  main.cpp
//  ConstructArray
//
//  Created by mndx on 06/01/2022.
//

#include <iostream>

typedef struct memo_table {
    bool is_set;
    long long val;
} m_table;

m_table* g_table;
m_table* f_table;

long long g_m(int n, int k, int x, int m);
long long f_m(int n, int k, int x, int m);

void init_tables(int n) {
    g_table = new m_table[n + 1];
    f_table = new m_table[n + 1];
    
    for(int i = 0; i < n + 1; ++i) {
        g_table[i].is_set = false;
        g_table[i].val = 0;
        f_table[i].is_set = false;
        f_table[i].val = 0;
    }
}

long long g_m(int n, int k, int x, int m) {
    long long res = 0;
    
    if(g_table[m].is_set)
        return g_table[m].val;
    
    if(m == 2)
        return 1;
    
    if(m > 2)
        res = f_m(n, k, x, m - 1) + g_m(n, k, x, m - 1) * (k - 2);
    
    res = res % ((int) 1e+9 + 7);
    g_table[m].val = res;
    g_table[m].is_set = true;
    
    return res;
}

long long f_m(int n, int k, int x, int m) {
    long long res = 0;
    
    if(f_table[m].is_set)
        return f_table[m].val;
    
    if(m == 2)
        return 0;
    
    if(m > 2)
        res = g_m(n, k, x, m - 1) * (k - 1);
    
    res = res % ((int) 1e+9 + 7);
    f_table[m].val = res;
    f_table[m].is_set = true;
    
    return res;
}

long long count_array(int n, int k, int x) {
    long long res = 0;

    if(k < x || n < 2)
        return res;
    
    if(n == 2 && x == 1)
        return 0;
    
    if(n == 2 && x != 1)
        return 1;
        
    if(x == 1)
        res = f_m(n, k, x, n) % ((int) 1e9 + 7);
    
    if(x != 1)
        res = g_m(n, k, x, n) % ((int) 1e9 + 7);
    
    return res;
}

int main(int argc, const char * argv[]) {
    int n, k, x;
    
    //Set parameters
    n = 6; //Number of elements in array. 1 < n <= 1e+5
    k = 5; //Number of elements to select from. 2 <= k <= 1e+5
    x = 2; //Last element in array. 1 <= x <= k
    
    //Initialize memo tables
    init_tables(n);
    
    //Compute number of admissable arrays
    long long num_arrays = count_array(n, k, x);
    
    //Print results
    std::cout << "number of admissable arrays: " << num_arrays << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}

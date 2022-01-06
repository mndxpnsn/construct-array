//
//  main.cpp
//  ConstructArray
//
//  Created by mndx on 06/01/2022.
//  The solution is based on the recurrence:
//  f(2) = 0
//  g(2) = 1
//
//  f(n) = g(n - 1) * (k - 1)
//  g(n) = f(n - 1) + g(n - 1) * (k - 2)
//
//  For all 3 <= n <= 1e+5 and 2 <= k <= 1e+5
//

#include <iostream>

typedef struct memo_table {
    bool is_set;
    long long val;
} m_table;

m_table* g_table;
m_table* f_table;

long long g_n(int n, int k, int x);
long long f_n(int n, int k, int x);

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

long long g_n(int n, int k, int x) {
    long long res = 0;
    
    if(g_table[n].is_set)
        return g_table[n].val;
    
    if(n == 2)
        return 1;
    
    if(n > 2)
        res = f_n(n - 1, k, x) + g_n(n - 1, k, x) * (k - 2);
    
    res = res % ((int) 1e+9 + 7);
    g_table[n].val = res;
    g_table[n].is_set = true;
    
    return res;
}

long long f_n(int n, int k, int x) {
    long long res = 0;
    
    if(f_table[n].is_set)
        return f_table[n].val;
    
    if(n == 2)
        return 0;
    
    if(n > 2)
        res = g_n(n - 1, k, x) * (k - 1);
    
    res = res % ((int) 1e+9 + 7);
    f_table[n].val = res;
    f_table[n].is_set = true;
    
    return res;
}

long long count_array(int n, int k, int x) {
    long long res = 0;

    if(k < x || n < 2)
        return res;
        
    if(x == 1)
        res = f_n(n, k, x) % ((int) 1e9 + 7);
    
    if(x != 1)
        res = g_n(n, k, x) % ((int) 1e9 + 7);
    
    return res;
}

int main(int argc, const char * argv[]) {
    int n, k, x;
    
    //Set parameters
    n = 6; //Number of elements in array. 2 <= n <= 1e+5
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

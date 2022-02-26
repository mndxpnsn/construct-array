//
//  main.cpp
//  ConstructArray
//
//  Created by mndx on 06/01/2022.
//  The solution is based on the recurrence:
//  g(3, k) = k - 1
//  f(3, k) = k - 2
//
//  g(n, k) = (k - 1) * f(n - 1, k)
//  f(n, k) = g(n - 1, k) + (k - 2) * f(n - 1, k)
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

void init_m_tables(int n) {
    g_table = new m_table[n + 1];
    f_table = new m_table[n + 1];
    
    for(int i = 0; i < n + 1; ++i) {
        g_table[i].is_set = false;
        g_table[i].val = 0;
        f_table[i].is_set = false;
        f_table[i].val = 0;
    }
}

void delete_m_tables() {
    delete [] g_table;
    delete [] f_table;
}

long long g(int n, int k);
long long f(int n, int k);

long long g(int n, int k) {
    long long res = 0;
    
    if(g_table[n].is_set)
        return g_table[n].val;
    
    if(n == 3)
        return k - 1;
    
    if(n > 3)
        res = (k - 1) * f(n - 1, k);
    
    res = res % (long long) (1e9 + 7);
    g_table[n].is_set = true;
    g_table[n].val = res;
    
    return res;
}

long long f(int n, int k) {
    long long res = 0;
    
    if(f_table[n].is_set)
        return f_table[n].val;
    
    if(n == 3)
        return k - 2;
    
    if(n > 3)
        res = g(n - 1, k) + (k - 2) * f(n - 1, k);
    
    res = res % (long long) (1e9 + 7);
    f_table[n].is_set = true;
    f_table[n].val = res;
    
    return res;
}

long count_array(int n, int k, int x) {
    long num_ways = 0;
    
    init_m_tables(n);
    
    num_ways = (x == 1) ? g(n, k) : f(n, k);
    
    delete_m_tables();
    
    return num_ways;
}

int main(int argc, const char * argv[]) {
    int n, k, x;
    
    //Set parameters
    n = 6; //Number of elements in array. 2 <= n <= 1e+5
    k = 5; //Number of elements to select from. 2 <= k <= 1e+5
    x = 2; //Last element in array. 1 <= x <= k
    
    //Compute number of admissable arrays
    long long num_arrays = count_array(n, k, x);
    
    //Print results
    std::cout << "number of admissable arrays: " << num_arrays << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}

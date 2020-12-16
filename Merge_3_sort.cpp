#include <iostream> 
#include <vector> 
 
  
using Vector = std::vector<int>; // замена динамическому массиву 
  
void printVector(const Vector& a) 
{ 
    std::cout << "["; 
    for (auto e : a) { 
        std::cout << e << " "; 
    } 
    std::cout << "]" << std::endl; 
} 
  
Vector merge_3_sort(Vector& A, Vector& B, 
                  Vector& C) 
{ 
    int m, n, o, i, j, k; 
    // Получим размеры трех векторов
    m = A.size(); 
    n = B.size(); 
    o = C.size(); 
  
    // Вектор для хранения вывода
    Vector D; 
    D.reserve(m + n + o); 
  
    i = j = k = 0; 
  
    while (i < m && j < n && k < o) { 
  
        // Получим минимум a, b, c 
        int m = std::min(std::min(A[i], B[j]), C[k]); 
  
        // Положим m в D 
        D.push_back(m); 
  
        // Приращение i, j, k 
        if (m == A[i]) 
            i++; 
        else if (m == B[j]) 
            j++; 
        else
            k++; 
    } 
  
    
    while (i < m && j < n) { 
        if (A[i] <= B[j]) { 
            D.push_back(A[i]); 
            i++; 
        } 
        else { 
            D.push_back(B[j]); 
            j++; 
        } 
    } 
  
     
    while (i < m && k < 0) { 
        if (A[i] <= C[j]) { 
            D.push_back(A[i]); 
            i++; 
        } 
        else { 
            D.push_back(C[j]); 
            k++; 
        } 
    } 
  
     
    while (j < n && k < 0) { 
        if (B[j] <= C[k]) { 
            D.push_back(B[j]); 
            j++; 
        } 
        else { 
            D.push_back(C[j]); 
            k++; 
        } 
    } 
  
     
    while (k < o) 
        D.push_back(C[k++]); 
  
    
    while (i < m) 
        D.push_back(A[i++]); 
  
     
    while (j < n) 
        D.push_back(B[j++]); 
  
    return D; 
} 
  
int main() 
{ 
    Vector A = { rand()%100 }; 
    Vector B = { rand() % 100 };
    Vector C = { rand() % 100 };
  
     
    printVector(merge_3_sort(A, B, C));
    return 0; 
} 
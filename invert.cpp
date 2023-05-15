#include <iostream>
#include <numeric>
#include <vector>
#include <limits>

void invert( float matrix[], int matrix_size ){
    // Initialize row states to unnormalized [0]
    short row_states[ matrix_size ] = { 0 };
    size_t i, j, k, pivot_index;
    float normal_pivot, reduction_pivot, pivot_candidate;
    for( k = 0; k < matrix_size; k++ ){
        normal_pivot = -( std::numeric_limits< float >::max() );
        for( i = 0; i < matrix_size; i++ ){
            if( row_states[ i ] == 0 ){
                pivot_candidate = matrix[ ( i * matrix_size ) + i ];
                if( pivot_candidate >= normal_pivot ){
                    normal_pivot = pivot_candidate;
                    pivot_index = i;
                }
            }
        }
        // Normalize pivot row
        matrix[ ( pivot_index * matrix_size ) + pivot_index ] = 1.0;
        for( j = 0; j < matrix_size; j++ ){
            matrix[ ( pivot_index * matrix_size ) + j ] = matrix[ ( pivot_index * matrix_size ) + j ] 
                / normal_pivot;
        }
        // Reduce non-pivot rows
        for( i = ( pivot_index + 1 ) % matrix_size; i != pivot_index; i = ( i + 1 ) % matrix_size ){
            reduction_pivot = matrix[ ( i * matrix_size ) + pivot_index ];
            matrix[ ( i * matrix_size ) + pivot_index ] = 0.0;
            for( j = 0; j < matrix_size; j++ ){
                matrix[ ( i * matrix_size ) + j ] = matrix[ ( i * matrix_size ) + j ] - 
                    ( matrix[ ( pivot_index * matrix_size ) + j ] * reduction_pivot );
            }
        }
        // Mark pivot row as normalized [1]
        row_states[ pivot_index ] = 1;
    }
}

void print_matrix( float matrix[], int matrix_size ){
    for( int i = 0; i < matrix_size; i++ ){
        for( int j = 0; j < matrix_size; j++ ){
            std::cout << "\t" << matrix[ ( i * matrix_size ) + j ];
        }
        std::cout << ";\n";
    }
}

int main(){
    // Get input matrix from console
    int n = 0;
    std::cout << "Input a value for n in the range [2, 100]: ";
    std::cin >> n;
    if( n < 2 || n > 100 ){
        return( 1 );
    }
    std::cout << "Input is within required range\n\n";
    float a[ n * n ] = { 0 };

    std::cout << "Enter matrix elements:\n";
    for( int i = 0; i < n; i++ ){
        std::cout << "row " << i << ",";
        for( int j = 0; j < n; j++ ){
            std::cout << "\tcol " << j << ":\t";
            std::cin >> a[ ( i * n ) + j ];
        }
    }
    std::cout << "\n";

    // Print input matrix
    std::cout << "Input matrix M:\n";
    print_matrix( a, n );
    // Gauss Jordan matrix inversion
    invert( a, n );
    // Print inverted matrix
    std::cout << "Inverse matrix M^-1:\n";
    print_matrix( a, n );

    return( 0 );
}

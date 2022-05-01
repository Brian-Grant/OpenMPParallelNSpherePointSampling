#include <immintrin.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <random>
#include <iostream>
#include <cassert>
#include <unistd.h>

#define N 16*1000000
int main(void){
	
	alignas(32) static float w1[N], x1[N], y1[N], z1[N], w2[N], x2[N], y2[N], z2[N];



	std::default_random_engine eng;
    std::uniform_real_distribution<float> dist(0, 100);
    for (int i = 0; i < N; i++) {
        w1[i] = dist(eng);
        x1[i] = dist(eng);
        y1[i] = dist(eng);
		z1[i] = dist(eng);
        w2[i] = dist(eng);
        x2[i] = dist(eng);
		y2[i] = dist(eng);
        z2[i] = dist(eng);
    }
	
	//sequential	
	auto s_start = std::chrono::steady_clock::now();
	static float l_s[N];
	for(int i = 0; i < N; i++){
		l_s[i] = std::sqrt(w1[i]*w2[i] + x1[i]*x2[i] + y1[i]*y2[i] + z1[i]*z2[i]);
	}
	auto s_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> s_interval = s_end-s_start;
	
	//SIMD
	alignas(32) static float l_v[N];
	
	auto v_start = std::chrono::steady_clock::now();
	for (int i = 0; i < N/8; i++) {
            __m256 ymm_w1 = _mm256_load_ps(w1 + 8*i);
            __m256 ymm_x1 = _mm256_load_ps(x1 + 8*i);
            __m256 ymm_y1 = _mm256_load_ps(y1 + 8*i);
            __m256 ymm_z1 = _mm256_load_ps(z1 + 8*i);

			__m256 ymm_w2 = _mm256_load_ps(w2 + 8*i);
            __m256 ymm_x2 = _mm256_load_ps(x2 + 8*i);
            __m256 ymm_y2 = _mm256_load_ps(y2 + 8*i);
            __m256 ymm_z2 = _mm256_load_ps(z2 + 8*i);
	
			__m256 ymm_l = _mm256_sqrt_ps(_mm256_mul_ps(ymm_w1, ymm_w2)
                                          + _mm256_mul_ps(ymm_x1, ymm_x2)
                                          + _mm256_mul_ps(ymm_y1, ymm_y2)
										  + _mm256_mul_ps(ymm_z1, ymm_z2));
            _mm256_store_ps(l_v + 8*i, ymm_l);
        }

	auto v_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> v_interval = v_end-v_start;


	std::cout << std::endl;
	std::cout << "Sequential Execution Time: "<< s_interval.count() << std::endl;
	std::cout << "SIMD Execution Time: "<< v_interval.count() << std::endl;

	float max = 0;
    for (int i = 0; i < N; i++) {
		/*		
		std::cout << i << std::endl;		
     	std::cout <<  l_s[i] << std::endl;   
		std::cout <<  l_v[i] << std::endl;         
		*/

		
        if (l_s[i] - l_v[i]!= 0) {
			std::cout << i << std::endl;		
     		std::cout <<  l_s[i] << std::endl;   
			std::cout <<  l_v[i] << std::endl;      
			assert(false);
        }
        
        max = std::max(max, l_s[i] - l_v[i]);
    }
	std::cout << "max: " << max << std::endl;
	return 0;
}

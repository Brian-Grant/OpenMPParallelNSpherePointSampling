#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <chrono>
#include <iomanip>
#include <fstream>
//#include <sstream>

#define d_idx(x) (x-2)
#define N_PTS 1000000



typedef std::uniform_real_distribution<float> RNG;
typedef std::mt19937 ENG;

float gen_pt_get_dist(int d, RNG & dis, ENG & gen);

//int main(int argc, char **argv){
int main(void){
	//std::cout << "prog" << std::endl;
	//std::cout << omp_get_num_threads() << std::endl;
	
    int histogram[15][100] = {0};
	
	//float point_dist[15][N_PTS];
	
	float histo_interval = 0.01;

	
	//#pragma omp parallel private(tid)
	//{
	//	tid = omp_get_thread_num();
	//	printf("tid: %d\n", tid);

	//}
	auto start = std::chrono::steady_clock::now();
	#pragma omp parallel for schedule(dynamic)
	for(unsigned int d = 2; d < 17; d++){
		int tid = omp_get_thread_num();
		float dist;
		int idx;		
		//printf("tid: %d   d: %d\n", tid, d);
		std::random_device rd;
		ENG gen(rd() + clock() + tid);
		RNG dis(0, 1.0);
		for(unsigned int i = 0; i < N_PTS; i++){
			//point_dist[d_idx(d)][i] = gen_pt_get_dist(d, dis, gen);
			dist = gen_pt_get_dist(d, dis, gen);
			idx = (int)floor(dist/histo_interval);
			histogram[d_idx(d)][idx] += 1;
		}
	}
    auto end = std::chrono::steady_clock::now();
	
	/*
	#pragma omp parallel for schedule(dynamic)
	for(unsigned int d = 2; d < 17; d++){
		int idx;	
		float pt_len;	
		for(unsigned int i = 0; i < N_PTS; i++){
			pt_len = point_dist[d_idx(d)][i];
			idx = (int)floor(pt_len/histo_interval);
			//std::cout << pt_len << " " << idx << std::endl;
			histogram[d_idx(d)][idx] += 1;
		}
	}
	*/

	for(unsigned int d = 2; d < 17; d++){
		std::cout << "\t" << d;	
	}
	std::cout << "\n" << std::endl;	
	std::cout << std::setprecision(2) << std::fixed;
	for(unsigned int i = 0; i < 100; i++){		
		std::cout << i/100.0;		
		for(unsigned int d = 2; d < 17; d++){
			std::cout << "\t" << histogram[d_idx(d)][i];	
		}
		std::cout << std::endl;
	}	
	
	std::chrono::duration<double> interval = end-start;
	std::cout << std::endl;
	std::cout << "Execution Time: "<< interval.count() << std::endl;
	

	std::ofstream output("out.csv");
	if(output.is_open()){
		for(unsigned int d = 2; d < 17; d++){
			for(unsigned int i = 0; i < 100; i++){	
				output << d << "," << i/100.0 << "," << histogram[d_idx(d)][i] << std::endl;
			}

		}
		output.close();	
	} else{
		std::cout << "problem writing to file" << std::endl;
	}
	return 0;

}


float gen_pt_get_dist(int d, RNG & dis, ENG & gen){
	float* pt = new float[d];
	float sq_sum = 0;
	float len = 2.0; //dummy for the while loop
	float norm;
	float r;
	float coeff;		
	for(int i = 0; i < d; i++){
		pt[i] = dis(gen);
		//std::cout << "pt " << pt[i] << std::endl;
		sq_sum += pt[i] * pt[i];
	}
	norm = sqrt(sq_sum);
	r = pow(dis(gen), 1.0/d);
	coeff = r/norm;
	sq_sum = 0;		
	for(int i = 0; i < d; i++){
		pt[i] = pt[i] * coeff;
		sq_sum += (pt[i] * pt[i]);
	}
	len = sqrt(sq_sum);
	
	assert(len <= 1.0);
	
	//std::cout << "len: " << len << std::endl;
	delete[] pt;
	/*
	if(len > 1.0){
		return gen_pt_get_dist(d, dis, gen);
	}
	*/
	return len;
	
}

/*

float gen_pt_get_dist(int d, RNG & dis, ENG & gen){
	float pt[d];
	float sq_sum = 0;
	float len = 2.0; //dummy for the while loop
	float norm;
	float r;
	float coeff;		
	for(unsigned int i = 0; i < d; i++){
		pt[i] = dis(gen);
		//std::cout << "pt " << pt[i] << std::endl;
		sq_sum += pt[i] * pt[i];
	}
	norm = sqrt(sq_sum);
	r = pow(dis(gen), 1.0/5);
	coeff = r/norm;
	sq_sum = 0;		
	for(unsigned int i = 0; i < d; i++){
		pt[i] = pt[i] * coeff;
		sq_sum += (pt[i] * pt[i]);
	}
	len = sqrt(sq_sum);
	assert(len <= 1.0);
	//std::cout << "len: " << len << std::endl;
	return len;
	
}






*/





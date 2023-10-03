#include "Sphere.h"

#define _USE_MATH_DEFINES 

#include <cmath>
#include <vector>
#include<string>
#include <iostream>

//#define pi = 3.141592653589793
float pi = 3.141592653589793;


// simplificacion de la clase Sphere.h/cpp de http://www.songho.ca/opengl/gl_sphere.html 
// 
// genera la esfera de radio r, vrtx guarda los vertices generados e indices asigna indices a los vertices


float* Sphere::create() {
	float* positions;
	unsigned int* idx;
	int idx_size = buildVertices(1.f, sectorCount, positions, idx);
	return positions;
}


int buildVertices(double r, int sectorCount, float*& vrtx, unsigned int*& indices){
	std::vector<unsigned int> idx;  // vertex index vector

	int stackCount = sectorCount / 2;
	vrtx = new float[(stackCount + 1) * (sectorCount + 1) * 3];

	for (int i = 0; i <= stackCount; ++i){
		float theta = pi / (sectorCount / 2) * i;
		for (int j = 0; j <= sectorCount; ++j){
			float phi = 2 * pi / sectorCount * j;

			vrtx[3 * (i * (sectorCount + 1) + j)] = r * sin(theta) * cos(phi);			    // x
			vrtx[3 * (i * (sectorCount + 1) + j) + 1] = r * cos(theta);					    // y
			vrtx[3 * (i * (sectorCount + 1) + j) + 2] = r * sin(theta) * sin(phi);		// z

			if (i < stackCount && j < sectorCount){
				idx.push_back(i * (sectorCount + 1) + j);
				idx.push_back((i + 1) * (sectorCount + 1) + j);
				idx.push_back(i * (sectorCount + 1) + (j + 1));
				idx.push_back(i * (sectorCount + 1) + (j + 1));
				idx.push_back((i + 1) * (sectorCount + 1) + j);
				idx.push_back((i + 1) * (sectorCount + 1) + (j + 1));
			}
		}
	}

	indices = new unsigned int[idx.size()];
	int k = 0;


	for (unsigned int p : idx){
		indices[k] = p;
		k++;

	}

	return idx.size(); //regresa el tamaño del arreglo de vertices
										//hubiera querido que esta funcion fuera void pero intentar sacar idx.size en el main causa conflictos
}


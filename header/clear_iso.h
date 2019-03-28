#pragma once
/*
Created by Yuhan Ping.
This is for detecting and clean isolated triangles
*/
#ifndef CLEAR_ISO_H
#define CLEAR_ISO_H	

#include <igl\facet_components.h>
#include <igl/vertex_components.h>
#include <iostream>

using namespace std;
using namespace Eigen;

bool get_components(MatrixXi &F, VectorXi &CF, VectorXi &AC, MatrixX2i & CP);// detect the isolated triangles
/*
	F: face matrix
	C: connect components ids  
	AC: all connect components info
	CP: components start end position
*/

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &AC, MatrixX2i &CP, MatrixXd &V_max, MatrixXi &F_max); // leave max components and detect others
/*
	NOTES: Currently all non-max components is regarded as "isolate triangles", maybe add a THRESHOLD in the feature
	V: vertex matrix
	F: face matrix
	AC: all connect components info
	V_max: vertex of max components 
	F_max: faces of max components
*/

#endif // !CLEAR_ISO_H

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

bool get_components(MatrixXi &F, VectorXi &CF,VectorXi &CV, VectorXi &ACF,VectorXi &ACV, MatrixX2i & CPF, MatrixX2i & CPV);// detect the isolated triangles
/*
	F: face matrix
	CF: connect components ids per face
	CV: connect components idx per vertex
	ACF: all connect components info on faces
	ACV: all connect components info on vertex
	CPF: components start end position on face
	CPV: components start end position on vertex
*/

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &ACF, MatrixX2i &CPF, MatrixXd &V_max, MatrixXi &F_max); // leave max components and detect others
/*
	NOTES: Currently all non-max components is regarded as "isolate triangles", maybe add a THRESHOLD in the feature
	V: vertex matrix
	F: face matrix
	ACF: all connect components info on faces
	CPF: connect components start end pos on faces
	V_max: vertex of max components 
	F_max: faces of max components
*/

#endif // !CLEAR_ISO_H

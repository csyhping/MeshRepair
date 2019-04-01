#pragma once
/*
Created by Yuhan Ping.
This is for detecting and clean isolated triangles
*/
#ifndef CLEAR_ISO_H
#define CLEAR_ISO_H	

#include <igl\facet_components.h>
#include <igl/vertex_components.h>
#include <igl/jet.h>
#include <igl\remove_unreferenced.h>
#include <igl\write_triangle_mesh.h>
#include <igl\slice.h>
#include <iostream>

using namespace std;
using namespace Eigen;

bool delete_iso_v(MatrixXd &V, MatrixXi &F, MatrixXd &NV, MatrixXi &NF, MatrixXd &IM); // delete isolate vertex
/*
	V: vertex matrix
	F: face matrix
	NV: vertex matrix after delete iso vertex
	NF: face matrix after delete iso vertex
	IM: #V by 1 list of indices such that: NF = IM(F) and NT = IM(T) and V(find(IM<=size(NV,1)),:) = NV
*/

bool get_components(MatrixXd &V, MatrixXi &F, VectorXi &CF,VectorXi &CV, VectorXi &ACF,VectorXi &ACV, MatrixXi & CPF, MatrixXi & CPV);// detect the isolated triangles
/*
	V: vertex matrix
	F: face matrix
	CF: connect components ids per face
	CV: connect components idx per vertex
	ACF: all connect components info on faces
	ACV: all connect components info on vertex
	CPF: records the face position belongs to each components
	CPV: records the vertex position belongs to each components
*/

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &ACF, VectorXi &ACV, MatrixXi &CPF, MatrixXi & CPV, MatrixXd &V_max, MatrixXi &F_max); // leave max components and detect others
/*
	NOTES: Currently all non-max components is regarded as "isolate triangles", maybe add a THRESHOLD in the feature
	V: vertex matrix
	F: face matrix
	ACF: all connect components info on faces
	CPF: records the face position belongs to each components
	V_max: vertex of max components 
	F_max: faces of max components
*/

#endif // !CLEAR_ISO_H

// Created by Yuhan Ping on 21/03/2019
// This is a program for mesh repair
// Latest update on 21/03/2019

#include <igl\opengl\glfw\Viewer.h>
#include <iostream>
#include <imgui\imgui.h>
#include <igl\opengl\glfw\imgui\ImGuiHelpers.h>
#include <igl\opengl\glfw\imgui\ImGuiMenu.h>
#include <igl\is_edge_manifold.h>
#include <igl\is_vertex_manifold.h>
#include <igl\extract_manifold_patches.h>
#include "header\io.h"
#include "header\clear_iso.h"


using namespace std;
using namespace Eigen;

// define the vertex and face matrix
MatrixXd V, V2, V_max(1, 3), color_per_face;;
/*
	V: vertex of input mesh
	V_max: max vertex components 
	color_per_face: color for each face 
*/

MatrixXi F, F2, F_max(1, 3), Components_P_F, Components_P_V;
/*
	F: faces of input mesh
	F_max: max face components
	Components_P_F: records the face position belongs to each components
	Components_P_V: records the vertex position belongs to each components
*/

VectorXi CF, All_Components_F,All_Components_V, CV;
/*
	CF: connected components ids per faces
	All_Components_F: all connect components info on faces
	All_Components_V: all connect components info on vertex
	CV: connected components idx per vertex
*/

bool viewer_on = false;

int main(int argv, char* argc[]) {
	// print the default info
	if (argv < 2) {
		default_info();
	}
	if (argv == 3 && !strcmp(argc[2], "-o")) {
		viewer_on = true;
	}
	//"C:/Users/admin/csyhping/Project/MeshRepair/MeshRepair/coffeecup.off"
	// read off file 
	load_file_off(argc[1], V, F);

	// calculate connect components
	get_components(V, F, CF, CV, All_Components_F, All_Components_V, Components_P_F, Components_P_V);

	if (viewer_on) {
		set_color_per_component(V, F, CF, color_per_face);
	}

	// delete isolate triangles
	detete_isolate_Triangles(V, F, All_Components_F,All_Components_V, Components_P_F,Components_P_V, V_max, F_max);

	getchar();


}

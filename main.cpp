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
#include <igl\remove_unreferenced.h>
#include <igl\write_triangle_mesh.h>
#include <igl\writeOFF.h>


using namespace std;
using namespace Eigen;

// define the vertex and face matrix
MatrixXd V, V2, V_max, color_per_face, NV,IM;
/*
	V: vertex of input mesh
	V_max: max vertex components 
	color_per_face: color for each face
	NV: vertex matrix after delete isolate vertices
	IM: #V by 1 list of indices such that: NF = IM(F) and NT = IM(T) and V(find(IM<=size(NV,1)),:) = NV
*/

MatrixXi F, F2, F_max, Components_P_F, Components_P_V, NF;
/*
	F: faces of input mesh
	F_max: max face components
	Components_P_F: records the face position belongs to each components
	Components_P_V: records the vertex position belongs to each components
	NF: face matrix after delete isolate vertices
*/

VectorXi CF, All_Components_F,All_Components_V, CV;
/*
	CF: connected components ids per faces
	All_Components_F: all connect components info on faces
	All_Components_V: all connect components info on vertex
	CV: connected components idx per vertex
*/

bool color_on = false;
bool viewer_on = false;

int main(int argv, char* argc[]) {
	// print the default info
	if (argv < 2) {
		default_info();
	}
	if (argv == 4 && !strcmp(argc[3], "-c")) {
		color_on = true;
	}
	if (argv == 4 && !strcmp(argc[3], "-v")) {
		viewer_on = true;
	}

	// read off file 
	load_file_off(argc[1], V, F);
	//load_file_off("C:/Users/admin/csyhping/MeshRepair/37.off", V, F);

	// delete isolate vertices
	delete_iso_v(V, F, NV, NF, IM);

	// calculate connect components
	get_components(V, F, CF, CV, All_Components_F, All_Components_V, Components_P_F, Components_P_V);

	// if user choose to set color
	if (color_on) {
		set_color_per_component(V, F, CF, color_per_face);
	}

	// delete isolate triangles
	detete_isolate_Triangles(V, F, All_Components_F,All_Components_V, Components_P_F,Components_P_V, V_max, F_max);

	// if user choose to launch viewer
	if (viewer_on) {
		igl::opengl::glfw::Viewer viewer;
		viewer.data().set_mesh(V_max, F_max);
		viewer.launch();
	}

	// write cleaned mesh
	igl::writeOFF(argc[2], V_max, F_max);
	//igl::write_triangle_mesh("C:/Users/admin/csyhping/data/ModelsForYuhan/model_1/44_remove_iso_v.off", NV, NF);
	
	//getchar();


}

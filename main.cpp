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
MatrixXd V, V2, V_max(1, 3);
MatrixXi F, F2, F_max(1, 3);
MatrixX2i Components_P_F(1, 2), Components_P_V(1, 2);
/*
	Components_P_F: records the components start and end position on face
	Components_P_V: records the components start and end position on vertex
*/
VectorXi CF, All_Components_F(1),All_Components_V(1), CV;
/*
	CF: connected components ids per faces
	All_Components_F: all connect components info on faces
	All_Components_V: all connect components info on vertex
	CV: connected components idx per vertex
*/

bool viewer_on = false;



// keyboard interaction
bool keydown(igl::opengl::glfw::Viewer&viewer, unsigned int key, int modifier) {
	std::cout << "key " << key << (unsigned int)key << std::endl;
	if (key == '1') {
		viewer.data().clear();
		viewer.data().set_mesh(V, F);
		return true;
	}
	else if (key == '2') {
		viewer.data().clear();
		viewer.data().set_mesh(V2, F2);
		return true;
	}
	return false;
}

int main(int argv, char* argc[]) {
	// print the default info
	//if (argv < 2) {
	//	default_info();
	//}
	//if (argv == 3 && !strcmp(argc[2], "-o")) {
	//	viewer_on = true;
	//}

	// read off file 
	load_file_off("C:/Users/admin/csyhping/Project/MeshRepair/MeshRepair/coffeecup.off", V, F, viewer_on);

	// calculate connect components
	get_components(F, CF, CV, All_Components_F, All_Components_V, Components_P_F, Components_P_V);

	detete_isolate_Triangles(V, F, All_Components_F, Components_P_F, V_max, F_max);

	getchar();


}

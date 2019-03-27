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
#include <igl\facet_components.h>


using namespace std;
using namespace Eigen;

// define the vertex and face matrix
MatrixXd V, V2, V_max(1, 3);
MatrixXi F, F2, F_max(1, 3);
MatrixX2i Components_P(1, 2);
/*
	Components_P: records the components start and end position
*/
VectorXi C, All_Components(1);
/*
	C: connected components ids
	AC: all connect components info
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
	load_file_off("F:/StudyMaterials/HKU/RA/MeshRepair/MeshRepair/coffeecup.off", V2, F2, viewer_on);

	// calculate connect components
	get_components(F2, C, All_Components, Components_P);

	detete_isolate_Triangles(V2, F2, C, All_Components, Components_P, V_max, F_max);

	getchar();


}

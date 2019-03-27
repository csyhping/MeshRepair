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
#include <igl\vertex_components.h>
#include "header\io.h"


using namespace std;
using namespace Eigen;

// define the vertex and face matrix
Eigen::MatrixXd V, V2;
Eigen::MatrixXi F, Vertex_Manifold_Check, F2;

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
	if (argv < 2) {
		default_info();
	}
	if (argv == 3 && !strcmp(argc[2], "-o")) {
		viewer_on = true;
	}
	// read off file 
	load_file_off(argc[1], V2, F2, viewer_on);


}

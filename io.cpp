#include "header\io.h"
#include <iostream>
#include <ctime>

void default_info() {
	std::cout << "First Mesh Demo by Yuhan Ping. Version 0.1." << std::endl;
	std::cout << "-------" << std::endl;
	time_t now = time(0);
	char* dt = ctime(&now);
	std::cout << "Currently under developing. Latest update on " << dt << std::endl;
	std::cout << "-------" << std::endl;
	std::cout << "Use [-o] to enable the ImGui viewer." << std::endl;
	std::cout << "Press Enter to exit." << std::endl;
	getchar();
	exit(0);
}

bool load_file_off(char*filename, Eigen::MatrixXd V, Eigen::MatrixXi F, bool viewer_on) {
	bool load_file_flag = false;
	load_file_flag = igl::readOFF(filename, V, F);
	if (load_file_flag) {
		std::cout << "Load file succesfully." << std::endl;
		std::cout << "The mesh contains " << V.rows() << " vertices and " << F.rows() << " faces." << std::endl;

		if (viewer_on) {
			// define a viewer
			igl::opengl::glfw::Viewer viewer;

			// define a menu
			igl::opengl::glfw::imgui::ImGuiMenu menu;

			// set up the menu plugin
			viewer.plugins.push_back(&menu);

			// set up the mesh
			viewer.data().set_mesh(V, F);

			// launch the viewer
			viewer.launch();
		}
		return true;
	}
	else {
		std::cout << "Error occured when loading file, please check." << std::endl;
		return false;
	}

}
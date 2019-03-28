#include "header\io.h"


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

bool load_file_off(char* filename, Eigen::MatrixXd &V, Eigen::MatrixXi &F) {
	bool load_file_flag = false;
	load_file_flag = igl::readOFF(filename, V, F);
	if (load_file_flag) {
		std::cout << "[INFO]" << std::endl;
		std::cout << "Load file succesfully." << std::endl;
		std::cout << "The mesh contains " << V.rows() << " vertices and " << F.rows() << " faces." << std::endl;
		return true;
	}
	else {
		std::cout << "[INFO]" << std::endl;
		std::cout << "Error occured when loading file, please check." << std::endl;
		return false;
	}

}

bool set_color_per_component(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::VectorXi &CF, Eigen::MatrixXd &color_per_face) {
	// set color
	color_per_face.resize(CF.rows(), 3);
	color_per_face.setZero();
	igl::jet(CF.col(0), true, color_per_face);
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_mesh(V, F);
	viewer.data().set_colors(color_per_face);
	viewer.launch();
	return true;
}
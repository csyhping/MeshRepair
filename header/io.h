#pragma once
/*
	Created by Yuhan Ping.
	This is for the io operation.
*/
#ifndef IO_H
#define IO_H

#include <igl\readOFF.h>
#include <igl\opengl\glfw\Viewer.h>
#include <imgui\imgui.h>
#include <igl\opengl\glfw\imgui\ImGuiHelpers.h>
#include <igl\opengl\glfw\imgui\ImGuiMenu.h>
#include <igl/jet.h>
#include <iostream>
#include <ctime>



void default_info(); // show author info and default info

bool load_file_off(char*filename, Eigen::MatrixXd &V, Eigen::MatrixXi &F); // load off format 

bool set_color_per_component(Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::VectorXi &CF, Eigen::MatrixXd &color_per_face); // set color for each components


#endif // !IO_H

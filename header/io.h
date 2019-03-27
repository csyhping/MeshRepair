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
#include <iostream>
#include <ctime>



void default_info(); // show author info and default info

bool load_file_off(char*filename, Eigen::MatrixXd &V, Eigen::MatrixXi &F, bool viewer_on); // load off format 


#endif // !IO_H

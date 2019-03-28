#include "header\clear_iso.h"


bool get_components(MatrixXi &F, VectorXi &CF,VectorXi &CV, VectorXi &ACF, VectorXi &ACV, MatrixX2i & CPF, MatrixX2i & CPV) {
	// find connect components per face and per vertex
	igl::facet_components(F, CF);
	igl::vertex_components(F, CV);

	/*--------------------------Face componennts operation--------------------------------------*/
	int current_components_id = 0;
	int component_counts = 1; // at least there is 1 component

	// collect all components info, ACF(i) records the size of components i, CPF records the start and end postion of each components
	ACF(0) = 0;
	CPF(0, 0) = 0;
	CPF(0, 1) = 0;

	// collect all face components info
	for (int i = 0; i < CF.rows(); i++) {
		if (CF(i) == current_components_id) {
			ACF(CF(i)) += 1;
		}
		else
		{
			CPF(current_components_id, 0) = i - ACF(current_components_id); // start pos
			CPF(current_components_id, 1) = i - 1; // end pos
			current_components_id = CF(i);
			component_counts += 1;
			// if #components > current ACF size, need to resize and initialize as 1
			ACF.conservativeResize(component_counts); // .resize() will do damage
			CPF.conservativeResize(component_counts, 2);
			ACF(component_counts - 1) = 1;
		}

	}
	CPF(current_components_id, 0) = CF.rows() - ACF(current_components_id);
	CPF(current_components_id, 1) = CF.rows() - 1;

	cout << "There are " << component_counts << " face components" << endl;
	cout << "All face components info [components id][faces]:" << endl << ACF << endl;
	cout << "Face components start end " << CPF << endl;

	/*--------------------------Vertex componennts operation--------------------------------------*/
	current_components_id = 0;
	component_counts = 1; // at least there is 1 component
	// collect all components info. ACV(i) records the size of components i, CPV records the start and end position of each components
	ACV(0) = 0;
	CPV(0, 0) = 0;
	CPV(0, 1) = 0;

	// collect all vertex components info

	return true;
}

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &ACF, MatrixX2i &CPF, MatrixXd &V_max, MatrixXi &F_max) {
	// locate max components position and its counts
	VectorXi::Index maxRow, maxCol;
	int max_components = ACF.maxCoeff(&maxRow, &maxCol);
	cout << "Max components " << max_components << " at " << maxRow << endl;

	F_max(0, 0) = F(CPF(maxRow, 1), 0);
	F_max(0, 1) = F(CPF(maxRow, 1), 1);
	F_max(0, 2) = F(CPF(maxRow, 1), 2);

	cout << "F max " << F_max << endl;
	// eliminate iso;ate triangles
	/*
		NOTES: Currently, only keep the max components, all others will be regarded as "iso triangles" and eliminated
	*/
	//for (int i = 0; i < max_components; i++) {
	//	F_max(i, 0) = F(CP(maxRow, 0), 0);
	//	F_max(i, 1) = F(CP(maxRow, 1), 1);
	//	F_max(i, 2) = F(CP(maxRow, 2), 2);
	//}
	return true;
}
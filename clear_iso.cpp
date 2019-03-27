#include "header\clear_iso.h"


bool get_components(MatrixXi &F, VectorXi &C, VectorXi &AC, MatrixX2i & CP) {
	// find connect components
	igl::facet_components(F, C);

	int current_components_id = 0;
	int component_counts = 1; // at least there is a component

	// collect all components info, AC(i) records the size of components i, CP records the start and end postion of each components
	AC(0) = 0;
	CP(0, 0) = 0;
	CP(0, 1) = 0;

	
	// find the max components
	for (int i = 0; i < C.rows(); i++) {
		if (C(i) == current_components_id) {
			AC(C(i)) += 1;
		}
		else
		{
			CP(current_components_id, 0) = i - AC(current_components_id); // start pos
			CP(current_components_id, 1) = i - 1; // end pos
			current_components_id = C(i);
			component_counts += 1;
			// if #components > current AC size, need to resize and initialize as 1
			AC.conservativeResize(component_counts); // .resize() will do damage
			CP.conservativeResize(component_counts, 2);
			AC(component_counts - 1) = 1;
		}

	}
	CP(current_components_id, 0) = C.rows() - AC(current_components_id);
	CP(current_components_id, 1) = C.rows() - 1;

	cout << "There are " << component_counts << " components" << endl;
	cout << "All Components info [components id][faces]:" << endl << AC << endl;
	cout << "Components start end " << CP << endl;
	return true;
}

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &C, VectorXi &AC, MatrixX2i &CP, MatrixXd &V_max, MatrixXi &F_max) {
	// locate max components position and its counts
	VectorXi::Index maxRow, maxCol;
	int max_components = AC.maxCoeff(&maxRow, &maxCol);
	cout << "Max components " << max_components << " at " << maxRow << endl;

	F_max(0, 0) = F(CP(maxRow, 1), 0);
	F_max(0, 1) = F(CP(maxRow, 1), 1);
	F_max(0, 2) = F(CP(maxRow, 1), 2);

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
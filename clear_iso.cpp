#include "header\clear_iso.h"

bool delete_iso_v(MatrixXd &V, MatrixXi &F, MatrixXd &NV, MatrixXi &NF, MatrixXd &IM) {
	igl::remove_unreferenced(V, F, NV, NF, IM);
	int removed_vertex = V.rows() - NV.rows();
	if (removed_vertex != 0) {
		cout << removed_vertex << " vertices has been detected and removed." << endl;
		
		// if remove iso vertices, refresh V/F by NV/NF
		V.resize(NV.rows(), NV.cols());
		V = NV;
		//cout << "New v " << V.rows() << endl;
		F.resize(NF.rows(), NF.cols());
		F = NF;
	}
	return true;
}

bool get_components(MatrixXd &V, MatrixXi &F, VectorXi &CF,VectorXi &CV, VectorXi &ACF, VectorXi &ACV, MatrixXi & CPF, MatrixXi & CPV) {

	VectorXi::Index maxRow, maxCol;
	VectorXi Pos_flag; // records the current index in each row of position matrix
	// find connect components per face and per vertex
	igl::facet_components(F, CF);
	igl::vertex_components(F, CV);

	// check the size of ACV/ACF/CPV/CPF by max components id
	int max_f_size = CF.maxCoeff();
	int max_v_size = CV.maxCoeff();
	cout << "[INFO]" << endl;
	cout << "There are " << max_f_size + 1 << " face components" << endl;
	cout << "There are " << max_v_size + 1 << " vertex components" << endl;

	// resize above dynamic vars
	ACF.resize(max_f_size + 1);
	ACV.resize(max_v_size + 1);

	/*--------------------------Face componennts operation--------------------------------------*/
	int current_components_id = 0;
	int component_counts = 1; // at least there is 1 component

	// initialization before counting
	ACF.setZero();
	ACV.setZero();

	// collect all face components info
	for (int i = 0; i < CF.rows(); i++) {
		ACF(CF(i)) += 1;
	}
	//cout << "All face comp " << endl << ACF << endl;
	// initialization before records the face position info
	int max_value = ACF.maxCoeff(&maxRow, &maxCol);
	CPF.resize(max_f_size + 1, max_value);
	CPF.setZero();
	Pos_flag.resize(max_f_size + 1);
	Pos_flag.setZero();

	// records face position info of each components
	for (int i = 0; i < CF.rows(); i++) {
		CPF(CF(i), Pos_flag(CF(i))) = i;
		Pos_flag(CF(i)) += 1;
	}

	// collect all vertex components info
	for (int i = 0; i < CV.rows(); i++) {
		ACV(CV(i)) += 1;
	}
	//cout << "All vertex comp " << endl << ACV << endl;
	// initialization before records the vertex position info
	max_value = ACV.maxCoeff(&maxRow, &maxCol);
	CPV.resize(max_v_size + 1, max_value);
	CPV.setZero();
	Pos_flag.resize(max_v_size + 1);
	Pos_flag.setZero();

	// record the vertex position info of each component
	for (int i = 0; i < CV.rows(); i++) {
		CPV(CV(i), Pos_flag(CV(i))) = i;
		Pos_flag(CV(i)) += 1;
	}

	return true;
}

bool detete_isolate_Triangles(MatrixXd &V, MatrixXi &F, VectorXi &ACF, VectorXi &ACV, MatrixXi &CPF, MatrixXi & CPV, MatrixXd &V_max, MatrixXi &F_max) {
	// locate max components position and its counts
	VectorXi::Index maxRow_F, maxCol_F, maxRow_V, maxCol_V;

	// test min
	int max_components_f = ACF.maxCoeff(&maxRow_F, &maxCol_F);
	int max_components_v = ACV.maxCoeff(&maxRow_V, &maxCol_V);

	VectorXi RV, FV; // slice vector for V and F
	VectorXi V_Change; // records the index change
	VectorXi C = (VectorXi(3) <<
		0, 1, 2).finished();
	
	// initialization
	RV.resize(ACV(maxRow_V));
	FV.resize(ACF(maxRow_F));
	V_Change.resize(V.rows());
	V_Change.setZero();

	// extract vertices of the max component
	for (int i = 0; i < ACV(maxRow_V); i++) {
		if (i > 0 && CPV(maxRow_V,i) == 0) {
			// cut when meet 0 in CPV
			break;
		}
		else {
			RV(i) = CPV(maxRow_V, i);
			V_Change(RV(i)) = CPV(maxRow_V, i) - i; // eg, if V3->V0, records the change 3
		}
	}

	//cout << "RV size " << RV.rows() << endl;
	//cout << "RV max"<<RV(RV.rows()-1) << endl;
	//cout << "RV " << RV << endl;
	igl::slice(V, RV, C, V_max);
	//cout << "V_max " << V_max.rows() << endl;

	// extract faces of the max component
	for (int i = 0; i < ACF(maxRow_F); i++) {
		if (i > 0 && CPF(maxRow_F, i) == 0) {
			// cut when meet 0 in CPF
			break;
		}
		else {
			FV(i) = CPF(maxRow_F, i);
		}
	}

	//cout << "FV size " << FV.rows() << endl;
	igl::slice(F, FV, C, F_max);
	//cout << "F_max " << F_max.rows() << endl;

	//cout << "V change size " << V_Change.rows() << endl;

	// update F_max to according to the change between V and V_max
	for (int i = 0; i < F_max.rows(); i++) {
		for (int j = 0; j < F_max.cols(); j++) {
			F_max(i, j) -= V_Change(F_max(i, j));
		}
	}

	cout << ACF.rows() - 1 << " small components has been removed." << endl;

	return true;
}
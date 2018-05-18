////////////////////////////////////////////////////////////////////////////////

#include "TriQuadrature.hpp"
#include "TetQuadrature.hpp"
#include "FEBasis2d.hpp"
#include "FEBasis3d.hpp"
#include "auto_bases.hpp"

#include <catch.hpp>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

using namespace poly_fem;


TEST_CASE("P1_2d", "[bases]") {
	TriQuadrature rule;
	Quadrature quad;
	rule.get_quadrature(12, quad);

	Eigen::MatrixXd expected, val;
	for(int i = 0; i < 3; ++i){
		poly_fem::FEBasis2d::linear_tri_basis_value(i, quad.points, expected);
		poly_fem::autogen::p_basis_value_2d(1, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));

		poly_fem::FEBasis2d::linear_tri_basis_grad(i, quad.points, expected);
		poly_fem::autogen::p_grad_basis_value_2d(1, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));
	}

}

TEST_CASE("P2_2d", "[bases]") {
	TriQuadrature rule;
	Quadrature quad;
	rule.get_quadrature(12, quad);

	Eigen::MatrixXd expected, val;
	for(int i = 0; i < 6; ++i){
		poly_fem::FEBasis2d::quadr_tri_basis_value(i, quad.points, expected);
		poly_fem::autogen::p_basis_value_2d(2, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));

		poly_fem::FEBasis2d::quadr_tri_basis_grad(i, quad.points, expected);
		poly_fem::autogen::p_grad_basis_value_2d(2, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));
	}
}


TEST_CASE("P1_3d", "[bases]") {
	TetQuadrature rule;
	Quadrature quad;
	rule.get_quadrature(8, quad);

	Eigen::MatrixXd expected, val;
	for(int i = 0; i < 4; ++i){
		poly_fem::FEBasis3d::linear_tet_basis_value(i, quad.points, expected);
		poly_fem::autogen::p_basis_value_3d(1, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));

		poly_fem::FEBasis3d::linear_tet_basis_grad(i, quad.points, expected);
		poly_fem::autogen::p_grad_basis_value_3d(1, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));
	}

}

TEST_CASE("P2_3d", "[bases]") {
	TetQuadrature rule;
	Quadrature quad;
	rule.get_quadrature(8, quad);

	Eigen::MatrixXd expected, val;
	for(int i = 0; i < 10; ++i){
		poly_fem::FEBasis3d::quadr_tet_basis_value(i, quad.points, expected);
		poly_fem::autogen::p_basis_value_3d(2, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));

		poly_fem::FEBasis3d::quadr_tet_basis_grad(i, quad.points, expected);
		poly_fem::autogen::p_grad_basis_value_3d(2, i, quad.points, val);

		for(int j = 0; j < val.size(); ++j)
			REQUIRE(expected(j) == Approx(val(j)).margin(1e-10));
	}
}


TEST_CASE("P3_2d", "[bases]") {
	Eigen::MatrixXd pts(10, 2);
	pts <<
	0, 0,
	1, 0,
	0, 1,
	1./3., 0,
	2./3., 0,
	2./3., 1./3.,
	1./3., 2./3.,
	0, 2./3.,
	0, 1./3.,
	1./3., 1./3.;

	Eigen::MatrixXd val;

	for(int i = 0; i < pts.rows(); ++i){
		poly_fem::autogen::p_basis_value_2d(3, i, pts, val);

		// std::cout<<i<<"\n"<<val<<"\n\n\n"<<std::endl;

		for(int j = 0; j < val.size(); ++j){
			if(i == j)
				REQUIRE(val(j) == Approx(1).margin(1e-10));
			else
				REQUIRE(val(j) == Approx(0).margin(1e-10));
		}
	}
}

TEST_CASE("Pk_2d", "[bases]") {

	Eigen::MatrixXd pts;
	for(int k = 1; k < poly_fem::autogen::MAX_P_BASES; ++k)
	{
		poly_fem::autogen::p_nodes_2d(k, pts);

		Eigen::MatrixXd val;
		for(int i = 0; i < pts.rows(); ++i){
			poly_fem::autogen::p_basis_value_2d(k, i, pts, val);

		// std::cout<<i<<"\n"<<val<<"\n\n\n"<<std::endl;

			for(int j = 0; j < val.size(); ++j){
				if(i == j)
					REQUIRE(val(j) == Approx(1).margin(1e-10));
				else
					REQUIRE(val(j) == Approx(0).margin(1e-10));
			}
		}
	}
}

TEST_CASE("Pk_3d", "[bases]") {
	Eigen::MatrixXd pts;
	for(int k = 1; k < poly_fem::autogen::MAX_P_BASES; ++k)
	{
		poly_fem::autogen::p_nodes_3d(k, pts);

		Eigen::MatrixXd val;
		for(int i = 0; i < pts.rows(); ++i){
			poly_fem::autogen::p_basis_value_3d(k, i, pts, val);

		// std::cout<<i<<"\n"<<val<<"\n\n\n"<<std::endl;

			for(int j = 0; j < val.size(); ++j){
				if(i == j)
					REQUIRE(val(j) == Approx(1).margin(1e-10));
				else
					REQUIRE(val(j) == Approx(0).margin(1e-10));
			}
		}
	}
}

#pragma once

#include "Problem.hpp"
#include "ProblemWithSolution.hpp"

#include <vector>
#include <Eigen/Dense>

namespace poly_fem
{
	class ElasticProblem: public Problem
	{
	public:
		ElasticProblem(const std::string &name);

		void rhs(const std::string &formulation, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;
		void bc(const Mesh &mesh, const Eigen::MatrixXi &global_ids, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;

		bool has_exact_sol() const override { return false; }
		bool is_scalar() const override { return false; }
	};


	class ElasticForceProblem: public Problem
	{
	public:
		ElasticForceProblem(const std::string &name);

		void rhs(const std::string &formulation, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;
		void bc(const Mesh &mesh, const Eigen::MatrixXi &global_ids, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;
		void neumann_bc(const Mesh &mesh, const Eigen::MatrixXi &global_ids, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;

		bool has_exact_sol() const override { return false; }
		bool is_scalar() const override { return false; }

		void set_parameters(const json &params) override;
	private:
		std::vector<RowVectorNd> forces_;
		std::vector<RowVectorNd> displacements_;
	};

	class ElasticProblemZeroBC: public Problem
	{
	public:
		ElasticProblemZeroBC(const std::string &name);

		void rhs(const std::string &formulation, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;
		void bc(const Mesh &mesh, const Eigen::MatrixXi &global_ids, const Eigen::MatrixXd &pts, Eigen::MatrixXd &val) const override;

		bool has_exact_sol() const override { return false; }
		bool is_scalar() const override { return false; }
	};


	class ElasticProblemExact: public ProblemWithSolution
	{
	public:
		ElasticProblemExact(const std::string &name);

		VectorNd eval_fun(const VectorNd &pt) const override;
		AutodiffGradPt eval_fun(const AutodiffGradPt &pt) const override;
		AutodiffHessianPt eval_fun(const AutodiffHessianPt &pt) const override;

		bool is_scalar() const override { return false; }
	};


	class CompressionElasticProblemExact: public ProblemWithSolution
	{
	public:
		CompressionElasticProblemExact(const std::string &name);

		VectorNd eval_fun(const VectorNd &pt) const override;
		AutodiffGradPt eval_fun(const AutodiffGradPt &pt) const override;
		AutodiffHessianPt eval_fun(const AutodiffHessianPt &pt) const override;

		bool is_scalar() const override { return false; }
	};



	class QuadraticElasticProblemExact: public ProblemWithSolution
	{
	public:
		QuadraticElasticProblemExact(const std::string &name);

		VectorNd eval_fun(const VectorNd &pt) const override;
		AutodiffGradPt eval_fun(const AutodiffGradPt &pt) const override;
		AutodiffHessianPt eval_fun(const AutodiffHessianPt &pt) const override;

		bool is_scalar() const override { return false; }
	};


	class LinearElasticProblemExact: public ProblemWithSolution
	{
	public:
		LinearElasticProblemExact(const std::string &name);

		VectorNd eval_fun(const VectorNd &pt) const override;
		AutodiffGradPt eval_fun(const AutodiffGradPt &pt) const override;
		AutodiffHessianPt eval_fun(const AutodiffHessianPt &pt) const override;

		bool is_scalar() const override { return false; }
	};
}


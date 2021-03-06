#pragma once


#include <polyfem/AssemblerUtils.hpp>
#include <polyfem/RhsAssembler.hpp>
#include <polyfem/State.hpp>

#include <cppoptlib/problem.h>
#include <Eigen/Sparse>



namespace polyfem
{
	class NLProblem : public cppoptlib::Problem<double> {
	public:
		using typename cppoptlib::Problem<double>::Scalar;
		using typename cppoptlib::Problem<double>::TVector;
		typedef Eigen::SparseMatrix<double> THessian;

		NLProblem(State &state, const RhsAssembler &rhs_assembler, const double t);
		NLProblem(State &state, const RhsAssembler &rhs_assembler, const double t, const int full_size, const int reduced_size);

		TVector initial_guess();

		double value(const TVector &x) override;
		void gradient(const TVector &x, TVector &gradv) override;

		#include <polyfem/DisableWarnings.hpp>
		void hessian(const TVector &x, THessian &hessian);
		#include <polyfem/EnableWarnings.hpp>


		template<class FullMat, class ReducedMat>
		static void full_to_reduced_aux(State &state, const int full_size, const int reduced_size, const FullMat &full, ReducedMat &reduced)
		{
			using namespace polyfem;

			assert(full.size() == full_size);
			assert(full.cols() == 1);
			reduced.resize(reduced_size, 1);

			long j = 0;
			size_t k = 0;
			for(int i = 0; i < full.size(); ++i)
			{
				if(k < state.boundary_nodes.size() && state.boundary_nodes[k] == i)
				{
					++k;
					continue;
				}

				reduced(j++) = full(i);
			}
			assert(j == reduced.size());
		}

		template<class ReducedMat, class FullMat>
		static void reduced_to_full_aux(State &state, const int full_size, const int reduced_size, const ReducedMat &reduced, const Eigen::MatrixXd &rhs, FullMat &full)
		{
			using namespace polyfem;

			assert(reduced.size() == reduced_size);
			assert(reduced.cols() == 1);
			full.resize(full_size, 1);

			long j = 0;
			size_t k = 0;
			for(int i = 0; i < full.size(); ++i)
			{
				if(k < state.boundary_nodes.size() && state.boundary_nodes[k] == i)
				{
					++k;
					full(i) = rhs(i);
					continue;
				}

				full(i) = reduced(j++);
			}

			assert(j == reduced.size());
		}

		void full_to_reduced(const Eigen::MatrixXd &full, TVector &reduced) const;
		void reduced_to_full(const TVector &reduced, Eigen::MatrixXd &full);

		const Eigen::MatrixXd &current_rhs();

	private:
		State &state;
		AssemblerUtils &assembler;
		const RhsAssembler &rhs_assembler;
		Eigen::MatrixXd _current_rhs;

		const int full_size, reduced_size;
		const double t;
		bool rhs_computed;
	};
}
